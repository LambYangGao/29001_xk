/****************************************************************************
** Meta object code from reading C++ file 'rtspstream.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../rtspstream.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtspstream.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DecodeMore_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DecodeMore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DecodeMore_t qt_meta_stringdata_DecodeMore = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DecodeMore"
QT_MOC_LITERAL(1, 11, 11), // "decodeStart"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10) // "decodeStop"

    },
    "DecodeMore\0decodeStart\0\0decodeStop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DecodeMore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DecodeMore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DecodeMore *_t = static_cast<DecodeMore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->decodeStart(); break;
        case 1: _t->decodeStop(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DecodeMore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DecodeMore.data,
      qt_meta_data_DecodeMore,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DecodeMore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DecodeMore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DecodeMore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DecodeMore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_DisplayMore_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisplayMore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisplayMore_t qt_meta_stringdata_DisplayMore = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DisplayMore"
QT_MOC_LITERAL(1, 12, 12), // "displayStart"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11) // "displayStop"

    },
    "DisplayMore\0displayStart\0\0displayStop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisplayMore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,

       0        // eod
};

void DisplayMore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DisplayMore *_t = static_cast<DisplayMore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->displayStart();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->displayStop(); break;
        default: ;
        }
    }
}

const QMetaObject DisplayMore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DisplayMore.data,
      qt_meta_data_DisplayMore,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DisplayMore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisplayMore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayMore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DisplayMore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_EncodeMore_t {
    QByteArrayData data[5];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EncodeMore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EncodeMore_t qt_meta_stringdata_EncodeMore = {
    {
QT_MOC_LITERAL(0, 0, 10), // "EncodeMore"
QT_MOC_LITERAL(1, 11, 11), // "encodeStart"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "in_out_url"
QT_MOC_LITERAL(4, 35, 10) // "encodeStop"

    },
    "EncodeMore\0encodeStart\0\0in_out_url\0"
    "encodeStop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EncodeMore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    0,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void EncodeMore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EncodeMore *_t = static_cast<EncodeMore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->encodeStart((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->encodeStop(); break;
        default: ;
        }
    }
}

const QMetaObject EncodeMore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EncodeMore.data,
      qt_meta_data_EncodeMore,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *EncodeMore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EncodeMore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EncodeMore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EncodeMore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VideoMore_t {
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoMore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoMore_t qt_meta_stringdata_VideoMore = {
    {
QT_MOC_LITERAL(0, 0, 9), // "VideoMore"
QT_MOC_LITERAL(1, 10, 17), // "sigEncodeMp4Start"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "in_out_url"
QT_MOC_LITERAL(4, 40, 16), // "sigReDecodeStart"
QT_MOC_LITERAL(5, 57, 17), // "sigReDisplayStart"
QT_MOC_LITERAL(6, 75, 5), // "start"
QT_MOC_LITERAL(7, 81, 4) // "stop"

    },
    "VideoMore\0sigEncodeMp4Start\0\0in_out_url\0"
    "sigReDecodeStart\0sigReDisplayStart\0"
    "start\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoMore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,
       5,    0,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoMore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoMore *_t = static_cast<VideoMore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigEncodeMp4Start((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigReDecodeStart(); break;
        case 2: _t->sigReDisplayStart(); break;
        case 3: _t->start(); break;
        case 4: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (VideoMore::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoMore::sigEncodeMp4Start)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VideoMore::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoMore::sigReDecodeStart)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VideoMore::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoMore::sigReDisplayStart)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject VideoMore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VideoMore.data,
      qt_meta_data_VideoMore,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VideoMore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoMore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoMore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VideoMore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VideoMore::sigEncodeMp4Start(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoMore::sigReDecodeStart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VideoMore::sigReDisplayStart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
