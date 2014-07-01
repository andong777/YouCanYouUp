#include "cocos2d.h"
#include "MapLayer.h"
#include "SnowMapLayer.h"
#include "CharacterLayer.h"
#include "GameSetting.h"

class BattleScene : public cocos2d::Scene
{
private:
	//UI界面层
	//Layer* UILayer;
	//地形场景层
	//Layer* mapLayer;
	//角色层
	//Layer* characterLayer;
	//初始化
	virtual bool init();
	static Layer* selectMap(GameSetting::Map map); 
public:
	//创建场景
	static Scene* createScene(GameSetting::Map map);
	CREATE_FUNC(BattleScene);
};

