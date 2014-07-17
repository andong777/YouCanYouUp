#include "MainScene.h"
#include "CCSGUIReader.h"
#include "Online\LoginScene.h"
#include "HelpScene.h"
#include "Local\CharacterSelectScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("home.ExportJson"));
	this->addChild(pNode);
	Button *single = (Button*)(ui::Helper::seekWidgetByName(pNode, "Info_btn"));
	single->addTouchEventListener(CC_CALLBACK_2(MainScene::singleEvent, this));
	Button *online = (Button*)(ui::Helper::seekWidgetByName(pNode, "more_games_btn"));
	online->addTouchEventListener(CC_CALLBACK_2(MainScene::onlineEvent, this));
	Button *help = (Button*)(ui::Helper::seekWidgetByName(pNode, "Help_btn"));
	help->addTouchEventListener(CC_CALLBACK_2(MainScene::helpEvent, this));

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/bgMusic.mp3",true); //²¥·Å±³¾°ÒôÀÖ

    return true;
}

void MainScene::singleEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //²¥·ÅÒôÐ§
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *menu = CharacterSelectScene::create();
		TransitionScene *transition = TransitionFade::create(0.5, menu);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}

void MainScene::onlineEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //²¥·ÅÒôÐ§
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *login = LoginScene::create();
		TransitionScene *transition = TransitionFade::create(0.5, login);
		Director::getInstance()->pushScene(transition);
		break;
	}
}

void MainScene::helpEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //²¥·ÅÒôÐ§
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *help = HelpScene::create(); 
		TransitionScene *transition = TransitionFade::create(0.5, help);
		Director::getInstance()->pushScene(transition);
		break;
	}
}
