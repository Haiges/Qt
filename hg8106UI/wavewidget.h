#ifndef WAVEWIDGET_H
#define WAVEWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QUdpSocket>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_plot.h>

class QwtPlotMarker;
namespace Ui {
class MainWindow;
}
class QwtPlot;
class WaveWidget;

class UdpThread: public QThread{
        Q_OBJECT
public:
    UdpThread(WaveWidget* widget );
private:
    virtual void run();
    void CreateUDP();

Q_SIGNALS:
    void AddData(double data_x,double data_y);
     void AddData(int data_x,int data_y);
private:
     QUdpSocket* udp_;
     WaveWidget* widget_;
};

class WaveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WaveWidget(QWidget *parent = 0);
    ~WaveWidget();
    int CreateQwtCounter();
    int CreateQwtPlotPanner();
    void setupRealtimeDataDemo(QwtPlot *qwtplot);
    double getData(double time);

private Q_SLOTS:
    void newValue(double value);
    void SampleUpdate();
    void updatedataSlot();
    void CreateQwtMarker(QPoint& pos);
    void UpdateDataFromUDP(double data_x,double data_y);
    void UpdateDataFromUDP(int data_x,int data_y);
    void Replot();

private:
    QwtPlot* plot;
    QwtPlotMarker* marker;
    int x;
    Ui::MainWindow *ui;
    QTimer dataTimer;

   QwtPlotCurve curve;
   QwtPlotCurve curve_r;//硬折点曲线画布
    QVector<double> xs;
    QVector<double> ys;
    UdpThread* thread_;
};

class MyPicker: public QwtPlotPicker
{
public:
    MyPicker( QWidget *canvas ):
        QwtPlotPicker( canvas )
    {
        //数据什么时候显示
        setTrackerMode( QwtPlotPicker::AlwaysOn );
        //数据获取的坐标轴的选择
        setAxis(QwtPlot::xBottom, QwtPlot::yLeft);
    }

protected:
    //这个重载实现的是鼠标移动显示的数据
    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QString s;
        s.sprintf( " 数值：%.4f ", pos.y() );
        QwtText text( s );
        text.setColor( Qt::white );
        //显示的样式的东西：
        QColor c(Qt::gray);
        text.setBorderPen( QPen( c ) );
        text.setBorderRadius( 6 );
        c.setAlpha( 150 );
        text.setBackgroundBrush( c );

        return text;
    }
};

class CurveDataTracker: public QwtPlotPicker
{
public:
    CurveDataTracker( QWidget * );

protected:
    virtual QwtText trackerTextF( const QPointF & ) const;
   // virtual QRecttrackerRect( const QFont & ) const;

private:
    QString curveInfoAt( const QwtPlotCurve *, const QPointF & ) const;
    QLineF curveLineAt( const QwtPlotCurve *, double x ) const;

};


#endif // WAVEWIDGET_H
