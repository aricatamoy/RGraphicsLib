#include "RGraphicsLibTest.h"
#include "RGraphicsItem.h"

RGraphicsLibTest::RGraphicsLibTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pScene = new RGraphicsScene(this);
	ui.graphicsView->setScene(m_pScene);

	// m_pScene->addRect(QRectF(0, 0, 300, 300), QPen(QColor("#ff0000")));
	RGrapihcsItem* pItem = new RGrapihcsItem(nullptr);
	pItem->setRect(0, 0, 300, 300);
	pItem->setPen(QColor("#eee"));
	pItem->setBrush(QColor("#eee"));
	pItem->setItemLimitedInScene(true);
	m_pScene->addItem(pItem);

	m_pScene->setSceneRect(0, 0, 500, 500);
}
