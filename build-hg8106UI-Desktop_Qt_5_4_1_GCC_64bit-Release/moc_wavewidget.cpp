/****************************************************************************
** Meta object code from reading C++ file 'wavewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hg8106UI/wavewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wavewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UdpThread_t {
    QByteArrayData data[5];
    char stringdata[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpThread_t qt_meta_stringdata_UdpThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UdpThread"
QT_MOC_LITERAL(1, 10, 7), // "AddData"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "data_x"
QT_MOC_LITERAL(4, 26, 6) // "data_y"

    },
    "UdpThread\0AddData\0\0data_x\0data_y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       1,    2,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

       0        // eod
};

void UdpThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UdpThread *_t = static_cast<UdpThread *>(_o);
        switch (_id) {
        case 0: _t->AddData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->AddData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UdpThread::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpThread::AddData)) {
                *result = 0;
            }
        }
        {
            typedef void (UdpThread::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpThread::AddData)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject UdpThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_UdpThread.data,
      qt_meta_data_UdpThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UdpThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UdpThread.stringdata))
        return static_cast<void*>(const_cast< UdpThread*>(this));
    return QThread::qt_metacast(_clname);
}

int UdpThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void UdpThread::AddData(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpThread::AddData(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WaveWidget_t {
    QByteArrayData data[13];
    char stringdata[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WaveWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WaveWidget_t qt_meta_stringdata_WaveWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WaveWidget"
QT_MOC_LITERAL(1, 11, 8), // "newValue"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 5), // "value"
QT_MOC_LITERAL(4, 27, 12), // "SampleUpdate"
QT_MOC_LITERAL(5, 40, 14), // "updatedataSlot"
QT_MOC_LITERAL(6, 55, 15), // "CreateQwtMarker"
QT_MOC_LITERAL(7, 71, 7), // "QPoint&"
QT_MOC_LITERAL(8, 79, 3), // "pos"
QT_MOC_LITERAL(9, 83, 17), // "UpdateDataFromUDP"
QT_MOC_LITERAL(10, 101, 6), // "data_x"
QT_MOC_LITERAL(11, 108, 6), // "data_y"
QT_MOC_LITERAL(12, 115, 6) // "Replot"

    },
    "WaveWidget\0newValue\0\0value\0SampleUpdate\0"
    "updatedataSlot\0CreateQwtMarker\0QPoint&\0"
    "pos\0UpdateDataFromUDP\0data_x\0data_y\0"
    "Replot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WaveWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    0,   52,    2, 0x08 /* Private */,
       5,    0,   53,    2, 0x08 /* Private */,
       6,    1,   54,    2, 0x08 /* Private */,
       9,    2,   57,    2, 0x08 /* Private */,
       9,    2,   62,    2, 0x08 /* Private */,
      12,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,

       0        // eod
};

void WaveWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WaveWidget *_t = static_cast<WaveWidget *>(_o);
        switch (_id) {
        case 0: _t->newValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->SampleUpdate(); break;
        case 2: _t->updatedataSlot(); break;
        case 3: _t->CreateQwtMarker((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->UpdateDataFromUDP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->UpdateDataFromUDP((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->Replot(); break;
        default: ;
        }
    }
}

const QMetaObject WaveWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WaveWidget.data,
      qt_meta_data_WaveWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WaveWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WaveWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WaveWidget.stringdata))
        return static_cast<void*>(const_cast< WaveWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int WaveWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
