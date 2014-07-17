#include "CharacterSelectScene.h"
#include "MapSelectScene.h"
#include "CCSGUIReader.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool CharacterSelectScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("characterselect.ExportJson"));
	this->addChild(pNode);

	returnBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_16"));
	cha1Btn = ui::Helper::seekWidgetByName(pNode, "Button_14");
	cha2Btn = ui::Helper::seekWidgetByName(pNode, "Button_15");

	cha1Btn->addTouchEventListener(CC_CALLBACK_2(CharacterSelectScene::selectEvent, this));
	cha2Btn->addTouchEventListener(CC_CALLBACK_2(CharacterSelectScene::selectEvent, this));
	returnBtn->addTouchEventListener(CC_CALLBACK_2(CharacterSelectScene::returnEvent, this));
	return true;
}

void CharacterSelectScene::selectEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //播放音效
	switch(type)
	{
	case Widget::TouchEventType::ENDED:
		if(pSender == cha1Btn)
		{
			charSelected = GameSetting::Character::CHARACTER1;
		}
		else if(pSender == cha2Btn)
		{
			charSelected = GameSetting::Character::CHARACTER2;
		}
		else
		{
			charSelected = GameSetting::Character::CHARACTER1;
		}
		auto map = MapSelectScene::create();
		map->setCharSelected(charSelected);
		TransitionScene *transition = TransitionFade::create(0.5, map);
		Director::getInstance()->replaceScene(transition);
		break;
	}
}

void CharacterSelectScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //播放音效
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}
