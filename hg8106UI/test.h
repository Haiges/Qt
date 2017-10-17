#include<qobjectdefs.h>
#include<QObject>
#include <QDebug>

#ifndef TEST_H
#define TEST_H


class Test :public QObject
{
    Q_OBJECT
private slots :
    void  Print();
};

class TestEmit:public QObject
{
    Q_OBJECT
public:
    void send(){
        emit Print(1);
    }

signals:
    void  Print(bool i);

};
#endif // TEST_H
