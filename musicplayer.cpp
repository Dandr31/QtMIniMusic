#include "musicplayer.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QMediaPlayer>
MusicPlayer::MusicPlayer(QWidget *parent):QWidget (parent)
{
     playList = new PlayList(this);
     controlBar = new ControlBar(this);
     controlBar->setMediaPlayer(&mediaPlayer);
     controlBar->setPlayList(playList);


     QBoxLayout *playerLayout = new QVBoxLayout;
     playerLayout->addWidget(playList);
     playerLayout->addWidget(controlBar);
     setLayout(playerLayout);

     connect(&mediaPlayer, &QMediaPlayer::positionChanged, controlBar, &ControlBar::updatePosition);
     connect(&mediaPlayer, &QMediaPlayer::durationChanged, controlBar, &ControlBar::updateDuration);
     connect(&mediaPlayer, &QMediaObject::metaDataAvailableChanged, controlBar, &ControlBar::updateInfo);

     connect(&mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
               controlBar, &ControlBar::handleError);
     connect(&mediaPlayer, &QMediaPlayer::stateChanged,
                controlBar, &ControlBar::updateState);
}

void MusicPlayer::playUrl(const QUrl &url)
{
    controlBar->setInfo(url);
    const QString filePath = url.toLocalFile();
    setWindowFilePath(filePath);

    mediaPlayer.setMedia(url);
    mediaPlayer.play();

}

