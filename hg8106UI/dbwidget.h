#ifndef DBWIDGET_H
#define DBWIDGET_H

#include <QWidget>
#include <QSqlDatabase>

class DbWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DbWidget(QWidget *parent = 0);
    ~DbWidget();
private:
    void InitDb();
    void Init();
signals:

public slots:

private:
        QSqlDatabase  db_;
};

#endif // DBWIDGET_H
