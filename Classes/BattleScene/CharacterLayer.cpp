#include "CharacterLayer.h"

bool CharacterLayer:: init()
{
	//*enemy = new Character[3];
	//enemyAI = new EnemyAI(enemy);

	//触屏事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CharacterLayer::onTouchBegan,this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(CharacterLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//定时判断角色状态
	this->schedule(schedule_selector(CharacterLayer::scheduleCallBack), 1.f);  

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
	cha= new Character(GameSetting::Character::CHARACTER1);
	cha->setPosition(Vec2(300,500));
	this->addChild(cha->getSprite());
}


CharacterLayer::~CharacterLayer(){
	delete hero;
	/*for(int i=0;i<sizeof(enemy)/sizeof(Character);i++)
	{
		delete enemy[i];
	}
	delete enemy;*/
}

void CharacterLayer::setHero(GameSetting::Character hero)
{
	//操作角色
	this->hero = new Character(hero);
	this->hero->setPosition(Vec2(300,500));
	this->addChild(this->hero->getSprite());
}

void CharacterLayer::setEnemy(std::vector<GameSetting::Character> enemy)
{
	//敌人角色
	for(int i=0;i<enemy.size();i++)
	{
		this->enemy.push_back(Character(enemy[i]));
		this->enemy[i].setPosition(Vec2(500,500));
		this->addChild(this->enemy[i].getSprite());
		enemyAI = new EnemyAI(&this->enemy[i]);	
	}
}

