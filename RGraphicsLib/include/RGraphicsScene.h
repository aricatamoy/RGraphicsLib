#pragma once

#include <QGraphicsScene>
#include "rgraphicslib_global.h"

class RGRAPHICSLIB_EXPORT RGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	RGraphicsScene(QObject *parent);
	~RGraphicsScene();
};
