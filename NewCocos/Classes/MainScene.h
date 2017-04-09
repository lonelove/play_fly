#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include"cocos2d.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class MainScene :public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);

private:
	void OnClickEndless(Ref* pSende, TouchEventType eventtype);
	void OnClickStory(Ref* pSende, TouchEventType eventtype);
	void OnClickOptions(Ref* pSende, TouchEventType eventtype);
	void OnClickMyHangar(Ref* pSende, TouchEventType eventtype);
//	void OnClickShare(Ref* pSende, TouchEventType eventtype);
	void OnClickRank(Ref* pSende, TouchEventType eventtype);
	void OnClickMyMusic(Ref* pSende, TouchEventType eventtype);
	void OnClickSign(Ref* pSende, TouchEventType eventtype);
	void menuCloseCallback(Object *pSender);
private:
	ui::Button* button8; 
	void saveScreenshot(); //½ØÍ¼¹¦ÄÜ
};


#endif