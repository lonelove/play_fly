#ifndef __MYHANAGER_SCENE_H__
#define __MYHANAGER_SCENE_H__
#include "cocos2d.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class MyHanager :public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MyHanager);
	CheckBox* checkbox1;
	CheckBox* checkbox2;
	CheckBox* checkbox3;
	CheckBox* checkbox4;
	Scale9Sprite* IM;
private:
	void OnClickfly1(Ref* pSende, TouchEventType eventtype);
	void OnClickfly2(Ref* pSende, TouchEventType eventtype);
	void OnClickfly3(Ref* pSende, TouchEventType eventtype);
	void OnClickfly4(Ref* pSende, TouchEventType eventtype);
	void checkBoxCallback1(Ref* sender, CheckBoxEventType type);
	void checkBoxCallback2(Ref* sender, CheckBoxEventType type);
	void checkBoxCallback3(Ref* sender, CheckBoxEventType type);
	void checkBoxCallback4(Ref* sender, CheckBoxEventType type);
	void OnClickBack(Ref* pSende, TouchEventType eventtype);
};

#endif