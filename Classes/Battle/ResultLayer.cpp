#include "ResultLayer.h"
#include "MainScene.h"
#include "Local/CharacterSelectScene.h"
USING_NS_CC;



bool ResultLayer::init(Result result){
	switch (result)
	{
	case Result::WIN:
		youWinInit();
		break;
	case Result::LOSE:
		youLoseInit();
		break;
	default:
		break;
	}
	return true;
}

void ResultLayer::youWinInit()
{
	auto sp01= Sprite::create("youwin.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	sp01->setPosition(visibleSize.width*0.5f,visibleSize.height*0.5f);
	this ->addChild(sp01,0);
	addButton();
}

void ResultLayer::youLoseInit()
{
	auto sp02= Sprite::create("youlose.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	sp02->setPosition(visibleSize.width*0.5f,visibleSize.height*0.5f);
	this ->addChild(sp02,0);
	addButton();
}

void ResultLayer::addButton()
{
	auto replayItem = MenuItemImage::create(
									"replay.png",
									"replay.png",
									CC_CALLBACK_1(ResultLayer::menuReplayCallback,this));
	auto exitItem = MenuItemImage::create(
									"exit.png",
									"exit.png",
									CC_CALLBACK_1(ResultLayer::menuCloseCallback,this)); 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	replayItem ->setPosition(Point(replayItem->getContentSize().width/2,replayItem->getContentSize().height/2));
	exitItem ->setPosition(Point(visibleSize.width-(exitItem->getContentSize().width/2),exitItem->getContentSize().height/2));
	auto menu = Menu::create(replayItem,exitItem,NULL);
	//auto menu1 = Menu::create(exitItem,NULL);
	menu ->setPosition(Vec2::ZERO);
	this->addChild(menu,1);
	//this->addChild(menu1,1);

}

void ResultLayer::menuReplayCallback(Ref* pSender)
{
	/*Scene* game = MainScene::create();*/
	CharacterSelectScene* game = CharacterSelectScene::create();
	TransitionScene *transition = TransitionFade::create(0.5, game);
	Director::getInstance()->replaceScene(transition);
	//Director::sharedDirector()->runWithScene(game);
}

void ResultLayer::menuCloseCallback(Ref* pSender)
{
	MainScene* game = MainScene::create();
	TransitionScene *transition = TransitionFade::create(0.5, game);
	Director::getInstance()->replaceScene(transition);
}
