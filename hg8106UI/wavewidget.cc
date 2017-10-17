#include "wavewidget.h"
#include "ui_mainwindow.h"
#include <qwt_counter.h>
#include <qwt_plot_panner.h>
#include <qwt_plot.h>
#include <QDebug>
#include <QHBoxLayout>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <QTimer>
#include <QTime>
#include <qwt_legend.h>
#include <qwt_symbol.h>
#include <qwt_scale_draw.h>
#include <qwt_picker_machine.h>

struct compareX
{
    inline bool operator()( const double x, const QPointF &pos ) const
    {
        return ( x < pos.x() );
    }
};
CurveDataTracker::CurveDataTracker( QWidget *canvas ):
QwtPlotPicker( canvas )
{
    setTrackerMode( QwtPlotPicker::ActiveOnly );
    setTrackerPen(QPen(QColor(0,255,0) ));
    setRubberBand( CrossRubberBand );
    setRubberBandPen(QPen(QColor(255,0,0) ));

   setStateMachine( new QwtPickerClickPointMachine() );
}
/*
QRect CurveDataTracker::trackerRect( const QFont &font ) const
{
    QRect r = QwtPlotPicker::trackerRect( font );

    int heigth = r.height();
    r.moveTop(pickArea().boundingRect().top());
    return r;
}
*/
QwtText CurveDataTracker::trackerTextF( const QPointF &pos ) const
{
    QwtText trackerText;
    trackerText.setColor( Qt::black );

    QColor c(0,255,0,50);
    trackerText.setBorderPen( QPen( c, 2 ) );
    trackerText.setBackgroundBrush( c );

    QString info;
    const QwtPlotItemList curves =   plot()->itemList( QwtPlotItem::Rtti_PlotCurve );

    for ( int i = 0; i < curves.size(); i++ )
    {
        const QString curveInfo = curveInfoAt(
        static_cast<const QwtPlotCurve *>( curves[i] ), pos );

        if ( !curveInfo.isEmpty() )
        {
            if ( !info.isEmpty() )
                info += "<br>";

            info += curveInfo;
        }
    }

    trackerText.setText( info );
    return trackerText;
}

QString CurveDataTracker::curveInfoAt(
    const QwtPlotCurve *curve, const QPointF &pos ) const
{
    const QLineF line = curveLineAt( curve, pos.x() );
    if ( line.isNull() )
        return QString::null;

    const double y = line.pointAt(
        ( pos.x() - line.p1().x() ) / line.dx() ).y();

    QString info( "<font color=""%1"">(%2,%3)</font>" );
    return info.arg( curve->pen().color().name() ).arg( pos.x() ).arg( y );
}

QLineF CurveDataTracker::curveLineAt(
    const QwtPlotCurve *curve, double x ) const
{
    QLineF line;

    if ( curve->dataSize() >= 2 )
    {
        const QRectF br = curve->boundingRect();
        if ( br.isValid() && x >= br.left() && x <= br.right() )
        {
            int index = qwtUpperSampleIndex<QPointF>(
                *curve->data(), x, compareX() );

            if ( index == -1 &&
                x == curve->sample( curve->dataSize() - 1 ).x() )
            {
                // the last sample is excluded from qwtUpperSampleIndex
                index = curve->dataSize() - 1;
            }

            if ( index > 0 )
            {
                line.setP1( curve->sample( index - 1 ) );
                line.setP2( curve->sample( index ) );
            }
        }
    }

    return line;
}

WaveWidget::WaveWidget(QWidget *parent)
{
    //ui->setupUi(this);
   // CreateQwtCounter();
   CreateQwtPlotPanner();

    plot = new QwtPlot();
    plot->resize(5000,500);
    plot->autoReplot();
    QHBoxLayout* layout = new QHBoxLayout();
    layout ->addWidget(plot);
    setLayout(layout);
    thread_ = new UdpThread(this);
    thread_->start();
    setupRealtimeDataDemo(plot);
}

