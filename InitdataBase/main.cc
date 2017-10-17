#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include <QMap>
#include <QPair>
#include <QString>

#include "define.h"


bool AddData(QString para_name,QMap<QString,int> map){
    QSqlQuery query;
    query.prepare("insert into CmdDefine(CmdName,itemname,itemvalue) values (?,?,?)");

    QVariantList CmdName;
    QVariantList itemname;
    QVariantList itemvalue;
    for(QMap<QString,int>::Iterator it=map.begin();it!=map.end();it++){
        CmdName<<para_name;
        itemname<<it.key();
        itemvalue<<(double)it.value();
    }
    query.addBindValue(CmdName);
    query.addBindValue(itemname);
    query.addBindValue(itemvalue);

    if (!query.execBatch()) {//进行批处理，如果出错就输出错误
      qWarning()<<"QSqlDatabase cann't execBatch!"<<query.lastError();
      return false;
    }
    return true;
}

bool InitTableFpgatype(){
    QSqlQuery query;
    query.prepare("insert into CmdComponentType(CmdName,ComponentType,value) values (?,?,?)");

    QVariantList CmdName;
    QVariantList ComponentType;
    QVariantList value;

  CmdName<<NAME_EMIT_FREQUENCY
    <<NAME_EMIT_MODE
    <<NAME_MODUELATE_MODE
    <<NAME_PTT
    <<NAME_RECEIVER_MODE
    <<NAME_RECEIVER_MODUELATE_MODE
    <<NAME_ANALOG_AGC_MODE
    <<NAME_DIGITAL_AGC_MODE
    <<NAME_AGC_ATTENUATION
    << NAME_GAIN_VALUE;
    ComponentType<<COMPONENGT_TYPE_QDOUBLESPINBOX
      <<COMPONENGT_TYPE_QCOMBOBOX
      <<COMPONENGT_TYPE_QCOMBOBOX
      <<COMPONENGT_TYPE_QCOMBOBOX
      <<COMPONENGT_TYPE_QCOMBOBOX
      <<COMPONENGT_TYPE_QCOMBOBOX
      <<COMPONENGT_TYPE_QCOMBOBOX
      <<COMPONENGT_TYPE_QCOMBOBOX
      <<COMPONENGT_TYPE_QPINBOX
      <<COMPONENGT_TYPE_QPINBOX;
    value<<10000000
      <<EMIT_MODE_STATIC_FREQUENCY
      <<MODUELATE_MODE_AM
      <<PTT_OFF
      <<EMIT_MODE_STATIC_FREQUENCY
      <<MODUELATE_MODE_AM
      <<ANALOG_AGC_MODE_MGC
      <<DIGITAL_AGC_MODE_MGC
      <<0
      <<0;

    query.addBindValue(CmdName);
    query.addBindValue(ComponentType);
    query.addBindValue(value);

    if (!query.execBatch()) {//进行批处理，如果出错就输出错误
      qWarning()<<"QSqlDatabase cann't execBatch!"<<query.lastError();
      return false;
    }
    return true;
}
int Query(){
    qWarning() << "SELECT created! start";
        QSqlQuery query1;
        query1.exec("SELECT * FROM CmdDefine"); // 查询的结果可能不止一条记录，所以我们称之为结果集
        while (query1.next())
        {
            QString name = query1.value(0).toString(); //取第i条记录第1个字段(从0开始计数)的结果
            QString age = query1.value(1).toString(); //取第i条记录第2个字段的结果
            qWarning()<<name<<age;
            // ... 处理name,age变量数据
        }
           qWarning() << "SELECT created! end";
}

