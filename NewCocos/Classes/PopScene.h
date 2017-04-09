#ifndef __POP_SCENE_H__
#define __POP_SCENE_H__
#include "cocos2d.h"

using namespace cocos2d;

class PopScene : public LayerColor
{
public:
	//static Scene * scene();
	virtual bool init();
	CREATE_FUNC(PopScene);
private:
	void yesButton(Object * object);
	void noButton(Object * object);
};
#endif
