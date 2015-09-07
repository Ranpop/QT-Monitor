/****************************************************************************
** Meta object code from reading C++ file 'frmmain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmmain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_frmMain_t {
    QByteArrayData data[17];
    char stringdata[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_frmMain_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_frmMain_t qt_meta_stringdata_frmMain = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 13),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 11),
QT_MOC_LITERAL(4, 35, 15),
QT_MOC_LITERAL(5, 51, 15),
QT_MOC_LITERAL(6, 67, 13),
QT_MOC_LITERAL(7, 81, 9),
QT_MOC_LITERAL(8, 91, 10),
QT_MOC_LITERAL(9, 102, 12),
QT_MOC_LITERAL(10, 115, 12),
QT_MOC_LITERAL(11, 128, 20),
QT_MOC_LITERAL(12, 149, 16),
QT_MOC_LITERAL(13, 166, 19),
QT_MOC_LITERAL(14, 186, 17),
QT_MOC_LITERAL(15, 204, 24),
QT_MOC_LITERAL(16, 229, 21)
    },
    "frmMain\0emergencyStop\0\0screen_full\0"
    "delete_plot_one\0delete_plot_all\0"
    "show_paramter\0path_edit\0path_clear\0"
    "path_operate\0path_endEdit\0"
    "path_setcurrentPoint\0path_removePoint\0"
    "on_btnClose_clicked\0on_btnMin_clicked\0"
    "on_btnAutoManual_clicked\0on_btnConnect_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmMain[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    0,   90,    2, 0x08,
       4,    0,   91,    2, 0x08,
       5,    0,   92,    2, 0x08,
       6,    0,   93,    2, 0x08,
       7,    0,   94,    2, 0x08,
       8,    0,   95,    2, 0x08,
       9,    0,   96,    2, 0x08,
      10,    0,   97,    2, 0x08,
      11,    0,   98,    2, 0x08,
      12,    0,   99,    2, 0x08,
      13,    0,  100,    2, 0x08,
      14,    0,  101,    2, 0x08,
      15,    0,  102,    2, 0x08,
      16,    0,  103,    2, 0x08,

 // signals: parameters
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

       0        // eod
};

void frmMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmMain *_t = static_cast<frmMain *>(_o);
        switch (_id) {
        case 0: _t->emergencyStop(); break;
        case 1: _t->screen_full(); break;
        case 2: _t->delete_plot_one(); break;
        case 3: _t->delete_plot_all(); break;
        case 4: _t->show_paramter(); break;
        case 5: _t->path_edit(); break;
        case 6: _t->path_clear(); break;
        case 7: _t->path_operate(); break;
        case 8: _t->path_endEdit(); break;
        case 9: _t->path_setcurrentPoint(); break;
        case 10: _t->path_removePoint(); break;
        case 11: _t->on_btnClose_clicked(); break;
        case 12: _t->on_btnMin_clicked(); break;
        case 13: _t->on_btnAutoManual_clicked(); break;
        case 14: _t->on_btnConnect_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (frmMain::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&frmMain::emergencyStop)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject frmMain::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_frmMain.data,
      qt_meta_data_frmMain,  qt_static_metacall, 0, 0}
};


const QMetaObject *frmMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_frmMain.stringdata))
        return static_cast<void*>(const_cast< frmMain*>(this));
    return QDialog::qt_metacast(_clname);
}

int frmMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void frmMain::emergencyStop()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
