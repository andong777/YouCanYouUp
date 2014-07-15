
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

	//场景和角色层
	/*auto battleScene = (BattleScene*)this->getScene();
	characterLayer = (CharacterLayer*)(battleScene->getChildByTag(2));*/
	//characterLayer = (CharacterLayer*)(this->getScene()->getChildByTag(2));

	//体力槽
	healthBar = Sprite::create("health.png");
	healthBar->setPosition(20,visibleSize.height-20);
	this->addChild(healthBar);
	heroHealth = new Health();
	//
	//Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("UILayer/single.ExportJson"));
	//this->addChild(pNode);


	//Button* aaa;
	this->schedule(schedule_selector(HUDLayer::scheduleCallBack), 0.2f);

	NotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(HUDLayer::getHealth),"getHealth",NULL);

	return true;
}

void HUDLayer::scheduleCallBack(float delta){
	healthBar->setScaleX((float)(heroHealth->health)/100);
}


void HUDLayer::getHealth(Object* pSender){
	Health* health = (Health*)pSender;
	heroHealth->health = health->health;
}