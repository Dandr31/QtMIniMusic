#include "playerwidget.h"
#include <QtWidgets>
PlayerWidget:: PlayerWidget(QWidget *parent): QWidget(parent)
{
    createWidgets();
}


void PlayerWidget::createWidgets()
{
    playButton = new QToolButton(this);
    playButton->setEnabled(false);
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        //connect(playButton, &QAbstractButton::clicked, this, &MusicPlayer::togglePlayback);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setEnabled(false);
    positionSlider->setToolTip(tr("Seek"));
        //connect(positionSlider, &QAbstractSlider::valueChanged, this, &MusicPlayer::setPosition);
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);
    setLayout(controlLayout);

}
