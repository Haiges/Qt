#include "dbwidget.h"
#include <QTableView>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QHBoxLayout>
#include <QDebug>

DbWidget::DbWidget(QWidget *parent) : QWidget(parent)
{
    InitDb();
    Init();
}

void DbWidget::Init(){
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("student");
    //model->setSort(1, Qt::AscendingOrder);
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Age");
    model->select();

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    //view->setColumnHidden(0, true);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::DoubleClicked);

    QHeaderView *header = view->horizontalHeader();
    header->setStretchLastSection(true);

    QHBoxLayout* layout =  new QHBoxLayout();
    layout->addWidget(view);

    setLayout(layout);
}

void DbWidget::InitDb(){
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db_ = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db_ = QSqlDatabase::addDatabase("QSQLITE");
        db_.setDatabaseName("Cmds.db");
        db_.setUserName("Chark");
        db_.setPassword("123456");
    }
   // db_.setHostName("localhost"); 	//数据库主机名

    if(!db_.open())			//打开数据库连接
    {
        qWarning()<<"QSqlDatabase cann't open!"<<db_.lastError();
    }
/*
    QSqlQuery query_c;
     if(!query_c.exec("create table student(name nvarchar(20), age int)"))
    {
        qWarning() << "Error: Fail to create table." << query_c.lastError();
    }
    else
    {
        qWarning() << "Table created!";
    }

     QSqlQuery query;
     query.prepare("insert into student values (?, ?)");
    QVariantList names;
    names << "小王" << "小明" << "小张" << "小新"; // 如果要提交空串，用QVariant(QVariant::String)代替名字
    query.addBindValue(names);
    QVariantList ages;
    ages << 11 << 13 << 12 << 11;
    query.addBindValue(ages);
    if (!query.execBatch()) //进行批处理，如果出错就输出错误
      qWarning()<<"QSqlDatabase cann't execBatch!"<<query.lastError();

      QSqlQuery query1;
      query1.exec("SELECT * FROM student"); // 查询的结果可能不止一条记录，所以我们称之为结果集
      while (query1.next())
      {
          QString name = query1.value(0).toString(); //取第i条记录第1个字段(从0开始计数)的结果
          int age = query1.value(1).toInt(); //取第i条记录第2个字段的结果
          qWarning()<<name<<age;
          // ... 处理name,age变量数据
      }*/
}

DbWidget::~DbWidget()
{
    db_.close();			//释放数据库连接
}

