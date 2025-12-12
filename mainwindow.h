#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initPlaylist();
    void loadFileToPlaylist(const QString& filename);
private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Play_clicked();


    void on_horizontalSlider_Time_sliderMoved(qint64 position);

    void on_pushButton_Mute_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Pause_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_diration_changet(qint64 duration);

    void on_position_changet(qint64 position);



    void on_pushButton_Shuffle_clicked();

    void on_pushButton_Loop_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Clr_clicked();

    void savePlaylistToFile(const QString &filePath);
    void loadPlaylistFromFile(const QString &filePath);

    void on_pushButton_Dir_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* m_player;
    QMediaPlaylist *m_playlist;
    QStandardItemModel *m_playlist_model;

    bool shuffle;
    bool loop;
   // QUrl url;

    QMediaPlayer m_duration_player;
};

#endif // MAINWINDOW_H
