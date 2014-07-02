#pragma once
#include "cocos2d.h"
class SnowMapLayer:  public cocos2d::Layer
{
protected:
	virtual bool init();  

public:
	/*
	MapLayer(void);
	~MapLayer(void);
	*/
	CREATE_FUNC(SnowMapLayer);

	//void movePlate(float fDelta);


};
