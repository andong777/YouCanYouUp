#include "Battle/Character.h"
#include "Battle/BodyInfo.h"

#ifndef MANAGERINFOMATION_DEFINE
#define MANAGERINFOMATION_DEFINE


/**
*   存储body的四个点位置
*/ 
struct BodyPos{
public:
	Vec2 * pos;
	void normalPoints();
	
	bool operator < (const BodyPos & p2) const{
		return pos[1].y > p2.pos[1].y;//比较的是左上角的位置
	}
};



/**
*	存储EnemyManager的所需要信息
*/
class ManagerInfo{

protected:
	Character * hero;
	std::vector<Character*> enemys;
	BodyInfo* bodyInfo;
	
public:

	const static int NUM=10;
	const static int posNum=10;  //记录位置的数量
		std::list<Vec2> eList[NUM];   //存储enemy的前面的位置
		std::list<Vec2> hList[NUM];    //存储hero前面的位置
		int eListSize[NUM];      //存储eList的长度
		int hListSize[NUM];   //存储hList的长度

	std::vector<BodyPos> bodyPos;
	std::vector<bool> isOK;

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

	//处理bodyIndo的body信息
	void  handleBodyInfo();
};

#endif