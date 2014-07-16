#include "MapLayer.h"
USING_NS_CC;

/*
MapLayer::MapLayer(void)
{
}


MapLayer::~MapLayer(void)
{
}
*/


bool MapLayer:: init(){
	if ( !Layer::init() )
    {
        return false;
    }

	bodyInfo = new BodyInfo();

	this->schedule(schedule_selector(MapLayer::callBack),0.1f,20,0);
	/*NotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(MapLayer::Ready),"getBodyInfo",NULL);*/
	

	return true;
}

//
//void MapLayer::Ready(Object * obj){
//	NotificationCenter::sharedNotificationCenter()->postNotification("getBodyInfo",bodyInfo);
//}
void MapLayer::callBack(float delta){
	NotificationCenter::sharedNotificationCenter()->postNotification("getBodyInfo",bodyInfo);
}