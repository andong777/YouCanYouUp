#ifndef _CHARACTERLAYER_H_
#define _CHARACTERLAYER_H_

#include "cocos2d.h"
#include "Character.h"
#include "Health.h"
#include <vector>

class CharacterLayer : public cocos2d::Layer
{

protected:

	//触屏操作的起始和终止点
	Point posBegan,posEnded;

	//操控角色
	Character* hero;

	int hero_lives;
	int enemy_lives;

	//判断胜负
	virtual void CheckResult() = 0;
	//角色重生
	virtual void Rebirth(Character* cha) = 0;

	//触屏起始事件
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) = 0;
	//触屏终止事件
	virtual void onTouchEnded(Touch *touch, Event *unused_event) = 0;

	Health* heroHealth;
	int getHeroHealth(){return hero->getHealth();};

	//判断结果schedule
	virtual void checkResSchedule(float delta){ CheckResult(); };

	//恢复schedule 
	virtual void recoverySchedule(float delta) = 0;

public:

	virtual void setHero(GameSetting::Character hero){};
	virtual void setEnemy(std::vector<GameSetting::Character> enemy){};

};

#endif
