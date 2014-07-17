#include "MapSelectScene.h"
#include "Battle\BattleScene.h"
#include "CCSGUIReader.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool MapSelectScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("single.ExportJson"));
	this->addChild(pNode);

	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_1"));
	desertBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_3"));
	forestBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_4"));
	islandBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_5"));

	desertBtn->addTouchEventListener(CC_CALLBACK_2(MapSelectScene::selectEvent, this));
	forestBtn->addTouchEventListener(CC_CALLBACK_2(MapSelectScene::selectEvent, this));
	islandBtn->addTouchEventListener(CC_CALLBACK_2(MapSelectScene::selectEvent, this));

	return_->addTouchEventListener(CC_CALLBACK_2(MapSelectScene::returnEvent, this));
	return true;
}

void MapSelectScene::selectEvent(Ref *pSender, Widget::TouchEventType type)
{

	switch(type)
	{
	case Widget::TouchEventType::ENDED:
		if(pSender == desertBtn)
		{
			mapSelected = GameSetting::Map::DESERT;
		}
		else if(pSender == forestBtn)
		{
			mapSelected = GameSetting::Map::FOREST;
		}else if(pSender == islandBtn)
		{
			mapSelected = GameSetting::Map::ISLAND;
		}
		std::vector<GameSetting::Character> enemy;
		enemy.push_back(GameSetting::Character::CHARACTER2);
		Scene *game = BattleScene::createScene(false, charSelected, mapSelected, enemy);
		TransitionScene *transition = TransitionFade::create(0.5, game);
		Director::getInstance()->replaceScene(transition);
	}
}

void MapSelectScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}

void MapSelectScene::setCharSelected(GameSetting::Character cha)
{
	this->charSelected = cha;
}