#include "EnemyManager.h"
USING_NS_CC;
EnemyManager::EnemyManager()
{

	NotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(EnemyManager::getBodyInfo),"getBodyInfo",NULL);
	/*schedule(i 0.2f); 
	NotificationCenter::sharedNotificationCenter()->postNotification("getBodyInfo",bodyInfo);*/
	info = new ManagerInfo();
	ai=new AI(info);
	countInt=0;
}


void EnemyManager::addEnemy(Character* enemy)
{
	info->addEnemy(enemy);
	ai->addState(enemy);
	CCLOG("enemyManager  push_back  success");
}

void EnemyManager::getBodyInfo(Object * obj)
{
		info->setBodyInfo((BodyInfo *)obj);
		if(ai->getReady()==false)
		{
			ai->setReady(true);
			info->handleBodyInfo();
		}
		//CCLOG("BodyNum is = %d",bodyInfo->body.size());
}

void EnemyManager::setHero(Character* hero){
	info->setHero(hero);
}

//void EnemyManager::scheduleCallBack(float fDelta){
//
//}
void EnemyManager::action()
{
	if(++countInt==5)
	{
		ai->changeState();
		countInt=0;
	}
	ai->actions();
	//CCLOG("enemyManager action\n");
}

void EnemyManager::recovery(int a)
{
	std::vector<Character*> & enemys=info->getEnemys();
	int len=enemys.size();
	for(int i=0;i<len;i++)
	{
		enemys[i]->recovery(a);
	}

}