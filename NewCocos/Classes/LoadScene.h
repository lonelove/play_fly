#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include"cocos2d.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;


class LoadScene :public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LoadScene);
public:
	void PreloadMusicAndPicture(); // ‘§º”‘ÿ“Ù¿÷∫ÕÕº∆¨
private:
	int percent1;
	int percent2;
	ui::ImageView* image;
	Sprite* star1;
	Sprite* star2;
	Sprite* star3;
	Sprite* star4;
	int time;
	void OnClickStart(Ref* pSende, TouchEventType eventtype);
	void update(float dt);
};



#endif