#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSharedPointer>
#include "qcustomplot.h"
#include "fftw3.h"
#include <qwt_plot_curve.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //设置qcustomplot画图属性，实时
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
        void realtimeDataSlot(QCustomPlot *customPlot);
private slots:
    //添加实时数据槽
    void realtimeDataSlot();
  void horzScrollBarChanged(int value);
  void vertScrollBarChanged(int value);
  void xAxisChanged(QCPRange range);
  void yAxisChanged(QCPRange range);
  void my_mouseMove(QMouseEvent* event);

private:
    int Init(QCustomPlot *plot);
    int UnInit();
    int FftPlot(double data,int key,QCustomPlot *plot);
    int ADDFFTData();

private:
    Ui::MainWindow *ui;
    //定时器，周期调用realtimeDataSlot()槽，实现动态数据添加到曲线
    QTimer dataTimer;
    fftw_complex *in, *out;
    fftw_plan p;
    QSharedPointer< QCPGraphDataContainer > data_;

    QwtPlot* plot;

    QwtPlotCurve curve;
    QwtPlotCurve curve_r;//硬折点曲线画布
    QVector<double> xs;
    QVector<double> ys;
};

#endif // MAINWINDOW_H
