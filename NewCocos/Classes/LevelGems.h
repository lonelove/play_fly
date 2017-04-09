#ifndef __LevelGems_H__
#define __LevelGems_H__

#include "cocos2d.h"
using namespace cocos2d;

class LevelGems : public cocos2d::Sprite
{
public:
	static LevelGems* createGem(const char* fileName, int gemType);//实例函数

private:
	int glintTime;
	int glintCount;
	bool isDisappear;
	int gemType;
	int gemMoveCount;
	bool chaneMove;
	void gemInit(int gemTypeTemp);//初始化函数
	void update(float dt);
	virtual void onExit();
};

#endif 

