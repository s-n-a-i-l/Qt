#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Play_clicked();


    void on_horizontalSlider_Time_sliderMoved(qint64 position);

    void on_pushButton_Mute_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Next_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_diration_changet(qint64 duration);

    void on_position_changet(qint64 position);



private:
    Ui::MainWindow *ui;
    QMediaPlayer* m_player;
};
#endif // MAINWINDOW_H
