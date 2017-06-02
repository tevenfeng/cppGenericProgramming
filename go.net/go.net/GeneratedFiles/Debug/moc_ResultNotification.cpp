/****************************************************************************
** Meta object code from reading C++ file 'ResultNotification.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ResultNotification.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ResultNotification.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ResultNotification_t {
    QByteArrayData data[6];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ResultNotification_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ResultNotification_t qt_meta_stringdata_ResultNotification = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ResultNotification"
QT_MOC_LITERAL(1, 19, 11), // "restartGame"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "exitGame"
QT_MOC_LITERAL(4, 41, 11), // "restartSlot"
QT_MOC_LITERAL(5, 53, 8) // "exitSlot"

    },
    "ResultNotification\0restartGame\0\0"
    "exitGame\0restartSlot\0exitSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ResultNotification[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ResultNotification::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ResultNotification *_t = static_cast<ResultNotification *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->restartGame(); break;
        case 1: _t->exitGame(); break;
        case 2: _t->restartSlot(); break;
        case 3: _t->exitSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ResultNotification::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ResultNotification::restartGame)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ResultNotification::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ResultNotification::exitGame)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ResultNotification::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ResultNotification.data,
      qt_meta_data_ResultNotification,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ResultNotification::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ResultNotification::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ResultNotification.stringdata0))
        return static_cast<void*>(const_cast< ResultNotification*>(this));
    return QDialog::qt_metacast(_clname);
}

int ResultNotification::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void ResultNotification::restartGame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ResultNotification::exitGame()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
