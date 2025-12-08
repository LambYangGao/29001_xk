/****************************************************************************
** Meta object code from reading C++ file 'protocol_yaogan.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../protocol_yaogan.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocol_yaogan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_protocol_yaogan_t {
    QByteArrayData data[10];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_protocol_yaogan_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_protocol_yaogan_t qt_meta_stringdata_protocol_yaogan = {
    {
QT_MOC_LITERAL(0, 0, 15), // "protocol_yaogan"
QT_MOC_LITERAL(1, 16, 12), // "sig_PosEvent"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "JoyPosInfoMsg"
QT_MOC_LITERAL(4, 44, 4), // "info"
QT_MOC_LITERAL(5, 49, 12), // "sig_BtnEvent"
QT_MOC_LITERAL(6, 62, 13), // "JoyBtnInfoMsg"
QT_MOC_LITERAL(7, 76, 12), // "sig_PovEvent"
QT_MOC_LITERAL(8, 89, 5), // "state"
QT_MOC_LITERAL(9, 95, 13) // "sig_SateEvent"

    },
    "protocol_yaogan\0sig_PosEvent\0\0"
    "JoyPosInfoMsg\0info\0sig_BtnEvent\0"
    "JoyBtnInfoMsg\0sig_PovEvent\0state\0"
    "sig_SateEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_protocol_yaogan[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       7,    1,   40,    2, 0x06 /* Public */,
       9,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void protocol_yaogan::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        protocol_yaogan *_t = static_cast<protocol_yaogan *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_PosEvent((*reinterpret_cast< JoyPosInfoMsg(*)>(_a[1]))); break;
        case 1: _t->sig_BtnEvent((*reinterpret_cast< JoyBtnInfoMsg(*)>(_a[1]))); break;
        case 2: _t->sig_PovEvent((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sig_SateEvent((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (protocol_yaogan::*_t)(JoyPosInfoMsg );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&protocol_yaogan::sig_PosEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (protocol_yaogan::*_t)(JoyBtnInfoMsg );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&protocol_yaogan::sig_BtnEvent)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (protocol_yaogan::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&protocol_yaogan::sig_PovEvent)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (protocol_yaogan::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&protocol_yaogan::sig_SateEvent)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject protocol_yaogan::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_protocol_yaogan.data,
      qt_meta_data_protocol_yaogan,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *protocol_yaogan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *protocol_yaogan::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_protocol_yaogan.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int protocol_yaogan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void protocol_yaogan::sig_PosEvent(JoyPosInfoMsg _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void protocol_yaogan::sig_BtnEvent(JoyBtnInfoMsg _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void protocol_yaogan::sig_PovEvent(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void protocol_yaogan::sig_SateEvent(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
