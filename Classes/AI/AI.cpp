#include "AI.h"

#define MIN(x,y)  (x<y?x:y)

/**
*  主要用于判断左右方向，不动返回0；向左返回1，向右返回2；
*/
int StateNode::judgeDir(Character * enemy,int i)
{
	Vec2 now = enemy->getPosition();
	std::list<Vec2>::iterator it =  (info->eList[i]).begin();
	Vec2 tem= now-(*it);
	if(tem.x<0)
		return 1;
	else if(tem.x>0)
		return 2;
	else
		return 0;
}

/**
*	保命要紧
*/
void StateNode::saveMe()
{
	double time = (double)AI::delta/100;

	std::vector<Character*> & enemys=info->getEnemys();
	int len= enemys.size();

	for(int i=0;i<len;i++)
	{
		Vec2 now = enemys[i]->getPosition();
		std::list<Vec2>::iterator it=  (info->eList[i]).begin();
		int tem=3;
		while(tem--)
		{
			it++;
			if(it==(info->eList[i]).end())
			{
				it--;
				break;
			}
		}
		/*int ssize = (info->eList[i]).size();
		CCLOG("  i:%d     size:%d",i,ssize);*/

		
		int jud=judgeDir(enemys[i],i);
		if(jud==0)
			continue;
		
		double speed = (now-(*it)).length()/(2*time);

		int ll = (info->bodyPos).size();
		double dis=1e8;
		int id=-1;
		int last=-1;
		for(int i=0;i<len;i++)
		{
			if(info->isOK[i])
			{
				if(info->bodyPos[i].pos[1].y<now.y)
				{
					if(id==-1||dis<now.y-info->bodyPos[i].pos[1].y)
					{
						id=i;
						dis=now.y-info->bodyPos[i].pos[1].y;
					}
				}
				last=i;
			}
		}

		if(id==-1)
		{
			CCLOG("always  id=-1  shit");

			Vec2 teml1 = info->bodyPos[last].pos[1] - now;
			Vec2 teml2= info->bodyPos[last].pos[2] - now;
			if(teml1.length()<teml2.length())
			{
				teml1.x-=20;
				teml1.y+=20;
				enemys[i]->applyMove((teml1*20));
			}	
			else
			{
				teml2.x+=20;
				teml2.y+=20;
				enemys[i]->applyMove((teml2*20));
			}
		}
		else if(jud == 1)
		{
			enemys[i]->applyMove(Vec2( 20 ,0));
		}
		else
		{
			enemys[i]->applyMove(Vec2( -20 ,0));
		}
	}
}


/**
*  调用该函数首先分析自身位置和周围的着落点的距离，分析着落点四个边界点和该点的位置关系，然后返回一个较为理智的向量
*/
Vec2  StateNode::getCloseVec(Vec2 now){

	BodyInfo * bodyInfo = info->getBodyInfo();
	int len = bodyInfo->body.size();//着落点的数量
	int id=-1;
	double dis=1e8;
	for(int i=0;i<len;i++)
	{
		if(bodyInfo->shape[i]==ShapeType::POLYGON && info->isOK[i])
		{
			double l1= (double) ((info->bodyPos[i].pos[1]-now).length());
			double l2 = (double)  ((info->bodyPos[i].pos[2]-now).length());
			if(id==-1||dis > l1 || dis> l2 )
			{
				id=i;
				dis= MIN( l1, l2 );
			}
		}
	}

	if(id>0)
	{
		
		double l1= (double) ((info->bodyPos[id].pos[1]-now).length());
		double l2 = (double)  ((info->bodyPos[id].pos[2]-now).length());
		if(l1<l2)
		{
			Vec2 ttt=info->bodyPos[id].pos[1]-now;
			ttt.x-=20;
			ttt.y+=20;
			return ttt;
		}
		else
		{
			Vec2 ttt=info->bodyPos[id].pos[2]-now;
			ttt.x+=20;
			ttt.y+=20;
			return ttt;
		}
	}

	return Vec2(10,10);
}

void DefendStateNode::enter(){
	//CCLOG("我正在防守\n");
}

void DefendStateNode::action(){

	CCLOG("defend  action");
	
	/**
	** 计算hero移动的方向是否朝向enemy，通过计算cos来判断     	
	*/
	Vec2 tPos1 = info->getHero()->getPosition();
	int tem=10;while(tem--);
	Vec2 tPos2 = info->getHero()->getPosition();
	Vec2 tPos3 = enemy->getPosition();
	Vec2 a1=tPos1-tPos2;
	Vec2 a2=tPos2-tPos3;
	double cos=(a1.dot(a2))/(a1.length()*a2.length());
	if(cos>0.95)
	{
		if(a2.length()<5)
		{
			int x=a2.y, y=-a2.x;
			if(y<0)
			{
				y=-y;x=-x;
			}
			Vec2 tem(x,y);
			enemy->applyImpulse(tem*10);
		}else
		{
			Vec2 tem=getCloseVec(tPos3);
			enemy->applyImpulse(tem*20);
		}
	}else
	{
		Vec2 tem=getCloseVec(tPos3);
		enemy->applyImpulse(tem*20);
	}
}

