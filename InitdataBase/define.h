#ifndef DEFINE
#define DEFINE

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

enum ComponentType{
    COMPONENGT_TYPE_QDOUBLESPINBOX,
    COMPONENGT_TYPE_QPINBOX,
    COMPONENGT_TYPE_QCOMBOBOX,
};

enum{
  PTT_OFF,
  PTT_ON,
};
enum{
  EMIT_MODE_STATIC_FREQUENCY,
  EMIT_MODE_JUMP_FREQUENCY,
  EMIT_MODE_SELF_ADAPTE,
  EMIT_MODE_SELF_CONTROL,
  EMIT_MODE_SELF_SELCT_FREQUENCY,
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
#endif // DEFINE

