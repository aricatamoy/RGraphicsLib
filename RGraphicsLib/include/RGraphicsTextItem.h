#pragma once
#include "RGraphicsItem.h"
#include <QTextOption>
#include <QFont>
#include <QPen>

class RGRAPHICSLIB_EXPORT RGraphicsTextItem : public RGraphicsItem
{
public:
	RGraphicsTextItem(QGraphicsItem* parent = nullptr);
	~RGraphicsTextItem();

	void setText(QString strText);
	void setTextAlignment(Qt::Alignment alignment);
	void setFont(QFont font);
	void setTextPen(QPen pen);
	void setShadowEnabled(bool bEnabled);
	void setShadowParameter(float fXOffset, float fYOffset, int nOpacity, QColor color);

	void setOutlineEnabled(bool bEnabled);
	void setOutlineParameter(int nWidth, QColor color);

protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
	QString m_strText;
 	QTextOption m_option;
	QFont m_font;
	QPen m_pen;

	// Shadow
	bool m_bEnableShadow = false;
	float m_fShadowXOffset = 1.0f;
	float m_fShadowYOffset = 1.0f;
	int m_nShadowOpacity = 100;
	QColor m_colorShadow;

	// Outline
	bool m_bEnableOutline = false;
	int m_nWidth = 0;
	QColor m_colorOutline;
};

