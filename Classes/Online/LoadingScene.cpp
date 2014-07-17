#include "LoadingScene.h"
#include "CocosGUI.h"  
#include "CCSGUIReader.h"
#include "Battle/BattleScene.h"
#include "Battle/CmdTool.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool LoadingScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI2.ExportJson"));
	this->addChild(pNode);
	
	// ---------- WebSocket ---------
	_wsiClient = new cocos2d::network::WebSocket();
	_wsiClient->init(*this, "ws://202.194.14.196:8001");
	// ---------- WebSocket ---------
	
	return true;
}

// ------------------ websocket function -----------------------
// 开始socket连接
void LoadingScene::onOpen(cocos2d::network::WebSocket* ws)
{
    CCLOG("connect");
}

// 接收到了消息
void LoadingScene::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
	std::string msgStr = data.bytes;
    CCLOG("收到的消息：%s",msgStr.c_str());
    std::string cmdStr = CmdTool::getCmd(msgStr);
    std::string cmdPara = CmdTool::getCmdPara(msgStr);

	std::vector<GameSetting::Character> enemy;
	enemy.push_back(GameSetting::Character::CHARACTER2);
    Scene *game = BattleScene::createScene(true, GameSetting::Character::CHARACTER1, GameSetting::Map::DESERT, enemy);
	TransitionScene *transition = TransitionFade::create(0.5, game);
	Director::getInstance()->replaceScene(transition);
}

// 连接关闭
void LoadingScene::onClose(cocos2d::network::WebSocket* ws)
{
    if (ws == _wsiClient)
    {
        _wsiClient = NULL;
    }
    CC_SAFE_DELETE(ws);
    CCLOG("onClose");
}

// 遇到错误
void LoadingScene::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    if (ws == _wsiClient)
    {
        char buf[100] = {0};
        sprintf(buf, "an error was fired, code: %d", error);
    }
    CCLOG("Error was fired, error code: %d", error);
}

