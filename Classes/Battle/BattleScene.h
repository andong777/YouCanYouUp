#pragma once

#include "cocos2d.h"
#include "ForestMapLayer.h"
#include "IslandMapLayer.h"
#include "DesertMapLayer.h"
#include "SPCharacterLayer.h"
#include "MPCharacterLayer.h"
#include "GameSetting.h"
#include "HUDLayer.h"
#include <vector>

class BattleScene : public cocos2d::Scene
{
private:
	CharacterLayer *characterLayer;

	virtual bool init();

	static Layer* selectMap(GameSetting::Map map); 

public:
	//´´½¨³¡¾°
	static Scene* createScene(bool online, GameSetting::Character hero, GameSetting::Map map, std::vector<GameSetting::Character> enemy);
};

