#include "mainwindow.h"
#include <QtDebug>
#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QGridLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
      musicPlayer = new MusicPlayer(this);
      setCentralWidget(musicPlayer);
      createMenus();
      setWindowTitle(tr("QtMiniMusic"));

}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	openAct = new QAction(tr("&Open..."),this);
	fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
	

//    testAct = new QAction(tr("&Test"));
//    fileMenu->addAction(testAct);
//    connect(testAct,&QAction::triggered,this,&MainWindow::test);

//    playMusicAct = new QAction(tr("playMusic"));
//    fileMenu->addAction(playMusicAct);
//    connect(playMusicAct, &QAction::triggered, this, &MainWindow::playMusic);

	exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);


}
void MainWindow::openFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open File"));
    if (fileDialog.exec() == QDialog::Accepted)
        musicPlayer->playUrl(fileDialog.selectedUrls().constFirst());
}

void MainWindow::test()
{
  QString str("test");
  qDebug()<<str;
  QFileDialog fileDialog(this);
  fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog.setWindowTitle(tr("Open File"));
  if (fileDialog.exec() == QDialog::Accepted)
      musicPlayer->playUrl(fileDialog.selectedUrls().constFirst());

}


