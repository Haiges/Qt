#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDialog>
#include <QFile>
#include <QtWidgets/QWidget>
#include <QtUiTools/QUiLoader>
#include "ui_formm.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QLabel *label = new QLabel("Hello QT!");
    QUiLoader  loader;Qt::Horizontal
    QFile* file = new QFile("formm.ui");
    QWidget* widet = loader.load(file);
    Horize= *layout1 = new QHBoxLayout();
    //Ui::Formm ui;
    //QDialog *dia = new QDialog();
    //ui.setupUi(dia);
   // dia->adjustSize();
    widet->show();

    //QObject::connect(button,SIGNAL(clicked()),&a,SLOT(quit()));
    //label->show();
    //button->show();
    return a.exec();
}
