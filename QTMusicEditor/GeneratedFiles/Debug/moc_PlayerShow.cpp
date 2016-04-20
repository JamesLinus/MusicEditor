/****************************************************************************
** Meta object code from reading C++ file 'PlayerShow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PlayerShow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlayerShow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayerShow_t {
    QByteArrayData data[19];
    char stringdata[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerShow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerShow_t qt_meta_stringdata_PlayerShow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlayerShow"
QT_MOC_LITERAL(1, 11, 4), // "play"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 5), // "pause"
QT_MOC_LITERAL(4, 23, 8), // "openFile"
QT_MOC_LITERAL(5, 32, 14), // "updatePosition"
QT_MOC_LITERAL(6, 47, 8), // "position"
QT_MOC_LITERAL(7, 56, 14), // "updateDuration"
QT_MOC_LITERAL(8, 71, 8), // "duration"
QT_MOC_LITERAL(9, 80, 11), // "setPosition"
QT_MOC_LITERAL(10, 92, 10), // "updateInfo"
QT_MOC_LITERAL(11, 103, 9), // "setVolume"
QT_MOC_LITERAL(12, 113, 6), // "volume"
QT_MOC_LITERAL(13, 120, 20), // "forwardMusic_clicked"
QT_MOC_LITERAL(14, 141, 21), // "backwardMusic_clicked"
QT_MOC_LITERAL(15, 163, 9), // "setRate25"
QT_MOC_LITERAL(16, 173, 9), // "setRate50"
QT_MOC_LITERAL(17, 183, 9), // "setRate75"
QT_MOC_LITERAL(18, 193, 10) // "setRate100"

    },
    "PlayerShow\0play\0\0pause\0openFile\0"
    "updatePosition\0position\0updateDuration\0"
    "duration\0setPosition\0updateInfo\0"
    "setVolume\0volume\0forwardMusic_clicked\0"
    "backwardMusic_clicked\0setRate25\0"
    "setRate50\0setRate75\0setRate100"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerShow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x09 /* Protected */,
       3,    0,   85,    2, 0x09 /* Protected */,
       4,    0,   86,    2, 0x09 /* Protected */,
       5,    1,   87,    2, 0x09 /* Protected */,
       7,    1,   90,    2, 0x09 /* Protected */,
       9,    1,   93,    2, 0x09 /* Protected */,
      10,    0,   96,    2, 0x09 /* Protected */,
      11,    1,   97,    2, 0x09 /* Protected */,
      13,    0,  100,    2, 0x09 /* Protected */,
      14,    0,  101,    2, 0x09 /* Protected */,
      15,    0,  102,    2, 0x09 /* Protected */,
      16,    0,  103,    2, 0x09 /* Protected */,
      17,    0,  104,    2, 0x09 /* Protected */,
      18,    0,  105,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayerShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerShow *_t = static_cast<PlayerShow *>(_o);
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->pause(); break;
        case 2: _t->openFile(); break;
        case 3: _t->updatePosition((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->updateDuration((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->setPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateInfo(); break;
        case 7: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->forwardMusic_clicked(); break;
        case 9: _t->backwardMusic_clicked(); break;
        case 10: _t->setRate25(); break;
        case 11: _t->setRate50(); break;
        case 12: _t->setRate75(); break;
        case 13: _t->setRate100(); break;
        default: ;
        }
    }
}

const QMetaObject PlayerShow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayerShow.data,
      qt_meta_data_PlayerShow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayerShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerShow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerShow.stringdata))
        return static_cast<void*>(const_cast< PlayerShow*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayerShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
