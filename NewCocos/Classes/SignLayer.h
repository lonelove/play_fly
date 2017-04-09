#ifndef __SIGNLAYER_H__
#define __SIGNLAYER_H__

#include"cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class SignLayer :public Layer{
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(SignLayer);
public:
	void backMain(Object *pSender);
	void run();
	void onTouchEnded(Touch *pTouch, Event *pEvent);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	Sprite* m_cat;
	Sprite* background;
	int daycont;
	int day;
};


#endif