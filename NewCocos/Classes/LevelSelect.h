#ifndef __LevelSelect_H__
#define __LevelSelect_H__

#include"cocos2d.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class LevelSelect :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelSelect);
	Sprite* m_gif1;
	Sprite* m_gif2;
	Sprite* m_gif3;
	void runGif1();
	void runGif2();
	void runGif3();
private:
	void PlayGo1(Ref* pSende, TouchEventType eventtype);
	void PlayGo2(Ref* pSende, TouchEventType eventtype);
	void PlayGo3(Ref* pSende, TouchEventType eventtype);
	void backMain(Ref* pSende, TouchEventType eventtype);
};

#endif
