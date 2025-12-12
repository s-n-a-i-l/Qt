#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>
#include <QFileDialog>
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    shuffle=false;
    loop=false;
    //url = QUrl( "E:\\repos\\MediaPlayerPD411\\SavePlaylist\\playlist.m3u");


    //Buttons stule:
    ui->pushButton_Add->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));
    ui->pushButton_Prev->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Next->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    ui->pushButton_Loop->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

    //Player Init:
    m_player = new QMediaPlayer();
    m_player->setVolume(70);
    ui->label_Volume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
    ui->horizontalSlider_Volume->setValue(m_player->volume());

    // громкость
    ui->horizontalSlider_Volume->setRange(0,100);

    connect(m_player, &QMediaPlayer::durationChanged, this, &MainWindow::on_diration_changet);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MainWindow::on_position_changet);
    connect(this->ui->horizontalSlider_Time, &QSlider::sliderMoved,
            this, &MainWindow::on_horizontalSlider_Time_sliderMoved);



    // playlist init
      m_playlist_model = new QStandardItemModel(this);
      initPlaylist();
      //loadPlaylistFromFile("E:\\repos\\MediaPlayerPD411\\SavePlaylist\\playlist.m3u");
//    this->ui->tableView_Playlist->setModel(m_playlist_model);// predstavlenie
//    m_playlist_model->setHorizontalHeaderLabels(QStringList() << "Audio track" << "File path" <<"Duration");
//    this->ui->tableView_Playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    this->ui->tableView_Playlist->setSelectionBehavior(QAbstractItemView::SelectRows);

//    this->ui->tableView_Playlist->hideColumn(1);
//    int duration_widht = 64;
//    this->ui->tableView_Playlist->setColumnWidth(2, duration_widht);
//    this->ui->tableView_Playlist->setColumnWidth(0, this->ui->tableView_Playlist->width()-duration_widht*1.7);

    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    loadPlaylistFromFile("E:\\repos\\MediaPlayerPD411\\SavePlaylist\\playlist.m3u");

    connect(this->ui->pushButton_Prev, &QPushButton::clicked, this->m_playlist, &QMediaPlaylist::previous);
    connect(this->ui->pushButton_Next, &QPushButton::clicked, this->m_playlist, &QMediaPlaylist::next);
    connect(this->m_playlist, &QMediaPlaylist::currentIndexChanged, this->ui->tableView_Playlist, &QTableView::selectRow);
    connect(this->ui->tableView_Playlist, &QTableView::doubleClicked,
            [this](const QModelIndex& index){m_playlist->setCurrentIndex(index.row()); this->m_player->play();}
    );
    connect(this->m_player, &QMediaPlayer::currentMediaChanged,
            [this](const QMediaContent& media)
            { this->ui->label_FileName->setText(media.canonicalUrl().toString());
              this->setWindowTitle(this->ui->label_FileName->text().split('/').last());
            }
    );

   // connect(this->ui->pushButton_Clr, &QPushButton::clicked, this->m_playlist, &QMediaPlaylist::clear);
    //connect(this->ui->pushButton_Clr, &QPushButton::clicked, this->m_playlist_model, &QStandardItemModel::clear);
}

MainWindow::~MainWindow()
{
    delete m_playlist;
    delete m_playlist_model;
    delete m_player;
    delete ui;
}

void MainWindow::initPlaylist()
{

    this->ui->tableView_Playlist->setModel(m_playlist_model);// predstavlenie
    m_playlist_model->setHorizontalHeaderLabels(QStringList() << "Audio track" << "File path" <<"Duration");
    this->ui->tableView_Playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableView_Playlist->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->ui->tableView_Playlist->hideColumn(1);
    int duration_widht = 64;
    this->ui->tableView_Playlist->setColumnWidth(2, duration_widht);
    this->ui->tableView_Playlist->setColumnWidth(0, this->ui->tableView_Playlist->width()-duration_widht*1.7);

}



void MainWindow::loadFileToPlaylist(const QString &filename)
{
    m_playlist->addMedia(QUrl(filename));
    QList<QStandardItem*> items;
    items.append(new QStandardItem(QDir(filename).dirName()));
    items.append(new QStandardItem(filename));
    //QMediaPlayer player;
//    m_duration_player.setMedia(QUrl(filename));
//    m_duration_player.play();
//    items.append(new QStandardItem(QTime::fromMSecsSinceStartOfDay(m_duration_player.duration()).toString("mm:ss")));
//    m_duration_player.pause();
    m_playlist_model->appendRow(items);

    savePlaylistToFile("E:\\repos\\MediaPlayerPD411\\SavePlaylist\\playlist.m3u");
}

void MainWindow::on_diration_changet(qint64 duration)
{
    this->ui->horizontalSlider_Time->setRange(0,duration);
    this->ui->label_Duration->setText(QTime::fromMSecsSinceStartOfDay(duration).toString("hh:mm:ss"));
}

