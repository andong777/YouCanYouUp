#include "cocos2d.h"
#include "Character.h"
#include "CharacterLayer.h"
#include "Health.h"
#include "AI/EnemyManager.h"

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

	void scheduleCallBack(float fDelta);

public:

	virtual bool init();  
	~SPCharacterLayer();
	CREATE_FUNC(SPCharacterLayer);

	void setHero(GameSetting::Character hero);
	void setEnemy(std::vector<GameSetting::Character> enemy);

};

