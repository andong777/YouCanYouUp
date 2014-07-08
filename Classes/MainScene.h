#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h"  

class MainScene : public cocos2d::Scene
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void singleEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void onlineEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void helpEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

};

#endif // __MAIN_SCENE_H__
