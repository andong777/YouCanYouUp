#include "OnlineScene.h"
#include "CCSGUIReader.h"
#include "Battle\BattleScene.h"
#include "RecordScene.h"
#include "LoginScene.h"
#include "LoadingScene.h"
#include "base/CCUserDefault.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool OnlineScene::init()
{
	if(!Scene::init()){
		return false;
	}

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

	// 找到显示用户名的文本框
	text = (Text*)(ui::Helper::seekWidgetByName(pNode, "playername"));
	std::string username = UserDefault::getInstance()->getStringForKey("username");
	text->setText(username);

	return true;
}

void OnlineScene::pvpEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //播放音效
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *loading = LoadingScene::create();
		Director::getInstance()->replaceScene(loading);
		break;
	}	
}

void OnlineScene::recordEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //播放音效
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *record = RecordScene::create();
		TransitionScene *transition = TransitionFade::create(0.5, record);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}

void OnlineScene::offlineEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //播放音效
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *login = LoginScene::create();
		TransitionScene *transition = TransitionFade::create(0.5, login);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}

void OnlineScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //播放音效
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}