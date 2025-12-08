/****************************************************************************
** Meta object code from reading C++ file 'h264camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../h264camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'h264camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RTSPDataDecode_t {
    QByteArrayData data[24];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RTSPDataDecode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RTSPDataDecode_t qt_meta_stringdata_RTSPDataDecode = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RTSPDataDecode"
QT_MOC_LITERAL(1, 15, 17), // "SigImageChangedVi"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 8), // "cv::Mat&"
QT_MOC_LITERAL(4, 43, 6), // "in_mat"
QT_MOC_LITERAL(5, 50, 17), // "SigImageChangedIr"
QT_MOC_LITERAL(6, 68, 12), // "Sig_PacketVi"
QT_MOC_LITERAL(7, 81, 16), // "AVFormatContext*"
QT_MOC_LITERAL(8, 98, 15), // "in_FrameContext"
QT_MOC_LITERAL(9, 114, 9), // "AVPacket*"
QT_MOC_LITERAL(10, 124, 8), // "inPacket"
QT_MOC_LITERAL(11, 133, 12), // "Sig_PacketIr"
QT_MOC_LITERAL(12, 146, 14), // "SigImageDataVi"
QT_MOC_LITERAL(13, 161, 7), // "quint8*"
QT_MOC_LITERAL(14, 169, 12), // "in_imageData"
QT_MOC_LITERAL(15, 182, 14), // "SigImageDataIr"
QT_MOC_LITERAL(16, 197, 9), // "RTSP_Open"
QT_MOC_LITERAL(17, 207, 5), // "start"
QT_MOC_LITERAL(18, 213, 4), // "stop"
QT_MOC_LITERAL(19, 218, 5), // "pause"
QT_MOC_LITERAL(20, 224, 11), // "frame_state"
QT_MOC_LITERAL(21, 236, 3), // "res"
QT_MOC_LITERAL(22, 240, 9), // "showError"
QT_MOC_LITERAL(23, 250, 3) // "err"

    },
    "RTSPDataDecode\0SigImageChangedVi\0\0"
    "cv::Mat&\0in_mat\0SigImageChangedIr\0"
    "Sig_PacketVi\0AVFormatContext*\0"
    "in_FrameContext\0AVPacket*\0inPacket\0"
    "Sig_PacketIr\0SigImageDataVi\0quint8*\0"
    "in_imageData\0SigImageDataIr\0RTSP_Open\0"
    "start\0stop\0pause\0frame_state\0res\0"
    "showError\0err"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RTSPDataDecode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,
       6,    2,   80,    2, 0x06 /* Public */,
      11,    2,   85,    2, 0x06 /* Public */,
      12,    1,   90,    2, 0x06 /* Public */,
      15,    1,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,   96,    2, 0x0a /* Public */,
      17,    0,   97,    2, 0x0a /* Public */,
      18,    0,   98,    2, 0x0a /* Public */,
      19,    0,   99,    2, 0x0a /* Public */,
      20,    1,  100,    2, 0x0a /* Public */,
      22,    1,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::Int,   23,

       0        // eod
};

