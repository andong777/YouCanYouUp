#include "HelpScene.h"
#include "CocosGUI.h"  
#include "CCArmature.h"
#include "CCSGUIReader.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool HelpScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Animation0.png","Animation0.plist","Animation.ExportJson");
	CCArmature *armature = CCArmature::create("Animation");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.5f);
	armature->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.5));
	this->addChild(armature);*/

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("help.ExportJson"));
	this->addChild(pNode);
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button"));
	return_->addTouchEventListener(CC_CALLBACK_2(HelpScene::returnEvent, this));
	return true;
}

void HelpScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}