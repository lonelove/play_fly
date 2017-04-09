#ifndef __LEVELBULLETENEMY_H__
#define __LEVELBULLETENEMY_H__

#include "cocos2d.h"
using namespace cocos2d;

class LevelBulletEnemy : public cocos2d::Sprite
{
public:
	//ʵ��������
	static LevelBulletEnemy* createBullet(const char* _fileName, float _speed, Point _position, Point _playerPosition, int _type);

private:
	//��ʼ������
	void bulletInit(float _speed, Point _position, Point _playerPosition, int _type);
	void update(float time);//�߼�
	float speed;//�ƶ��ٶ�
	int bulletType;

	virtual void onExit();
	int bulletShootDelay;

	void aimAt();
	Point goalPoint;
	Point startingPoint;
	float slope;
	bool isAimAt;
	Point velocity;

};

#endif 
