/****************************************************************************
** Meta object code from reading C++ file 'plotwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graphics/plotwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_plotWidget_t {
    QByteArrayData data[10];
    char stringdata[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_plotWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_plotWidget_t qt_meta_stringdata_plotWidget = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 10),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 11),
QT_MOC_LITERAL(4, 35, 8),
QT_MOC_LITERAL(5, 44, 15),
QT_MOC_LITERAL(6, 60, 14),
QT_MOC_LITERAL(7, 75, 10),
QT_MOC_LITERAL(8, 86, 12),
QT_MOC_LITERAL(9, 99, 5)
    },
    "plotWidget\0updateData\0\0GetDataType\0"
    "dataType\0SetRealtimeData\0SetRealtimeImg\0"
    "paintEvent\0QPaintEvent*\0event\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plotWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a,
       5,    0,   37,    2, 0x08,
       6,    0,   38,    2, 0x08,
       7,    1,   39,    2, 0x08,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void plotWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        plotWidget *_t = static_cast<plotWidget *>(_o);
        switch (_id) {
        case 0: _t->updateData((*reinterpret_cast< GetDataType(*)>(_a[1]))); break;
        case 1: _t->SetRealtimeData(); break;
        case 2: _t->SetRealtimeImg(); break;
        case 3: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject plotWidget::staticMetaObject = {
    { &QCustomPlot::staticMetaObject, qt_meta_stringdata_plotWidget.data,
      qt_meta_data_plotWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *plotWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plotWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_plotWidget.stringdata))
        return static_cast<void*>(const_cast< plotWidget*>(this));
    return QCustomPlot::qt_metacast(_clname);
}

int plotWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
