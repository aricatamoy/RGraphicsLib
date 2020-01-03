#include "RGraphicsItem.h"
#include <QDebug>
#include <QCursor>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>

class RGrapihcsItemPrivate
{
	friend class RGraphicsItem;

private:
	float fHitTestBorder = 3.0f;				// 边缘测试的边界
	bool bMovable = true;						// 是否允许移动
	bool bLimitedInRect = false;				// 是否限制在指定的限制框中，未指定框则默认是所属 scene 的 sceneRect
	QRectF rectLimited;							// 指定的限制框
	CustomPaintingFunc funcCustomPainting = &RGraphicsItem::defaultPaintingFunc;		// 选中状态绘制函数
};

QMap<int, int> RGraphicsItem::scMapBorderAreaCursor = QMap<int, int>(std::initializer_list<std::pair<int, int> >({
		std::make_pair(kBorderAreaCenter, Qt::SizeAllCursor),
		std::make_pair(kBorderAreaLeft, Qt::SizeHorCursor),
		std::make_pair(kBorderAreaTop, Qt::SizeVerCursor),
		std::make_pair(kBorderAreaRight, Qt::SizeHorCursor),
		std::make_pair(kBorderAreaBottom, Qt::SizeVerCursor),
		std::make_pair(kBorderAreaTopLeft, Qt::SizeFDiagCursor),
		std::make_pair(kBorderAreaTopRight, Qt::SizeBDiagCursor),
		std::make_pair(kBorderAreaBottomLeft, Qt::SizeBDiagCursor),
		std::make_pair(kBorderAreaBottomRight, Qt::SizeFDiagCursor)
	}));

bool RGraphicsItem::isXValid(float fX) const
{
	bool bValid = true;
	QRectF rectLimited = limitedRect();
	if (m.bLimitedInRect && !rectLimited.isNull())
	{
		bValid = fX > rectLimited.left() && fX < rectLimited.right();
	}
	return bValid;
}

bool RGraphicsItem::isYValid(float fY) const
{
	bool bValid = true;
	QRectF rectLimited = limitedRect();
	if (m.bLimitedInRect && !rectLimited.isNull())
	{
		bValid = fY > rectLimited.top() && fY < rectLimited.bottom();
	}
	return bValid;
}

QRectF RGraphicsItem::limitedRect() const
{
	QRectF rectLimited = m.rectLimited;
	if (rectLimited.isNull() && scene())
	{
		rectLimited = scene()->sceneRect();
	}
	return rectLimited;
}

RGraphicsItem::RGraphicsItem(QGraphicsItem* parent)
	: QObject(nullptr)
	, QGraphicsRectItem(parent)
	, m(*new RGrapihcsItemPrivate)
{
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);
}

RGraphicsItem::~RGraphicsItem()
{
	delete &m;
}

void RGraphicsItem::setActualRect(QRectF rect, bool bModifySize /* = true*/)
{
	//  修改尺寸
	if (bModifySize)
	{
		if (m.bLimitedInRect)
		{
			QRectF rectLimited = limitedRect();
			rect.setLeft(qMax(rect.left(), rectLimited.left()));
			rect.setRight(qMin(rect.right(), rectLimited.right()));
			rect.setTop(qMax(rect.top(), rectLimited.top()));
			rect.setBottom(qMin(rect.bottom(), rectLimited.bottom()));
		}

		rect.translate(QPointF(-pos().x(), -pos().y()));
		setRect(rect);
	}
	// 修改位移
	else
	{
		if (m.bLimitedInRect)
		{
			QRectF rectLimited = limitedRect();
			rect.moveLeft(qMax(rect.left(), rectLimited.left()));
			rect.moveRight(qMin(rect.right(), rectLimited.right()));
			rect.moveTop(qMax(rect.top(), rectLimited.top()));
			rect.moveBottom(qMin(rect.bottom(), rectLimited.bottom()));
		}

		Q_ASSERT(rect.size() == this->rect().size());
		QPointF ptPosition =  rect.topLeft() - this->rect().topLeft();
		setPos(ptPosition);
	}

	emit signalGeometryChanged(rect);
}

QRectF RGraphicsItem::actualRect() const
{
	QRectF rectActual = rect();
	rectActual.translate(pos());
	return rectActual;
}

void RGraphicsItem::setHitTestBorder(float fBorder)
{
	m.fHitTestBorder = fBorder;
}

void RGraphicsItem::setItemMovable(bool bMovable)
{
	m.bMovable = bMovable;
}

void RGraphicsItem::setItemLimitedInScene(bool bLimitedInScene)
{
	m.bLimitedInRect = bLimitedInScene;
	m.rectLimited = QRectF();
}

void RGraphicsItem::setItemLimitedInRect(QRectF rect, bool bLimited /*= true*/)
{
	m.bLimitedInRect = bLimited;
	if (!bLimited)
	{
		m.rectLimited = QRectF();
	}
}

void RGraphicsItem::setSelectedStatePaintingFunction(CustomPaintingFunc funPainting)
{
	m.funcCustomPainting = funPainting;
}

