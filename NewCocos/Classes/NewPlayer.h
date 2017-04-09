#ifndef __NewPlayer_H__
#define __NewPlayer_H__

#include "cocos2d.h"
using namespace cocos2d;

class NewPlayer : public cocos2d::Sprite
{
public:
	static NewPlayer* createPlayer(const char* fileName);//ʵ������
	int hp;//Ѫ��
	int hpMax;//Ѫ�����ֵ
	int score;//����
	int killCount;//ɱ����
	void downHp();//��Ѫ
	void addHp();//��Ѫ
	void addScore(float _value);//�ӷ�
	void addKillCount(float _value);//��ɱ����
	bool isDead;//�Ƿ�����
	int strongTime;//�޵�ʱ��
	bool isStrong;//�Ƿ����޵�ʱ��
	int strongCount;//�޵�ʱ�ļ�����
	void strongIng(float dt);//�����޵�ʱ����˸�ȴ���

private:
	//void playerInit();//��ʼ������
	void playerInit();//��ʼ������
};

#endif 
