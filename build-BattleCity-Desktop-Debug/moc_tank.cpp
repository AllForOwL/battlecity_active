/****************************************************************************
** Meta object code from reading C++ file 'tank.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BattleCity/tank.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tank.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tank_t {
    QByteArrayData data[16];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tank_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tank_t qt_meta_stringdata_Tank = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Tank"
QT_MOC_LITERAL(1, 5, 10), // "signalShot"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 10), // "typeObject"
QT_MOC_LITERAL(4, 28, 18), // "signalTankTookStar"
QT_MOC_LITERAL(5, 47, 28), // "signalBuildProtectionForBase"
QT_MOC_LITERAL(6, 76, 17), // "signalStopAllBots"
QT_MOC_LITERAL(7, 94, 22), // "signalExplosionAllBots"
QT_MOC_LITERAL(8, 117, 15), // "signalGameOver2"
QT_MOC_LITERAL(9, 133, 18), // "signalSearchNewWay"
QT_MOC_LITERAL(10, 152, 9), // "useRotate"
QT_MOC_LITERAL(11, 162, 12), // "slotMoveTank"
QT_MOC_LITERAL(12, 175, 12), // "slotTankShot"
QT_MOC_LITERAL(13, 188, 13), // "slotAllowShot"
QT_MOC_LITERAL(14, 202, 12), // "slotGameOver"
QT_MOC_LITERAL(15, 215, 11) // "slotKillBot"

    },
    "Tank\0signalShot\0\0typeObject\0"
    "signalTankTookStar\0signalBuildProtectionForBase\0"
    "signalStopAllBots\0signalExplosionAllBots\0"
    "signalGameOver2\0signalSearchNewWay\0"
    "useRotate\0slotMoveTank\0slotTankShot\0"
    "slotAllowShot\0slotGameOver\0slotKillBot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tank[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    0,   77,    2, 0x06 /* Public */,
       5,    0,   78,    2, 0x06 /* Public */,
       6,    0,   79,    2, 0x06 /* Public */,
       7,    0,   80,    2, 0x06 /* Public */,
       8,    0,   81,    2, 0x06 /* Public */,
       9,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   85,    2, 0x0a /* Public */,
      12,    1,   86,    2, 0x0a /* Public */,
      13,    0,   89,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x0a /* Public */,
      15,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tank::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tank *_t = static_cast<Tank *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalShot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalTankTookStar(); break;
        case 2: _t->signalBuildProtectionForBase(); break;
        case 3: _t->signalStopAllBots(); break;
        case 4: _t->signalExplosionAllBots(); break;
        case 5: _t->signalGameOver2(); break;
        case 6: _t->signalSearchNewWay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slotMoveTank(); break;
        case 8: _t->slotTankShot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->slotAllowShot(); break;
        case 10: _t->slotGameOver(); break;
        case 11: _t->slotKillBot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Tank::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalShot)) {
                *result = 0;
            }
        }
        {
            typedef void (Tank::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalTankTookStar)) {
                *result = 1;
            }
        }
        {
            typedef void (Tank::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalBuildProtectionForBase)) {
                *result = 2;
            }
        }
        {
            typedef void (Tank::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalStopAllBots)) {
                *result = 3;
            }
        }
        {
            typedef void (Tank::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalExplosionAllBots)) {
                *result = 4;
            }
        }
        {
            typedef void (Tank::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalGameOver2)) {
                *result = 5;
            }
        }
        {
            typedef void (Tank::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalSearchNewWay)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject Tank::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tank.data,
      qt_meta_data_Tank,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Tank::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tank::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Tank.stringdata0))
        return static_cast<void*>(const_cast< Tank*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Tank*>(this));
    return QObject::qt_metacast(_clname);
}

int Tank::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Tank::signalShot(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Tank::signalTankTookStar()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Tank::signalBuildProtectionForBase()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Tank::signalStopAllBots()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Tank::signalExplosionAllBots()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Tank::signalGameOver2()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void Tank::signalSearchNewWay(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
