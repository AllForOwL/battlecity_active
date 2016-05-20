/****************************************************************************
** Meta object code from reading C++ file 'battlecitymap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BattleCity/battlecitymap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'battlecitymap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BattleCityMap_t {
    QByteArrayData data[53];
    char stringdata0[853];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BattleCityMap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BattleCityMap_t qt_meta_stringdata_BattleCityMap = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BattleCityMap"
QT_MOC_LITERAL(1, 14, 22), // "signalTimeoutForOneBot"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 22), // "signalTimeoutForTwoBot"
QT_MOC_LITERAL(4, 61, 5), // "xBase"
QT_MOC_LITERAL(5, 67, 5), // "yBase"
QT_MOC_LITERAL(6, 73, 24), // "signalTimeoutForThreeBot"
QT_MOC_LITERAL(7, 98, 7), // "xPlayer"
QT_MOC_LITERAL(8, 106, 7), // "yPlayer"
QT_MOC_LITERAL(9, 114, 23), // "signalTimeoutForFourBot"
QT_MOC_LITERAL(10, 138, 16), // "signalMoveOneBot"
QT_MOC_LITERAL(11, 155, 16), // "signalMoveTwoBot"
QT_MOC_LITERAL(12, 172, 18), // "signalMoveThreeBot"
QT_MOC_LITERAL(13, 191, 1), // "x"
QT_MOC_LITERAL(14, 193, 1), // "y"
QT_MOC_LITERAL(15, 195, 17), // "signalMoveFourBot"
QT_MOC_LITERAL(16, 213, 16), // "signalUpdateBase"
QT_MOC_LITERAL(17, 230, 8), // "typeWall"
QT_MOC_LITERAL(18, 239, 14), // "signalGameOver"
QT_MOC_LITERAL(19, 254, 20), // "numberKillsOnePlayer"
QT_MOC_LITERAL(20, 275, 20), // "numberKillsTwoPlayer"
QT_MOC_LITERAL(21, 296, 25), // "signalKillBotForStatistic"
QT_MOC_LITERAL(22, 322, 19), // "signalShowNextLevel"
QT_MOC_LITERAL(23, 342, 26), // "signalKillTankForStatistic"
QT_MOC_LITERAL(24, 369, 12), // "slotAddBot_1"
QT_MOC_LITERAL(25, 382, 12), // "slotAddBot_2"
QT_MOC_LITERAL(26, 395, 12), // "slotAddBot_3"
QT_MOC_LITERAL(27, 408, 12), // "slotAddBot_4"
QT_MOC_LITERAL(28, 421, 13), // "slotShowBonus"
QT_MOC_LITERAL(29, 435, 15), // "slotRemoveBonus"
QT_MOC_LITERAL(30, 451, 22), // "slotShowProtectionBase"
QT_MOC_LITERAL(31, 474, 26), // "slotBuildProtectionForBase"
QT_MOC_LITERAL(32, 501, 22), // "slotRemoveBonusForBase"
QT_MOC_LITERAL(33, 524, 17), // "slotShowTimeBonus"
QT_MOC_LITERAL(34, 542, 15), // "slotStopAllBots"
QT_MOC_LITERAL(35, 558, 27), // "slotRemoveBonusForTimeBonus"
QT_MOC_LITERAL(36, 586, 22), // "slotShowExplosionBonus"
QT_MOC_LITERAL(37, 609, 24), // "slotRemoveExplosionBonus"
QT_MOC_LITERAL(38, 634, 29), // "slotRemoveExplosionBonusTimer"
QT_MOC_LITERAL(39, 664, 13), // "slotRunOneBot"
QT_MOC_LITERAL(40, 678, 13), // "slotRunTwoBot"
QT_MOC_LITERAL(41, 692, 15), // "slotRunThreeBot"
QT_MOC_LITERAL(42, 708, 14), // "slotRunFourBot"
QT_MOC_LITERAL(43, 723, 16), // "slotMoveThreeBot"
QT_MOC_LITERAL(44, 740, 15), // "slotMoveFourBot"
QT_MOC_LITERAL(45, 756, 12), // "slotGameOver"
QT_MOC_LITERAL(46, 769, 23), // "slotSetPosPlayerForSend"
QT_MOC_LITERAL(47, 793, 16), // "slotMoveOpponent"
QT_MOC_LITERAL(48, 810, 6), // "rotate"
QT_MOC_LITERAL(49, 817, 5), // "shot2"
QT_MOC_LITERAL(50, 823, 12), // "slotShotTank"
QT_MOC_LITERAL(51, 836, 3), // "str"
QT_MOC_LITERAL(52, 840, 12) // "slotKillTank"

    },
    "BattleCityMap\0signalTimeoutForOneBot\0"
    "\0signalTimeoutForTwoBot\0xBase\0yBase\0"
    "signalTimeoutForThreeBot\0xPlayer\0"
    "yPlayer\0signalTimeoutForFourBot\0"
    "signalMoveOneBot\0signalMoveTwoBot\0"
    "signalMoveThreeBot\0x\0y\0signalMoveFourBot\0"
    "signalUpdateBase\0typeWall\0signalGameOver\0"
    "numberKillsOnePlayer\0numberKillsTwoPlayer\0"
    "signalKillBotForStatistic\0signalShowNextLevel\0"
    "signalKillTankForStatistic\0slotAddBot_1\0"
    "slotAddBot_2\0slotAddBot_3\0slotAddBot_4\0"
    "slotShowBonus\0slotRemoveBonus\0"
    "slotShowProtectionBase\0"
    "slotBuildProtectionForBase\0"
    "slotRemoveBonusForBase\0slotShowTimeBonus\0"
    "slotStopAllBots\0slotRemoveBonusForTimeBonus\0"
    "slotShowExplosionBonus\0slotRemoveExplosionBonus\0"
    "slotRemoveExplosionBonusTimer\0"
    "slotRunOneBot\0slotRunTwoBot\0slotRunThreeBot\0"
    "slotRunFourBot\0slotMoveThreeBot\0"
    "slotMoveFourBot\0slotGameOver\0"
    "slotSetPosPlayerForSend\0slotMoveOpponent\0"
    "rotate\0shot2\0slotShotTank\0str\0"
    "slotKillTank"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BattleCityMap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  219,    2, 0x06 /* Public */,
       3,    0,  220,    2, 0x06 /* Public */,
       1,    2,  221,    2, 0x06 /* Public */,
       3,    2,  226,    2, 0x06 /* Public */,
       6,    2,  231,    2, 0x06 /* Public */,
       9,    2,  236,    2, 0x06 /* Public */,
      10,    0,  241,    2, 0x06 /* Public */,
      11,    0,  242,    2, 0x06 /* Public */,
      12,    2,  243,    2, 0x06 /* Public */,
      15,    2,  248,    2, 0x06 /* Public */,
      16,    1,  253,    2, 0x06 /* Public */,
      18,    2,  256,    2, 0x06 /* Public */,
      21,    0,  261,    2, 0x06 /* Public */,
      22,    0,  262,    2, 0x06 /* Public */,
      23,    0,  263,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    0,  264,    2, 0x0a /* Public */,
      25,    0,  265,    2, 0x0a /* Public */,
      26,    0,  266,    2, 0x0a /* Public */,
      27,    0,  267,    2, 0x0a /* Public */,
      28,    0,  268,    2, 0x0a /* Public */,
      29,    0,  269,    2, 0x0a /* Public */,
      30,    0,  270,    2, 0x0a /* Public */,
      31,    0,  271,    2, 0x0a /* Public */,
      32,    0,  272,    2, 0x0a /* Public */,
      33,    0,  273,    2, 0x0a /* Public */,
      34,    0,  274,    2, 0x0a /* Public */,
      35,    0,  275,    2, 0x0a /* Public */,
      36,    0,  276,    2, 0x0a /* Public */,
      37,    0,  277,    2, 0x0a /* Public */,
      38,    0,  278,    2, 0x0a /* Public */,
      39,    0,  279,    2, 0x0a /* Public */,
      40,    0,  280,    2, 0x0a /* Public */,
      41,    0,  281,    2, 0x0a /* Public */,
      42,    0,  282,    2, 0x0a /* Public */,
      43,    0,  283,    2, 0x0a /* Public */,
      44,    0,  284,    2, 0x0a /* Public */,
      45,    0,  285,    2, 0x0a /* Public */,
      46,    0,  286,    2, 0x0a /* Public */,
      47,    4,  287,    2, 0x0a /* Public */,
      50,    1,  296,    2, 0x0a /* Public */,
      52,    0,  299,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   13,   14,   48,   49,
    QMetaType::Void, QMetaType::QString,   51,
    QMetaType::Void,

       0        // eod
};

void BattleCityMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BattleCityMap *_t = static_cast<BattleCityMap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalTimeoutForOneBot(); break;
        case 1: _t->signalTimeoutForTwoBot(); break;
        case 2: _t->signalTimeoutForOneBot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->signalTimeoutForTwoBot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->signalTimeoutForThreeBot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->signalTimeoutForFourBot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->signalMoveOneBot(); break;
        case 7: _t->signalMoveTwoBot(); break;
        case 8: _t->signalMoveThreeBot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->signalMoveFourBot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->signalUpdateBase((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->signalGameOver((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->signalKillBotForStatistic(); break;
        case 13: _t->signalShowNextLevel(); break;
        case 14: _t->signalKillTankForStatistic(); break;
        case 15: _t->slotAddBot_1(); break;
        case 16: _t->slotAddBot_2(); break;
        case 17: _t->slotAddBot_3(); break;
        case 18: _t->slotAddBot_4(); break;
        case 19: _t->slotShowBonus(); break;
        case 20: _t->slotRemoveBonus(); break;
        case 21: _t->slotShowProtectionBase(); break;
        case 22: _t->slotBuildProtectionForBase(); break;
        case 23: _t->slotRemoveBonusForBase(); break;
        case 24: _t->slotShowTimeBonus(); break;
        case 25: _t->slotStopAllBots(); break;
        case 26: _t->slotRemoveBonusForTimeBonus(); break;
        case 27: _t->slotShowExplosionBonus(); break;
        case 28: _t->slotRemoveExplosionBonus(); break;
        case 29: _t->slotRemoveExplosionBonusTimer(); break;
        case 30: _t->slotRunOneBot(); break;
        case 31: _t->slotRunTwoBot(); break;
        case 32: _t->slotRunThreeBot(); break;
        case 33: _t->slotRunFourBot(); break;
        case 34: _t->slotMoveThreeBot(); break;
        case 35: _t->slotMoveFourBot(); break;
        case 36: _t->slotGameOver(); break;
        case 37: _t->slotSetPosPlayerForSend(); break;
        case 38: _t->slotMoveOpponent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 39: _t->slotShotTank((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->slotKillTank(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BattleCityMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalTimeoutForOneBot)) {
                *result = 0;
            }
        }
        {
            typedef void (BattleCityMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalTimeoutForTwoBot)) {
                *result = 1;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalTimeoutForOneBot)) {
                *result = 2;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalTimeoutForTwoBot)) {
                *result = 3;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalTimeoutForThreeBot)) {
                *result = 4;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalTimeoutForFourBot)) {
                *result = 5;
            }
        }
        {
            typedef void (BattleCityMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalMoveOneBot)) {
                *result = 6;
            }
        }
        {
            typedef void (BattleCityMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalMoveTwoBot)) {
                *result = 7;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalMoveThreeBot)) {
                *result = 8;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalMoveFourBot)) {
                *result = 9;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalUpdateBase)) {
                *result = 10;
            }
        }
        {
            typedef void (BattleCityMap::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalGameOver)) {
                *result = 11;
            }
        }
        {
            typedef void (BattleCityMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalKillBotForStatistic)) {
                *result = 12;
            }
        }
        {
            typedef void (BattleCityMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalShowNextLevel)) {
                *result = 13;
            }
        }
        {
            typedef void (BattleCityMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BattleCityMap::signalKillTankForStatistic)) {
                *result = 14;
            }
        }
    }
}

const QMetaObject BattleCityMap::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_BattleCityMap.data,
      qt_meta_data_BattleCityMap,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BattleCityMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BattleCityMap::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BattleCityMap.stringdata0))
        return static_cast<void*>(const_cast< BattleCityMap*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int BattleCityMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void BattleCityMap::signalTimeoutForOneBot()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void BattleCityMap::signalTimeoutForTwoBot()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void BattleCityMap::signalTimeoutForOneBot(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BattleCityMap::signalTimeoutForTwoBot(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BattleCityMap::signalTimeoutForThreeBot(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BattleCityMap::signalTimeoutForFourBot(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void BattleCityMap::signalMoveOneBot()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void BattleCityMap::signalMoveTwoBot()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void BattleCityMap::signalMoveThreeBot(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void BattleCityMap::signalMoveFourBot(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void BattleCityMap::signalUpdateBase(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void BattleCityMap::signalGameOver(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void BattleCityMap::signalKillBotForStatistic()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void BattleCityMap::signalShowNextLevel()
{
    QMetaObject::activate(this, &staticMetaObject, 13, Q_NULLPTR);
}

// SIGNAL 14
void BattleCityMap::signalKillTankForStatistic()
{
    QMetaObject::activate(this, &staticMetaObject, 14, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
