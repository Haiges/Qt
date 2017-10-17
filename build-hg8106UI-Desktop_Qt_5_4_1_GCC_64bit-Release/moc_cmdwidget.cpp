/****************************************************************************
** Meta object code from reading C++ file 'cmdwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hg8106UI/cmdwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmdwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CmdWidget_t {
    QByteArrayData data[14];
    char stringdata[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CmdWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CmdWidget_t qt_meta_stringdata_CmdWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CmdWidget"
QT_MOC_LITERAL(1, 10, 16), // "SetEmitFrequency"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "value"
QT_MOC_LITERAL(4, 34, 11), // "SetEmitMode"
QT_MOC_LITERAL(5, 46, 15), // "SetModulateMode"
QT_MOC_LITERAL(6, 62, 6), // "SetPPT"
QT_MOC_LITERAL(7, 69, 20), // "SetReceiverFrequency"
QT_MOC_LITERAL(8, 90, 15), // "SetReceiverMode"
QT_MOC_LITERAL(9, 106, 23), // "SetReceiverModulateMode"
QT_MOC_LITERAL(10, 130, 16), // "SetAnalogAgcMode"
QT_MOC_LITERAL(11, 147, 22), // "SetAGCAteenuationValue"
QT_MOC_LITERAL(12, 170, 17), // "SetDigitalAgcMode"
QT_MOC_LITERAL(13, 188, 15) // "SetAgcGainValue"

    },
    "CmdWidget\0SetEmitFrequency\0\0value\0"
    "SetEmitMode\0SetModulateMode\0SetPPT\0"
    "SetReceiverFrequency\0SetReceiverMode\0"
    "SetReceiverModulateMode\0SetAnalogAgcMode\0"
    "SetAGCAteenuationValue\0SetDigitalAgcMode\0"
    "SetAgcGainValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CmdWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       4,    1,   72,    2, 0x0a /* Public */,
       5,    1,   75,    2, 0x0a /* Public */,
       6,    1,   78,    2, 0x0a /* Public */,
       7,    1,   81,    2, 0x0a /* Public */,
       8,    1,   84,    2, 0x0a /* Public */,
       9,    1,   87,    2, 0x0a /* Public */,
      10,    1,   90,    2, 0x0a /* Public */,
      11,    1,   93,    2, 0x0a /* Public */,
      12,    1,   96,    2, 0x0a /* Public */,
      13,    1,   99,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void CmdWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CmdWidget *_t = static_cast<CmdWidget *>(_o);
        switch (_id) {
        case 0: _t->SetEmitFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->SetEmitMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SetModulateMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SetPPT((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetReceiverFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->SetReceiverMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->SetReceiverModulateMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->SetAnalogAgcMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SetAGCAteenuationValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->SetDigitalAgcMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->SetAgcGainValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CmdWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CmdWidget.data,
      qt_meta_data_CmdWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CmdWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CmdWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CmdWidget.stringdata))
        return static_cast<void*>(const_cast< CmdWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CmdWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
