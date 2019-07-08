/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionLyrics;
    QAction *actionNext;
    QAction *actionPrevious;
    QAction *actionVolume_Up;
    QAction *actionVolume_Down;
    QAction *actionPlay;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *rewind_button;
    QPushButton *play_button;
    QPushButton *forward_button;
    QSlider *seek_slider;
    QLabel *artist_name_Label;
    QLabel *song_name_label;
    QLabel *label;
    QLabel *current_time_label;
    QLabel *total_time_label;
    QSlider *volume_slider;
    QListView *listView;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuPlayback;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(509, 441);
        MainWindow->setTabShape(QTabWidget::Triangular);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionLyrics = new QAction(MainWindow);
        actionLyrics->setObjectName(QStringLiteral("actionLyrics"));
        actionNext = new QAction(MainWindow);
        actionNext->setObjectName(QStringLiteral("actionNext"));
        actionPrevious = new QAction(MainWindow);
        actionPrevious->setObjectName(QStringLiteral("actionPrevious"));
        actionVolume_Up = new QAction(MainWindow);
        actionVolume_Up->setObjectName(QStringLiteral("actionVolume_Up"));
        actionVolume_Down = new QAction(MainWindow);
        actionVolume_Down->setObjectName(QStringLiteral("actionVolume_Down"));
        actionPlay = new QAction(MainWindow);
        actionPlay->setObjectName(QStringLiteral("actionPlay"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(150, 290, 111, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rewind_button = new QPushButton(horizontalLayoutWidget);
        rewind_button->setObjectName(QStringLiteral("rewind_button"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rewind_button->sizePolicy().hasHeightForWidth());
        rewind_button->setSizePolicy(sizePolicy);
        rewind_button->setMinimumSize(QSize(32, 32));
        rewind_button->setMaximumSize(QSize(32, 32));
        rewind_button->setStyleSheet(QLatin1String("border: none;\n"
"outline:none;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/skip_previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        rewind_button->setIcon(icon);
        rewind_button->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(rewind_button);

        play_button = new QPushButton(horizontalLayoutWidget);
        play_button->setObjectName(QStringLiteral("play_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(play_button->sizePolicy().hasHeightForWidth());
        play_button->setSizePolicy(sizePolicy1);
        play_button->setMinimumSize(QSize(32, 32));
        play_button->setMaximumSize(QSize(32, 32));
        play_button->setStyleSheet(QLatin1String("border: none;\n"
"outline:none;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/resources/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/resources/pause.png"), QSize(), QIcon::Normal, QIcon::On);
        play_button->setIcon(icon1);
        play_button->setIconSize(QSize(32, 32));
        play_button->setCheckable(true);

        horizontalLayout->addWidget(play_button);

        forward_button = new QPushButton(horizontalLayoutWidget);
        forward_button->setObjectName(QStringLiteral("forward_button"));
        sizePolicy1.setHeightForWidth(forward_button->sizePolicy().hasHeightForWidth());
        forward_button->setSizePolicy(sizePolicy1);
        forward_button->setMinimumSize(QSize(32, 32));
        forward_button->setMaximumSize(QSize(32, 32));
        forward_button->setStyleSheet(QLatin1String("border: none;\n"
"outline:none;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/resources/skip_forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        forward_button->setIcon(icon2);
        forward_button->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(forward_button);

        seek_slider = new QSlider(centralWidget);
        seek_slider->setObjectName(QStringLiteral("seek_slider"));
        seek_slider->setGeometry(QRect(10, 350, 276, 16));
        seek_slider->setOrientation(Qt::Horizontal);
        artist_name_Label = new QLabel(centralWidget);
        artist_name_Label->setObjectName(QStringLiteral("artist_name_Label"));
        artist_name_Label->setGeometry(QRect(20, 310, 121, 20));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(artist_name_Label->sizePolicy().hasHeightForWidth());
        artist_name_Label->setSizePolicy(sizePolicy2);
        song_name_label = new QLabel(centralWidget);
        song_name_label->setObjectName(QStringLiteral("song_name_label"));
        song_name_label->setGeometry(QRect(20, 290, 121, 20));
        sizePolicy2.setHeightForWidth(song_name_label->sizePolicy().hasHeightForWidth());
        song_name_label->setSizePolicy(sizePolicy2);
        song_name_label->setScaledContents(true);
        song_name_label->setWordWrap(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 256, 256));
        label->setPixmap(QPixmap(QString::fromUtf8(":/resources/missing.png")));
        label->setScaledContents(true);
        current_time_label = new QLabel(centralWidget);
        current_time_label->setObjectName(QStringLiteral("current_time_label"));
        current_time_label->setGeometry(QRect(10, 370, 47, 13));
        total_time_label = new QLabel(centralWidget);
        total_time_label->setObjectName(QStringLiteral("total_time_label"));
        total_time_label->setGeometry(QRect(240, 370, 47, 13));
        total_time_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        volume_slider = new QSlider(centralWidget);
        volume_slider->setObjectName(QStringLiteral("volume_slider"));
        volume_slider->setGeometry(QRect(270, 289, 20, 51));
        volume_slider->setOrientation(Qt::Vertical);
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(300, 20, 200, 361));
        listView->setAcceptDrops(true);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setDragEnabled(false);
        listView->setDragDropOverwriteMode(false);
        listView->setDragDropMode(QAbstractItemView::DropOnly);
        listView->setDefaultDropAction(Qt::TargetMoveAction);
        listView->setMovement(QListView::Static);
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(520, 20, 256, 192));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 509, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuPlayback = new QMenu(menuBar);
        menuPlayback->setObjectName(QStringLiteral("menuPlayback"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuPlayback->menuAction());
        menuFile->addAction(actionOpen);
        menuView->addAction(actionLyrics);
        menuPlayback->addSeparator();
        menuPlayback->addAction(actionNext);
        menuPlayback->addAction(actionPrevious);
        menuPlayback->addSeparator();
        menuPlayback->addAction(actionVolume_Up);
        menuPlayback->addAction(actionVolume_Down);
        menuPlayback->addSeparator();
        menuPlayback->addAction(actionPlay);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "WS_Player", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionLyrics->setText(QApplication::translate("MainWindow", "Lyrics", nullptr));
        actionNext->setText(QApplication::translate("MainWindow", "Next (Ctrl+Right)", nullptr));
        actionPrevious->setText(QApplication::translate("MainWindow", "Previous (Ctrl+Left)", nullptr));
        actionVolume_Up->setText(QApplication::translate("MainWindow", "Volume Up (Ctrl+Up)", nullptr));
        actionVolume_Down->setText(QApplication::translate("MainWindow", "Volume Down (Ctrl+Down)", nullptr));
        actionPlay->setText(QApplication::translate("MainWindow", "Play", nullptr));
        rewind_button->setText(QString());
        play_button->setText(QString());
        forward_button->setText(QString());
        artist_name_Label->setText(QApplication::translate("MainWindow", "Artist Name", nullptr));
        song_name_label->setText(QApplication::translate("MainWindow", "Song Name", nullptr));
        label->setText(QString());
        current_time_label->setText(QApplication::translate("MainWindow", "0:00", nullptr));
        total_time_label->setText(QApplication::translate("MainWindow", "0:00", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
        menuPlayback->setTitle(QApplication::translate("MainWindow", "Playback", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
