#include "Character.h"
#include "CharacterParameter.h"

//有图片的构造函数
Character::Character(const std::string &filename,Point p)
{
	sprite = Sprite::create(filename); 
	sprite->setScale(0.3f);

	body = PhysicsBody::createCircle(sprite->getContentSize().width *0.3/ 2);
	/*
	Vec2* polygonEdge = new Vec2[4];float w = sprite->getContentSize().width*0.3/2;
	polygonEdge[0]= Vec2(-w,-w);polygonEdge[3]= Vec2(w,-w);polygonEdge[2]= Vec2(w,w);polygonEdge[1]= Vec2(-w,w);
	body = PhysicsBody::createPolygon(polygonEdge,4,PHYSICSBODY_MATERIAL_DEFAULT,Vec2(0,0));
	*/
	sprite->setPhysicsBody(body);
    sprite->setPosition(p);
    
	//设置刚体的shape的弹性
	body->getShape(0)->setRestitution(CharacterParameter::character1_restitution);
	//设置最大体力，初始体力与最大体力相同
	max_health = CharacterParameter::character1_max_health;
	health = max_health;
	//设置重力
	body->setMass(CharacterParameter::character1_mass);
	
}
//没有图片的构造函数
Character::Character(Point p){
	sprite = Sprite::create();
	body = PhysicsBody::createCircle(40);
	sprite->setPhysicsBody(body);
    sprite->setPosition(p);

}

Sprite* Character::getSprite(){
	return sprite;
}

PhysicsBody* Character::getBody(){
	return body;
}

Character::~Character(void)
{
	
}


void Character::applyImpulse(Vec2 vec){
	//body->applyForce(vec);
	
	//vec.x*=200;
	//vec.y*=200;
	vec*= body->getMass()/2;
	body->applyImpulse(vec);
}

Vec2 Character::getPosition(){
	return body->getPosition();
}

/*
Vec2 Character::getLastForce(){
	return this->lastForce;
}

void Character::setLastForce(Vec2 newForce){
	lastForce= newForce;
}*/