void WaveWidget::setupRealtimeDataDemo(QwtPlot *qwtplot)
{
    //初始化xdata,x对应长度为5的坐标，y初始全为0
  /*  for(x=0;x<5001;x++){
       xs.append(x);
       ys.append(double(x)/1000-5);
   }*/

    curve.setSymbol(new QwtSymbol(QwtSymbol::HLine, Qt::Dense1Pattern,
    QPen(Qt::blue), QSize(0, 0) ) );
    curve.setTitle("肌电信号1");//曲线名字
    curve.setPen( Qt::blue, 1 );//曲线的颜色 宽度;

    QwtScaleDraw* draw = new QwtScaleDraw();
    draw->setLabelAlignment(Qt::AlignLeft);
    //  draw->setLabelRotation();
    //    draw->setTickLength(QwtScaleDiv::MajorTick,1);

    QString demoName = "Real Time";
    qwtplot->setTitle(demoName);
    qwtplot->setCanvasBackground(Qt::white);//背景
    qwtplot->insertLegend(new QwtLegend(),QwtPlot::RightLegend);//标签
    qwtplot->setAxisScaleDraw(QwtPlot::xBottom,draw);
    qwtplot->setAxisTitle(QwtPlot::xBottom, " System Uptime");
    qwtplot->setAxisTitle(QwtPlot::yLeft,"EMG");
    qwtplot->setAxisScale(QwtPlot::yLeft,-100,100,20);
    qwtplot->setAxisScale(QwtPlot::xBottom,-5000,0,500);


    QwtPlotZoomer *zoomer = new QwtPlotZoomer( qwtplot->canvas() );
    zoomer->setRubberBandPen( QColor( Qt::blue ) );
    zoomer->setTrackerPen( QColor( Qt::black ) );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton );

    //zoomer->
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier( qwtplot->canvas() );                 //默认的滑轮及右键缩放功能  图形的整体缩放
    magnifier->setMouseButton(Qt::LeftButton);

      //biaochi
      CurveDataTracker* myPicker = new CurveDataTracker(qwtplot->canvas());
        connect(myPicker,SIGNAL(selected(QPointF)),this,SLOT(CreateQwtMarker(QPoint&)));
    //myPicker->
    //    magnifier->setMouseButton(Qt::LeftButton);     //设置哪个按钮与滑轮为缩放画布  如果不设置(注册掉当前行)按钮默认为滑轮以及右键为缩放
     marker = new QwtPlotMarker();
     marker->setXValue(100 );
     marker->setLabel(QString::fromLatin1(("x====")));
     marker->setLineStyle( QwtPlotMarker::Cross );
     marker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
     marker->setLinePen( Qt::green, 0, Qt::DashDotLine );
     marker->attach( plot );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableX( true );//设置网格线
    grid->enableY( true );
    grid->setMajorPen( Qt::blue, 0, Qt::DotLine );
    grid->attach(qwtplot);

    QwtScaleMap x_map = qwtplot->canvasMap(QwtPlot::xBottom);
    QwtScaleMap y_map = qwtplot->canvasMap(QwtPlot::yLeft);
    //double fx = x_map.invTransform(QwtPlot::xBottom,e->pos.x())

    QwtScaleDiv *scale = new QwtScaleDiv();
    //qwtplot->show();

    connect(&dataTimer,SIGNAL(timeout()),this,SLOT(Replot()));
    dataTimer.start(10);
}

void WaveWidget::CreateQwtMarker(QPoint& pos){
    marker = new QwtPlotMarker();
    marker->setXValue(pos.x()+100 );
    marker->setLabel(QString::fromLatin1(("x====")));
    marker->setLineStyle( QwtPlotMarker::Cross );
    marker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
    marker->setLinePen( Qt::green, 0, Qt::DashDotLine );
    marker->attach( plot );
}

int WaveWidget::CreateQwtCounter(){
    QwtCounter *counter = new QwtCounter(this);
    counter->setRange(0.0, 100.0);
    counter->setSingleStep( 1.0 );
    counter->setNumButtons(4);
    counter->setIncSteps(QwtCounter::Button1, 1);
    counter->setIncSteps(QwtCounter::Button2, 20);

    connect(counter, SIGNAL(valueChanged(double)), this, SLOT(newValue(double)));
}
int WaveWidget::CreateQwtPlotPanner(){
    QwtPlotPanner *panner = new QwtPlotPanner(this);
    panner->setMouseButton(Qt::LeftButton);
    panner->setAxisEnabled(3,true);
}

