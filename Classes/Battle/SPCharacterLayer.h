#include "cocos2d.h"
#include "Character.h"
#include "CharacterLayer.h"
#include "Health.h"
#include "AI/EnemyManager.h"

#include "SimpleAudioEngine.h"

class SPCharacterLayer : public CharacterLayer
{
private:

	//专供敌人管理
	EnemyManager* enemyManager;

	//判断胜负
	void CheckResult();
	//角色重生
	void Rebirth(Character* cha);

	//触屏起始事件
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	//触屏终止事件
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	//行动schedule
	virtual void actionSchedule(float delta);

	//恢复schedule 
	virtual void recoverySchedule(float delta);

public:

	virtual bool init();  
	~SPCharacterLayer();
	CREATE_FUNC(SPCharacterLayer);

	void setHero(GameSetting::Character hero);
	void setEnemy(std::vector<GameSetting::Character> enemy);

};

