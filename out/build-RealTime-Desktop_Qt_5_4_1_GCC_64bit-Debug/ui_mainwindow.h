/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QCheckBox *checkBox_temp;
    QCheckBox *checkBox_hui;
    QPushButton *button_start;
    QPushButton *button_stop;
    QLabel *label;
    QCustomPlot *fftPlot;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(768, 615);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(9, -1, 551, 251));
        checkBox_temp = new QCheckBox(centralWidget);
        checkBox_temp->setObjectName(QStringLiteral("checkBox_temp"));
        checkBox_temp->setGeometry(QRect(570, 0, 97, 22));
        checkBox_hui = new QCheckBox(centralWidget);
        checkBox_hui->setObjectName(QStringLiteral("checkBox_hui"));
        checkBox_hui->setGeometry(QRect(570, 30, 97, 22));
        button_start = new QPushButton(centralWidget);
        button_start->setObjectName(QStringLiteral("button_start"));
        button_start->setGeometry(QRect(570, 60, 99, 27));
        button_stop = new QPushButton(centralWidget);
        button_stop->setObjectName(QStringLiteral("button_stop"));
        button_stop->setGeometry(QRect(570, 90, 99, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(580, 130, 81, 21));
        fftPlot = new QCustomPlot(centralWidget);
        fftPlot->setObjectName(QStringLiteral("fftPlot"));
        fftPlot->setGeometry(QRect(-10, 240, 571, 271));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 768, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        checkBox_temp->setText(QApplication::translate("MainWindow", "CheckBox", 0));
        checkBox_hui->setText(QApplication::translate("MainWindow", "CheckBox", 0));
        button_start->setText(QApplication::translate("MainWindow", "Start", 0));
        button_stop->setText(QApplication::translate("MainWindow", "Stop", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
