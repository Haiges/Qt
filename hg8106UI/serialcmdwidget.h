#ifndef SERIALCMDWIDGET_H
#define SERIALCMDWIDGET_H

#include <QTableWidget>
#include <QUdpSocket>
#include <QBoxLayout>
#include <QComboBox>

#define HOST_ADDRESS "172.17.70.232"
#define LOCAL_ADDRESS "172.17.70.93"
//#define HOST_ADDRESS "127.0.0.1"
#define HOST_PORT 3334
#define LABEL_SIZE  200

enum {
  CmdIDWorkFrequency,
  CmdIDTURN,
  CmdIDPOWER,
  CmdIDPPT,
  CmdIDSELFECHECK,
  CmdIDERRORNO,
  CmdIDVERSION,
  CmdIDLRUPOWER,
  CmdIDLRUTEMPRATURE,
  CmdIDLRUCURRENT,

  CmdIDNUMBERS,
};

class CmdWidgetBase : public QTableWidget
{
    Q_OBJECT
public:
    explicit CmdWidgetBase(QWidget *parent = 0);
    ~CmdWidgetBase(){}

protected:
    virtual QString GetPreStr( ) = 0;
    void        SendData(char* data,int size);

    void SetCmdInt(int value,int offset);
    void SetCmdDoubleFre(double value,int offset);
    void CreateUDP();
signals:

public slots:
    private:
        QHostAddress host_address_;
        QUdpSocket* udp_socket_;
};

class SerialCmdWidget : public CmdWidgetBase
{
    Q_OBJECT
public:
    explicit SerialCmdWidget(QWidget *parent = 0);
    ~SerialCmdWidget();
private:
    void init();
    virtual QString GetPreStr( ) ;

    void CreateFrequency();
    void CreateTurn();
    void CreatePower();
    void CreatePTT();
    void CreateSelfCheck();
    void CreateErrorNo();
    void CreateVersion();
    void CreateLruPower();
    void CreateLruTemprature();
    void CreateLruCurrent();
public slots:
    void SetFrequency(double value);
    void SetTurn();
    void SetPower(int value);
    void SetPTT(int value);
    void SetSelfCheck(int value);
    void SetErrorNo(int value = 0);
    void SetVersion(int value = 0);
    void SetLruPower(int value = 0);
    void SetLruTemprature(int value = 0);
    void SetLruCurrent(int value = 0);
private:
    QComboBox* box;
    QHostAddress* locl_address_;
};

#endif // SERIALCMDWIDGET_H
