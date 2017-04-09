#ifndef __LEVELNEWENEMY_H__
#define __LEVELNEWENEMY_H__

#include "cocos2d.h"
using namespace cocos2d;

class LevelNewEnemy : public cocos2d::Sprite
{
public:
	//ʵ��������
	static LevelNewEnemy* createEnemy(const char* fileName, int _type, int _way);
	//��ֵ���ٷ���
	int scoreValue;
	//Ѫ��
	int hp;
	int enemyType;
private:
	//��ʼ��
	void enemyInit(const char* fileName, int _type, int _way);
	//�����߼�
	void update(float time);
	//�Ƿ��Ѿ��˶�����
	bool isActed;
	//��ǰ��������
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