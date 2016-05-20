/****************************************************************************
** Meta object code from reading C++ file 'battlecityview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BattleCity/battlecityview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'battlecityview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BattleCityView_t {
    QByteArrayData data[7];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BattleCityView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BattleCityView_t qt_meta_stringdata_BattleCityView = {
    {
QT_MOC_LITERAL(0, 0, 14), // "BattleCityView"
QT_MOC_LITERAL(1, 15, 9), // "slotClose"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "numberKillsOnePlayer"
QT_MOC_LITERAL(4, 47, 20), // "numberKillsTwoPlayer"
QT_MOC_LITERAL(5, 68, 20), // "slotKillBotStatistic"
QT_MOC_LITERAL(6, 89, 21) // "slotKillTankStatistic"

    },
    "BattleCityView\0slotClose\0\0"
    "numberKillsOnePlayer\0numberKillsTwoPlayer\0"
    "slotKillBotStatistic\0slotKillTankStatistic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BattleCityView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x0a /* Public */,
       5,    0,   34,    2, 0x0a /* Public */,
       6,    0,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BattleCityView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BattleCityView *_t = static_cast<BattleCityView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotClose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotKillBotStatistic(); break;
        case 2: _t->slotKillTankStatistic(); break;
        default: ;
        }
    }
}

const QMetaObject BattleCityView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_BattleCityView.data,
      qt_meta_data_BattleCityView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BattleCityView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BattleCityView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BattleCityView.stringdata0))
        return static_cast<void*>(const_cast< BattleCityView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int BattleCityView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
