#include "Battle/Character.h"
#include "Battle/BodyInfo.h"

#ifndef MANAGERINFOMATION_DEFINE
#define MANAGERINFOMATION_DEFINE

/**
*	存储EnemyManager的所需要信息
*/
class ManagerInfo{

protected:
	Character * hero;
	std::vector<Character*> enemys;
	BodyInfo* bodyInfo;

public:
	
	Character * getHero(){return hero;}
	void setHero(Character * hero){this->hero=hero;}

	void addEnemy(Character* enemy){
		enemys.push_back(enemy);

		CCLOG("size %d  ",enemys.size());
	}

	std::vector<Character*> & getEnemys(){
	//	CCLOG("enemys  size: %d",enemys.size());
		return enemys;
	}

	void setBodyInfo(BodyInfo * bodyInfo)
	{
		this->bodyInfo=bodyInfo;
	}

	BodyInfo* getBodyInfo()
	{
		return bodyInfo;
	}

};

#endif