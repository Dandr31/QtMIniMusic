#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "tablemodel.h"
#include <QTabWidget>
class PlayList : public QTabWidget
{
    Q_OBJECT
public:
    PlayList(QWidget *parent=0);
    void addEntry(QString name, QString address);
    void removeEntry();
private:
     TableModel *table;

};

#endif // PLAYLIST_H
