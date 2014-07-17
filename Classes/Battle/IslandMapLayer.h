#pragma once
#include "MapLayer.h"
class IslandMapLayer:  public MapLayer
{
protected:
	virtual bool init();  
public:
	CREATE_FUNC(IslandMapLayer);
};
