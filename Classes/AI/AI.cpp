#include "AI.h"

/**
*	将points变成从左上角指针
*/
int StateNode::leftup(Vec2* v)
{
	int id=0;
	for(int i=1;i<4;i++)
	{
		if(v[i].x<=v[id].x||v[i].y<=v[id].y)
		{
			id=i;
		}
	}
	return id;
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
		if(bodyInfo->shape[i]==ShapeType::POLYGON)
		{
			
			if(id==-1||dis>(bodyInfo->body[i]->getPosition()-now).length())
			{
				id=i;
				dis=(bodyInfo->body[i]->getPosition()-now).length();
			}
		}
	}

	if(id>0)
	{
		PhysicsShapePolygon * tem= (PhysicsShapePolygon*)(bodyInfo->body)[id]->getShape(0);
		Vec2 * ppoints;
		tem->getPoints(ppoints);
		int id= leftup(ppoints);
		
		if(now.x>ppoints[id].x&&now.x<ppoints[(id+2)%4].x)
		{
			if(now.y<ppoints[(id+1)%4].y)
			{
				if(now.x-ppoints[id].x<=ppoints[(id+2)%4].x-now.x)
				{
					return Vec2(ppoints[id].x-now.x,10);
				}else
				{
					return Vec2(ppoints[(id+2)%4].x-now.x,10);
				}
			}
			else
			{
				return Vec2((ppoints[id].x+ppoints[(id+2)%4].x)/2-now.x,0);
			}
		}else if(now.x<ppoints[id].x)
		{
			return Vec2(ppoints[id].x-now.x,ppoints[id].y-now.y);
		}else
		{
			return Vec2(ppoints[(id+2)%4].x-now.x,ppoints[(id+2)%4].y-now.y);
		}
	}

	return Vec2(10,10);
}

void DefendStateNode::enter(){
	//CCLOG("我正在防守\n");
}

void DefendStateNode::action(){

	//CCLOG("defend  action");
	
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
			enemy->applyImpulse(tem);

		}else
		{
			Vec2 tem=getCloseVec(tPos3);
			enemy->applyImpulse(tem);
		}
	}else
	{
		Vec2 tem=getCloseVec(tPos3);
		enemy->applyImpulse(tem);
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

	//CCLOG("attack  action");

	if(info->getBodyInfo()==NULL)
		return;

	Vec2 tPos1 = info->getHero()->getPosition();
	Vec2 tPos3 = enemy->getPosition();
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

	//CCLOG("strategy   action");

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
		if(eListSize[i] > posNum)
			continue;
		eList[i].push_back(tPos);
		eListSize[i]++;
	}
	if(!ready)
		return;

	for(int i=0;i<len;i++)
	{
		states[i]->action();
	}
}
