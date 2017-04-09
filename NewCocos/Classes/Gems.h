#ifndef __Gems_H__
#define __Gems_H__

#include "cocos2d.h"
using namespace cocos2d;

class Gems : public cocos2d::Sprite
{
public:
	static Gems* createGem(const char* fileName, int gemType);//ʵ������

private:
	int glintTime;
	int glintCount;
	bool isDisappear;
	int gemType;
	int gemMoveCount;
	bool chaneMove;
	void gemInit(int gemTypeTemp);//��ʼ������
	void update(float dt);
	virtual void onExit();
};

#endif 

