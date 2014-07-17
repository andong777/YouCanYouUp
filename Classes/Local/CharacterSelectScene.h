#ifndef __CHARACTER_SELECT_SCENE_H__
#define __CHARACTER_SELECT_SCENE_H__

#include "CocosGUI.h" 
#include "cocos2d.h"
#include "GameSetting.h"
#include "SimpleAudioEngine.h"
class CharacterSelectScene : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
    // implement the "static create()" method manually
    CREATE_FUNC(CharacterSelectScene);

	void returnEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void selectEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	// 用户选择的人物
	GameSetting::Character charSelected;
	// 人物按钮
	cocos2d::ui::Widget * cha1Btn;
	cocos2d::ui::Widget * cha2Btn;
	// 其他按钮
	cocos2d::ui::Button * returnBtn;
};


#endif // __CHARACTER_SELECT_SCENE_H__