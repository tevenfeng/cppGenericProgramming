/****************************************************************************
** Meta object code from reading C++ file 'gonet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gonet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gonet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gonet_t {
    QByteArrayData data[15];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gonet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gonet_t qt_meta_stringdata_gonet = {
    {
QT_MOC_LITERAL(0, 0, 5), // "gonet"
QT_MOC_LITERAL(1, 6, 11), // "itemClicked"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 5), // "index"
QT_MOC_LITERAL(4, 25, 12), // "goBtnClicked"
QT_MOC_LITERAL(5, 38, 3), // "arg"
QT_MOC_LITERAL(6, 42, 14), // "fiveBtnClicked"
QT_MOC_LITERAL(7, 57, 11), // "agreeToPlay"
QT_MOC_LITERAL(8, 69, 6), // "string"
QT_MOC_LITERAL(9, 76, 8), // "remoteIp"
QT_MOC_LITERAL(10, 85, 7), // "localIp"
QT_MOC_LITERAL(11, 93, 9), // "chessType"
QT_MOC_LITERAL(12, 103, 21), // "afterGameWindowClosed"
QT_MOC_LITERAL(13, 125, 6), // "Action"
QT_MOC_LITERAL(14, 132, 4) // "data"

    },
    "gonet\0itemClicked\0\0index\0goBtnClicked\0"
    "arg\0fiveBtnClicked\0agreeToPlay\0string\0"
    "remoteIp\0localIp\0chessType\0"
    "afterGameWindowClosed\0Action\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gonet[] = {

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
       1,    1,   44,    2, 0x0a /* Public */,
       4,    1,   47,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       7,    3,   53,    2, 0x0a /* Public */,
      12,    0,   60,    2, 0x0a /* Public */,
      13,    1,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8, QMetaType::Bool,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,   14,

       0        // eod
};

void gonet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gonet *_t = static_cast<gonet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->goBtnClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->fiveBtnClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->agreeToPlay((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: _t->afterGameWindowClosed(); break;
        case 5: _t->Action((*reinterpret_cast< string(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject gonet::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_gonet.data,
      qt_meta_data_gonet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *gonet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gonet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_gonet.stringdata0))
        return static_cast<void*>(const_cast< gonet*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int gonet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
