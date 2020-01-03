#pragma once

#include <QWidget>
#include "RGraphicsItem.h"

class RGRAPHICSLIB_EXPORT IRItemWidget : public QWidget
{
	Q_OBJECT

public:
	IRItemWidget(QWidget *parent = nullptr);
	~IRItemWidget();

	virtual void bindItem(RGraphicsItem* pItem);
	virtual void unbindItem();

protected:
    RGraphicsItem* m_pCurrentItem = nullptr;
};
