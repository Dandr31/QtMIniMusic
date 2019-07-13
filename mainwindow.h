#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "musicplayer.h"
#include <QMainWindow>
#include <QMediaPlayer>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void openFile();
    void test();
private:
    void createMenus();
    QMenu *fileMenu;
    QAction *openAct;
    QAction *exitAct;
    QAction *playMusicAct;
    QAction *testAct;

    MusicPlayer *musicPlayer;
    QMediaPlayer mediaPlayer;

};

#endif // MAINWINDOW_H
