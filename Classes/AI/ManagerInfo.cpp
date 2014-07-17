#include "ManagerInfo.h"

#define jud(x,y) (x-y>0?x-y:y-x)

void BodyPos::normalPoints()
{
	int id=0;
	for(int i=1;i<4;i++)
	{
		if(pos[i].x<=pos[id].x&&pos[i].y<=pos[id].y)
			id=i;
	}

	for(int i=0;id<4;i++)
	{
		Vec2 tem=pos[id];
		pos[id]=pos[i];
		pos[i]=tem;
		id++;
		if(id>=4)
			break;
	}
}

void ManagerInfo::handleBodyInfo()
{
	int len=bodyInfo->body.size();
	for(int i=0;i<len;i++)
	{
		BodyPos tem;
		Vec2 posCenter = (bodyInfo->body)[i]->getPosition();
		PhysicsShapePolygon * bodyShape= (PhysicsShapePolygon*)(bodyInfo->body)[i]->getShape(0);
		Vec2 * ppoints = new Vec2[4];
		bodyShape->getPoints(ppoints);
		tem.pos=ppoints;

		for(int i=0;i<4;i++)
		{
			ppoints[i].x+=posCenter.x;
			ppoints[i].y+=posCenter.y
;		}

		//tem.normalPoints();
		bodyPos.push_back(tem);
		isOK.push_back(true);
	}
	
	std::sort(bodyPos.begin(),bodyPos.end());

	for(int i=0;i<len;i++)
	{
		if(i-1>=0)
		{
			if(jud(bodyPos[i-1].pos[0].y,bodyPos[i].pos[1].y)<5 && jud( bodyPos[i-1].pos[1].x , bodyPos[i].pos[1].x )<5 &&  jud(bodyPos[i-1].pos[2].x , bodyPos[i].pos[2].x )<5)
				isOK[i]=false;

		}
	}
	//for(int i=0;i<len;i++)
	//{
	//	CCLOG("i:%d   y0:%f   y1:%f   y2:%f    y3:%f",i,bodyPos[i].pos[0].y,bodyPos[i].pos[1].y,bodyPos[i].pos[2].y,bodyPos[i].pos[3].y);
	//}
}

