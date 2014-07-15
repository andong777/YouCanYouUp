#pragma once

#include "cocos2d.h"
#include "ForestMapLayer.h"
#include "SnowMapLayer.h"
#include "MPCharacterLayer.h"
#include "SPCharacterLayer.h"
#include "GameSetting.h"
#include "HUDLayer.h"

class BattleScene : public cocos2d::Scene
{
private:
	CharacterLayer *characterLayer;

	virtual bool init();

	static Layer* selectMap(GameSetting::Map map); 

public:
	//´´½¨³¡¾°
	static Scene* createScene(bool online, GameSetting::Character hero, GameSetting::Map map, GameSetting::Character enemy, int initNum, std::string &enemyKey);
};

