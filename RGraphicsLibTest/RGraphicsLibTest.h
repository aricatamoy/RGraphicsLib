#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RGraphicsLibTest.h"
#include "RGraphicsScene.h"

class RectItemWidget;
class RGraphicsLibTest : public QMainWindow
{
	Q_OBJECT

public:
	RGraphicsLibTest(QWidget *parent = Q_NULLPTR);
	~RGraphicsLibTest();

public slots:
	void slotSelectionChanged();

private:
	Ui::RGraphicsLibTestClass ui;

	RGraphicsScene* m_pScene = nullptr;
	void initStackedWidget();
	QWidget* m_pEmptyPage = nullptr;
	RectItemWidget* m_pRectPage = nullptr;
	QMap<int, QWidget*> m_mapTypePage;
};
