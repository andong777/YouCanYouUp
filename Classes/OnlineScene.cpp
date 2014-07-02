#include "OnlineScene.h"
#include "CCSGUIReader.h"
#include "BattleScene\BattleScene.h"
#include "RecordScene.h"
#include "LoginScene.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool OnlineScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI1.ExportJson"));
	this->addChild(pNode);
	Button *pvp = (Button*)(ui::Helper::seekWidgetByName(pNode, "PVP"));
	pvp->addTouchEventListener(CC_CALLBACK_2(OnlineScene::pvpEvent, this));
	Button *record = (Button*)(ui::Helper::seekWidgetByName(pNode, "record"));
	record->addTouchEventListener(CC_CALLBACK_2(OnlineScene::recordEvent, this));
	Button *offline = (Button*)(ui::Helper::seekWidgetByName(pNode, "offline"));
	offline->addTouchEventListener(CC_CALLBACK_2(OnlineScene::offlineEvent, this));
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	return_->addTouchEventListener(CC_CALLBACK_2(OnlineScene::returnEvent, this));
	return true;
}

void OnlineScene::pvpEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		/*Scene *matching = MatchingScene::create();
		Director::getInstance()->replaceScene(MatchingScene);*/
		// Æ¥Åä¹¤×÷
		Scene *game = BattleScene::create();
		TransitionScene *transition = TransitionFade::create(1, game);
		Director::getInstance()->replaceScene(transition);
		break;
	}	
}

void OnlineScene::recordEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *record = RecordScene::create();
		TransitionScene *transition = TransitionFade::create(1, record);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}

void OnlineScene::offlineEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *login = LoginScene::create();
		TransitionScene *transition = TransitionFade::create(1, login);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}

void OnlineScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}