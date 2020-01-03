#pragma once

#include <QGraphicsScene>
#include "rgraphicslib_global.h"

class RGRAPHICSLIB_EXPORT RGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	RGraphicsScene(QObject *parent);
	~RGraphicsScene();

	template<class T>
	QList<T> customItems(Qt::SortOrder order = Qt::DescendingOrder) const;

	template<class T>
	QList<T> selectedCustomItems() const;
};

template<class T>
QList<T>
RGraphicsScene::customItems(Qt::SortOrder order /*= Qt::DescendingOrder*/) const
{
	QList<T> listItems;
	Q_FOREACH(QGraphicsItem* pItem, customItems(order))
	{
		T* pCastedItem = dynamic_cast<T>(pItem);
		if (pCastedItem)
		{
			listItems.append(pCastedItem);
		}
	}
	return listItems;
}

template<class T>
QList<T>
RGraphicsScene::selectedCustomItems() const
{
	QList<T> listItems;
	Q_FOREACH(QGraphicsItem* pItem, selectedCustomItems())
	{
		T* pCastedItem = dynamic_cast<T>(pItem);
		if (pCastedItem)
		{
			listItems.append(pCastedItem);
		}
	}
	return listItems;

}
