#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RGraphicsLibTest.h"
#include "RGraphicsScene.h"

class RGraphicsLibTest : public QMainWindow
{
	Q_OBJECT

public:
	RGraphicsLibTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::RGraphicsLibTestClass ui;

	RGraphicsScene* m_pScene = nullptr;
};
