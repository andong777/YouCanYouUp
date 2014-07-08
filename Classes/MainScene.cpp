#include "MainScene.h"
#include "CCSGUIReader.h"
#include "Online\OnlineScene.h"
#include "HelpScene.h"
#include "Local\CharacterSelectScene.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	std::string textStr("1&203&712.43");
	int begin = textStr.find_first_of("&");
	int end = textStr.find_last_of("&");
	CCLOG("%d, %d", begin, end);
	//std::string num = textStr.substr(0, begin);
	std::string s1 = textStr.substr(begin+1, end-begin-1);
	float x = std::stod(s1);
	std::string s2 = textStr.substr(end+1, textStr.length()-end-2);
	float y = std::stod(s2);
	//CCLOG("%s:(%d,%d)", num, x, y);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//Node* pNode = SceneReader::getInstance()->createNodeWithSceneFile("home/home.ExportJson");
	//this->addChild(pNode);
	// 获取精灵并执行操作
	/*ComRender *render = (ComRender*)(pNode->getChildByTag(10008)->getComponent("CCArmature"));
	Sprite *object = (Sprite*)(render->getNode());
	object->runAction(MoveBy::create(5, Vec2(-1000, 0)));*/
	// 获取UI组件并绑定事件监听
	/*ComRender *render2 = (ComRender*)(pNode->getChildByTag(10010)->getComponent("GUIComponent"));
	Widget *widget = (Widget*)(render2->getNode());
	widget->addTouchEventListener(CC_CALLBACK_2(MainScene::touchEvent, this));*/

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("home.ExportJson"));
	this->addChild(pNode);
	Button *single = (Button*)(ui::Helper::seekWidgetByName(pNode, "Info_btn"));
	single->addTouchEventListener(CC_CALLBACK_2(MainScene::singleEvent, this));
	Button *online = (Button*)(ui::Helper::seekWidgetByName(pNode, "more_games_btn"));
	online->addTouchEventListener(CC_CALLBACK_2(MainScene::onlineEvent, this));
	Button *help = (Button*)(ui::Helper::seekWidgetByName(pNode, "Help_btn"));
	help->addTouchEventListener(CC_CALLBACK_2(MainScene::helpEvent, this));

    return true;
}

void MainScene::singleEvent(Ref *pSender, Widget::TouchEventType type)
{
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
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *online = OnlineScene::create();
		TransitionScene *transition = TransitionFade::create(0.5, online);
		Director::getInstance()->pushScene(transition);
		break;
	}
}

void MainScene::helpEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *help = HelpScene::create(); 
		TransitionScene *transition = TransitionFade::create(0.5, help);
		Director::getInstance()->pushScene(transition);
		break;
	}
}
