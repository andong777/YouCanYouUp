#include "cocos2d.h"

USING_NS_CC;
enum class Result{
	WIN,
	LOSE
};

class ResultLayer : public cocos2d::Layer
{
protected:
	virtual bool init(Result result);  
public:
	//CREATE_FUNC(ResultLayer);
	static ResultLayer* create(Result result)
	{ 
		ResultLayer *pRet = new ResultLayer(); 
		if (pRet && pRet->init(result)) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL;
			return NULL; 
		} 
	}

	void youWinInit();
	void youLoseInit();
	void addButton();
	void menuReplayCallback(Ref* pSender);
	void menuCloseCallback(Ref* pSender);

};