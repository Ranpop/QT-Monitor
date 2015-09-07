/****************************************************************************
** Meta object code from reading C++ file 'mapwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graphics/mapwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MapWidget_t {
    QByteArrayData data[8];
    char stringdata[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MapWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MapWidget_t qt_meta_stringdata_MapWidget = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 6),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 10),
QT_MOC_LITERAL(4, 29, 11),
QT_MOC_LITERAL(5, 41, 8),
QT_MOC_LITERAL(6, 50, 16),
QT_MOC_LITERAL(7, 67, 14)
    },
    "MapWidget\0setCmd\0\0updateData\0GetDataType\0"
    "dataType\0emergencyStopCmd\0updateDataSlot\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x0a,
       6,    0,   38,    2, 0x0a,
       7,    0,   39,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MapWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapWidget *_t = static_cast<MapWidget *>(_o);
        switch (_id) {
        case 0: _t->setCmd(); break;
        case 1: _t->updateData((*reinterpret_cast< GetDataType(*)>(_a[1]))); break;
        case 2: _t->emergencyStopCmd(); break;
        case 3: _t->updateDataSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MapWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapWidget::setCmd)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MapWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_MapWidget.data,
      qt_meta_data_MapWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *MapWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapWidget.stringdata))
        return static_cast<void*>(const_cast< MapWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int MapWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
void MapWidget::setCmd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
