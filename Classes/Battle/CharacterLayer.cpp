#include "CharacterLayer.h"

bool CharacterLayer:: init()
{
	//*enemy = new Character[3];
	//enemyAI = new EnemyAI(enemy);

	// ---------- WebSocket ---------
	//_wsiClient = new cocos2d::network::WebSocket();
	//_wsiClient->init(*this, "ws://211.87.229.116:8001");
	// ---------- WebSocket ---------


	ready = false;


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

	//_wsiClient->send("1&"+std::to_string(force.x)+"&"+std::to_string(force.y));

	hero->applyImpulse(force);
}

void CharacterLayer::scheduleCallBack(float fDelta){
	CheckResult();
	enemyAI->action(hero);
}

void CharacterLayer::CheckResult(){
	float heroY = hero->getSprite()->getPositionY();
	if(heroY<0){
		CCLOG("you lose");
		//Director::getInstance()->end();
		Rebirth(hero,Point(400,500));
	}
	for(auto e: enemy)
	{
		float enemyY = e.getSprite()->getPositionY();
		if(enemyY<0){
			CCLOG("you win");
			//Director::getInstance()->end();
			Rebirth(&e,Point(400,500));
		}
	}
}

void CharacterLayer::Rebirth(Character* cha,Point birthPoint){
	/*this->removeChild(cha->getSprite(),false);
	delete cha;
	cha= new Character(GameSetting::Character::CHARACTER1);*/
	cha->init();
	cha->setPosition(Vec2(300,500));
	//this->addChild(cha->getSprite());
}


CharacterLayer::~CharacterLayer(){
	delete hero;
	
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



// ------------------ websocket function -----------------------
// 开始socket连接
//void CharacterLayer::onOpen(cocos2d::network::WebSocket* ws)
//{
//    CCLOG("OnOpen");
//	_wsiClient->send("game1");
//}
//
//// 接收到了消息
//void CharacterLayer::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
//{
//    std::string textStr = data.bytes;
//    CCLOG(textStr.c_str());
//	int begin = textStr.find_first_of("&");
//	int end = textStr.find_last_of("&");
//	std::string num = textStr.substr(0, begin);
//	std::string s1 = textStr.substr(begin+1, end-begin-1);
//	float x = std::stod(s1);
//	std::string s2 = textStr.substr(end+1, textStr.length()-end-2);
//	float y = std::stod(s2);
//
//	hero->applyImpulse(Vec2(x,y));
//}
//
//// 连接关闭
//void CharacterLayer::onClose(cocos2d::network::WebSocket* ws)
//{
//    if (ws == _wsiClient)
//    {
//        _wsiClient = NULL;
//    }
//    CC_SAFE_DELETE(ws);
//    CCLOG("onClose");
//}
//
//// 遇到错误
//void CharacterLayer::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
//{
//    if (ws == _wsiClient)
//    {
//        char buf[100] = {0};
//        sprintf(buf, "an error was fired, code: %d", error);
//    }
//    CCLOG("Error was fired, error code: %d", error);
//}