#ifndef __MAP_SELECT_SCENE_H__
#define __MAP_SELECT_SCENE_H__

#include "CocosGUI.h" 
#include "cocos2d.h"
#include "GameSetting.h"
#include "SimpleAudioEngine.h"
class MapSelectScene : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
    // implement the "static create()" method manually
    CREATE_FUNC(MapSelectScene);

	void returnEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void selectEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);

	void setCharSelected(GameSetting::Character cha);

private:

	GameSetting::Character charSelected;
	GameSetting::Map mapSelected;
	// µØÍ¼°´Å¥
	cocos2d::ui::Button * desertBtn;
	cocos2d::ui::Button * forestBtn;
	cocos2d::ui::Button * islandBtn;
};


#endif // __MAP_SELECT_SCENE_H__