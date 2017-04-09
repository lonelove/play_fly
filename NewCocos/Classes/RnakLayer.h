#ifndef __RNAKLAYER_H__
#define __RNAKLAYER_H__
#include "cocos2d.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class RankLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RankLayer);
	void OnClickBack(Ref* pSende, TouchEventType eventtype);
};
#endif
