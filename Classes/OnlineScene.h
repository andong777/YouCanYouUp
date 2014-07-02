#ifndef __ONLINE_SCENE_H__
#define __ONLINE_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h" 

class OnlineScene : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
    // implement the "static create()" method manually
    CREATE_FUNC(OnlineScene);

	void pvpEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void recordEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void offlineEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void returnEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // __ONLINE_SCENE_H__
