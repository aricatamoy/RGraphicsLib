#include "RGraphicsTextItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QTextCharFormat>
#include <QTextCursor>

RGraphicsTextItem::RGraphicsTextItem(QGraphicsItem* parent /*= nullptr*/)
	: RGraphicsItem(parent)
{

}

RGraphicsTextItem::~RGraphicsTextItem()
{

}

void RGraphicsTextItem::setText(QString strText)
{
	m_strText = strText;
	update();
}

void RGraphicsTextItem::setTextAlignment(Qt::Alignment alignment)
{
	m_option.setAlignment(alignment);
}

void RGraphicsTextItem::setFont(QFont font)
{
	m_font = font;
}

void RGraphicsTextItem::setTextPen(QPen pen)
{
	m_pen = pen;
}

void RGraphicsTextItem::setShadowEnabled(bool bEnabled)
{
	m_bEnableShadow = bEnabled;
}

void RGraphicsTextItem::setShadowParameter(float fXOffset, float fYOffset, int nOpacity, QColor color)
{
	m_fShadowXOffset = fXOffset;
	m_fShadowYOffset = fYOffset;
	m_nShadowOpacity = nOpacity;
	m_colorShadow = color;
}

void RGraphicsTextItem::setOutlineEnabled(bool bEnabled)
{
	m_bEnableOutline = bEnabled;
}

void RGraphicsTextItem::setOutlineParameter(int nWidth, QColor color)
{
	m_nWidth = nWidth;
	m_colorOutline = color;
}

void RGraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	RGraphicsItem::paint(painter, option, widget);

	//if (m_bEnableOutline)
	//{
	//	painter->save();
	//	painter->setPen(QColor(m_colorOutline));
	//	QFont font = m_font;
	//	painter->setFont(m_font);
	//	QRectF rectShadow = option->rect;
	//	rectShadow.translate(m_fShadowXOffset, m_fShadowYOffset);
	//	painter->drawText(rectShadow, m_strText, m_option);
	//	painter->restore();
	//}

	if (m_bEnableShadow)
	{
		painter->save();
		painter->setPen(QColor(m_colorShadow));
		painter->setFont(m_font);
		QRectF rectShadow = option->rect;
		rectShadow.translate(m_fShadowXOffset, m_fShadowYOffset);
		painter->drawText(rectShadow, m_strText, m_option);
		painter->restore();
	}

	painter->setPen(m_pen);
	painter->setBrush(QBrush(QColor("#ffff00")));
	painter->setFont(m_font);
	painter->drawText(option->rect, m_strText, m_option);
}
