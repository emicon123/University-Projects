#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QUrl>
#include <QDebug>

// Biblioteki do multimediow
#include <QMimeData>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QDateTime>
#include <QStringListModel>
#include <QMediaPlaylist>
#include <QKeyEvent>

// Input/output plikow
#include <QFileDialog>

//
#include <string>

//
#include <util.h>
#include <songinformation.h>
#include <songlistmodel.h>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

private:

    // Kontenery, obiekty
	Ui::MainWindow* ui;
	QMediaPlayer* player;
	QMediaPlaylist* playlist;
	SongInformation* currentsong;
	std::map<QString, uint> songmap;
	std::map<QString, QString> lyricsCache;
	SongListModel* model;
	QTextEdit* lyricsWindow;

    // Pamiec podreczna niektorych elementow interfejsu uzytkownika, abysmy nie musieli ich caly czas szukac
    QAction* menuPlaybackPlay;

    // Informacje o aplikacji (buforowane do uzycia miedzy eventami) - z tej pozycji aplikacja startuje
	uint volume = 100;
	uint songPosition = 0;
	SeekState seekState = SeekState::DEFAULT;
    int playbackSpeed = 1;
    QSet<int> keysPressed;
    bool firstRelease = true;

    // Metody i logika klasy
	void Init();
	void ConfigureDefaultUI();
	void ConfigureSlots();
	void LoadFiles(QList<QUrl> urls);
	void HandleMetadata();
	void UpdateUIMetadata();
	void UpdateLyrics();
    void HandleMultiKeys(QKeyEvent* e);

    // Zasob potrzebny do obslugi pozniejszych wyjatkow

	QString LyricsCache(QString url);

    // Metody automatyczne
    void onError(QMediaPlayer::Error error);
    void onPositionChanged(qint64 position);

    // Eventy
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

protected:

    // Emitowane eventy
	private slots:
	void on_play_button_clicked();
	void on_volume_slider_valueChanged(int value);
	void on_seek_slider_sliderMoved(int position);
	void on_seek_slider_sliderReleased();
	void on_seek_slider_sliderPressed();
	void on_listView_doubleClicked(const QModelIndex& index);
	void on_actionLyrics_triggered();
	void on_actionOpen_triggered();
    void on_forward_button_clicked();
    void on_rewind_button_clicked();
    void on_actionNext_triggered();
    void on_actionPrevious_triggered();
    void on_actionVolume_Up_triggered();
    void on_actionVolume_Down_triggered();
    void on_actionPlay_triggered();
};

#endif // MAINWINDOW_H
