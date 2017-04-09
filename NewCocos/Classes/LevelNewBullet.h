#ifndef __LEVELNEWBULLET_H__
#define __LEVELNEWBULLET_H__

#include "cocos2d.h"
using namespace cocos2d;

class LevelNewBullet : public cocos2d::Sprite
{
public:
	//ʵ��������
	static LevelNewBullet* createBullet(const char* _fileName, float _speed, Point _position, int _type);

private:
	//��ʼ������
	void bulletInit(float _speed, Point _position, int _type);
	void update(float time);//�߼�
	float speed;//�ƶ��ٶ�
	int bulletType;

	Point bulletPoint;
	Point enemyPoint;
	float newSlope;

	virtual void onExit();

	int rotation;
	Point velocity;
};


#endif /* defined(__PlaneDemo__NewBullet__) */
