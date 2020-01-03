#pragma once

#include "IRItemWidget.h"
#include "ui_RectItemWidget.h"

class RectItemWidget : public IRItemWidget
{
	Q_OBJECT

public:
	RectItemWidget(QWidget *parent = Q_NULLPTR);
	~RectItemWidget();

	virtual void bindItem(RGraphicsItem* pItem);

public slots:
	void slotUpdateGeometry();
	void slotUpdateItemPos();
	void slotUpdateItemSize();

private:
	Ui::RectItemWidget ui;
};
