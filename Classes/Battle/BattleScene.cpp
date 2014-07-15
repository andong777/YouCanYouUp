#include "BattleScene.h"

USING_NS_CC;

Scene* BattleScene::createScene(bool online, GameSetting::Character hero, GameSetting::Map map, GameSetting::Character enemy, int initNum, std::string &enemyKey){
	//创建场景 
	auto scene = Scene::createWithPhysics();
	//创建场景层
	auto mapLayer = BattleScene::selectMap(map);
	//创建角色层
	CharacterLayer *characterLayer;
	if(online)
	{
		characterLayer = MPCharacterLayer::create();
		((MPCharacterLayer*)characterLayer)->enemyKey = enemyKey;
	}
	else
	{
		characterLayer = SPCharacterLayer::create();
	}
		
	characterLayer->setHero(hero);
	characterLayer->setEnemy(enemy);

	if(online)
	{
		((MPCharacterLayer*)characterLayer)->initBattleScene(initNum);
	}

	//将层添加到场景中
	scene->addChild(mapLayer);
	scene->addChild(characterLayer);

	//设置物理世界刚体可见
	scene->getPhysicsWorld()->setDebugDrawMask(true);
	//设置物理世界的重力和倍速
	scene->getPhysicsWorld()->setGravity(Vec2(0,-300));
	scene->getPhysicsWorld()->setSpeed(1.5f);

	return scene;
}

bool BattleScene::init(){
	return true;
}

Layer* BattleScene::selectMap(GameSetting::Map map){
	if(map==GameSetting::Map::FOREST){
		return ForestMapLayer::create();
	}
	if(map==GameSetting::Map::SNOW){
		return SnowMapLayer::create();
	}
	return nullptr;
}
