#ifndef CONTROLBAR_H
#define CONTROLBAR_H
#include <QWidget>

#include <QSlider>
#include <QLabel>
#include <QAbstractButton>
#include "playlist.h"
#include <QMediaPlayer>

class ControlBar:public QWidget
{
    Q_OBJECT
public:
    ControlBar(QWidget *parent=0);
    void setMediaPlayer(QMediaPlayer *cmediaPlayer);
    void setPlayList(PlayList *playList);
    void createWidgets();
    void setInfo(const QUrl &url);
public slots:
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void updateInfo();
    void handleError();
    void togglePlayback();
private:
    QAbstractButton *playButton = nullptr;
    QSlider *positionSlider = nullptr;
    QLabel *positionLabel = nullptr;
    QLabel *infoLabel = nullptr;
    QString fileName;
    QMediaPlayer *cmediaPlayer;
    PlayList *cplayList;
    QUrl curl;
};

#endif // CONTROLBAR_H
