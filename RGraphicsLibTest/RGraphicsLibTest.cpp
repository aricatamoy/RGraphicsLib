#include "RGraphicsLibTest.h"
#include "RGraphicsItem.h"
#include "RGraphicsTextItem.h"
#include "RectItemWidget.h"
#include "IRItemWidget.h"
#include <QDebug>

RGraphicsLibTest::RGraphicsLibTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pScene = new RGraphicsScene(this);
	ui.graphicsView->setScene(m_pScene);

	// m_pScene->addRect(QRectF(0, 0, 300, 300), QPen(QColor("#ff0000")));
	{
		RGraphicsItem* pItem = new RGraphicsItem(nullptr);
		pItem->setRect(0, 0, 300, 300);
		pItem->setPen(QColor("#eee"));
		pItem->setBrush(QColor("#eee"));
		pItem->setItemLimitedInScene(true);
		m_pScene->addItem(pItem);
	}

	{
		RGraphicsTextItem* pItem = new RGraphicsTextItem(nullptr);
		pItem->setRect(300, 300, 284, 107);
		pItem->setPen(QColor("#eee"));
		pItem->setBrush(QColor("#eee"));
		pItem->setItemLimitedInScene(true);
		pItem->setText("Hello world!");
		pItem->setTextAlignment(Qt::AlignCenter);
		pItem->setTextPen(QPen(QColor("#ffff00")));
		QFont font;
		font.setBold(true);
		font.setPixelSize(40);
		pItem->setFont(font);
		m_pScene->addItem(pItem);

		pItem->setShadowParameter(5, 5, 100, "#2f00ff00");
		pItem->setShadowEnabled(true);
	}

	initStackedWidget();
	m_pScene->setSceneRect(0, 0, 500, 500);
	connect(m_pScene, &QGraphicsScene::selectionChanged, this, &RGraphicsLibTest::slotSelectionChanged);
}

RGraphicsLibTest::~RGraphicsLibTest()
{
	m_pScene->disconnect();
}

void RGraphicsLibTest::slotSelectionChanged()
{
	ui.stackedWidget->setCurrentWidget(m_pEmptyPage);
	QList<QGraphicsItem*> items = m_pScene->selectedItems();
	if (!items.isEmpty())
	{
		QGraphicsItem* pItem = items[0];
		QWidget* pWidget = m_mapTypePage.value(pItem->type(), m_pEmptyPage);
		ui.stackedWidget->setCurrentWidget(pWidget);

		RGraphicsItem* pRectItem = qgraphicsitem_cast<RGraphicsItem*>(pItem);
		IRItemWidget* pItemWidget = dynamic_cast<IRItemWidget*>(pWidget);
		if (pRectItem && pItemWidget)
		{
			pItemWidget->bindItem(pRectItem);
		}
	}
}

void RGraphicsLibTest::initStackedWidget()
{
	m_pEmptyPage = new QWidget(this);
	m_pRectPage = new RectItemWidget(this);

	ui.stackedWidget->addWidget(m_pEmptyPage);
	ui.stackedWidget->addWidget(m_pRectPage);

	m_mapTypePage[RGraphicsItem(nullptr).type()] = m_pRectPage;
}
