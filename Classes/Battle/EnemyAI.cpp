#include "EnemyAI.h"

void EnemyAI::chase(Vec2 vec){
	//Vec2 vec = target->getPosition()-cha->getPosition();
	
	//vec*=50;
	cha->applyImpulse(vec);
}

void EnemyAI::escape(Vec2 vec){
	vec*=-1;
	//vec*=50;
	cha->applyImpulse(vec);
}

void EnemyAI::dodge(Vec2 vec){
	//vec*=50;
	/*
	float temp = vec.y;
	vec.y=vec.x;
	vec.x = temp;//x与y交换*/

	vec.x*=-1;//向量旋转90度
	cha->applyImpulse(vec);
}

void EnemyAI::action(Character* target){

	//目标的上次受力和位置
	//Vec2 tLastForce = target->getLastForce();
	Vec2 tPos = target->getPosition();

	//AI的上次受力和位置
	//Vec2 lastForce = cha->getLastForce();
	Vec2 pos = cha->getPosition();

	//AI到目标的向量
	Vec2 vec = tPos- pos;
	/*
	//行动判断
	if(tPos.y>pos.y){
		//目标在AI下方
		if(tLastForce.cross(pos)>1/2){
			//目标冲向AI,AI躲避(余弦值大于1/2)
			dodge(vec);
		}
		else{
			//目标远离AI，AI追赶
			chase(vec);
		}
	}
	else{
		//目标在AI上方，AI追赶
		chase(vec);
	}
	*/
	chase(vec*2);
	//cha->setLastForce(Vec2(0,0));
}


EnemyAI::EnemyAI(Character* cha){
	this->cha = cha;
}
EnemyAI::~EnemyAI(){
}