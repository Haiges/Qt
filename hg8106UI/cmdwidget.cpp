#include "cmdwidget.h"
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QUdpSocket>
#include <QObject>
#include <QString>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include "serialcmdwidget.h"
#include "wavewidget.h"
#include "dbwidget.h"

CmdWidget::CmdWidget(QWidget *parent) : QWidget(parent)
{
     InitDb();
     CreateUDP();
    CreateLayOut();

    resize(1000,500);
}

CmdWidget::~CmdWidget()
{
    db_.close();			//释放数据库连接
}

void CmdWidget::CreateUDP(){
    host_address_ =new  QHostAddress(HOST_ADDRESS);
    udp_socket_ = new QUdpSocket(this);
}

void CmdWidget::InitDb(){
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
     if(!query_c.exec("create table FpgaCmd(name nvarchar(20), value double)"))
    {
        qWarning() << "Error: Fail to create table." << query_c.lastError();
    }
    else
    {
        qWarning() << "Table created!";
    }
}

void CmdWidget::CreateLayOut(){
     QTabWidget* tab_widget = new QTabWidget();
     tab_widget->addTab(CreateTabFpga(),"FPGA");
    tab_widget->addTab(CreateTabSerial(),"Serial");
    tab_widget->addTab(CreateTabWave(),"Wave");
    //tab_widget->addTab(CreateTabDb(),"Db");

     QVBoxLayout*  tab_layout= new QVBoxLayout();
     tab_layout->addWidget(tab_widget);
    setLayout(tab_layout);
}

QWidget* CmdWidget::CreateTabFpga(){
    QVBoxLayout* tab_layout = new QVBoxLayout();
    QVBoxLayout * emit_layout = new QVBoxLayout();
    QGroupBox* emit_box = new QGroupBox("发射");
    QVBoxLayout * rece_layout = new QVBoxLayout();
    QGroupBox* rece_box = new QGroupBox("接收");

    QSqlQuery query;
    query.exec("Select * from CmdComponentType");
    while(query.next()){
        if(query.value("id").toInt()<=4){
           CreateComponent(emit_layout,query);
        }else{
           CreateComponent(rece_layout,query);
        }
    }

    emit_box->setLayout(emit_layout);
    tab_layout->addWidget(emit_box);
     rece_box->setLayout(rece_layout);
     tab_layout->addWidget(rece_box);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addLayout(tab_layout);
    layout->addSpacerItem(new QSpacerItem(800,100));

    QWidget* widget = new QWidget();
    widget->setLayout(layout);

     return widget;
}

QWidget* CmdWidget::CreateTabSerial(){
    SerialCmdWidget* serial_widget = new SerialCmdWidget();
    QVBoxLayout * layout = new QVBoxLayout();
    QWidget* widget = new QWidget();
    layout->addWidget(serial_widget);
   // layout->a
    widget->setLayout(layout);

    return widget;
}

QWidget* CmdWidget::CreateTabWave(){
    QVBoxLayout* tab_layout = new QVBoxLayout();
    QVBoxLayout * emit_layout = new QVBoxLayout();
    WaveWidget * wave = new WaveWidget();
     tab_layout->addWidget(wave);

     QWidget* widget = new QWidget();
     widget->setLayout(tab_layout);

     return widget;
}

QWidget* CmdWidget::CreateTabDb(){
     return new DbWidget(0);
}

