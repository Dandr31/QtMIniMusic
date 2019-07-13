

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>



struct Song
{
    QString name;
    QString path;

    bool operator==(const Song &other) const
    {
        return name == other.name && path == other.path;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Song &song)
{
    return stream << song.name << song.path;
}

inline QDataStream &operator>>(QDataStream &stream, Song &song)
{
    return stream >> song.name >> song.path;
}

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);
    TableModel(QList<Song> songs, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<Song> getSongs() const;

private:
    QList<Song> songs;
};

#endif // TABLEMODEL_H
