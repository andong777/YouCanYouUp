#include "cocos2d.h"
#include "Character.h"
#include "network/WebSocket.h"
#include "CharacterLayer.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "SimpleAudioEngine.h"
class MPCharacterLayer : public CharacterLayer, public cocos2d::network::WebSocket::Delegate
{
private:
	Character *enemy;
	//判断胜负
	void CheckResult();
	//角色重生
	void Rebirth(Character* cha);

	//触屏起始事件
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	//触屏终止事件
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	//恢复schedule 
	virtual void recoverySchedule(float delta);

public:

	virtual bool init();  
	~MPCharacterLayer();
	CREATE_FUNC(MPCharacterLayer);

	void setHero(GameSetting::Character hero);
	void setEnemy(std::vector<GameSetting::Character> enemy);

	// for virtual function in websocket delegate
	virtual void onOpen(cocos2d::network::WebSocket* ws);
	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	virtual void onClose(cocos2d::network::WebSocket* ws);
	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

	// the websocket io client
	cocos2d::network::WebSocket* _wsiClient;

	std::string enemyKey;

	void initBattleScene(int tag);

	void sendFightCmd(float fDelta);
};
