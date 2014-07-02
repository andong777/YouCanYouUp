#include "SingleMenuScene.h"
#include "BattleScene\BattleScene.h"
#include "CCSGUIReader.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool SingleMenuScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("single.ExportJson"));
	this->addChild(pNode);

	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_1"));
	defaultBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_3"));
	snowBtn = (Button*)(ui::Helper::seekWidgetByName(pNode, "Button_4"));

	defaultBtn->addTouchEventListener(CC_CALLBACK_2(SingleMenuScene::selectEvent, this));
	snowBtn->addTouchEventListener(CC_CALLBACK_2(SingleMenuScene::selectEvent, this));
	return_->addTouchEventListener(CC_CALLBACK_2(SingleMenuScene::returnEvent, this));
	return true;
}

void SingleMenuScene::selectEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type)
	{
	case Widget::TouchEventType::ENDED:
		GameSetting::Map map = GameSetting::Map::DEFAULT;
		if(pSender == defaultBtn)
		{
			map = GameSetting::Map::DEFAULT;
		}
		else if(pSender == snowBtn)
		{
			map = GameSetting::Map::SNOW;
		}

		std::vector<GameSetting::Character> enemy;
		enemy.push_back(GameSetting::Character::CHARACTER1);
		enemy.push_back(GameSetting::Character::CHARACTER2);
		Scene *game = BattleScene::createScene(map, GameSetting::Character::CHARACTER1, enemy);
		TransitionScene *transition = TransitionFade::create(0.5, game);
		Director::getInstance()->replaceScene(transition);

	}
}

void SingleMenuScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}