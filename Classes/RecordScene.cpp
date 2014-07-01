#include "RecordScene.h"
#include "CCSGUIReader.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool RecordScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI3.ExportJson"));
	this->addChild(pNode);
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	return_->addTouchEventListener(CC_CALLBACK_2(RecordScene::returnEvent, this));
	return true;
}

void RecordScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}