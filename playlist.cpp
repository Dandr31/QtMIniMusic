#include "playlist.h"
#include <QtWidgets>
PlayList::PlayList(QWidget *parent):QTabWidget (parent)
{
    table = new TableModel(this);
    QTableView *tableView = new QTableView;

    tableView->setModel(table);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    //tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSortingEnabled(true);
     addTab(tableView, QString("播放列表"));
}

void PlayList::addEntry(QString name, QString path)
{
    if (!table->getSongs().contains({ name, path })) {
        table->insertRows(0, 1, QModelIndex());
        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, path, Qt::EditRole);
        //removeTab(indexOf(newAddressTab));
    }
}


