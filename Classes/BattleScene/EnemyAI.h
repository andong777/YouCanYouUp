#include "Character.h"

class EnemyAI
{
private:
	//角色
	Character* cha;
	//难度
	int difficulty;
	//AI的具体行动
	void chase(Vec2 vec);
	void escape(Vec2 vec);
	void dodge(Vec2 vec);
public:
	//让AI采取行动
	void action(Character* target);
	EnemyAI(Character* cha);
	~EnemyAI();
};