#include "LoginScene.h"
#include "CCSGUIReader.h"
#include "SignupScene.h"
#include "OnlineScene.h"
#include "base/CCUserDefault.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace network;

bool LoginScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI5.ExportJson"));
	this->addChild(pNode);
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	return_->addTouchEventListener(CC_CALLBACK_2(LoginScene::returnEvent, this));
	Button *signup = (Button*)(ui::Helper::seekWidgetByName(pNode, "register"));
	signup->addTouchEventListener(CC_CALLBACK_2(LoginScene::signupEvent, this));

	// 找到两个输入框
	username = (TextField*)(ui::Helper::seekWidgetByName(pNode, "username"));
	password = (TextField*)(ui::Helper::seekWidgetByName(pNode, "code"));
	return true;
}

void LoginScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}

void LoginScene::signupEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *signup = SignupScene::create();
		TransitionScene *transition = TransitionFade::create(1, signup);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}

void LoginScene::loginEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		std::string username_s = username->getStringValue();
		std::string password_s = password->getStringValue();
		CCLOG("GET-Login");
		HttpRequest* request = new HttpRequest();  
		std::string url = "http://whydemo.sinaapp.com/whyuser/sign_in/"+username_s+"/"+password_s;
		request->setUrl(url.c_str());  
		request->setRequestType(HttpRequest::Type::GET);  
		request->setResponseCallback(this, httpresponse_selector(LoginScene::onHttpRequestCompleted));    
		request->setTag("GET-Login");  
		HttpClient::getInstance()->send(request);  
		request->release();
		break;
	}	
}

void LoginScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response) 
{  
	if(!response || !response->isSucceed())
		return;

    std::vector<char>* buffer = response->getResponseData();  
    char res = (*buffer)[0];
	// 登录成功
	if(res == '1')
	{
		// 加入用户信息
		UserDefault::getInstance()->setStringForKey("username", username->getStringValue());
		UserDefault::getInstance()->setStringForKey("password", password->getStringValue());
		Scene *online = OnlineScene::create(); 
		TransitionScene *transition = TransitionFade::create(0.5, online);
		Director::getInstance()->pushScene(transition);
	}
	// 登录失败。清空两个输入框
	else
	{
		username->setText("");
		password->setText("");
	}
}  