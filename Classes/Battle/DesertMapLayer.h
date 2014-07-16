#pragma once
#include "MapLayer.h"
class DesertMapLayer:  public MapLayer
{
protected:
	virtual bool init();  
public:
	CREATE_FUNC(DesertMapLayer);
};
