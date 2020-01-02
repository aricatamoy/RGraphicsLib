#pragma once

#include <QObject>
#include <QGraphicsView>
#include "rgraphicslib_global.h"

class RGRAPHICSLIB_EXPORT RGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	RGraphicsView(QWidget *parent);
	~RGraphicsView();
};
