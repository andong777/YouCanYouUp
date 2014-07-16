#pragma once

#include "BodyInfo.h"

USING_NS_CC;



class MapLayer:  public cocos2d::Layer
{
private:
	/*void Ready(Object * obj);*/
	void callBack(float delta);
protected:
	virtual bool init();  
	BodyInfo * bodyInfo;
	
public:
	//bool ready;

	CREATE_FUNC(MapLayer);

	void addBody(PhysicsBody* tem){(bodyInfo->body).push_back(tem);}

	void addShape(ShapeType tem){(bodyInfo->shape).push_back(tem);}
	
};