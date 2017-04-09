#ifndef __LOSTGAME_H__
#define __LOSTGAME_H__
#include"cocos2d.h"
using namespace cocos2d;
class LostGame :public Layer{
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(LostGame);
private:
	void playAgain(Object * object);
	void backHome(Object * object);
	void run();
	Sprite* sad;
	Sprite* background;
};



#endif