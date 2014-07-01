#include "LoginScene.h"
#include "CCSGUIReader.h"
#include "SignupScene.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool LoginScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI5.ExportJson"));
	this->addChild(pNode);
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	return_->addTouchEventListener(CC_CALLBACK_2(LoginScene::returnEvent, this));
	Button *signup = (Button*)(ui::Helper::seekWidgetByName(pNode, "register"));
	signup->addTouchEventListener(CC_CALLBACK_2(LoginScene::signupEvent, this));
	return true;
}

void LoginScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}

void LoginScene::signupEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *signup = SignupScene::create();
		TransitionScene *transition = TransitionFade::create(1, signup);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}