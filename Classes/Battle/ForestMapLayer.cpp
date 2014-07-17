#include "ForestMapLayer.h"
USING_NS_CC;
bool ForestMapLayer:: init(){
	if ( !MapLayer::init() )
    {
        return false;
    }



	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*
	//边框盒
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	*/

	//背景
	auto background = Sprite::create("Map/map3.jpg");
	background->setPosition(visibleSize/2);
	this->addChild(background);

	//左，上，右边界
	Vec2* edge =  new Vec2[4];
	edge[0] = Vec2(0,0);
	edge[1] = Vec2(0,visibleSize.height);
	edge[2] = Vec2(visibleSize.width,visibleSize.height);
	edge[3] = Vec2(visibleSize.width,0);
	auto edgeBody = PhysicsBody::createEdgeChain(edge,4,PHYSICSBODY_MATERIAL_DEFAULT,3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(0,0));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	//下方平台
	Point* edgeDown = new Point[4];
	
	/*edgeDown[0] = Point(visibleSize.width/4,visibleSize.height/10);
	edgeDown[1] = Point(visibleSize.width*3/4,visibleSize.height/10);
	edgeDown[2] = Point(visibleSize.width*3/4,0);
	edgeDown[3] = Point(visibleSize.width/4,0);*/
	/*  全封闭平台
	edgeDown[0] = Point(0,visibleSize.height/10);
	edgeDown[1] = Point(visibleSize.width,visibleSize.height/10);
	edgeDown[2] = Point(visibleSize.width,0);
	edgeDown[3] = Point(0,0);
	*/
	auto edgeDownBody = PhysicsBody::createBox(Size(visibleSize.width/2,visibleSize.height/10),PHYSICSBODY_MATERIAL_DEFAULT,Vec2(0,0));
	edgeDownBody->setDynamic(false);//不受力
	auto edgeDownNode = Node::create();
	edgeDownNode->setPosition(visibleSize.width/2,visibleSize.height/20);
	edgeDownNode->setPhysicsBody(edgeDownBody);
	this->addChild(edgeDownNode);
	//edgeDownBody->getShape(0)->setFriction(300);  //设置摩擦力
	
	//加入刚体至BodyInfo，设定刚体类型
	addBody(edgeDownBody);
	addShape(ShapeType::BOX);

	//平台
	PhysicsBody* plates[4];
	Node* plateNodes[4];
	for(int i=0;i<4;i++){
		plates[i] = PhysicsBody::createBox(visibleSize/6,PHYSICSBODY_MATERIAL_DEFAULT );
		plates[i]->setDynamic(false);
		plateNodes[i] = Node::create();
		plateNodes[i]->setPhysicsBody(plates[i]);
		this->addChild(plateNodes[i]);
		//plateNodes[i] = setPosition(Point())
	}
	plateNodes[0]->setPosition(Point(visibleSize.width/4,visibleSize.height/3));
	plateNodes[1]->setPosition(Point(visibleSize.width*3/4,visibleSize.height*3/4));
	plateNodes[2]->setPosition(Point(visibleSize.width/4,visibleSize.height*3/4));
	plateNodes[3]->setPosition(Point(visibleSize.width*3/4,visibleSize.height/3));

	//
	for(int i=0;i<4;i++){
		addBody(plates[i]);
		addShape(ShapeType::BOX);
	}

	/*移动平台
	mPlate = PhysicsBody::createBox(visibleSize/6,PHYSICSBODY_MATERIAL_DEFAULT);
	mPlate->setDynamic(false);
	mPlateNode = Node::create();
	mPlateNode->setPhysicsBody(mPlate);
	mPlateNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(mPlateNode);
	
	this->schedule(schedule_selector(MapLayer::movePlate), 0.2f);
	//mPlateNode->setPositionY(10);
	*/

	return true;
}