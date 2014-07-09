//#pragma once
#ifndef _CHARACTERLAYER_H_
#define _CHARACTERLAYER_H_

#include "cocos2d.h"
#include "Character.h"
#include "EnemyAI.h"
#include <vector>
#include "network/WebSocket.h"
#include "Health.h"


class CharacterLayer : public cocos2d::Layer/*, public cocos2d::network::WebSocket::Delegate*/
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

	Health* heroHealth;
	void sendHealth(Object* obj);
	int getHeroHealth();

public:
	
	virtual bool init();  
	~CharacterLayer();
	CREATE_FUNC(CharacterLayer);

	void setHero(GameSetting::Character hero);
	void setEnemy(std::vector<GameSetting::Character> enemy);


	// for virtual function in websocket delegate
	/*virtual void onOpen(cocos2d::network::WebSocket* ws);
	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	virtual void onClose(cocos2d::network::WebSocket* ws);
	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);*/

	// the websocket io client
	//cocos2d::network::WebSocket* _wsiClient;
};

#endif