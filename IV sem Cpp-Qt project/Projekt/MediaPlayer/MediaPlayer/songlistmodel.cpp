#include "songlistmodel.h"

SongListModel::SongListModel(const QStringList& strings, QObject* parent) : QStringListModel(strings, parent)
{
}

SongListModel::SongListModel(QObject* parent) : QStringListModel(parent)
{

}

Qt::ItemFlags SongListModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags;
    if (index.isValid())
    {
		flags = Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled;
	}
    else
    {
		flags = Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
	}
	return flags;
}
