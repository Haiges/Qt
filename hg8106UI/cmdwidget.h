#ifndef CMDWIDGET_H
#define CMDWIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>
#include <QString>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QString>

#define NAME_EMIT_FREQUENCY                                     "发射频率/MHz"
#define NAME_EMIT_MODE                                               "发射模式"
#define NAME_MODUELATE_MODE                                  "发射工作模式"
#define NAME_PTT                                                              "PTT控制"

#define NAME_RECEIVER_MODE                                        "接收模式"
#define NAME_RECEIVER_MODUELATE_MODE                 "接收工作模式"
#define NAME_ANALOG_AGC_MODE                                "模拟Agc模式"
#define NAME_DIGITAL_AGC_MODE                                  "Agc模式"
#define NAME_AGC_ATTENUATION                                    "Agc衰减值/dB"
#define NAME_GAIN_VALUE                                                "数字增益/dB"

enum{
    COMPONENGT_TYPE_QDOUBLESPINBOX,
    COMPONENGT_TYPE_QPINBOX,
    COMPONENGT_TYPE_QCOMBOBOX,
};

#define REG_SELFCHECK                         0x0000

//the Offset of Emit reg in bram 0
#define REG_EMIT_FREQUENCY                               0x0400    //2000000~29999900Hz
#define REG_EMIT_MODE                                         0x0404
#define REG_EMIT_MODUELATE_MODE                  0x0408
#define REG_PTT_SWITCH                                         0x040c

//the Offset of receiver reg in bram 0
#define REG_RECEIVER_FREQUENCY                0x0800
#define REG_RECEIVER_MODE                     0x0804
#define REG_RECEIVER_MODUELATE_MODE           0x0808    // 0:CW 1:USB 2:LSB 3:AM 4:ISB 4:Data
#define REG_ANALOG_AGC_MODE                   0x080c    // 0:AGC 1:MGC
#define REG_ANALOG_AGC_ATEENUATION_VALUE      0x0810    // 0~46dB
#define REG_DIGITAL_AGC_MODE                  0x081C    //0:Fast 1:Middle 2:Slow 3:MGC
#define REG_DIGITAL_AGC_GAIN_VALUE            0x0820    // ((0~1120)-160)*0.125dB

#define REG_SOFTVERSION         0x1000

enum{
  EMIT_MODE_STATIC_FREQUENCY,
  EMIT_MODE_JUMP_FREQUENCY,
  EMIT_MODE_SELF_ADAPTE,
  EMIT_MODE_SELF_CONTROL,
  EMIT_MODE_SELF_SELCT_FREQUENCY,
};

enum{
  PTT_OFF,
  PTT_ON,
};

enum{
  MODUELATE_MODE_CW,
  MODUELATE_MODE_USB,
  MODUELATE_MODE_LSB,
  MODUELATE_MODE_AM,
  MODUELATE_MODE_ISB,
  MODUELATE_MODE_Data,
};

enum{
  ANALOG_AGC_MODE_AGC,
  ANALOG_AGC_MODE_MGC,
};

enum{
  DIGITAL_AGC_MODE_FAST,
  DIGITAL_AGC_MODE_MIDDLE,
  DIGITAL_AGC_MODE_SlOW,
  DIGITAL_AGC_MODE_MGC,
};

class QComboBox;
class CmdWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CmdWidget(QWidget *parent = 0);
    ~CmdWidget();

signals:

public slots:
    //Emit
    void SetEmitFrequency(double value);
    void SetEmitMode(int value);
    void SetModulateMode(int value);
    void SetPPT(int value);
    //Receiver
    void SetReceiverFrequency(double value);
    void SetReceiverMode(int value);
    void SetReceiverModulateMode(int value);
    void SetAnalogAgcMode(int value);
    void SetAGCAteenuationValue(int value);
    void SetDigitalAgcMode(int value);
    void SetAgcGainValue(int value);

private:
   void CreateUDP();
   void InitDb();
   void CreateLayOut();
    QWidget* CreateTabFpga();
    QWidget* CreateTabSerial();
    QWidget* CreateTabWave();
    QWidget* CreateTabDb();

    void CreateEmitFrequency(QBoxLayout* parent_layout);
    void CreateEmitMode(QBoxLayout* parent_layout);
    void CreateEmitModulateMode(QBoxLayout* parent_layout);
    void CreatePTT(QBoxLayout* parent_layout);
    void CreateReceiverFrequency(QBoxLayout* parent_layout) ;
    void CreateReceiverMode(QBoxLayout* parent_layout);
    void CreateReceiverModulateMode(QBoxLayout* parent_layout);
    void CreateAgcMode(QBoxLayout* parent_layout);
    void CreateAGCAteenuationValue(QBoxLayout* parent_layout);
    void CreateDigitalAgcMode(QBoxLayout* parent_layout);
    void CreateAgcGainValue(QBoxLayout* parent_layout);
    void CreateComponent(QBoxLayout* parent_layout,QSqlQuery query);
    template<typename ComponengType>
        void Connect(ComponengType* compo,QString& cmd_name);
    double FindDBMinOrMan(QString& cmd_name,QString itemname);
    void InitQComboBox(QComboBox* box,QString& cmd_name);

    void SetCmdInt(int value,int offset);
    void SetCmdDoubleFre(double value,int offset);
    void SendData(char* data,int size);
  private:
    QSqlDatabase  db_;
    QUdpSocket* udp_socket_;
    QHostAddress*  host_address_;
};

#endif // CMDWIDGET_H
