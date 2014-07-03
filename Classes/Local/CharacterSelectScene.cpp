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

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("CharacterselectUI.ExportJson"));
	this->addChild(pNode);

	returnBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	nextBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "mapselect"));
	cha1Btn = ui::Helper::seekWidgetByName(pNode, "CheckBox1");
	cha2Btn = ui::Helper::seekWidgetByName(pNode, "CheckBox2");

	cha1Btn->addTouchEventListener(CC_CALLBACK_2(CharacterSelectScene::selectEvent, this));
	cha2Btn->addTouchEventListener(CC_CALLBACK_2(CharacterSelectScene::selectEvent, this));
	returnBtn->addTouchEventListener(CC_CALLBACK_2(CharacterSelectScene::returnEvent, this));
	nextBtn->addTouchEventListener(CC_CALLBACK_2(CharacterSelectScene::nextEvent, this));
	return true;
}

void CharacterSelectScene::selectEvent(Ref *pSender, Widget::TouchEventType type)
{
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

	}
}

void CharacterSelectScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}

void CharacterSelectScene::nextEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	std::vector<GameSetting::Character> enemy;
	enemy.push_back(GameSetting::Character::CHARACTER1);
	enemy.push_back(GameSetting::Character::CHARACTER2);
	auto map = MapSelectScene::create();
	map->setCharSelected(charSelected);
	TransitionScene *transition = TransitionFade::create(0.5, map);
	Director::getInstance()->replaceScene(transition);
}