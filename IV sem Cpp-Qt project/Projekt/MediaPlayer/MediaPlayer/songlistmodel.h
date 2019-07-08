#ifndef SONGLISTMODEL_H
#define SONGLISTMODEL_H

#include <QStringListModel>

class SongListModel : public QStringListModel
{
public:
	SongListModel(const QStringList &strings, QObject *parent = 0);
	SongListModel(QObject *parent = Q_NULLPTR);
	Qt::ItemFlags flags(const QModelIndex&index) const;
};

#endif // SONGLISTMODEL_H
