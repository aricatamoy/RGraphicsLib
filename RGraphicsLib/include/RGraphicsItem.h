#pragma once
#include <QGraphicsRectItem>
#include "rgraphicslib_global.h"

typedef void(*CustomPaintingFunc)(QPainter* painter, QRectF rect);

class RGrapihcsItemPrivate;
class RGRAPHICSLIB_EXPORT RGraphicsItem : public QObject, public QGraphicsRectItem
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
	RGraphicsItem(QGraphicsItem* parent);
	~RGraphicsItem();

	static void defaultPaintingFunc(QPainter* painter, QRectF rect);

	enum { kType = RGraphicsItem::UserType + 1 };
	int type() const;

	void setActualRect(QRectF rect, bool bModifyRect = true);
	QRectF actualRect() const;

	void setHitTestBorder(float fBorder);
	void setItemMovable(bool bMovable);
	void setItemLimitedInScene(bool bLimitedInScene);
	void setItemLimitedInRect(QRectF rect, bool bLimited = true);
	void setSelectedStatePaintingFunction(CustomPaintingFunc funPainting);

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
	int borderAreaHitTest(QPointF pt);
	static QMap<int, int> scMapBorderAreaCursor;
	bool isXValid(float fX) const;
	bool isYValid(float fY) const;
	QRectF limitedRect() const;

	int m_nLastBorderArea = kBorderAreaCenter;
	QPointF m_ptLastPosition;
	
	RGrapihcsItemPrivate& m;
};