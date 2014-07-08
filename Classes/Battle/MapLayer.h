#pragma once
#include "cocos2d.h"
//#include "ShapeType.h"
class MapLayer:  public cocos2d::Layer
{
private:


protected:
	virtual bool init();  
	
public:
	bool ready;

	CREATE_FUNC(MapLayer);

};

