#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_plot.h>
class QwtPlotMarker;
namespace Ui {
class MainWindow;
}
class QwtPlot;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int CreateQwtCounter();
    int CreateQwtPlotPanner();
    void setupRealtimeDataDemo(QwtPlot *qwtplot);
    double getData(double time);

private Q_SLOTS:
    void newValue(double value);
    void SampleUpdate();
    void updatedataSlot();
    void CreateQwtMarker(QPoint& pos);

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
#endif // MAINWINDOW_H


/*
#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <math.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupRealtimeDataDemo(QwtPlot *qwtplot);

private:
    Ui::MainWindow *ui;
    QVector<double> xdata;
    QVector<double> ydata;
    QTimer updateTimer;
    QString demoName;
    QwtPlotCurve *curve ;
    double getData(double inteval);

private slots:
    void updatedataSlot();
};

#endif // MAINWINDOW_H
*/
