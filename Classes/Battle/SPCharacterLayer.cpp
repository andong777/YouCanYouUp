#include "SPCharacterLayer.h"
#include "Global.h"
#include "ResultLayer.h"

bool SPCharacterLayer:: init()
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false); //关闭原先的背景音乐
	heroHealth = new Health();

	enemyManager=new EnemyManager();

	hero_lives = INITIAL_LIVES;
	enemy_lives = INITIAL_LIVES;

	//触屏事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SPCharacterLayer::onTouchBegan,this);
	listener->onTouchEnded = CC_CALLBACK_2(SPCharacterLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/fighting.mp3",true); //播放背景音乐


	//定时判断角色状态
	this->schedule(schedule_selector(SPCharacterLayer::actionSchedule), (double)(AI::delta) / 100);
	//定时恢复体力
	this->schedule(schedule_selector(SPCharacterLayer::recoverySchedule), .5f);
	//定时判断结果
	this->schedule(schedule_selector(SPCharacterLayer::checkResSchedule), 1.f);

	return true;
}

void SPCharacterLayer::actionSchedule(float fDelta){
	enemyManager->action();

	hero->recovery(3);//每次恢复3hp
	enemyManager->recovery(3);

	heroHealth->health = getHeroHealth();
	NotificationCenter::sharedNotificationCenter()->postNotification("getHealth",heroHealth);
}

void SPCharacterLayer::recoverySchedule(float fDelta){
	hero->recovery(3);//每次恢复3hp
	enemyManager->recovery(3);

	heroHealth->health = getHeroHealth();
	NotificationCenter::sharedNotificationCenter()->postNotification("getHealth",heroHealth);
}

bool SPCharacterLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
	posBegan = pTouch->getLocation();
	return true;
}

void SPCharacterLayer::onTouchEnded(Touch *touch, Event *unused_event){
	posEnded = touch->getLocation();
	Vec2 force=2*(posEnded-posBegan);
	hero->applyImpulse(force);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/touch.wav"); //播放音效
}

void SPCharacterLayer::CheckResult(){
	float heroY = hero->getSprite()->getPositionY();
	if(heroY<0){
		if(--hero_lives){
			NotificationCenter::sharedNotificationCenter()->postNotification("loseHeroLife",NULL);
			Rebirth(hero);
		}
		else{
			CCLOG("You lose!");
			enemy_lives = INITIAL_LIVES;
			this->getScene()->addChild(ResultLayer::create(Result::LOSE));
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false); //关闭背景音乐
			unsigned int id = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/lost.wav"); //播放音效
			Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
		}
	}
	std::vector<Character*> & enemys=enemyManager->getEnemys();
	int len=enemys.size();
	for(int i=0;i<len;i++)
	{
		Character* e=enemys[i];
		float enemyY = e->getSprite()->getPositionY();
		if(enemyY<0)
		{
			if(--enemy_lives){
				NotificationCenter::sharedNotificationCenter()->postNotification("loseEnemyLife",NULL);
				Rebirth(e);
			}
			else{
				CCLOG("You win!");
				hero_lives = INITIAL_LIVES;
				this->getScene()->addChild(ResultLayer::create(Result::WIN));
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false); //关闭背景音乐
				unsigned int id = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/win.wav"); //播放音效
				Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
			}
			
		}
	}
}

void SPCharacterLayer::Rebirth(Character* cha){
	cha->init();
	cha->setPosition(Vec2(300,500));
}


SPCharacterLayer::~SPCharacterLayer(){
	delete hero;
	delete enemyManager;
	delete heroHealth;
}

void SPCharacterLayer::setHero(GameSetting::Character hero)
{
	//操作角色
	this->hero = new Character(hero);
	this->hero->setPosition(Vec2(300,500));
	this->addChild(this->hero->getSprite());

	enemyManager->setHero(this->hero);
}

void SPCharacterLayer::setEnemy(std::vector<GameSetting::Character> enemy)
{
	//敌人角色
	for(int i=0;i<enemy.size();i++)
	{
		Character * tem=new Character(enemy[i]);
		tem->setPosition(Vec2(500,500));
		this->addChild(tem->getSprite());

		//把enemy加入enemyManager中
		enemyManager->addEnemy(tem);
	}

}
