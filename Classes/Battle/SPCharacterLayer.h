#include "cocos2d.h"
#include "Character.h"
#include "EnemyAI.h"
#include <vector>
#include "CharacterLayer.h"

class SPCharacterLayer : public CharacterLayer
{
private:

	EnemyAI* enemyAI;
	
	//判断胜负
	void CheckResult();
	//角色重生
	void Rebirth(Character* cha);

	//触屏起始事件
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	//触屏终止事件
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

public:

	virtual bool init();  
	~SPCharacterLayer();
	CREATE_FUNC(SPCharacterLayer);

	void setHero(GameSetting::Character hero);
	void setEnemy(GameSetting::Character enemy);

};

