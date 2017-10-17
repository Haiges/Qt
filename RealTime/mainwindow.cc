#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QTimer>
#include <QTime>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupRealtimeDataDemo(ui->customPlot);
    ui->customPlot->replot();
    ui->fftPlot->replot();

    ui->checkBox_temp->setChecked(true);
    ui->checkBox_hui->setChecked(true);
    Init(ui->fftPlot);
    //ADDFFTData();
    connect(ui->button_start, SIGNAL(clicked()),&dataTimer, SLOT(start()));
    connect(ui->button_stop, SIGNAL(clicked()),&dataTimer, SLOT(stop()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//画图初始化
void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
//#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  //QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
//#endif
  //demoName = "Real Time Data Demo";

  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setName("temp");
  data_ = customPlot->graph(0)->data();
  //customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
  //customPlot->graph(0)->setAntialiasedFill(false);
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(1)->setName("hui");
  //customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));


  //customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
 // customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  //customPlot->xAxis->setAutoTickStep(false);
  //customPlot->xAxis->setTickStep(2);
  customPlot->axisRect()->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  //connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

  // create connection between axes and scroll bars:
  //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
 // connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));
    connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(my_mouseMove(QMouseEvent*)));

  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom|QCP::iSelectPlottables);
  //customPlot->setsele
  dataTimer.start(1); // Interval 0 means to refresh as fast as possible
  customPlot->legend->setVisible(true);



}
#define SAMPLE_RATE 0.000125
void MainWindow::realtimeDataSlot()
{
    //key的单位是秒
   static unsigned int  key  = 0;
    key ++;
    int16_t origin[]={5793,8192,5793,0,-5793,-8192,-5793,0};
     int index = key% (sizeof(origin)/sizeof(int16_t));
   // qsrand(origin[index]);
  //    qDebug()<<origin[index];
    //使用随机数产生两条曲线
    double value0;
    if(key%3000>1500)
        value0 = sin(key/100.0);
    else
        value0 = sin(key/1.0);
    double value1 = origin[index];
    if (ui->checkBox_temp->isChecked()){
        //data_->clear();
        ui->customPlot->graph(0)->addData(key, value0);//添加数据1到曲线1
        FftPlot(value0,key,ui->fftPlot);//fft
    }
  //  if (ui->checkBox_hui->isChecked())
       // ui->customPlot->graph(1)->addData(key, value1);//添加数据2到曲线2
    //删除8秒之前的数据。这里的8要和下面设置横坐标宽度的8配合起来
    //才能起到想要的效果，可以调整这两个值，观察显示的效果。
    if(key>=1000){
        data_->removeBefore(key-1000);
    }
    qDebug()<<"key:"<<key<<"  data:"<<data_->size();
  //  ui->customPlot->graph(1)->removeDataBefore(key-8);

      //自动设定graph(1)曲线y轴的范围，如果不设定，有可能看不到图像
//也可以用ui->customPlot->yAxis->setRange(up,low)手动设定y轴范围
    ui->customPlot->graph(0)->rescaleValueAxis(true);
 //   ui->customPlot->graph(1)->rescaleValueAxis(true);
    ui->customPlot->yAxis->setRange(1,2, Qt::AlignRight);//设定y轴的范围

         //QCPRange  range = ui->customPlot->yAxis->range();
        //       qDebug()<<range;
        // ui->customPlot->yAxis->setRangeUpper(range.lower+100);//设定y轴的范围
       //  ui->customPlot->yAxis->setRangeLower(range.upper-100);//设定y轴的范围
      //         qDebug()<<range;

    //这里的8，是指横坐标时间宽度为8秒，如果想要横坐标显示更多的时间
    //就把8调整为比较大到值，比如要显示60秒，那就改成60。
    //这时removeDataBefore(key-8)中的8也要改成60，否则曲线显示不完整。
    ui->customPlot->xAxis->setRange(key, 1000, Qt::AlignRight);//设定x轴的范围
    ui->customPlot->replot();

}
/*
void MainWindow::realtimeDataSlotQwt()
{
    //key的单位是秒
   static unsigned int  key  = 0;
    key ++;
    int16_t origin[]={5793,8192,5793,0,-5793,-8192,-5793,0};
     int index = key% (sizeof(origin)/sizeof(int16_t));
   // qsrand(origin[index]);
  //    qDebug()<<origin[index];
    //使用随机数产生两条曲线
    double value0;
    if(key%3000>1500)
        value0 = sin(key/100.0);
    else
        value0 = sin(key/1.0);
    double value1 = origin[index];
    if (ui->checkBox_temp->isChecked()){
        //data_->clear();
        curve.setSamples();
       curve->(key, value0);//添加数据1到曲线1
       // FftPlot(value0,key,ui->fftPlot);//fft
    }
  //  if (ui->checkBox_hui->isChecked())
       // ui->customPlot->graph(1)->addData(key, value1);//添加数据2到曲线2
    //删除8秒之前的数据。这里的8要和下面设置横坐标宽度的8配合起来
    //才能起到想要的效果，可以调整这两个值，观察显示的效果。
    if(key>=1000){
        data_->removeBefore(key-1000);
    }
    qDebug()<<"key:"<<key<<"  data:"<<data_->size();
  //  ui->customPlot->graph(1)->removeDataBefore(key-8);

      //自动设定graph(1)曲线y轴的范围，如果不设定，有可能看不到图像
//也可以用ui->customPlot->yAxis->setRange(up,low)手动设定y轴范围
    ui->customPlot->graph(0)->rescaleValueAxis(true);
 //   ui->customPlot->graph(1)->rescaleValueAxis(true);
    ui->customPlot->yAxis->setRange(1,2, Qt::AlignRight);//设定y轴的范围

         //QCPRange  range = ui->customPlot->yAxis->range();
        //       qDebug()<<range;
        // ui->customPlot->yAxis->setRangeUpper(range.lower+100);//设定y轴的范围
       //  ui->customPlot->yAxis->setRangeLower(range.upper-100);//设定y轴的范围
      //         qDebug()<<range;

    //这里的8，是指横坐标时间宽度为8秒，如果想要横坐标显示更多的时间
    //就把8调整为比较大到值，比如要显示60秒，那就改成60。
    //这时removeDataBefore(key-8)中的8也要改成60，否则曲线显示不完整。
    ui->customPlot->xAxis->setRange(key, 1000, Qt::AlignRight);//设定x轴的范围
    ui->customPlot->replot();

}*/
void MainWindow::horzScrollBarChanged(int value)
{
  if (qAbs(ui->customPlot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->customPlot->xAxis->setRange(value/100.0, ui->customPlot->xAxis->range().size(), Qt::AlignCenter);
    ui->customPlot->replot();
  }
}

void MainWindow::vertScrollBarChanged(int value)
{
  if (qAbs(ui->customPlot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->customPlot->yAxis->setRange(-value/100.0, ui->customPlot->yAxis->range().size(), Qt::AlignCenter);
    ui->customPlot->replot();
  }
}

void MainWindow::xAxisChanged(QCPRange range)
{
 // ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
 // ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void MainWindow::yAxisChanged(QCPRange range)
{
//  ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
  //ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void MainWindow::my_mouseMove(QMouseEvent* event)
{
 //获取鼠标坐标点
    int x_pos = event->pos().x();
    int y_pos = event->pos().y();

// 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
// coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
    float x_val = ui->customPlot->xAxis->pixelToCoord(x_pos);
    float y_val = ui->customPlot->yAxis->pixelToCoord(y_pos);

// 然后打印在界面上
    ui->label->setText(tr("(%1 a  %2  a ||  %3  a %4aa)").arg(x_pos).arg(y_pos).arg(x_val).arg(y_val));
    ui->label->adjustSize();
}
#define N 600
int MainWindow::Init(QCustomPlot *plot){
    //add code;
    plot->axisRect()->setupFullAxesBox();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom|QCP::iSelectPlottables);
    plot->legend->setVisible(true);
    plot->addGraph(); // blue line
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setName("temp");

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
}

int MainWindow::UnInit(){
    //add code;
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
}
int MainWindow::FftPlot(double data,int key,QCustomPlot *plot)
{
    //int N = 8;

    //add code;
    int index =key%N;
    in[index][0] = data;//real
    in[index][1] = 0;//image
  // qDebug()<<"index:"<<index<<"key:"<<key;
    if(index!=N-1){
        return -1;
    }
     fftw_execute(p); /* repeat as needed */

    QVector<double>  xdata;
    QVector<double>  ydata;
    //plot->graph(0)->re
    for(int i=0;i<N;i++){
        xdata.push_back(i);
        ydata.push_back(sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]));
      /*  if(i=0){
                    xdata.push_back(sqrt(out[i][0]+out[i][1]));
                    //plot->graph(0)->setData(i,sqrt(out[i][0]+out[i][1]));
        }else{
                   // plot->graph(0)->addData(i,sqrt(out[i][0]+out[i][1]));
        }*/
      //  plot->graph(0)->addData(i,sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]));
    }
   plot->graph(0)->setData(xdata,ydata);
   plot->graph(0)->rescaleValueAxis(true);
   plot->xAxis->setRange(N, N, Qt::AlignRight);//设定x轴的范围
    plot->replot();

    //add code;
  //  for (int i = 0; i < N; i++)
  //  {
  //      qDebug()<<out[i][0]<<","<<out[i][1];
 //   }

    return 0;
}

int MainWindow::ADDFFTData()
{
   // int N = 151;
    fftw_complex *in, *out;
    fftw_plan p;
    //add code;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    //add code;
    for (int i = 0; i < N; i++)
    {
        in[i][0] = sin(i);//real
        in[i][1] = 0;//image
           ui->customPlot->graph(0)->addData(i,sin(i));
    }
    fftw_execute(p); /* repeat as needed */
    //add code;
    for (int i = 0; i < N; i++)
    {
        qDebug()<<out[i][0]<<","<<out[i][1];
        ui->fftPlot->graph(0)->addData(i,sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]));
    }
    ui->customPlot->graph(0)->rescaleValueAxis(false);
    ui->customPlot->xAxis->setRange(N, N, Qt::AlignRight);//设定x轴的范围
    ui->customPlot->replot();

    ui->fftPlot->graph(0)->rescaleValueAxis(true);
    ui->fftPlot->xAxis->setRange(N, N, Qt::AlignRight);//设定x轴的范围
    ui->fftPlot->replot();

    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
    qDebug()<<"bye";
    return 0;
}/*
int MainWindow::CreatePlot(){
   // CreateQwtCounter();
   // CreateQwtPlotPanner();

    plot = new QwtPlot();
    plot->resize(700,500);
    plot->autoReplot();

    plot->setTitle("PLOT SAMPLE");
    plot->setAxisTitle(QwtPlot::xBottom,"X Bottom");
    plot->setAxisTitle(QwtPlot::yLeft,"yLeft");

    plot->setAxisAutoScale(QwtPlot::yRight);
    plot->setAxisScale(QwtPlot::xBottom,-2,2);
        plot->insertLegend(new QwtLegend(),QwtPlot::LeftLegend);
      new QwtPlotMagnifier(plot->canvas());
        new QwtPlotPanner(plot->canvas());

        //平滑曲线
        curve.attach(plot);//把曲线附加到plot上
       // curve.setSamples(xs,ys);
        curve.setStyle(QwtPlotCurve::Lines);//设置曲线上是点还是线，默认是线，所以此行可不加
        curve.setCurveAttribute(QwtPlotCurve::Fitted, true);//使曲线更光滑，不加这句曲线会很硬朗，有折点
        curve.setPen(QPen(Qt::black));//设置画笔
    //QHBoxLayout* layout = new QHBoxLayout();
    //layout->addWidget(plot);
   // setLayout(layout);

        plot->show();
}
*/