QVariant RGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	/*	if (change == ItemPositionHasChanged && scene())
		{
			emit signalGeometryChanged(actualRect());
		}
		else*/
	if (change == ItemSelectedHasChanged && !isSelected())
	{
		setCursor(Qt::PointingHandCursor);
	}

	return QGraphicsRectItem::itemChange(change, value);
}

void RGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor((Qt::CursorShape)scMapBorderAreaCursor.value(borderAreaHitTest(event->scenePos())));
	if (isSelected())
	{
		m_nLastBorderArea = borderAreaHitTest(event->scenePos());
		m_ptLastPosition = event->scenePos();
		setFlag(ItemIsMovable, false);
	}
	grabMouse();
	return QGraphicsRectItem::mousePressEvent(event);
}

void RGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	setFlag(ItemIsMovable, false);
	QRectF rectActual = actualRect();

	switch (m_nLastBorderArea)
	{
	case kBorderAreaTop:
	{
		rectActual.setTop(event->scenePos().y());
		setActualRect(rectActual);
		break;
	}
	case kBorderAreaBottom:
	{
		rectActual.setBottom(event->scenePos().y());
		setActualRect(rectActual);
		break;
	}

	case kBorderAreaLeft:
	{
		rectActual.setLeft(event->scenePos().x());
		setActualRect(rectActual);
		break;
	}
	case kBorderAreaRight:
	{
		rectActual.setRight(event->scenePos().x());
		setActualRect(rectActual);
		break;
	}

	case kBorderAreaTopLeft:
	{
		rectActual.setLeft(event->scenePos().x());
		rectActual.setTop(event->scenePos().y());
		setActualRect(rectActual);
		break;
	}
	case kBorderAreaTopRight:
	{
		rectActual.setRight(event->scenePos().x());
		rectActual.setTop(event->scenePos().y());
		setActualRect(rectActual);
		break;
	}
	case kBorderAreaBottomLeft:
	{
		rectActual.setLeft(event->scenePos().x());
		rectActual.setBottom(event->scenePos().y());
		setActualRect(rectActual);
		break;
	}
	case kBorderAreaBottomRight:
	{
		rectActual.setRight(event->scenePos().x());
		rectActual.setBottom(event->scenePos().y());
		setActualRect(rectActual);
		break;
	}
	case kBorderAreaCenter:
	{
		setFlag(ItemIsMovable, m.bMovable);
	}

	default:
		break;
	}
	QGraphicsRectItem::mouseMoveEvent(event);

	// 移动后重新设置以校验边界值
	QRectF rectMoved = actualRect();
	setActualRect(rectMoved, false);
}

void RGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	m_nLastBorderArea = kBorderAreaCenter;
	m_ptLastPosition = QPointF(0, 0);
	ungrabMouse();
	return QGraphicsRectItem::mouseReleaseEvent(event);
}

void RGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	if (this->isSelected())
	{
		QPointF ptCursor = event->scenePos();
		setCursor((Qt::CursorShape)scMapBorderAreaCursor.value(borderAreaHitTest(ptCursor)));
	}
	return QGraphicsRectItem::hoverMoveEvent(event);
}

void RGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m.funcCustomPainting != nullptr)
	{
		// 不绘制原有的选中状态
		QStyleOptionGraphicsItem paintOption = *option;
		paintOption.state &= ~QStyle::State_Selected;
		QGraphicsRectItem::paint(painter, &paintOption, widget);

		// 绘制自定义选中状态
		if (QStyle::State_Selected & option->state)
		{
			m.funcCustomPainting(painter, option->rect);
		}
	}
	else
	{
		return QGraphicsRectItem::paint(painter, option, widget);
	}
}

int RGraphicsItem::type() const
{
	return kType;
}

void RGraphicsItem::defaultPaintingFunc(QPainter* painter, QRectF rect)
{
	painter->fillRect(rect, QBrush(QColor("#1fff0000")));
}

int RGraphicsItem::borderAreaHitTest(QPointF pt)
{
	int nBorderArea = kBorderAreaCenter;
	QRectF rectActual = actualRect();

	float fBorder = m.fHitTestBorder;
	bool bTriggerLeft = (pt.x() - rectActual.left() < fBorder);
	bool bTriggerTop = (pt.y() - rectActual.top() < fBorder);
	bool bTriggerRight = (rectActual.right() - pt.x() < fBorder);
	bool bTriggerBottom = (rectActual.bottom() - pt.y() < fBorder);

	if (bTriggerTop && bTriggerLeft) {
		nBorderArea = kBorderAreaTopLeft;
	}
	else if (bTriggerRight && bTriggerTop) {
		nBorderArea = kBorderAreaTopRight;
	}
	else if (bTriggerLeft && bTriggerBottom) {
		nBorderArea = kBorderAreaBottomLeft;
	}
	else if (bTriggerRight && bTriggerBottom) {
		nBorderArea = kBorderAreaBottomRight;
	}
	else if (bTriggerLeft) {
		nBorderArea = kBorderAreaLeft;
	}
	else if (bTriggerTop) {
		nBorderArea = kBorderAreaTop;
	}
	else if (bTriggerRight) {
		nBorderArea = kBorderAreaRight;
	}
	else if (bTriggerBottom) {
		nBorderArea = kBorderAreaBottom;
	}

	return nBorderArea;
}
