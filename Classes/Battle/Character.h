#pragma once
#include "cocos2d.h"
#include "CharacterParameter.h"
USING_NS_CC;

class Character
{
private:
	//角色的精灵
	Sprite* sprite;
	//角色的物理刚体
	PhysicsBody* body;
	//角色体力
	int health;

	float mass;

	//角色上次受力
	//Vec2 lastForce;

	// 这个人是谁？
	GameSetting::Character who;
	//角色属性
	//float mass;
	int maxHealth;


public:
	Character(GameSetting::Character character);
	Character();
	~Character(void);
	//返回角色的精灵指针
	Sprite* getSprite();
	//返回角色的刚体指针
	PhysicsBody* getBody();
	//给刚体叠加一个速度
	void applyImpulse(Vec2 vec);

	void applyMove(Vec2 vec){
		vec = vec/vec.length();
		applyImpulse(vec*500);
	}

	//获取质量
	float getMass();

	//返回角色位置
	Vec2 getPosition();
	//设置角色位置
	void setPosition(Vec2 pos);

	//消耗角色体力
	bool useHealth(int v);
	//回复角色体力
	void recovery(int v);
	//返回当前体力值
	int getHealth();

	int getMaxHealth(){return maxHealth;}

	void init();
};

