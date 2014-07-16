
#ifndef BODY_INFO_DEFINE
#define BODY_INFO_DEFINE

#include "cocos2d.h"
#include <vector>
#include "ShapeType.h"

USING_NS_CC;

class BodyInfo: public cocos2d::Ref{
public:
	std::vector<PhysicsBody*> body;
	std::vector<ShapeType>	shape;
};


#endif