/****************************************************************************
** Meta object code from reading C++ file 'RwriteLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../RwriteLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RwriteLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RectLabel_t {
    QByteArrayData data[9];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RectLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RectLabel_t qt_meta_stringdata_RectLabel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RectLabel"
QT_MOC_LITERAL(1, 10, 16), // "sig_painter_size"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "startPT"
QT_MOC_LITERAL(4, 36, 5), // "endPT"
QT_MOC_LITERAL(5, 42, 5), // "width"
QT_MOC_LITERAL(6, 48, 6), // "height"
QT_MOC_LITERAL(7, 55, 16), // "sig_current_wind"
QT_MOC_LITERAL(8, 72, 12) // "currentState"

    },
    "RectLabel\0sig_painter_size\0\0startPT\0"
    "endPT\0width\0height\0sig_current_wind\0"
    "currentState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RectLabel[] = {

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
       1,    4,   24,    2, 0x06 /* Public */,
       7,    1,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::Float, QMetaType::Float,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void RectLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RectLabel *_t = static_cast<RectLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_painter_size((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: _t->sig_current_wind((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (RectLabel::*_t)(QPoint , QPoint , float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RectLabel::sig_painter_size)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RectLabel::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RectLabel::sig_current_wind)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject RectLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_RectLabel.data,
      qt_meta_data_RectLabel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RectLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RectLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RectLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int RectLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void RectLabel::sig_painter_size(QPoint _t1, QPoint _t2, float _t3, float _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RectLabel::sig_current_wind(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