void CmdWidget::CreateComponent(QBoxLayout* parent_layout,QSqlQuery query){
    int type = query.value("ComponentType").toInt();
    QString cmd_name  = query.value("CmdName").toString();
    double  value  = query.value("value").toDouble();
    switch(type){
        case COMPONENGT_TYPE_QDOUBLESPINBOX:{
            QLabel* label = new QLabel(cmd_name);
            QDoubleSpinBox* box = new QDoubleSpinBox();
             QHBoxLayout* layout = new QHBoxLayout();
            double min = FindDBMinOrMan(cmd_name,QString("MIN"));
            double max = FindDBMinOrMan(cmd_name,QString("MAX"));
                        qDebug()<<"min:"<<min<<"  max:"<<max;
             label->setFixedWidth(LABEL_SIZE);
             layout->addWidget(label);
             if(min!=-1){
                box->setMinimum(min);
             }
            if(max!=-1){
                box->setMaximum(max);
            }
             box->setDecimals(6);
             box->setValue(value);
             layout->addWidget(box);
             Connect(box,cmd_name);
             parent_layout->addLayout(layout);
        }break;
        case COMPONENGT_TYPE_QPINBOX:{
            QLabel* label = new QLabel(cmd_name);
            QSpinBox* box = new QSpinBox();
             QHBoxLayout* layout = new QHBoxLayout();
            double min = FindDBMinOrMan(cmd_name,QString("MIN"));
            double max = FindDBMinOrMan(cmd_name,QString("MAX"));
             label->setFixedWidth(LABEL_SIZE);
             layout->addWidget(label);
             if(min!=-1){
                box->setMinimum(min);
             }
            if(max!=-1){
                box->setMaximum(max);
            }
             box->setValue(value);
             layout->addWidget(box);
             Connect(box,cmd_name);
             parent_layout->addLayout(layout);
        }break;
        case COMPONENGT_TYPE_QCOMBOBOX:{
            QLabel* label = new QLabel(cmd_name);
            QComboBox* box = new QComboBox();
            QHBoxLayout* layout = new QHBoxLayout();
            InitQComboBox(box,cmd_name);
             label->setFixedWidth(LABEL_SIZE);
             box->setCurrentIndex(value);
             layout->addWidget(label);
             layout->addWidget(box);
             Connect(box,cmd_name);
             parent_layout->addLayout(layout);
        }break;
        default:{
        qDebug("No the Component type(%d)!",type);
        }
    }

}

template<typename ComponengType>
void CmdWidget::Connect(ComponengType* compo,QString& cmd_name){
    Q_CHECK_PTR(compo);
    if(cmd_name==NAME_EMIT_FREQUENCY){
        QObject::connect(compo,SIGNAL(valueChanged(double)),this,SLOT(SetEmitFrequency(double)));
    } else if(cmd_name==  NAME_EMIT_MODE){
        QObject::connect(compo,SIGNAL(currentIndexChanged(int)),this,SLOT(SetEmitMode(int)));
    }else if(cmd_name==  NAME_MODUELATE_MODE){
        QObject::connect(compo,SIGNAL(currentIndexChanged(int)),this,SLOT(SetModulateMode(int)));
    }else if(cmd_name==  NAME_PTT){
        QObject::connect(compo,SIGNAL(currentIndexChanged(int)),this,SLOT(SetPPT(int)));
    }else if(cmd_name==  NAME_RECEIVER_MODE){
      QObject::connect(compo,SIGNAL(currentIndexChanged(int)),this,SLOT(SetReceiverMode(int)));
    }else if(cmd_name==   NAME_RECEIVER_MODUELATE_MODE){
      QObject::connect(compo,SIGNAL(currentIndexChanged(int)),this,SLOT(SetReceiverModulateMode(int)));
     }else if(cmd_name==  NAME_ANALOG_AGC_MODE){
      QObject::connect(compo,SIGNAL(currentIndexChanged(int)),this,SLOT(SetAnalogAgcMode(int)));
    } else if(cmd_name==    NAME_DIGITAL_AGC_MODE){
      QObject::connect(compo,SIGNAL(currentIndexChanged(int)),this,SLOT(SetDigitalAgcMode(int)));
    } else if(cmd_name==     NAME_AGC_ATTENUATION ){
      QObject::connect(compo,SIGNAL(valueChanged(int)),this,SLOT(SetAGCAteenuationValue(int)));
    }else if(cmd_name==    NAME_GAIN_VALUE){
      QObject::connect(compo,SIGNAL(valueChanged(int)),this,SLOT(SetAgcGainValue(int)));
    }
}

double CmdWidget::FindDBMinOrMan(QString& cmd_name,QString itemname){
    QSqlQuery query;
    double value;
    QString str = "select itemvalue from  CmdDefine where CmdName='"+cmd_name+"'"+" and itemname='"+itemname+"'";
    qDebug()<<str;
     query.exec(str);
    if(query.next()){
         value = query.value("itemvalue").toDouble();
    }else{
        value = -1;
    }
    return value;
}

void CmdWidget::InitQComboBox(QComboBox* box,QString& cmd_name){
    QSqlQuery query;
    double value;
    QString str = "select itemname,itemvalue from  CmdDefine where CmdName='"+cmd_name+"'";

     query.exec(str);
      qDebug()<<str<<query.size();
    while(query.next()){
        box->addItem(query.value("itemname").toString(),query.value("itemvalue").toInt());
    }
}