void RTSPDataDecode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RTSPDataDecode *_t = static_cast<RTSPDataDecode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigImageChangedVi((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 1: _t->SigImageChangedIr((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 2: _t->Sig_PacketVi((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< AVPacket*(*)>(_a[2]))); break;
        case 3: _t->Sig_PacketIr((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< AVPacket*(*)>(_a[2]))); break;
        case 4: _t->SigImageDataVi((*reinterpret_cast< quint8*(*)>(_a[1]))); break;
        case 5: _t->SigImageDataIr((*reinterpret_cast< quint8*(*)>(_a[1]))); break;
        case 6: { int _r = _t->RTSP_Open();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->start(); break;
        case 8: _t->stop(); break;
        case 9: _t->pause(); break;
        case 10: _t->frame_state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->showError((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (RTSPDataDecode::*_t)(cv::Mat & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RTSPDataDecode::SigImageChangedVi)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RTSPDataDecode::*_t)(cv::Mat & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RTSPDataDecode::SigImageChangedIr)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (RTSPDataDecode::*_t)(AVFormatContext * , AVPacket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RTSPDataDecode::Sig_PacketVi)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (RTSPDataDecode::*_t)(AVFormatContext * , AVPacket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RTSPDataDecode::Sig_PacketIr)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (RTSPDataDecode::*_t)(quint8 * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RTSPDataDecode::SigImageDataVi)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (RTSPDataDecode::*_t)(quint8 * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RTSPDataDecode::SigImageDataIr)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject RTSPDataDecode::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RTSPDataDecode.data,
      qt_meta_data_RTSPDataDecode,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RTSPDataDecode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RTSPDataDecode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RTSPDataDecode.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RTSPDataDecode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void RTSPDataDecode::SigImageChangedVi(cv::Mat & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RTSPDataDecode::SigImageChangedIr(cv::Mat & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RTSPDataDecode::Sig_PacketVi(AVFormatContext * _t1, AVPacket * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RTSPDataDecode::Sig_PacketIr(AVFormatContext * _t1, AVPacket * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RTSPDataDecode::SigImageDataVi(quint8 * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RTSPDataDecode::SigImageDataIr(quint8 * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_SDL_Play_t {
    QByteArrayData data[17];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SDL_Play_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SDL_Play_t qt_meta_stringdata_SDL_Play = {
    {
QT_MOC_LITERAL(0, 0, 8), // "SDL_Play"
QT_MOC_LITERAL(1, 9, 16), // "SDL_Windows_Show"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "SDL_Renderer*"
QT_MOC_LITERAL(4, 41, 9), // "in_render"
QT_MOC_LITERAL(5, 51, 12), // "SDL_Texture*"
QT_MOC_LITERAL(6, 64, 10), // "in_texture"
QT_MOC_LITERAL(7, 75, 7), // "quint8*"
QT_MOC_LITERAL(8, 83, 12), // "in_imageData"
QT_MOC_LITERAL(9, 96, 16), // "SDL_Windows_Init"
QT_MOC_LITERAL(10, 113, 6), // "inType"
QT_MOC_LITERAL(11, 120, 5), // "start"
QT_MOC_LITERAL(12, 126, 4), // "stop"
QT_MOC_LITERAL(13, 131, 19), // "SDL_Refersh_Windows"
QT_MOC_LITERAL(14, 151, 8), // "in_width"
QT_MOC_LITERAL(15, 160, 9), // "in_height"
QT_MOC_LITERAL(16, 170, 19) // "SDL_Windows_Changed"

    },
    "SDL_Play\0SDL_Windows_Show\0\0SDL_Renderer*\0"
    "in_render\0SDL_Texture*\0in_texture\0"
    "quint8*\0in_imageData\0SDL_Windows_Init\0"
    "inType\0start\0stop\0SDL_Refersh_Windows\0"
    "in_width\0in_height\0SDL_Windows_Changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SDL_Play[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,
      11,    0,   54,    2, 0x0a /* Public */,
      12,    0,   55,    2, 0x0a /* Public */,
      13,    2,   56,    2, 0x0a /* Public */,
      16,    2,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,

       0        // eod
};

void SDL_Play::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SDL_Play *_t = static_cast<SDL_Play *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SDL_Windows_Show((*reinterpret_cast< SDL_Renderer*(*)>(_a[1])),(*reinterpret_cast< SDL_Texture*(*)>(_a[2])),(*reinterpret_cast< quint8*(*)>(_a[3]))); break;
        case 1: _t->SDL_Windows_Init((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->start(); break;
        case 3: _t->stop(); break;
        case 4: _t->SDL_Refersh_Windows((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->SDL_Windows_Changed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SDL_Play::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SDL_Play.data,
      qt_meta_data_SDL_Play,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SDL_Play::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SDL_Play::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SDL_Play.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SDL_Play::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
struct qt_meta_stringdata_RTSPRecord_t {
    QByteArrayData data[27];
    char stringdata0[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RTSPRecord_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RTSPRecord_t qt_meta_stringdata_RTSPRecord = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RTSPRecord"
QT_MOC_LITERAL(1, 11, 5), // "Start"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "filename"
QT_MOC_LITERAL(4, 27, 11), // "Packet_init"
QT_MOC_LITERAL(5, 39, 16), // "AVFormatContext*"
QT_MOC_LITERAL(6, 56, 14), // "i_FrameContext"
QT_MOC_LITERAL(7, 71, 14), // "o_FrameContext"
QT_MOC_LITERAL(8, 86, 11), // "const char*"
QT_MOC_LITERAL(9, 98, 6), // "o_file"
QT_MOC_LITERAL(10, 105, 18), // "Update_VideoStream"
QT_MOC_LITERAL(11, 124, 15), // "in_FrameContext"
QT_MOC_LITERAL(12, 140, 9), // "AVPacket*"
QT_MOC_LITERAL(13, 150, 6), // "in_pkt"
QT_MOC_LITERAL(14, 157, 10), // "Frame_init"
QT_MOC_LITERAL(15, 168, 10), // "videoindex"
QT_MOC_LITERAL(16, 179, 3), // "URL"
QT_MOC_LITERAL(17, 183, 12), // "Out_Put_init"
QT_MOC_LITERAL(18, 196, 17), // "AVFormatContext*&"
QT_MOC_LITERAL(19, 214, 4), // "int&"
QT_MOC_LITERAL(20, 219, 16), // "out_FrameContext"
QT_MOC_LITERAL(21, 236, 12), // "out_filename"
QT_MOC_LITERAL(22, 249, 10), // "AVStream*&"
QT_MOC_LITERAL(23, 260, 10), // "outVStream"
QT_MOC_LITERAL(24, 271, 4), // "Stop"
QT_MOC_LITERAL(25, 276, 12), // "Write_Packet"
QT_MOC_LITERAL(26, 289, 9) // "AVStream*"

    },
    "RTSPRecord\0Start\0\0filename\0Packet_init\0"
    "AVFormatContext*\0i_FrameContext\0"
    "o_FrameContext\0const char*\0o_file\0"
    "Update_VideoStream\0in_FrameContext\0"
    "AVPacket*\0in_pkt\0Frame_init\0videoindex\0"
    "URL\0Out_Put_init\0AVFormatContext*&\0"
    "int&\0out_FrameContext\0out_filename\0"
    "AVStream*&\0outVStream\0Stop\0Write_Packet\0"
    "AVStream*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RTSPRecord[] = {

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
       1,    1,   49,    2, 0x0a /* Public */,
       4,    3,   52,    2, 0x0a /* Public */,
      10,    2,   59,    2, 0x0a /* Public */,
      14,    3,   64,    2, 0x0a /* Public */,
      17,    5,   71,    2, 0x0a /* Public */,
      24,    0,   82,    2, 0x0a /* Public */,
      25,    4,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 8,    6,    7,    9,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 12,   11,   13,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int, 0x80000000 | 8,   11,   15,   16,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 19, 0x80000000 | 18, 0x80000000 | 8, 0x80000000 | 22,   11,   15,   20,   21,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, QMetaType::Int, 0x80000000 | 26,   11,   20,   15,   23,

       0        // eod
};

void RTSPRecord::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RTSPRecord *_t = static_cast<RTSPRecord *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Start((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Packet_init((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< AVFormatContext*(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3]))); break;
        case 2: _t->Update_VideoStream((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< AVPacket*(*)>(_a[2]))); break;
        case 3: _t->Frame_init((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3]))); break;
        case 4: _t->Out_Put_init((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< AVFormatContext*(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4])),(*reinterpret_cast< AVStream*(*)>(_a[5]))); break;
        case 5: _t->Stop(); break;
        case 6: _t->Write_Packet((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< AVFormatContext*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< AVStream*(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject RTSPRecord::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RTSPRecord.data,
      qt_meta_data_RTSPRecord,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RTSPRecord::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RTSPRecord::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RTSPRecord.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RTSPRecord::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
