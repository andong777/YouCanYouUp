
#include "Battle/Character.h"
#include "Battle/BodyInfo.h"
#include "ManagerInfo.h"
#include "AI.h"

#ifndef ENEMY_MANAGER_DEFINE
#define ENEMY_MANAGER_DEFINE

class EnemyManager: public cocos2d::Ref{
protected:
	//Character * hero;
	//std::vector<Character*> enemys;
	//BodyInfo* bodyInfo;
	//void scheduleCallBack(float fDelta);
	ManagerInfo * info;
	AI* ai;

	int countInt;

public:

	EnemyManager();

	~EnemyManager(){
		NotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	}

	void addEnemy(Character* enemy);
	
	void getBodyInfo(Object * obj);

	void setHero(Character* hero);

	Character* getHero(){return info->getHero();}
	
	BodyInfo* getBodyInfo(){return info->getBodyInfo();}

	std::vector<Character*> &  getEnemys(){return info->getEnemys();}

	void action();

	void recovery(int a);

};


#endif
