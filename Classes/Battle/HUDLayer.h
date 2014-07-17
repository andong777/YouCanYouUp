#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
#include "Health.h"
#include "CocosGUI.h" 
#include "Global.h"
#include <vector>
#include "MainScene.h"

USING_NS_CC;

class HUDLayer:  public cocos2d::Layer
{
private:
	void scheduleCallBack(float delta);

	Sprite* healthBar;
	Health* heroHealth;
	
	//获得主角体力的回调函数
	void getHealth(Object* pSender);

	//显示生命用的精灵向量
	std::vector<Sprite*> heroLife;
	std::vector<Sprite*> enemyLife;
	//削减生命数
	void loseHeroLife(Object* pSender);
	void loseEnemyLife(Object* pSender);
	void initHeroLife(int num);
	void initEnemyLife(int num);

	//按钮监听
	void menuReturnCallback(Ref* pSender);

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