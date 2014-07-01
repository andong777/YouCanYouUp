#ifndef __RECORD_SCENE_H__
#define __RECORD_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h" 

class RecordScene : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
    // implement the "static create()" method manually
    CREATE_FUNC(RecordScene);

	void returnEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // __RECORD_SCENE_H__