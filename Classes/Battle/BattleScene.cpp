#include "BattleScene.h"

USING_NS_CC;

Scene* BattleScene::createScene(GameSetting::Map map, GameSetting::Character hero, std::vector<GameSetting::Character> enemy){
	//创建场景
	auto scene = Scene::createWithPhysics();
	//创建场景层
	//auto mapLayer = MapLayer::create();
	auto mapLayer = BattleScene::selectMap(map);
	//创建角色层
	auto characterLayer = CharacterLayer::create();
	characterLayer->setHero(hero);
	characterLayer->setEnemy(enemy);
	//characterLayer->setCharacter(character);
	//创建UI层
	//auto uiLayer = UILayer::create();

	//将层添加到场景中
	scene->addChild(mapLayer);
	scene->addChild(characterLayer);

	//mapLayer->ready = true;
	characterLayer->ready = true;

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
