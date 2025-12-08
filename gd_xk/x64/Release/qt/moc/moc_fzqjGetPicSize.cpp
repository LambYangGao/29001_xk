/****************************************************************************
** Meta object code from reading C++ file 'fzqjGetPicSize.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../fzqjGetPicSize.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fzqjGetPicSize.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_fzqjGetPicSize_t {
    QByteArrayData data[20];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fzqjGetPicSize_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fzqjGetPicSize_t qt_meta_stringdata_fzqjGetPicSize = {
    {
QT_MOC_LITERAL(0, 0, 14), // "fzqjGetPicSize"
QT_MOC_LITERAL(1, 15, 26), // "on_btnImageRefresh_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 14), // "updateImageMat"
QT_MOC_LITERAL(4, 58, 7), // "cv::Mat"
QT_MOC_LITERAL(5, 66, 9), // "in_mat_vi"
QT_MOC_LITERAL(6, 76, 9), // "in_mat_ir"
QT_MOC_LITERAL(7, 86, 19), // "updatePainterSizeVi"
QT_MOC_LITERAL(8, 106, 7), // "startPT"
QT_MOC_LITERAL(9, 114, 5), // "endPT"
QT_MOC_LITERAL(10, 120, 5), // "width"
QT_MOC_LITERAL(11, 126, 6), // "height"
QT_MOC_LITERAL(12, 133, 19), // "updatePainterSizeIr"
QT_MOC_LITERAL(13, 153, 19), // "on_btnCount_clicked"
QT_MOC_LITERAL(14, 173, 20), // "updateCurrentStateVi"
QT_MOC_LITERAL(15, 194, 13), // "current_state"
QT_MOC_LITERAL(16, 208, 20), // "updateCurrentStateIr"
QT_MOC_LITERAL(17, 229, 17), // "updateFocalLength"
QT_MOC_LITERAL(18, 247, 6), // "vi_num"
QT_MOC_LITERAL(19, 254, 6) // "ir_num"

    },
    "fzqjGetPicSize\0on_btnImageRefresh_clicked\0"
    "\0updateImageMat\0cv::Mat\0in_mat_vi\0"
    "in_mat_ir\0updatePainterSizeVi\0startPT\0"
    "endPT\0width\0height\0updatePainterSizeIr\0"
    "on_btnCount_clicked\0updateCurrentStateVi\0"
    "current_state\0updateCurrentStateIr\0"
    "updateFocalLength\0vi_num\0ir_num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fzqjGetPicSize[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    2,   55,    2, 0x0a /* Public */,
       7,    4,   60,    2, 0x0a /* Public */,
      12,    4,   69,    2, 0x0a /* Public */,
      13,    0,   78,    2, 0x0a /* Public */,
      14,    1,   79,    2, 0x0a /* Public */,
      16,    1,   82,    2, 0x0a /* Public */,
      17,    2,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::Float, QMetaType::Float,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::Float, QMetaType::Float,    8,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,

       0        // eod
};

void fzqjGetPicSize::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fzqjGetPicSize *_t = static_cast<fzqjGetPicSize *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnImageRefresh_clicked(); break;
        case 1: _t->updateImageMat((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2]))); break;
        case 2: _t->updatePainterSizeVi((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 3: _t->updatePainterSizeIr((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 4: _t->on_btnCount_clicked(); break;
        case 5: _t->updateCurrentStateVi((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->updateCurrentStateIr((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->updateFocalLength((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject fzqjGetPicSize::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fzqjGetPicSize.data,
      qt_meta_data_fzqjGetPicSize,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *fzqjGetPicSize::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fzqjGetPicSize::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_fzqjGetPicSize.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int fzqjGetPicSize::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
