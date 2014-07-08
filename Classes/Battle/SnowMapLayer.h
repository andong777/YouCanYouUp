#pragma once
//#include "cocos2d.h"
#include "MapLayer.h"
class SnowMapLayer:  public MapLayer
{
protected:
	virtual bool init();  

	void scheduleCallBack(float fDelta);

public:
	/*
	MapLayer(void);
	~MapLayer(void);
	*/
	CREATE_FUNC(SnowMapLayer);

	//void movePlate(float fDelta);


};
