#include "RectItemWidget.h"

RectItemWidget::RectItemWidget(QWidget *parent)
	: IRItemWidget(parent)
{
	ui.setupUi(this);
}

RectItemWidget::~RectItemWidget()
{
}

void RectItemWidget::bindItem(RGraphicsItem* pItem)
{
	unbindItem();
	m_pCurrentItem = pItem;
	connect(m_pCurrentItem, &RGraphicsItem::signalGeometryChanged, this, &RectItemWidget::slotUpdateGeometry);
	connect(ui.xSpin, &QDoubleSpinBox::editingFinished, this, &RectItemWidget::slotUpdateItemPos);
	connect(ui.ySpin, &QDoubleSpinBox::editingFinished, this, &RectItemWidget::slotUpdateItemPos);
	connect(ui.widthSpin, &QDoubleSpinBox::editingFinished, this, &RectItemWidget::slotUpdateItemSize);
	connect(ui.heightSpin, &QDoubleSpinBox::editingFinished, this, &RectItemWidget::slotUpdateItemSize);

	slotUpdateGeometry();
}

void RectItemWidget::slotUpdateGeometry()
{
	if (m_pCurrentItem)
	{
		ui.xSpin->setValue(m_pCurrentItem->actualRect().x());
		ui.ySpin->setValue(m_pCurrentItem->actualRect().y());
		ui.widthSpin->setValue(m_pCurrentItem->actualRect().width());
		ui.heightSpin->setValue(m_pCurrentItem->actualRect().height());
	}
}

void RectItemWidget::slotUpdateItemPos()
{
	QRectF rect(ui.xSpin->value(), ui.ySpin->value(), ui.widthSpin->value(), ui.heightSpin->value());
	if (m_pCurrentItem)
	{
		m_pCurrentItem->setActualRect(rect);
	}
}

void RectItemWidget::slotUpdateItemSize()
{
	QRectF rect(ui.xSpin->value(), ui.ySpin->value(), ui.widthSpin->value(), ui.heightSpin->value());
	if (m_pCurrentItem)
	{
		m_pCurrentItem->setActualRect(rect, true);
	}
}
