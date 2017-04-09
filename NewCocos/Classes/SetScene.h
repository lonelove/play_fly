#ifndef __SET_SCENE_H__
#define __SET_SCENE_H__
#include "cocos2d.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class SetScene :public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SetScene);
private:
	void OnClickClose(Ref* pSende, TouchEventType eventtype);
	void OnClickAbout(Ref* pSende, TouchEventType eventtype);
	void OnClickBack(Ref* pSende, TouchEventType eventtype);
	void OnClickReset(Ref* pSende, TouchEventType eventtype);
	void OnClickMusic(Ref* pSende, SliderEventType type);
	void OnClickEffect(Ref* pSende, SliderEventType type);
	void OnClickMovse(Ref* pSende, SliderEventType type);
private:
	Slider* slider1;//滑动条1
	Slider* slider2;//滑动条2
	Slider* slider3;//滑动条3
};

#endif