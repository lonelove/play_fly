#ifndef __LevelUniqueSkill_H__
#define __LevelUniqueSkill_H__

#include <iostream>
#include "cocos2d.h"
#include "LevelNewEnemy.h"
using namespace std;
using namespace cocos2d;

class LevelUniqueSkill : public Node
{
public:
	static LevelUniqueSkill* createUniqueSkill(const char* fileName, int _uniqueSkillType);//实例函数
private:

	int skill1TimeCount;
	int skill2TimeCount;
	int skill3TimeCount;

	void uniqueSkillInit(const char* fileName, int _uniqueSkillType);//初始化函数
	void uniqueSkill1(Object* psend);
	void uniqueSkill2(Object* psend);
	void uniqueSkill3(Object* psend);
	void removeSprite();
	void createBullet();
	void finishBullet();
	void autoCreateBullet(float f);
	void changeAnimate(float f);
	void createAnimate(LevelNewEnemy* enemy);
	void strongSkill(float f);
	SpriteBatchNode* spritebatch;
	Sprite* skill3;
};

#endif 

