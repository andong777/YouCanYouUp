#pragma once
#include "cocos2d.h"

class MapLayer:  public cocos2d::Layer
{
protected:
	virtual bool init();  

public:
	/*
	MapLayer(void);
	~MapLayer(void);
	*/
	CREATE_FUNC(MapLayer);

	//void movePlate(float fDelta);


};

