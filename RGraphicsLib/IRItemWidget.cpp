#include "IRItemWidget.h"

IRItemWidget::IRItemWidget(QWidget *parent /*= nullptr*/)
	: QWidget(parent)
{

}

IRItemWidget::~IRItemWidget()
{
}

void IRItemWidget::bindItem(RGraphicsItem* pItem)
{
	unbindItem();
	m_pCurrentItem = pItem;
}

void IRItemWidget::unbindItem()
{
	if (m_pCurrentItem)
	{
		m_pCurrentItem->disconnect(this);
		this->disconnect(m_pCurrentItem);
	}
}

