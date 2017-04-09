#ifndef __LevelNewPlayer_H__
#define __LevelNewPlayer_H__

#include "cocos2d.h"
using namespace cocos2d;

class LevelNewPlayer : public cocos2d::Sprite
{
public:
	static LevelNewPlayer* createPlayer(const char* fileName);//实例函数
	int hp;//血量
	int hpMax;//血量最大值
	int score;//分数
	int killCount;//杀敌数
	void downHp();//掉血
	void addHp();//加血
	void addScore(float _value);//加分
	void addKillCount(float _value);//加杀敌数
	bool isDead;//是否死亡
	int strongTime;//无敌时间
	bool isStrong;//是否处于无敌时间
	int strongCount;//无敌时的计数器
	void strongIng(float dt);//处理无敌时的闪烁等处理

private:
	void playerInit();//初始化函数
};

#endif 
