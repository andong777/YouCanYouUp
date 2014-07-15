#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
//#include "BattleScene.h"
#include "Health.h"

USING_NS_CC;

class HUDLayer:  public cocos2d::Layer
{
private:
	void scheduleCallBack(float delta);
	//BattleScene* battleScene;
	//CharacterLayer* characterLayer;
	Sprite* healthBar;
	Health* heroHealth;
	//获得主角体力的回调函数
	void getHealth(Object* pSender);

protected:
	virtual bool init();  

public:

	~HUDLayer(void){
		delete heroHealth;
		NotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	}
	
	CREATE_FUNC(HUDLayer);
	

};


#endif