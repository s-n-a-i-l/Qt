#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>
#include <QFileDialog>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Buttons stule:
    ui->pushButton_Add->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));
    ui->pushButton_Prev->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Next->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));

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

}

MainWindow::~MainWindow()
{
    delete m_player;
    delete ui;
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
    QString file = QFileDialog::getOpenFileName
            (
              this,
              "Open File",
              "",
              "Audio files (*.mp3 *.flac);; MP-3 (*.mp3);; Flac (*.flac)"
            );
    ui->label_FileName -> setText(QString("File: ").append(file));
    this->m_player->setMedia(QUrl(file));
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

void MainWindow::on_pushButton_Next_clicked()
{

}













