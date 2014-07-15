#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "network/WebSocket.h"

class LoadingScene : public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate
{
public:

    virtual bool init();  

    CREATE_FUNC(LoadingScene);

	// for virtual function in websocket delegate
	virtual void onOpen(cocos2d::network::WebSocket* ws);
	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	virtual void onClose(cocos2d::network::WebSocket* ws);
	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

	// the websocket io client
	cocos2d::network::WebSocket* _wsiClient;

};

#endif // __LOADING_SCENE_H__
