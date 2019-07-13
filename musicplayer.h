#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "playlist.h"
#include "controlbar.h"
#include <QWidget>
#include <QMediaPlayer>

class MusicPlayer:public QWidget
{
    Q_OBJECT
public:
    MusicPlayer(QWidget *parent=0);
    void playUrl(const QUrl &url);

private:
    QMediaPlayer mediaPlayer;
    PlayList *playList;
    ControlBar *controlBar;

};

#endif // MUSICPLAYER_H
