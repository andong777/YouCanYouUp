#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "EnemyAI.h"
#include <vector>

class CharacterLayer : public cocos2d::Layer
{
private:
	//触屏操作的起始和终止点
	Point posBegan,posEnded;
	//操控角色
	Character* hero;
	//对手角色
	//Character enemy[3];
	std::vector<Character> enemy;
	EnemyAI* enemyAI;
	
	//schedule调用函数
	void scheduleCallBack(float fDelta);
	//判断胜负
	void CheckResult();
	//角色重生
	void Rebirth(Character* cha,Point birthPoint);

	//触屏起始事件
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	//触屏终止事件
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

public:
	virtual bool init();  
	~CharacterLayer();
	CREATE_FUNC(CharacterLayer);

	void setHero(GameSetting::Character hero);
	void setEnemy(std::vector<GameSetting::Character> enemy);
};

