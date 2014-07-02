#ifndef __SINGLE_MENU_SCENE_H__
#define __SINGLE_MENU_SCENE_H__

#include "CocosGUI.h" 
#include "cocos2d.h"

class SingleMenuScene : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
    // implement the "static create()" method manually
    CREATE_FUNC(SingleMenuScene);

	void returnEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void selectEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	// µØÍ¼°´Å¥
	cocos2d::ui::Button * defaultBtn;
	cocos2d::ui::Button * snowBtn;
};


#endif // __SINGLE_MENU_SCENE_H__