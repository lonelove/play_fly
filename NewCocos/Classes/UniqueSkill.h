#ifndef __UniqueSkill_H__
#define __UniqueSkill_H__

#include <iostream>
#include "cocos2d.h"
#include "NewEnemy.h"
using namespace std;
using namespace cocos2d;

class UniqueSkill : public Node
{
public:
	static UniqueSkill* createUniqueSkill(const char* fileName, int _uniqueSkillType);//实例函数
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
	void createAnimate(NewEnemy* enemy);
	void strongSkill(float f);
	SpriteBatchNode* spritebatch;
	Sprite* skill3;
};

#endif 

