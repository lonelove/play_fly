#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include<iostream>

#include"cocos2d.h"
#include "HPlayer.h"
#include "LevelNewPlayer.h"

using namespace cocos2d;
class LevelScene :public Layer{
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(LevelScene);
	virtual ~LevelScene();//��������
	//��ȡ��ǰ�ľ�̬ʵ��
	static LevelScene* sharedLevelScene();

	void onTouchMoved(Touch *pTouch, cocos2d::Event *pEvent);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
public:
	bool isPlayerChange;
	LevelNewPlayer* getPlayer();
	void addPlaneProperty();//�����������
	void resetPlayer(float f);
	void setPlayer(int i);
	const char* bulletType1;//�ӵ�1����
	const char* bulletType2;//�ӵ�2����
	const char* playerName;
	int BulletDelayCount;//�ӵ��ӳ�
	void autoCreateBullet(float f);//��������ӵ�

	Array * arrayEnemy;//��ŵйֵ�����
	Array* getArrayForEnemy();//��ȡ��ŵйֵ�����
	int allTimeCount;
	void autoCreateEnemy(float f);//��ӵ���

	void autoCreateGems(float f);//��ӵ���
	void putGems(CCPoint point);
	void removeSupplyPlane();

	void doPause(Object* psend);//��ͣ����
	void lostGame();//ʧ�ܽ���
	void winGame();//��������

	SpriteBatchNode *bulletBatchNode;
	SpriteBatchNode *enemyBatchNode;
	SpriteBatchNode *playersBatchNode;

	int M_Score;//��ǰ�÷�
	int chance;
	bool m_music;
};

#endif