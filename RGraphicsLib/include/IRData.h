#pragma once
#include "rgraphicslib_global.h"

#include <QRectF>

class RGRAPHICSLIB_EXPORT IRData
{
public:
	IRData();
	~IRData();

protected:
	QRectF m_rect;
};
