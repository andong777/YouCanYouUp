#include "SPCharacterLayer.h"

bool SPCharacterLayer:: init()
{
	enemyAI = new EnemyAI(enemy);

	//触屏事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SPCharacterLayer::onTouchBegan,this);
	listener->onTouchEnded = CC_CALLBACK_2(SPCharacterLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//定时判断角色状态
	this->schedule(schedule_selector(CharacterLayer::scheduleCallBack), 1.f);

	return true;
}

bool SPCharacterLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
	posBegan = pTouch->getLocation();
	return true;
}

void SPCharacterLayer::onTouchEnded(Touch *touch, Event *unused_event){
	posEnded = touch->getLocation();
	Vec2 force=posEnded-posBegan;
	hero->applyImpulse(force);
}

void SPCharacterLayer::CheckResult(){
	float heroY = hero->getSprite()->getPositionY();
	if(heroY<0){
		CCLOG("you lose");
		Rebirth(hero);
	}
	float enemyY = enemy->getSprite()->getPositionY();
	if(enemyY<0){
		CCLOG("you win");
		Rebirth(enemy);
	}
}

void SPCharacterLayer::Rebirth(Character* cha){
	cha->init();
	cha->setPosition(Vec2(300,500));
}


SPCharacterLayer::~SPCharacterLayer(){
	delete hero;
	delete enemy;
	delete enemyAI;
}

void SPCharacterLayer::setHero(GameSetting::Character hero)
{
	//操作角色
	this->hero = new Character(hero);
	this->hero->setPosition(Vec2(300,500));
	this->addChild(this->hero->getSprite());
}

void SPCharacterLayer::setEnemy(GameSetting::Character enemy)
{
	//敌人角色
	this->enemy = new Character(enemy);
	this->enemy->setPosition(Vec2(500,500));
	this->addChild(this->enemy->getSprite());
	enemyAI = new EnemyAI(this->enemy);	

}
