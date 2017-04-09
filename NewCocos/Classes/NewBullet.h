#ifndef __NEWBULLET_H__
#define __NEWBULLET_H__

#include "cocos2d.h"
using namespace cocos2d;

class NewBullet : public cocos2d::Sprite
{
public:
	//实例化函数
	static NewBullet* createBullet(const char* _fileName, float _speed, Point _position, int _type);

private:
	//初始化函数
	void bulletInit(float _speed, Point _position, int _type);
	void update(float time);//逻辑
	float speed;//移动速度
	int bulletType;

	Point bulletPoint;
	Point enemyPoint;
	float newSlope;

	virtual void onExit();

	int rotation;
	Point velocity;
};


#endif /* defined(__PlaneDemo__NewBullet__) */