void CmdWidget::CreateEmitFrequency(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("发射频率/MHz:");
    QDoubleSpinBox* box = new QDoubleSpinBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->setMinimum(1.5);
    box->setMaximum(30);
    box->setDecimals(6);

    QSqlQuery query;
    query .exec("SELECT * FROM FpgaCmd where name = '发射频率/MHz';");
    while (query.next())
    {
        double value = query.value(1).toDouble(); //取第i条记录第2个字段的结果
        qWarning()<<"value"<<value;
        box->setValue(value);
    }

    layout->addWidget(box);
    QObject::connect(box,SIGNAL(valueChanged(double)),this,SLOT(SetEmitFrequency(double)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateEmitMode(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("发射模式:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->addItem(QString("静频"),EMIT_MODE_STATIC_FREQUENCY);
    box->addItem(QString("跳頻"),EMIT_MODE_JUMP_FREQUENCY);
    box->addItem(QString("自适应"),EMIT_MODE_SELF_ADAPTE);
     box->addItem(QString("自动控制"),EMIT_MODE_SELF_CONTROL);
     box->addItem(QString("自动选频"),EMIT_MODE_SELF_SELCT_FREQUENCY);
     layout->addWidget(box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetEmitMode(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateEmitModulateMode(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("发射工作模式:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->addItem(QString("CW"),MODUELATE_MODE_CW);
    box->addItem(QString("USB"),MODUELATE_MODE_USB);
    box->addItem(QString("LSB"),MODUELATE_MODE_LSB);
     box->addItem(QString("AM"),MODUELATE_MODE_AM);
     box->addItem(QString("ISB"),MODUELATE_MODE_ISB);
     box->addItem(QString("数据"),MODUELATE_MODE_Data);
     layout->addWidget(box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetModulateMode(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreatePTT(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("PTT控制:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->addItem(QString("关"),0);
    box->addItem(QString("开"),1);
    layout->addWidget(box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetPPT(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateReceiverFrequency(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("接收频率/MHz:");
    QDoubleSpinBox* box = new QDoubleSpinBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->setMinimum(1.5);
    box->setMaximum(30);
    box->setDecimals(6);
    layout->addWidget(box);
    QObject::connect(box,SIGNAL(valueChanged(double)),this,SLOT(SetReceiverFrequency(double)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateReceiverMode(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("接收模式:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->addItem(QString("静频"),EMIT_MODE_STATIC_FREQUENCY);
    box->addItem(QString("跳頻"),EMIT_MODE_JUMP_FREQUENCY);
    box->addItem(QString("自适应"),EMIT_MODE_SELF_ADAPTE);
     box->addItem(QString("自动控制"),EMIT_MODE_SELF_CONTROL);
     box->addItem(QString("自动选频"),EMIT_MODE_SELF_SELCT_FREQUENCY);
     layout->addWidget(box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetReceiverMode(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateReceiverModulateMode(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("接收工作模式:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->addItem(QString("CW"),MODUELATE_MODE_CW);
    box->addItem(QString("USB"),MODUELATE_MODE_USB);
    box->addItem(QString("LSB"),MODUELATE_MODE_LSB);
     box->addItem(QString("AM"),MODUELATE_MODE_AM);
     box->addItem(QString("ISB"),MODUELATE_MODE_ISB);
     box->addItem(QString("数据"),MODUELATE_MODE_Data);
     layout->addWidget(box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetReceiverModulateMode(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateAgcMode(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("模拟Agc模式:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->addItem(QString("AGC"),ANALOG_AGC_MODE_AGC);
    box->addItem(QString("MGC"),ANALOG_AGC_MODE_MGC);
     layout->addWidget(box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetAnalogAgcMode(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateAGCAteenuationValue(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("Agc衰减值/dB:");
    QSpinBox* box = new QSpinBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->setMinimum(0);
    box->setMaximum(46);
    layout->addWidget(box);
    QObject::connect(box,SIGNAL(valueChanged(int)),this,SLOT(SetAGCAteenuationValue(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateDigitalAgcMode(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("Agc模式:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->addItem(QString("快AGC"),DIGITAL_AGC_MODE_FAST);
    box->addItem(QString("中AGC"),DIGITAL_AGC_MODE_MIDDLE);
    box->addItem(QString("慢AGC"),DIGITAL_AGC_MODE_SlOW);
    box->addItem(QString("MGC"),DIGITAL_AGC_MODE_MGC);
     layout->addWidget(box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetDigitalAgcMode(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::CreateAgcGainValue(QBoxLayout* parent_layout){
    QLabel* label = new QLabel("数字增益/dB:");
    QSpinBox* box = new QSpinBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    layout->addWidget(label);
    box->setMinimum(-20);
    box->setMaximum(120);
    layout->addWidget(box);
    QObject::connect(box,SIGNAL(valueChanged(int)),this,SLOT(SetAgcGainValue(int)));

    parent_layout->addLayout(layout);
}

void CmdWidget::SetEmitFrequency(double value){
    QSqlQuery query;
    QString str ="update  CmdComponentType set value = "+QString::number( value,'g',8)+"  where CmdName = '"+NAME_EMIT_FREQUENCY+"'";
  query.exec(str);
    qWarning()<<str;
     SetCmdDoubleFre(value,REG_EMIT_FREQUENCY);
}

void CmdWidget::SetEmitMode(int value){
  QSqlQuery query;
  QString str = "update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_EMIT_MODE+"'";
  query.exec(str);
   qWarning()<<str;
   SetCmdInt(value,REG_EMIT_MODE);
}

void CmdWidget::SetModulateMode(int value){
  QSqlQuery query;
  QString str = "update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_MODUELATE_MODE+"'";
  query.exec(str);
   qWarning()<<str;
   SetCmdInt(value,REG_EMIT_MODUELATE_MODE);
}

void CmdWidget::SetPPT(int value){
  QSqlQuery query;
  QString str = "update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_PTT+"'";
  query.exec(str);
   qWarning()<<str;
   SetCmdInt(value,REG_PTT_SWITCH);
}

void CmdWidget::SetReceiverFrequency(double value){
   QSqlQuery query;
   QString str ="update  CmdComponentType set value = "+QString::number( value,'g',8)+"  where CmdName = '"+NAME_EMIT_FREQUENCY+"'";
  query.exec(str);
   qWarning()<<str;
   SetCmdDoubleFre(value,REG_RECEIVER_FREQUENCY);
}

void CmdWidget::SetReceiverMode(int value){
   QSqlQuery query;
  QString str ="update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_RECEIVER_MODE+"'";
  query.exec(str);
  qWarning()<<str;
  SetCmdInt(value,REG_RECEIVER_MODE);
}

void CmdWidget::SetReceiverModulateMode(int value){
   QSqlQuery query;
  QString str ="update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_RECEIVER_MODUELATE_MODE+"'";
  query.exec(str);
  qWarning()<<str;
  SetCmdInt(value,REG_RECEIVER_MODUELATE_MODE);
}

void CmdWidget::SetAnalogAgcMode(int value){
   QSqlQuery query;
  QString str ="update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_ANALOG_AGC_MODE+"'";
  query.exec(str);
  qWarning()<<str;
  SetCmdInt(value,REG_ANALOG_AGC_MODE);
}

void CmdWidget::SetAGCAteenuationValue(int value){
  QSqlQuery query;
  QString str ="update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_AGC_ATTENUATION+"'";
  query.exec(str);
  qWarning()<<str;
  SetCmdInt(value*8+160,REG_ANALOG_AGC_ATEENUATION_VALUE);
}

void CmdWidget::SetDigitalAgcMode(int value){
  QSqlQuery query;
  QString str ="update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_DIGITAL_AGC_MODE+"'";
  query.exec(str);
  qWarning()<<str;
  SetCmdInt(value,REG_DIGITAL_AGC_MODE);
}

void CmdWidget::SetAgcGainValue(int value){
  QSqlQuery query;
  QString str ="update  CmdComponentType set value = "+QString::number( value,10)+"  where CmdName = '"+NAME_GAIN_VALUE+"'";
  query.exec(str);
  qWarning()<<str;
  SetCmdInt(value,REG_DIGITAL_AGC_GAIN_VALUE);
}

void CmdWidget::SetCmdInt(int value,int offset){
    QString str = "w 0x";
    str+=QString::number(offset,16);
    str+= " ";
    str+=QString::number(value,10);
    str+=" E\n";

    SendData((char*)str.toStdString().c_str(),str.size());
}

void CmdWidget::SetCmdDoubleFre(double value,int offset){
    QString str = "w 0x";
    str+=QString::number(offset,16);
    str+= " ";
    str+=QString::number((int)(value*1000000),10);
    str+=" E\n";

    SendData((char*)str.toStdString().c_str(),str.size());
}

void CmdWidget::SendData(char* data,int size){
     if(!udp_socket_){
        return;
      }
    qDebug()<<QString(data);
    if(-1==udp_socket_->writeDatagram(data,size,*host_address_,HOST_PORT)){
        qDebug()<<"SendError";
    }
}
