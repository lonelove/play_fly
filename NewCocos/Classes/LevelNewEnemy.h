#ifndef __LEVELNEWENEMY_H__
#define __LEVELNEWENEMY_H__

#include "cocos2d.h"
using namespace cocos2d;

class LevelNewEnemy : public cocos2d::Sprite
{
public:
	//实例化函数
	static LevelNewEnemy* createEnemy(const char* fileName, int _type, int _way);
	//价值多少分数
	int scoreValue;
	//血量
	int hp;
	int enemyType;
private:
	//初始化
	void enemyInit(const char* fileName, int _type, int _way);
	//敌人逻辑
	void update(float time);
	//是否已经运动过了
	bool isActed;
	//当前敌人类型
	int way;
	void enemyShoot();
	void shootMany(float f);
	int shootManyCount;
	void shootFive(Point playerPoint);
	void shootFour(float f);
	int shootFourCount;
	void shootOne(Point playerPoint);
	void enemyDead();
	virtual void onExit();
	int timeCount1;
};


#endif 