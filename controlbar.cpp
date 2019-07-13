#include "controlbar.h"

#include <QtWidgets>
#include <QToolButton>
#include <QBoxLayout>
#include <QStyle>
#include <QFile>
#include <QDir>
#include <QDebug>
ControlBar::ControlBar(QWidget *parent) : QWidget(parent)
{
    createWidgets();
}
void ControlBar::createWidgets()
{
    playButton = new QToolButton(this);
    playButton->setEnabled(false);
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, &QAbstractButton::clicked, this, &ControlBar::togglePlayback);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setEnabled(false);
    positionSlider->setToolTip(tr("Seek"));
    connect(positionSlider, &QAbstractSlider::valueChanged, this, &ControlBar::setPosition);

    infoLabel = new QLabel(this);

    positionLabel = new QLabel(tr("00:00"), this);
    positionLabel->setMinimumWidth(positionLabel->sizeHint().width());

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);
    controlLayout->addWidget(positionLabel);

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(controlLayout);
}

void ControlBar::setInfo(const QUrl &url)
{
    curl = url;
    playButton->setEnabled(true);
    if (url.isLocalFile())
    {
        const QString filePath = url.toLocalFile();
        infoLabel->setText(QDir::toNativeSeparators(filePath));
        fileName = QFileInfo(filePath).fileName();
    }
    else
    {
        setWindowFilePath(QString());
        infoLabel->setText(url.toString());
        fileName.clear();
    }
}

void ControlBar::setMediaPlayer(QMediaPlayer *cmediaPlayer)
{
    this->cmediaPlayer = cmediaPlayer;
}

void ControlBar::setPlayList(PlayList *playList)
{
    this->cplayList = playList;
}

static QString formatTime(qint64 timeMilliSeconds)
{
    qint64 seconds = timeMilliSeconds / 1000;
    const qint64 minutes = seconds / 60;
    seconds -= minutes * 60;
    return QStringLiteral("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

void ControlBar::updatePosition(qint64 position)
{
    positionSlider->setValue(position);
    positionLabel->setText(formatTime(position));
}

void ControlBar::updateDuration(qint64 duration)
{
    positionSlider->setRange(0, duration);
    positionSlider->setEnabled(duration > 0);
    positionSlider->setPageStep(duration / 10);
    updateInfo();
}

void ControlBar::updateInfo()
{
    QStringList info;
    QString author, title;
    if (!fileName.isEmpty())
    {
        info.append(fileName);
        qDebug() << QString("fileNmae:") << fileName;
    }
    if (cmediaPlayer->isMetaDataAvailable())
    {
        author = cmediaPlayer->metaData(QStringLiteral("Author")).toString();
        if (!author.isEmpty())
        {
            info.append(author);
            qDebug() << QString("author") << author;
        }
        title = cmediaPlayer->metaData(QStringLiteral("Title")).toString();
        if (!title.isEmpty())
        {
            info.append(title);
            qDebug() << QString("title") << title;
        }
        cplayList->addEntry(title, curl.toString());
    }

    info.append(formatTime(cmediaPlayer->duration()));
    infoLabel->setText(info.join(tr(" - ")));
}

void ControlBar::handleError()
{
    playButton->setEnabled(false);
    const QString errorString = cmediaPlayer->errorString();
    infoLabel->setText(errorString.isEmpty()
                           ? tr("Unknown error #%1").arg(int(cmediaPlayer->error()))
                           : tr("Error: %1").arg(errorString));
}

void ControlBar::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState)
    {
        playButton->setToolTip(tr("Pause"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        playButton->setToolTip(tr("Play"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void ControlBar::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(cmediaPlayer->position() - position) > 99)
        cmediaPlayer->setPosition(position);
}

void ControlBar::togglePlayback()
{
    if (cmediaPlayer->mediaStatus() == QMediaPlayer::NoMedia)
        QMessageBox::information(this, tr("Can't play"), "Please choose a song");
    else if (cmediaPlayer->state() == QMediaPlayer::PlayingState)
        cmediaPlayer->pause();
    else
        cmediaPlayer->play();
}
