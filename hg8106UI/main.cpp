#include "cmdwidget.h"
#include <QApplication>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include "test.h"
#include <QPushButton>
#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CmdWidget w;
    qDebug() << "AAA coordinate type:" ;

    w.show();

    return app.exec();
}
