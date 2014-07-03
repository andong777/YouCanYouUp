#include "SignupScene.h"
#include "LoginScene.h"
#include "CCSGUIReader.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool SignupScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI4.ExportJson"));
	this->addChild(pNode);
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	return_->addTouchEventListener(CC_CALLBACK_2(SignupScene::returnEvent, this));
	Button *login = (Button*)(ui::Helper::seekWidgetByName(pNode, "login"));
	login->addTouchEventListener(CC_CALLBACK_2(SignupScene::loginEvent, this));
	return true;
}

void SignupScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}

void SignupScene::loginEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *login = LoginScene::create();
		TransitionScene *transition = TransitionFade::create(1, login);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}