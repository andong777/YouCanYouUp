#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h" 
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "SimpleAudioEngine.h"

class LoginScene : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);

	void returnEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void signupEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	// µÇÂ¼ÊÂ¼þ
	void loginEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);

	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

private:

	cocos2d::ui::TextField *username;
	cocos2d::ui::TextField *password;

};

#endif // __LOGIN_SCENE_H__