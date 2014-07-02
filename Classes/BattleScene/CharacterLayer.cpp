#include "CharacterLayer.h"


bool CharacterLayer:: init(){
	//操作角色
	hero = new Character("Character/monster1.png",Point(300,500));
	this->addChild(hero->getSprite());
	//敌人角色
	enemy = new Character(Point(450,500));
	this->addChild(enemy->getSprite());
	enemyAI = new EnemyAI(enemy);


	//触屏事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CharacterLayer::onTouchBegan,this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(CharacterLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);


	//定时判断角色状态
	this->schedule(schedule_selector(CharacterLayer::scheduleCallBack), 0.2f);  


	return true;
}

bool CharacterLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
	posBegan = pTouch->getLocation();
	return true;
}

void CharacterLayer::onTouchEnded(Touch *touch, Event *unused_event){
	posEnded = touch->getLocation();
	Vec2 force=posEnded-posBegan;
	hero->applyImpulse(force);
}

void CharacterLayer::scheduleCallBack(float fDelta){
	CheckResult();
	enemyAI->action(hero);
}

void CharacterLayer::CheckResult(){
	float heroY = hero->getSprite()->getPositionY();
	if(heroY<0){
		CCLOG("you Lose");
		//Director::getInstance()->end();
		Rebirth(hero,Point(400,500));
	}
	
}

void CharacterLayer::Rebirth(Character* cha,Point birthPoint){
	this->removeChild(cha->getSprite(),false);
	delete cha;
	cha= new Character("Character/monster1.png",birthPoint);
	this->addChild(cha->getSprite());
}



CharacterLayer::~CharacterLayer(){
	delete hero;
	delete enemy;
	delete enemyAI;
}