void WaveWidget::SampleUpdate(){
   x++;
   static QTime dataTime(QTime::currentTime());
   long int eltime = dataTime.elapsed();
   static int lastpointtime = 0;
    UpdateDataFromUDP ((double)x,getData((((double)lastpointtime+1)/1000)));
    lastpointtime = eltime;
}

void WaveWidget::newValue(double value)
{
    qDebug()<<"value:"<<value;
}
WaveWidget::~WaveWidget()
{
}

double WaveWidget::getData(double time){

    double s = qCos( time * M_PI * 2 ) ;
    return s;
}


//用于更新ydata,实际情况就是read数据
void WaveWidget::updatedataSlot(){
    qDebug()<<"updatedataSlot";
    static QTime dataTime(QTime::currentTime());
    long int eltime = dataTime.elapsed();
    static int lastpointtime = 0;

    int size = (eltime - lastpointtime);


    if(size>0){//有数据传入
        ys.erase(ys.begin(),ys.begin()+size);//擦除多余的数据
        for(int i=1;i<size+1;i++){
            ys.append(getData((((double)lastpointtime+i)/1000)));
        }
        lastpointtime = eltime;
    }

    curve.setSamples(xs,ys);
    curve.attach(plot);
    plot->replot();

}

void WaveWidget::UpdateDataFromUDP(double data_x,double data_y){
        qDebug()<<"UpdateDataFromUDP"<<data_x<<data_y;
    if(xs.size()>=5000&&ys.size()>=5000){
        xs.erase(xs.begin());
        ys.erase(ys.begin());
    }
    xs.append(data_x);
    ys.append(data_y);

    //平滑曲线
    // curve.attach(plot);//把曲线附加到plot上
    curve.setSamples(xs,ys);
    curve.attach(plot);
    plot->setAxisScale(QwtPlot::xBottom,*(xs.end()-1)-5000,*(xs.end()-1),500);

    int x = * xs.begin()+1000;
    int y =  1;
    // marker->setValue(x,y );
    // QString str = "("+QString::number((x),10)+","+QString::number((y),10)+")";
     //marker->setLabel(str);
 // qDebug()<<"SampleUpdate:"<<y ;
    qDebug()<<QTime::currentTime();

}
void WaveWidget::Replot(){
    plot->replot();
}

void WaveWidget::UpdateDataFromUDP(int data_x,int data_y){
    UpdateDataFromUDP((double)data_x,(double)data_y);
}

UdpThread::UdpThread(WaveWidget* widget )
                    :widget_(NULL)
                    ,udp_(NULL){
    widget_  =widget;

}

#define DATA_UDP_PORT 5200
void UdpThread::CreateUDP(){
    udp_ = new QUdpSocket();
    udp_->bind(DATA_UDP_PORT);
    connect(this,SIGNAL(AddData(double,double)),widget_,SLOT(UpdateDataFromUDP(double,double)));
    connect(this,SIGNAL(AddData(int,int)),widget_,SLOT(UpdateDataFromUDP(int,int)));
}

void UdpThread::run(){
        CreateUDP();
    if(!udp_){
        qDebug()<<"Udp hasnt created!";
        return;
    }
    if(!widget_){
        qDebug()<<"widget_ hasnt created!";
        return;
    }
   static int x = 0;
   int16_t  data[512];
   while(isRunning()){
      //msleep(20);
      udp_->waitForReadyRead();
       while(udp_->hasPendingDatagrams()){

           int len = udp_->readDatagram((char*)data,sizeof(int16_t));
           if(len>=sizeof(data)*sizeof(int16_t)){
                len = sizeof(data)*sizeof(int16_t);
           }

           qDebug()<<"ReceUdp Data len:"<<len<<"  Data:"<<data[0];
           for(int i=0;i<len/sizeof(int16_t);i++){
                AddData(x,(int)data[i]);
                x++;
           }
       }
       qDebug()<<"ReceUdp  no Data len!";
   }
}




