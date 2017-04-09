#ifndef __BULLETENEMY_H__
#define __BULLETENEMY_H__

#include "cocos2d.h"
using namespace cocos2d;

class BulletEnemy : public cocos2d::Sprite
{
public:
	//实例化函数
	static BulletEnemy* createBullet(const char* _fileName, float _speed, Point _position, Point _playerPosition, int _type);

private:
	//初始化函数
	void bulletInit(float _speed, Point _position, Point _playerPosition, int _type);
	void update(float time);//逻辑
	float speed;//移动速度
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

#endif /* defined(__PlaneDemo__EnemyBullet__) */
