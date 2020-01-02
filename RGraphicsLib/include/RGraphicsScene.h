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
	QList<T> items(Qt::SortOrder order = Qt::DescendingOrder) const;

	template<class T>
	QList<T> selectedItems() const;
};

template<class T>
QList<T>
RGraphicsScene::items(Qt::SortOrder order /*= Qt::DescendingOrder*/) const
{
	QList<T> listItems;
	Q_FOREACH(QGraphicsItem* pItem, items(order))
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
RGraphicsScene::selectedItems() const
{
	QList<T> listItems;
	Q_FOREACH(QGraphicsItem* pItem, selectedItems())
	{
		T* pCastedItem = dynamic_cast<T>(pItem);
		if (pCastedItem)
		{
			listItems.append(pCastedItem);
		}
	}
	return listItems;

}
