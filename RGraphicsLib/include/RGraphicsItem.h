#pragma once
#include <QGraphicsRectItem>
#include "rgraphicslib_global.h"

class RGrapihcsItemPrivate;
class RGRAPHICSLIB_EXPORT RGrapihcsItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

	enum BorderArea{
		kBorderAreaCenter,
		kBorderAreaLeft,
		kBorderAreaTop,
		kBorderAreaRight,
		kBorderAreaBottom,
		kBorderAreaTopLeft,
		kBorderAreaTopRight,
		kBorderAreaBottomLeft,
		kBorderAreaBottomRight
	};
	
public:
	RGrapihcsItem(QGraphicsItem* parent);
	~RGrapihcsItem();

	void setActualRect(QRectF rect);
	QRectF actualRect() const;

	void setItemMovable(bool bMovable);
	void setItemLimitedInScene(bool bLimitedInScene);
	void setItemLimitedInRect(QRectF rect, bool bLimited = true);

protected:
	virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
	void signalGeometryChanged(QRectF rect);

private:
	int borderAreaHitTest(QPointF pt, float fBorder = 3);
	static QMap<int, int> scMapBorderAreaCursor;
	bool isXValid(float fX) const;
	bool isYValid(float fY) const;
	QRectF limitedRect() const;

	int m_nLastBorderArea = kBorderAreaCenter;
	QPointF m_ptLastPosition;
	
	RGrapihcsItemPrivate& m;
};