/****************************************************************************
** Meta object code from reading C++ file 'serialcmdwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hg8106UI/serialcmdwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialcmdwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CmdWidgetBase_t {
    QByteArrayData data[1];
    char stringdata[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CmdWidgetBase_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CmdWidgetBase_t qt_meta_stringdata_CmdWidgetBase = {
    {
QT_MOC_LITERAL(0, 0, 13) // "CmdWidgetBase"

    },
    "CmdWidgetBase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CmdWidgetBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CmdWidgetBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CmdWidgetBase::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_CmdWidgetBase.data,
      qt_meta_data_CmdWidgetBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CmdWidgetBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CmdWidgetBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CmdWidgetBase.stringdata))
        return static_cast<void*>(const_cast< CmdWidgetBase*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int CmdWidgetBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_SerialCmdWidget_t {
    QByteArrayData data[13];
    char stringdata[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialCmdWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialCmdWidget_t qt_meta_stringdata_SerialCmdWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SerialCmdWidget"
QT_MOC_LITERAL(1, 16, 12), // "SetFrequency"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "value"
QT_MOC_LITERAL(4, 36, 7), // "SetTurn"
QT_MOC_LITERAL(5, 44, 8), // "SetPower"
QT_MOC_LITERAL(6, 53, 6), // "SetPTT"
QT_MOC_LITERAL(7, 60, 12), // "SetSelfCheck"
QT_MOC_LITERAL(8, 73, 10), // "SetErrorNo"
QT_MOC_LITERAL(9, 84, 10), // "SetVersion"
QT_MOC_LITERAL(10, 95, 11), // "SetLruPower"
QT_MOC_LITERAL(11, 107, 16), // "SetLruTemprature"
QT_MOC_LITERAL(12, 124, 13) // "SetLruCurrent"

    },
    "SerialCmdWidget\0SetFrequency\0\0value\0"
    "SetTurn\0SetPower\0SetPTT\0SetSelfCheck\0"
    "SetErrorNo\0SetVersion\0SetLruPower\0"
    "SetLruTemprature\0SetLruCurrent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialCmdWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x0a /* Public */,
       4,    0,   92,    2, 0x0a /* Public */,
       5,    1,   93,    2, 0x0a /* Public */,
       6,    1,   96,    2, 0x0a /* Public */,
       7,    1,   99,    2, 0x0a /* Public */,
       8,    1,  102,    2, 0x0a /* Public */,
       8,    0,  105,    2, 0x2a /* Public | MethodCloned */,
       9,    1,  106,    2, 0x0a /* Public */,
       9,    0,  109,    2, 0x2a /* Public | MethodCloned */,
      10,    1,  110,    2, 0x0a /* Public */,
      10,    0,  113,    2, 0x2a /* Public | MethodCloned */,
      11,    1,  114,    2, 0x0a /* Public */,
      11,    0,  117,    2, 0x2a /* Public | MethodCloned */,
      12,    1,  118,    2, 0x0a /* Public */,
      12,    0,  121,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void SerialCmdWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialCmdWidget *_t = static_cast<SerialCmdWidget *>(_o);
        switch (_id) {
        case 0: _t->SetFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->SetTurn(); break;
        case 2: _t->SetPower((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SetPTT((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetSelfCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SetErrorNo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->SetErrorNo(); break;
        case 7: _t->SetVersion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SetVersion(); break;
        case 9: _t->SetLruPower((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->SetLruPower(); break;
        case 11: _t->SetLruTemprature((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->SetLruTemprature(); break;
        case 13: _t->SetLruCurrent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->SetLruCurrent(); break;
        default: ;
        }
    }
}

const QMetaObject SerialCmdWidget::staticMetaObject = {
    { &CmdWidgetBase::staticMetaObject, qt_meta_stringdata_SerialCmdWidget.data,
      qt_meta_data_SerialCmdWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SerialCmdWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialCmdWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SerialCmdWidget.stringdata))
        return static_cast<void*>(const_cast< SerialCmdWidget*>(this));
    return CmdWidgetBase::qt_metacast(_clname);
}

int SerialCmdWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CmdWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
