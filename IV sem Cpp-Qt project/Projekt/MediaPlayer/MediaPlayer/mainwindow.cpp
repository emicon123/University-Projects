#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    Init();
}

MainWindow::~MainWindow()
{
    // Destruktor user interface
    delete ui;
}

void MainWindow::Init()
{
    // Tworzenie instancji typow
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    model = new SongListModel(this);
    lyricsWindow = new QTextEdit();

    // Podstawowe ustawienia tj. eventy i UI
    ConfigureDefaultUI();
    ConfigureSlots();
}

void MainWindow::ConfigureDefaultUI()
{
    // Ustawienie wartosci glosnosci na domyslna (100)
    ui->volume_slider->setValue(volume);

    // Ustawienie playlisty tak, aby mozna bylo przeciagac utwory automatycznie z pulpitu/folderu
    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setMovement(QListView::Snap);
    ui->listView->setDragDropMode(QAbstractItemView::InternalMove);
    ui->listView->setDragDropOverwriteMode(false);

    QMenu* playback = ui->menuBar->findChild<QMenu*>("menuPlayback");
    QList<QAction*> actions = playback->actions();
    QList<QAction*>::iterator i;
    for (i = actions.begin(); i != actions.end(); ++i) {
        if ((*i)->text() == "Play") {
            menuPlaybackPlay = (*i);
        }
    }
}

void MainWindow::ConfigureSlots()
{
    // Miejsce na błąd (wywoływane, gdy wystąpi błąd z QMediaPlayer)
    connect(player, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error),
            [=](QMediaPlayer::Error error) { onError(error); });

    // Zmieniono metadane (Wywoływane po załadowaniu nowej ścieżki itp.)
    connect(player, static_cast<void(QMediaObject::*)()>(&QMediaObject::metaDataChanged),
            [=]() { HandleMetadata(); });

    // Zmieniono pozycję sciezki dzwiekowej
    connect(player, static_cast<void(QMediaPlayer::*)(qint64)>(&QMediaPlayer::positionChanged),
            [=](qint64 position) { onPositionChanged(position); });
}

void MainWindow::LoadFiles(QList<QUrl> urls)
{
    // Lista uzywana z QListView
    QStringList List;

    // Inicjalizacja kontenerow (by nie zwracaly nullptr)
    songmap = std::map<QString, uint>();
    lyricsCache = std::map<QString, QString>();
    playlist->clear();

    // Po zrzuceniu każdego adresu URL, dodajemy go do listy i przechowujemy w kontenerze songmap
    for (int i = 0; i < urls.count(); ++i) {
        QUrl url = urls[i];
        List << url.fileName();
        songmap[url.fileName()] = i;
        playlist->addMedia(url);
    }

    model->setStringList(List);

    // Sklejanie modeli
    ui->listView->setModel(model);

    // Get the file url of the media being passed
    // Przechwytywanie adresu URL pliku, ktory zostal przekazany do odtwarzacza
    QUrl url = urls[0]; // Dostep do pierwszego z przekazanych plikow

    // Dajemy odtwarzaczowi playliste
    player->setPlaylist(playlist);
}

// Logika i metody
void MainWindow::HandleMetadata()
{
    currentsong = new SongInformation(*player);
    UpdateUIMetadata();
}

void MainWindow::UpdateUIMetadata()
{
    QImage& image = currentsong->thumbnailImage;
    QString dur = mstosms(currentsong->duration);
    QString artists = "";

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->total_time_label->setText(dur);
    ui->song_name_label->setText(currentsong->title);
    if (currentsong->albumArtist == "") {
        if (!currentsong->contributingArtist.empty()) {
            for (int index = 0; index < currentsong->contributingArtist.size(); ++index) {
                if (index == 0) {
                    artists += currentsong->contributingArtist.at(index);
                }
                else {
                    artists += (", " + currentsong->contributingArtist.at(index));
                }
            }
        }
    }
    else {
        artists = currentsong->albumArtist;
    }
    ui->artist_name_Label->setText(artists);
    ui->current_time_label->setText("00:00");
    ui->seek_slider->setMaximum(currentsong->duration);

    if (lyricsWindow->isVisible()) {
        UpdateLyrics();
    }

}

void MainWindow::UpdateLyrics()
{

    // Sprawdzanie czy są dostępne media, a nastepnie, czy jest tekst utworu
    try
    {
        if (!player->currentMedia().isNull())
        {
            if (lyricsCache[player->currentMedia().canonicalUrl().toString()] == "")
            {
                if (currentsong->lyrics == "")
                {
                    currentsong->lyrics = currentsong->FetchLyrics();
                    lyricsCache[player->currentMedia().canonicalUrl().toString()] = currentsong->lyrics;
                    lyricsWindow->setText(currentsong->lyrics);
                }
                else
                {
                    lyricsWindow->setText(currentsong->lyrics);
                }
            }
            else
            {
                currentsong->lyrics = lyricsCache[player->currentMedia().canonicalUrl().toString()];
                lyricsWindow->setText(currentsong->lyrics);
            }
        }
    }
    catch (const std::exception& er)
    {
        printf("Error: %s\n", er.what());
    }
}

