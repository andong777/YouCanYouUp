#include "HUDLayer.h"
#include "CCSGUIReader.h"
#include "CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;


bool HUDLayer::init(){
	if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize(); 

	//体力槽
	healthBar = Sprite::create("HUD/health.png");
	healthBar->setPosition(0,visibleSize.height-30);
	this->addChild(healthBar);
	heroHealth = new Health();

	//生命数
	initHeroLife(INITIAL_LIVES);
	initEnemyLife(INITIAL_LIVES);

	this->schedule(schedule_selector(HUDLayer::scheduleCallBack), 0.2f);

	//返回按钮
	auto returnItem = MenuItemImage::create(
									"HUD/return.png",
									"HUD/return_down.png",
									CC_CALLBACK_1(HUDLayer::menuReturnCallback,this));
	returnItem ->setPosition(Point(returnItem->getContentSize().width/2,returnItem->getContentSize().height/2));
	auto menu = Menu::create(returnItem,NULL);
	menu ->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	//血量接受
	NotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(HUDLayer::getHealth),"getHealth",NULL);
	//生命数损失
	NotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(HUDLayer::loseHeroLife),"loseHeroLife",NULL);
	NotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(HUDLayer::loseEnemyLife),"loseEnemyLife",NULL);

	//触屏事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){   
        CCLOG("touch menu");  
        return true;   
    };
	listener->onTouchEnded = [=](Touch* touch, Event* event){};   
	listener->setSwallowTouches(false);//向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void HUDLayer::scheduleCallBack(float delta){
	healthBar->setScaleX((float)(heroHealth->health)/100);
}

void HUDLayer::getHealth(Object* pSender){
	Health* health = (Health*)pSender;
	heroHealth->health = health->health;
}

void HUDLayer::initHeroLife(int num){
	Size visibleSize = Director::getInstance()->getVisibleSize(); 
	Point start = Point(300,visibleSize.height-30);
	for(int i =0;i<num;i++){
		heroLife.push_back(Sprite::create("HUD/heroLife.png"));
		heroLife.at(i)->setPosition(start+Point(i*50,0));
		this->addChild(heroLife.at(i));
	}
}

void HUDLayer::initEnemyLife(int num){
	Size visibleSize = Director::getInstance()->getVisibleSize(); 
	Point start = Point(visibleSize.width-30,visibleSize.height-30);
	for(int i =0;i<num;i++){
		enemyLife.push_back(Sprite::create("HUD/enemyLife.png"));
		enemyLife.at(i)->setPosition(start-Point(i*50,0));
		this->addChild(enemyLife.at(i));
	}
}

void HUDLayer::loseHeroLife(Object* pSender){
	if(heroLife.empty()) return;
	Sprite* life = heroLife.at(heroLife.size()-1);
	this->removeChild(life);
	heroLife.pop_back();
}

void HUDLayer::loseEnemyLife(Object* pSender){
	if(enemyLife.empty()) return;
	Sprite* life = enemyLife.at(enemyLife.size()-1);
	this->removeChild(life);
	enemyLife.pop_back();
}

void HUDLayer::menuReturnCallback(Ref* pSender){
	MainScene* game = MainScene::create();
	TransitionScene *transition = TransitionFade::create(0.5, game);
	Director::getInstance()->replaceScene(transition);
}