void MainWindow::on_position_changet(qint64 position)
{
    this->ui->label_Position->setText(QString(QTime::fromMSecsSinceStartOfDay(position).toString("hh:mm:ss")));
    this->ui->horizontalSlider_Time->setValue(position);
}

void MainWindow::on_horizontalSlider_Time_sliderMoved(qint64 position)
{
    m_player->setPosition(position);
}

void MainWindow::on_pushButton_Add_clicked()
{
//    QString file = QFileDialog::getOpenFileName
//            (
//              this,
//              "Open File",
//              "E:\\music",
//              "Audio files (*.mp3 *.flac);; MP-3 (*.mp3);; Flac (*.flac)"
//            );
//    ui->label_FileName -> setText(QString("File: ").append(file));
//    this->m_player->setMedia(QUrl(file));

    QStringList files = QFileDialog::getOpenFileNames
            (
                this,
                "Open file",
                "E:\\music",
                "Audio files (*.mp3 *.flac *.flacc);; MP-3 (*.mp3);; Flac (*.flac *.flacc)"
            );

    for(QString file:files)
    {
      loadFileToPlaylist(file);
    }

}



void MainWindow::on_pushButton_Play_clicked()
{
    this->m_player->play();
}

void MainWindow::on_pushButton_Stop_clicked()
{
    m_player->stop();
}

void MainWindow::on_pushButton_Pause_clicked()
{
   m_player->state()==QMediaPlayer::State::PausedState
                                ?
               m_player->play() : m_player->pause();
}

void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    m_player->setVolume(value);
    ui->label_Volume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
}

void MainWindow::on_pushButton_Mute_clicked()
{
   m_player->setMuted(!m_player->isMuted());
   ui->pushButton_Mute->setIcon(style()->standardIcon(m_player->isMuted()?QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
   //m_player->setVolume(0);
   //ui->horizontalSlider_Volume->setSliderPosition(0);
   // ui->label_Volume->setText(QString("Volume: ").append(QString::number(m_player->volume())));

}

void MainWindow::on_pushButton_Shuffle_clicked()
{
    shuffle = !shuffle;
    this->ui->pushButton_Shuffle->setCheckable(true);
    this->m_playlist->setPlaybackMode(shuffle ? QMediaPlaylist::PlaybackMode::Random : QMediaPlaylist::PlaybackMode::Sequential);
    this->ui->pushButton_Shuffle->setChecked(shuffle);
}


void MainWindow::on_pushButton_Loop_clicked()
{
    loop = !loop;
    this->ui->pushButton_Loop->setCheckable(true);
    this->m_playlist->setPlaybackMode(loop?  QMediaPlaylist::PlaybackMode::Loop : QMediaPlaylist::PlaybackMode::Sequential);
    this->ui->pushButton_Loop->setChecked(loop);
}


void MainWindow::on_pushButton_Del_clicked()
{
//   QItemSelectionModel* selection = ui->tableView_Playlist->selectionModel();
//   QModelIndexList indexes = selection->selectedRows();
//   for(QModelIndex i:indexes)
//   {
//       m_playlist_model->removeRow(i.row());
//       m_playlist->removeMedia(i.row());
//   }
    QItemSelectionModel *selection = nullptr;
    do
    {
        selection = ui->tableView_Playlist->selectionModel();
        QModelIndexList indexes = selection->selectedRows();
        if(selection->selectedRows().count() > 0)
        {
            m_playlist_model->removeRow(indexes.first().row());
            m_playlist->removeMedia(indexes.first().row());
        }
    }while(selection->selectedRows().count());
}


void MainWindow::on_pushButton_Clr_clicked()
{
    m_playlist->clear();
    m_playlist_model->clear();
    initPlaylist();
}

void MainWindow::savePlaylistToFile(const QString &filePath)
{
    bool success = m_playlist->save(QUrl::fromLocalFile(filePath), "m3u");

       if (success) {
           qDebug() << "Плейлист успешно сохранен в" << filePath;
       } else {

           qDebug() << "Не удалось сохранить плейлист:" << m_playlist->errorString();
       }
}

void MainWindow::loadPlaylistFromFile(const QString &filePath)
{
    m_playlist->clear();
    m_playlist->load(QUrl::fromLocalFile(filePath), "m3u");
    for (int i = 0; i < m_playlist->mediaCount(); ++i)
    {
           QMediaContent content = m_playlist->media(i);
           QUrl url = content.canonicalUrl();

           QList<QStandardItem*> items;

           QFileInfo fileInfo(url.toLocalFile());
           items.append(new QStandardItem(fileInfo.fileName()));
           items.append(new QStandardItem(fileInfo.absoluteFilePath()));

           items.append(new QStandardItem("00:00"));

           m_playlist_model->appendRow(items);
    }
}



void MainWindow::on_pushButton_Dir_clicked()
{
    QString directory =
    QFileDialog::getExistingDirectory(this, tr("Select Music Folder"),
    QDir::homePath(),
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);


}

