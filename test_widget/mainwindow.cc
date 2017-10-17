#include "mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // CreateQwtCounter();
   CreateQwtPlotPanner();

    plot = new QwtPlot();
    plot->resize(700,500
                 );
    plot->autoReplot();

    setupRealtimeDataDemo(plot);
}

void MainWindow::setupRealtimeDataDemo(QwtPlot *qwtplot)
{
    //初始化xdata,x对应长度为5的坐标，y初始全为0
  /*  for(x=0;x<5001;x++){
       xs.append(x);
       ys.append(double(x)/1000-5);
   }*/

    curve.setSymbol(new QwtSymbol(QwtSymbol::HLine, Qt::Dense1Pattern,
    QPen(Qt::black), QSize(0, 0) ) );
    curve.setTitle("肌电信号1");//曲线名字
    curve.setPen( Qt::black, 1 );//曲线的颜色 宽度;

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
    qwtplot->setAxisScale(QwtPlot::yLeft,-2,2,1);
    qwtplot->setAxisScale(QwtPlot::xBottom,-5,0,1);


    /*QwtPlotZoomer *zoomer = new QwtPlotZoomer( qwtplot->canvas() );
    zoomer->setRubberBandPen( QColor( Qt::blue ) );
    zoomer->setTrackerPen( QColor( Qt::black ) );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton );
*/
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
    qwtplot->show();

    connect(&dataTimer,SIGNAL(timeout()),this,SLOT(SampleUpdate()));
    dataTimer.start(1);
}
void MainWindow::CreateQwtMarker(QPoint& pos){
    marker = new QwtPlotMarker();
    marker->setXValue(pos.x()+100 );
    marker->setLabel(QString::fromLatin1(("x====")));
    marker->setLineStyle( QwtPlotMarker::Cross );
    marker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
    marker->setLinePen( Qt::green, 0, Qt::DashDotLine );
    marker->attach( plot );
}

int MainWindow::CreateQwtCounter(){
    QwtCounter *counter = new QwtCounter(this);
    counter->setRange(0.0, 100.0);
    counter->setSingleStep( 1.0 );
    counter->setNumButtons(4);
    counter->setIncSteps(QwtCounter::Button1, 1);
    counter->setIncSteps(QwtCounter::Button2, 20);

    connect(counter, SIGNAL(valueChanged(double)), this, SLOT(newValue(double)));
}
int MainWindow::CreateQwtPlotPanner(){
    QwtPlotPanner *panner = new QwtPlotPanner(this);
    panner->setMouseButton(Qt::LeftButton);
    panner->setAxisEnabled(3,true);
}

void MainWindow::SampleUpdate(){
   x++;
   static QTime dataTime(QTime::currentTime());
   long int eltime = dataTime.elapsed();
   static int lastpointtime = 0;

    if(xs.size()>=5000&&ys.size()>=5000){
        xs.erase(xs.begin());
        ys.erase(ys.begin());
    }
    xs.append(x);
    ys.append(getData((((double)lastpointtime+1)/1000)));
    lastpointtime = eltime;
    //平滑曲线
    // curve.attach(plot);//把曲线附加到plot上
    curve.setSamples(xs,ys);
    curve.attach(plot);
    plot->setAxisScale(QwtPlot::xBottom,*(xs.end()-1)-5000,*(xs.end()-1),500);

    int x = * xs.begin()+1000;
    int y =  1;
     marker->setValue(x,y );
     QString str = "("+QString::number((x),10)+","+QString::number((y),10)+")";
     marker->setLabel(str);
  qDebug()<<"SampleUpdate:"<<y ;

    plot->replot();
}

void MainWindow::newValue(double value)
{
    qDebug()<<"value:"<<value;
}
MainWindow::~MainWindow()
{
    delete ui;

}
/*
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupRealtimeDataDemo(ui->qwtPlot);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setupRealtimeDataDemo(QwtPlot *qwtplot)
{


    //初始化xdata,x对应长度为5的坐标，y初始全为0
    for(int i=1;i<5001;i++){
        xdata.append(double(i)/1000-5);
        ydata.append(0);
    }

    demoName = "Real Time Data Demo";
    qwtplot->setTitle(demoName);
    qwtplot->setCanvasBackground(Qt::gray);//背景
    qwtplot->insertLegend(new QwtLegend(),QwtPlot::RightLegend);//标签

    curve = new QwtPlotCurve();
    curve->setTitle("肌电信号");//曲线名字
    curve->setPen( Qt::yellow, 1 );//曲线的颜色 宽度;

    QTime curtime;
    curtime=curtime.currentTime();
    qwtplot->setAxisTitle(QwtPlot::xBottom, " System Uptime");
    qwtplot->setAxisTitle(QwtPlot::yLeft,"EMG");
    qwtplot->setAxisScale(QwtPlot::yLeft,-2,2,1);
    qwtplot->setAxisScale(QwtPlot::xBottom,-5,0,1);



    QwtPlotZoomer *zoomer = new QwtPlotZoomer( qwtplot->canvas() );
    zoomer->setRubberBandPen( QColor( Qt::blue ) );
    zoomer->setTrackerPen( QColor( Qt::black ) );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton );
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier( qwtplot->canvas() );                 //默认的滑轮及右键缩放功能  图形的整体缩放

    //    magnifier->setMouseButton(Qt::LeftButton);     //设置哪个按钮与滑轮为缩放画布  如果不设置(注册掉当前行)按钮默认为滑轮以及右键为缩放

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableX( true );//设置网格线
    grid->enableY( true );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach(qwtplot);

    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(updatedataSlot()));
    updateTimer.start(0);


}

*/
double MainWindow::getData(double time){

    double s = qCos( time * M_PI * 2 ) ;
    return s;
}


//用于更新ydata,实际情况就是read数据
void MainWindow::updatedataSlot(){
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
/*
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    double fpstime = (double)eltime/1000.0-lastFpsKey;
    if ( fpstime> 2) // average fps over 2 seconds
    {
        ui->statusBar->showMessage(
                    QString("%1 FPS")
                    .arg(frameCount/fpstime, 0, 'f', 0)
                    , 0);
        lastFpsKey = (double)eltime/1000.0;
        frameCount = 0;
    }*/
}







