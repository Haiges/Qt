#include "serialcmdwidget.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>

#define LABEL_SIZE 200
SerialCmdWidget::SerialCmdWidget(QWidget *parent) : CmdWidgetBase(parent){
    init();
}

SerialCmdWidget::~SerialCmdWidget(){
}

void SerialCmdWidget::init(){
    setRowCount(CmdIDNUMBERS);
    setColumnCount(2);

    CreateFrequency();
    CreateTurn();
    CreatePower();
    CreatePTT();
    CreateSelfCheck();
    CreateErrorNo();
    CreateVersion();
    CreateLruPower();
    CreateLruTemprature();
    CreateLruCurrent();
    adjustSize();
    show();
}

void SerialCmdWidget::CreateFrequency(){
    QLabel* label = new QLabel("工作频率/MHz:");
    QDoubleSpinBox* box = new QDoubleSpinBox();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDWorkFrequency,0,label);
    box->setMinimum(1.5);
    box->setMaximum(30);
    box->setDecimals(6);
    setCellWidget(CmdIDWorkFrequency,1,box);
    QObject::connect(box,SIGNAL(valueChanged(double)),this,SLOT(SetFrequency(double)));

   // parent_layout->addLayout(layout);
}

void SerialCmdWidget::CreateTurn(){
    QLabel* label = new QLabel("调谐:");
   QPushButton* button = new QPushButton("设置");
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDTURN,0,label);
    setCellWidget(CmdIDTURN,1,button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(SetTurn()));

    //parent_layout->addLayout(layout);
}

void SerialCmdWidget::CreatePower(){
    QLabel* label = new QLabel("功率:");
     box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    //layout->addWidget(label);
    setCellWidget(CmdIDPOWER,0,label);
    box->addItem(QString("10w"),10);
    box->addItem(QString("50w"),50);
    box->addItem(QString("100w"),100);
    //layout->addWidget(box);
    setCellWidget(CmdIDPOWER,1,box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetPower(int)));

    //parent_layout->addLayout(layout);
}

void SerialCmdWidget::CreatePTT(){
    QLabel* label = new QLabel("PPT控制:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDPPT,0,label);
    box->addItem(QString("开"),0);
    box->addItem(QString("关"),1);
    setCellWidget(CmdIDPPT,1,box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetPTT(int)));
}

void SerialCmdWidget::CreateSelfCheck(){
    QLabel* label = new QLabel("自检:");
    QComboBox* box = new QComboBox();
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDSELFECHECK,0,label);
    box->addItem(QString("开"),0);
    box->addItem(QString("关"),1);
    setCellWidget(CmdIDSELFECHECK,1,box);
    QObject::connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(SetSelfCheck(int)));
}

void SerialCmdWidget::CreateErrorNo(){
    QLabel* label = new QLabel("状态:");
   QPushButton* button = new QPushButton("查询");
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDERRORNO,0,label);
    setCellWidget(CmdIDERRORNO,1,button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(SetErrorNo()));
}

void SerialCmdWidget::CreateVersion(){
    QLabel* label = new QLabel("版本:");
   QPushButton* button = new QPushButton("查询");
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDVERSION,0,label);
    setCellWidget(CmdIDVERSION,1,button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(SetVersion()));
}

void SerialCmdWidget::CreateLruPower(){
    QLabel* label = new QLabel("功率:");
   QPushButton* button = new QPushButton("查询");
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDLRUPOWER,0,label);
    setCellWidget(CmdIDLRUPOWER,1,button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(SetLruPower()));
}

void SerialCmdWidget::CreateLruTemprature(){
    QLabel* label = new QLabel("温度:");
   QPushButton* button = new QPushButton("查询");
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDLRUTEMPRATURE,0,label);
    setCellWidget(CmdIDLRUTEMPRATURE,1,button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(SetLruTemprature()));
}

void SerialCmdWidget::CreateLruCurrent(){
    QLabel* label = new QLabel("电流:");
    QPushButton* button = new QPushButton("查询");
    QHBoxLayout* layout = new QHBoxLayout();

    label->setFixedWidth(LABEL_SIZE);
    setCellWidget(CmdIDLRUCURRENT,0,label);
    setCellWidget(CmdIDLRUCURRENT,1,button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(SetLruCurrent()));
}

void SerialCmdWidget::SetFrequency(double value){
     SetCmdDoubleFre(value,CmdIDWorkFrequency);
}

void SerialCmdWidget::SetTurn(){
    int value = 0;
    SetCmdInt(value,CmdIDTURN);
}

void SerialCmdWidget::SetPower(int value){
    value = box->currentIndex();
    qDebug()<<"value:"<<value;
   qDebug()<<"text:"<< box->currentText();
    qDebug()<<"Data:"<<box->currentData();;
    SetCmdInt(value,CmdIDPOWER);
}

void SerialCmdWidget::SetPTT(int value){
    SetCmdInt(value,CmdIDPPT);
}

void SerialCmdWidget::SetSelfCheck(int value){
    SetCmdInt(value,CmdIDSELFECHECK);
}

void SerialCmdWidget::SetErrorNo(int value){
    SetCmdInt(value,CmdIDERRORNO);
}

void SerialCmdWidget::SetVersion(int value){
    SetCmdInt(value,CmdIDVERSION);
}

void SerialCmdWidget::SetLruPower(int value){
    SetCmdInt(value,CmdIDLRUPOWER);
}

void SerialCmdWidget::SetLruTemprature(int value){
    SetCmdInt(value,CmdIDLRUTEMPRATURE);
}

void SerialCmdWidget::SetLruCurrent(int value){
    SetCmdInt(value,CmdIDLRUCURRENT);
}

QString SerialCmdWidget::GetPreStr(){
    return "# 0x";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CmdWidgetBase::CmdWidgetBase(QWidget *parent){
    CreateUDP();
}

void CmdWidgetBase::SetCmdInt(int value,int offset){
    QString str = GetPreStr();
    str+=QString::number(offset,16);
    str+= " ";
    str+=QString::number(value,10);
    str+=" E\n";

    SendData((char*)str.toStdString().c_str(),str.size());
}

void CmdWidgetBase::SetCmdDoubleFre(double value,int offset){
    QString str = GetPreStr();
    str+=QString::number(offset,16);
    str+= " ";
    str+=QString::number((int)(value*1000000),10);
    str+=" E\n";

    SendData((char*)str.toStdString().c_str(),str.size());
}

void CmdWidgetBase::SendData(char* data,int size){
     if(!udp_socket_){
        return;
      }
    qDebug()<<QString(data);
    if(-1==udp_socket_->writeDatagram(data,size,QHostAddress::Broadcast,HOST_PORT)){
        qDebug()<<"SendError";
    }
}

void CmdWidgetBase::CreateUDP(){
    host_address_ =  QHostAddress(HOST_ADDRESS);
    udp_socket_ = new QUdpSocket(this);
}