void InitDb(){
    QSqlDatabase db_;
    QMap<QString,QMap<QString,int> > map_vec;

     QMap<QString,int> param_map_emit_fre;
     param_map_emit_fre.insert(QString("MIN"),1.5);
     param_map_emit_fre.insert(QString("MAX"),30);
    map_vec.insert(NAME_EMIT_FREQUENCY,param_map_emit_fre);

    QMap<QString,int> param_map_emit_mode;
    param_map_emit_mode.insert(QString("静频"),EMIT_MODE_STATIC_FREQUENCY);
    param_map_emit_mode.insert(QString("跳頻"),EMIT_MODE_JUMP_FREQUENCY);
    param_map_emit_mode.insert(QString("自适应"),EMIT_MODE_SELF_ADAPTE);
    param_map_emit_mode.insert(QString("自动控制"),EMIT_MODE_SELF_CONTROL);
    param_map_emit_mode.insert(QString("自动选频"),EMIT_MODE_SELF_SELCT_FREQUENCY);
    map_vec.insert(NAME_EMIT_MODE,param_map_emit_mode);

    QMap<QString,int> param_map_modulate_mode;
    param_map_modulate_mode.insert(QString("CW"),MODUELATE_MODE_CW);
    param_map_modulate_mode.insert(QString("USB"),MODUELATE_MODE_USB);
    param_map_modulate_mode.insert(QString("LSB"),MODUELATE_MODE_LSB);
    param_map_modulate_mode.insert(QString("AM"),MODUELATE_MODE_AM);
    param_map_modulate_mode.insert(QString("ISB"),MODUELATE_MODE_ISB);
    param_map_modulate_mode.insert(QString("数据"),MODUELATE_MODE_Data);
    map_vec.insert(NAME_MODUELATE_MODE,param_map_modulate_mode);

     QMap<QString,int> param_map_ptt;
    param_map_ptt.insert(QString("关"),0);
    param_map_ptt.insert(QString("开"),1);
    map_vec.insert(NAME_PTT,param_map_ptt);

    QMap<QString,int> param_map_rece_mode;
    param_map_rece_mode.insert(QString("静频"),EMIT_MODE_STATIC_FREQUENCY);
    param_map_rece_mode.insert(QString("跳頻"),EMIT_MODE_JUMP_FREQUENCY);
    param_map_rece_mode.insert(QString("自适应"),EMIT_MODE_SELF_ADAPTE);
    param_map_rece_mode.insert(QString("自动控制"),EMIT_MODE_SELF_CONTROL);
    param_map_rece_mode.insert(QString("自动选频"),EMIT_MODE_SELF_SELCT_FREQUENCY);
    map_vec.insert(NAME_RECEIVER_MODE,param_map_rece_mode);

    QMap<QString,int> param_map_rece_modulate_mode;
    param_map_rece_modulate_mode.insert(QString("CW"),MODUELATE_MODE_CW);
    param_map_rece_modulate_mode.insert(QString("USB"),MODUELATE_MODE_USB);
    param_map_rece_modulate_mode.insert(QString("LSB"),MODUELATE_MODE_LSB);
    param_map_rece_modulate_mode.insert(QString("AM"),MODUELATE_MODE_AM);
    param_map_rece_modulate_mode.insert(QString("ISB"),MODUELATE_MODE_ISB);
    param_map_rece_modulate_mode.insert(QString("数据"),MODUELATE_MODE_Data);
    map_vec.insert(NAME_RECEIVER_MODUELATE_MODE,param_map_rece_modulate_mode);


    QMap<QString,int> param_map_analog_agc_mode;
    param_map_analog_agc_mode.insert(QString("AGC"),ANALOG_AGC_MODE_AGC);
    param_map_analog_agc_mode.insert(QString("MGC"),ANALOG_AGC_MODE_MGC);
    map_vec.insert(NAME_ANALOG_AGC_MODE,param_map_analog_agc_mode);

    QMap<QString,int> param_agc_attenuation;
    param_agc_attenuation.insert(QString("MIN"),0);
    param_agc_attenuation.insert(QString("MAX"),46);
   map_vec.insert(NAME_AGC_ATTENUATION,param_agc_attenuation);

   QMap<QString,int> param_map_digital_agc_mode;
    param_map_digital_agc_mode.insert(QString("快AGC"),DIGITAL_AGC_MODE_FAST);
    param_map_digital_agc_mode.insert(QString("中AGC"),DIGITAL_AGC_MODE_MIDDLE);
    param_map_digital_agc_mode.insert(QString("慢AGC"),DIGITAL_AGC_MODE_SlOW);
    param_map_digital_agc_mode.insert(QString("MGC"),DIGITAL_AGC_MODE_MGC);
    map_vec.insert(NAME_DIGITAL_AGC_MODE,param_map_digital_agc_mode);

    QMap<QString,int> param_gain;
    param_gain.insert(QString("MIN"),-20);
    param_gain.insert(QString("MAX"),120);
   map_vec.insert(NAME_GAIN_VALUE,param_gain);

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db_ = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db_ = QSqlDatabase::addDatabase("QSQLITE");
        db_.setDatabaseName("mess.db");
        db_.setUserName("Chark");
        db_.setPassword("123456");
    }
   // db_.setHostName("localhost"); 	//数据库主机名

    if(!db_.open())			//打开数据库连接
    {
        qWarning()<<"QSqlDatabase cann't open!"<<db_.lastError();
    }

    QSqlQuery query_c;
    query_c.exec("drop table CmdDefine");
     if(!query_c.exec("CREATE TABLE CmdDefine(id integer primary key AUTOINCREMENT,CmdName varchar(64),itemname varchar(64),itemvalue double)"))
    {
        qWarning() << "Error: Fail to create table." << query_c.lastError();
    }
    else
    {
        qWarning() << "Table created!";
    }

        qDebug()<<QTime::currentTime();
        db_.transaction();
        bool rc = false;
        for(QMap<QString,QMap<QString,int> >::iterator it = map_vec.begin();it!=map_vec.end();it++){
                rc =  AddData(it.key(),it.value());
                if(!rc){
                    return;
                }
        }
        Query();

        qDebug()<<QTime::currentTime();
       if(rc){
            db_.commit();
       }else{
           qWarning() << "transaction failed!";
           db_.rollback();
       }
        qDebug()<<QTime::currentTime();

        query_c.exec("drop table CmdComponentType");
         if(!query_c.exec("CREATE TABLE CmdComponentType(id integer primary key AUTOINCREMENT,CmdName varchar(64),ComponentType int,value double)"))
        {
            qWarning() << "Error: Fail to create table." << query_c.lastError();
        }
        else
        {
            qWarning() << "Table created!";
        }
         InitTableFpgatype();
        db_.close();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    InitDb();
    return a.exec();
}