void DefendStateNode::exit(){


}

StateNode* DefendStateNode::changeState()
{
	int health=enemy->getHealth();
	int heroHealth=info->getHero()->getHealth();
	double healthRate=(double)health/enemy->getMaxHealth();
	double heroHealthRate=(double)health/info->getHero()->getMaxHealth();

	int randInt=rand()%100;
	if(healthRate<0.3)
	{
		if(randInt<80)
		{
			return new DefendStateNode(info,enemy);
		}else
			if(randInt<90)
				return new StrategyStateNode(info,enemy);
			return new AttackStateNode(info,enemy);
	}
	else if(healthRate<0.6)
	{
		if(heroHealthRate<0.3)
		{
			if(randInt<70)
				return new AttackStateNode(info,enemy);
			else if(randInt<90)
				return new StrategyStateNode(info,enemy);
			else
				return new DefendStateNode(info,enemy);
		}else
		{
			if(randInt<60)
				return new StrategyStateNode(info,enemy);
			else if(randInt<80)
				return new DefendStateNode(info,enemy);
			else
				return new AttackStateNode(info,enemy);
		}
	}else{
		if(heroHealthRate<0.3)
			return new AttackStateNode(info,enemy);
		else if(heroHealthRate<0.6)
		{
			if(randInt<70)
				return new AttackStateNode(info,enemy);
			else if(randInt<90)
				return new StrategyStateNode(info,enemy);
			else
				return new DefendStateNode(info,enemy);
		}
		else
		{
			if(randInt<60)
				return new StrategyStateNode(info,enemy);
			else if(randInt<80)
				return new DefendStateNode(info,enemy);
			else
				return new AttackStateNode(info,enemy);
		}
	}

}




void AttackStateNode::enter(){
	//CCLOG("我正在进攻\n");
}

void AttackStateNode::action(){

	CCLOG("attack  action");

	if(info->getBodyInfo()==NULL)
		return;

	Vec2 tPos1 = info->getHero()->getPosition();
	Vec2 tPos3 = enemy->getPosition();
	if((tPos1-tPos3).length()<20)
	{
		enemy->applyImpulse((tPos1-tPos3)*20);
	}
	else
		enemy->applyImpulse(tPos1-tPos3);
}

void AttackStateNode::exit(){


}


StateNode* AttackStateNode::changeState()
{
	int health=enemy->getHealth();
	int heroHealth=info->getHero()->getHealth();
	double healthRate=(double)health/enemy->getMaxHealth();
	double heroHealthRate=(double)health/info->getHero()->getMaxHealth();

	int randInt=rand()%100;

	if(healthRate<0.3)
	{
		if(randInt<80)
				return new DefendStateNode(info,enemy);
			else if(randInt<90)
				return new StrategyStateNode(info,enemy);
			else
				return new AttackStateNode(info,enemy);
	}else if(healthRate<0.6)
	{
		if(randInt<60)
				return new StrategyStateNode(info,enemy);
			else if(randInt<90)
				return new AttackStateNode(info,enemy);
			else
				return new DefendStateNode(info,enemy);
	}
	else 
	{
		if(randInt<80)
				return new AttackStateNode(info,enemy);
			else if(randInt<90)
				return new StrategyStateNode(info,enemy);
			else
				return new DefendStateNode(info,enemy);
	}

}

void StrategyStateNode::enter(){

	
	//CCLOG("我要采取策略了\n");

}

void StrategyStateNode::action(){

	CCLOG("strategy   action");

	if(info->getBodyInfo()==NULL)
		return;

	//CCLOG("这次饶了你\n");

}

void StrategyStateNode::exit(){


}

StateNode* StrategyStateNode::changeState()
{
	int health=enemy->getHealth();
	int heroHealth=info->getHero()->getHealth();
	double healthRate=(double)health/enemy->getMaxHealth();
	double heroHealthRate=(double)health/info->getHero()->getMaxHealth();

	int randInt=rand()%100;


	return new AttackStateNode(info,enemy);
}


void AI::changeState()
{
	int len=states.size();
	for(int i=0;i<len;i++)
	{
		StateNode* tem = states[i]->changeState();
		states[i]->exit();
		delete states[i];
		states[i]=tem;
		states[i]->enter();
	}
}

void AI::actions()
{

	std::vector<Character*> & enemys=info->getEnemys();
	int len=states.size();

	for(int i=0;i<len;i++)
	{
		Vec2 tPos = enemys[i]->getPosition();
		if(info->eListSize[i] > info->posNum)
		{
			info->eList[i].pop_front();
			info->eListSize[i]--;
		}
		info->eList[i].push_back(tPos);
		info->eListSize[i]++;
	}

	if(!ready)
		return;


	
	for(int i=0;i<len;i++)
	{
		states[i]->saveMe();
		states[i]->action();
	}
}
