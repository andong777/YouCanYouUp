#ifndef _CHARACTERLAYER_H_
#define _CHARACTERLAYER_H_

#include "cocos2d.h"
#include "Character.h"
#include "Health.h"

class CharacterLayer : public cocos2d::Layer
{

protected:

	//触屏操作的起始和终止点
	Point posBegan,posEnded;
	//操控角色
	Character* hero;
	Character* enemy;

	//判断胜负
	virtual void CheckResult() = 0;
	//角色重生
	virtual void Rebirth(Character* cha) = 0;

	//触屏起始事件
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) = 0;
	//触屏终止事件
	virtual void onTouchEnded(Touch *touch, Event *unused_event) = 0;

	Health* heroHealth;
	void sendHealth(Object* obj){
	/*
	Health* health = (Health*)obj;
	health->health = getHeroHealth();*/
};
	int getHeroHealth(){return hero->getHealth();};

public:

	//schedule调用函数
	virtual void scheduleCallBack(float fDelta){ CheckResult(); };

	virtual void setHero(GameSetting::Character hero){};
	virtual void setEnemy(GameSetting::Character enemy){};

};

#endif
