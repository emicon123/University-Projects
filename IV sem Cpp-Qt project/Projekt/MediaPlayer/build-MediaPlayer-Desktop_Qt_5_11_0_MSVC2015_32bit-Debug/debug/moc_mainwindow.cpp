/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MediaPlayer-master/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[447];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_play_button_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 29), // "on_volume_slider_valueChanged"
QT_MOC_LITERAL(4, 65, 5), // "value"
QT_MOC_LITERAL(5, 71, 26), // "on_seek_slider_sliderMoved"
QT_MOC_LITERAL(6, 98, 8), // "position"
QT_MOC_LITERAL(7, 107, 29), // "on_seek_slider_sliderReleased"
QT_MOC_LITERAL(8, 137, 28), // "on_seek_slider_sliderPressed"
QT_MOC_LITERAL(9, 166, 25), // "on_listView_doubleClicked"
QT_MOC_LITERAL(10, 192, 11), // "QModelIndex"
QT_MOC_LITERAL(11, 204, 5), // "index"
QT_MOC_LITERAL(12, 210, 25), // "on_actionLyrics_triggered"
QT_MOC_LITERAL(13, 236, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(14, 260, 25), // "on_forward_button_clicked"
QT_MOC_LITERAL(15, 286, 24), // "on_rewind_button_clicked"
QT_MOC_LITERAL(16, 311, 23), // "on_actionNext_triggered"
QT_MOC_LITERAL(17, 335, 27), // "on_actionPrevious_triggered"
QT_MOC_LITERAL(18, 363, 28), // "on_actionVolume_Up_triggered"
QT_MOC_LITERAL(19, 392, 30), // "on_actionVolume_Down_triggered"
QT_MOC_LITERAL(20, 423, 23) // "on_actionPlay_triggered"

    },
    "MainWindow\0on_play_button_clicked\0\0"
    "on_volume_slider_valueChanged\0value\0"
    "on_seek_slider_sliderMoved\0position\0"
    "on_seek_slider_sliderReleased\0"
    "on_seek_slider_sliderPressed\0"
    "on_listView_doubleClicked\0QModelIndex\0"
    "index\0on_actionLyrics_triggered\0"
    "on_actionOpen_triggered\0"
    "on_forward_button_clicked\0"
    "on_rewind_button_clicked\0"
    "on_actionNext_triggered\0"
    "on_actionPrevious_triggered\0"
    "on_actionVolume_Up_triggered\0"
    "on_actionVolume_Down_triggered\0"
    "on_actionPlay_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    1,   90,    2, 0x08 /* Private */,
       5,    1,   93,    2, 0x08 /* Private */,
       7,    0,   96,    2, 0x08 /* Private */,
       8,    0,   97,    2, 0x08 /* Private */,
       9,    1,   98,    2, 0x08 /* Private */,
      12,    0,  101,    2, 0x08 /* Private */,
      13,    0,  102,    2, 0x08 /* Private */,
      14,    0,  103,    2, 0x08 /* Private */,
      15,    0,  104,    2, 0x08 /* Private */,
      16,    0,  105,    2, 0x08 /* Private */,
      17,    0,  106,    2, 0x08 /* Private */,
      18,    0,  107,    2, 0x08 /* Private */,
      19,    0,  108,    2, 0x08 /* Private */,
      20,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_play_button_clicked(); break;
        case 1: _t->on_volume_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_seek_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_seek_slider_sliderReleased(); break;
        case 4: _t->on_seek_slider_sliderPressed(); break;
        case 5: _t->on_listView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_actionLyrics_triggered(); break;
        case 7: _t->on_actionOpen_triggered(); break;
        case 8: _t->on_forward_button_clicked(); break;
        case 9: _t->on_rewind_button_clicked(); break;
        case 10: _t->on_actionNext_triggered(); break;
        case 11: _t->on_actionPrevious_triggered(); break;
        case 12: _t->on_actionVolume_Up_triggered(); break;
        case 13: _t->on_actionVolume_Down_triggered(); break;
        case 14: _t->on_actionPlay_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
