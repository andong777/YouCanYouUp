#include "RecordScene.h"
#include "CCSGUIReader.h"
#include "json/rapidjson.h"  
#include "json/document.h" 
#include "Global.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace network;

bool RecordScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI3.ExportJson"));
	this->addChild(pNode);
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	return_->addTouchEventListener(CC_CALLBACK_2(RecordScene::returnEvent, this));

	//找到list
	list = (ScrollView*)(ui::Helper::seekWidgetByName(pNode, "List"));
	list->removeAllChildren();
	float innerWidth = list->getSize().width;
	float innerHeight = list->getSize().height;
	list->setInnerContainerSize(Size(innerWidth, innerHeight));

	// 从服务器读取排名并写入list
	CCLOG("GET-GetScore");
	HttpRequest* request = new HttpRequest();  
	std::string url = GET_SCORE_SERVER_URL;
	request->setUrl(url.c_str());  
	request->setRequestType(HttpRequest::Type::GET);  
	request->setResponseCallback(this, httpresponse_selector(RecordScene::onHttpRequestCompleted));    
	request->setTag("GET-GetScore");  
	HttpClient::getInstance()->send(request);  
	request->release();

	return true;
}

void RecordScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch(type){
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	}	
}

void RecordScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response) 
{  
	if(!response || !response->isSucceed())
		return;

    std::vector<char>* buffer = response->getResponseData();  
	std::stringstream ss;
    for(int i=0;i<buffer->size();i++){
		ss << (*buffer)[i];
	}
	rapidjson::Document doc;  
	doc.Parse<rapidjson::kParseDefaultFlags>(ss.str().c_str());  

	Layer *contentLayer = Layer::create();
	for(int i=0;i<doc.Size();i++)  
    {   
        rapidjson::Value &v=doc[i];  
            
        if(v.HasMember("username") && v.HasMember("score"))  
        {   
            std::string username = v["username"].GetString();  
            std::string score = v["score"].GetString();  

			Text *text = Text::create();
			text->setPosition(Vec2(0, i*list->getSize().height / doc.Size()));
			text->setText(username + ": " + score);
			list->getInnerContainer()->addChild(text);
        }  

    }  
}  