void MainWindow::HandleMultiKeys(QKeyEvent* event)
{
    int key = event->key();
    switch(event->key())
    {
        case Qt::Key_Up:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            on_actionVolume_Up_triggered();
        }
            break;
        case Qt::Key_Right:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            on_actionNext_triggered();
        }
            break;
        case Qt::Key_Down:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            on_actionVolume_Down_triggered();
        }
            break;
        case Qt::Key_Left:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            on_actionPrevious_triggered();
        }
        break;
        default:
            break;
    }
}

// Pamiec podreczna
QString MainWindow::LyricsCache(QString url)
{
    std::map<QString, QString>::const_iterator iter = lyricsCache.find(url);
    if (iter != lyricsCache.end()) // Przedmiot w kontenerze map
    {
        return iter->second;
    }
    else
    {
        throw std::exception("Error: Song URL not available");
    }
}


// Obsluga zdarzen emitowanych przez QMediaPlayer i powiazane klasy
void MainWindow::onError(QMediaPlayer::Error error)
{
    qDebug() << (mediaPlayerErrorCodes[static_cast<int>(error)].c_str());
}

void MainWindow::onPositionChanged(qint64 position)
{
    ui->current_time_label->setText(mstosms(position));
    if (seekState != SeekState::MOVING && seekState != SeekState::PRESSED)
    {
        ui->seek_slider->setValue(position);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    HandleMultiKeys(event);
}

void MainWindow::dropEvent(QDropEvent* event)
{
    // Sprawdzenie, czy mamy aktualne dane z eventu drop
    if (event->mimeData()->hasUrls())
    {
        LoadFiles(event->mimeData()->urls()); // Ladowanie pliku ze zdropowanego adresu URL
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* ev)
{
    ev->accept();
}

// Miejsca zwiazane z UI
void MainWindow::on_play_button_clicked()
{
    if (!player->currentMedia().isNull())
    {
        if (!ui->play_button->isChecked())
        {
            player->pause();
            menuPlaybackPlay->setText("Play");
        }
        else
        {
            player->play();
            menuPlaybackPlay->setText("Pause");
        }
    }
    else
    {
        ui->play_button->setChecked(false);
    }
}

void MainWindow::on_volume_slider_valueChanged(int value)
{
    volume = value;
    player->setVolume(volume);
}

void MainWindow::on_seek_slider_sliderMoved(int position)
{
    songPosition = position;
    ui->current_time_label->setText(mstosms(position));
    seekState = SeekState::MOVING;
}

void MainWindow::on_seek_slider_sliderReleased()
{
    player->setPosition(songPosition);
    ui->current_time_label->setText(mstosms(songPosition));
    seekState = SeekState::PLAYING;
}

void MainWindow::on_seek_slider_sliderPressed()
{
    seekState = SeekState::PRESSED;
}

void MainWindow::on_listView_doubleClicked(const QModelIndex& index)
{
    uint ind = songmap[model->data(index).value<QString>()];
    playlist->setCurrentIndex(ind);
    ui->play_button->setChecked(true);
    player->play();
    menuPlaybackPlay->setText("Pause");
}

void MainWindow::on_actionLyrics_triggered()
{
    lyricsWindow->setWindowFlags(Qt::Window);
    lyricsWindow->setReadOnly(true);
    lyricsWindow->setWindowTitle("Lyrics for " + currentsong->title);
    lyricsWindow->append("Loading...");
    lyricsWindow->show();
    UpdateLyrics();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filter = "File Description (*.mp3)";
    QList<QUrl> fileNames = QFileDialog::getOpenFileUrls(this, "Select a file...", QDir::homePath(), filter);
    LoadFiles(fileNames);
}

void MainWindow::on_forward_button_clicked()
{
    if (playlist->currentIndex() + 1 >= playlist->mediaCount())
    {
        playlist->setCurrentIndex(0);
    }
    else
    {
        playlist->next();
    }
}

void MainWindow::on_rewind_button_clicked()
{
    if (playlist->currentIndex() - 1 < 0)
    {
        playlist->setCurrentIndex(playlist->mediaCount() - 1);
    }
    else
    {
        playlist->previous();
    }
}

void MainWindow::on_actionNext_triggered()
{
    on_forward_button_clicked();
}

void MainWindow::on_actionPrevious_triggered()
{
    on_rewind_button_clicked();
}

void MainWindow::on_actionVolume_Up_triggered()
{
    if (volume + 5 >= 100) {
        volume = 100;
    }
    else
    {
        volume += 5;
    }
    player->setVolume(volume);
    ui->volume_slider->setValue(volume);
}

void MainWindow::on_actionVolume_Down_triggered()
{
    if (volume - 5 <= 0)
    {
        volume = 0;
    }
    else
    {
        volume -= 5;
    }
    player->setVolume(volume);
    ui->volume_slider->setValue(volume);
}

void MainWindow::on_actionPlay_triggered()
{
    if (!player->currentMedia().isNull())
    {
        if (ui->play_button->isChecked())
        {
            player->pause();
            menuPlaybackPlay->setText("Play");
            ui->play_button->setChecked(false);
        }
        else
        {
            player->play();
            menuPlaybackPlay->setText("Pause");
            ui->play_button->setChecked(true);
        }
    }
}
