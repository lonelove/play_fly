#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include<iostream>

#include"cocos2d.h"
#include "HPlayer.h"
#include "NewPlayer.h"

using namespace cocos2d;


class PlayerScene :public Layer{
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(PlayerScene);
	virtual ~PlayerScene();//析构函数
	//获取当前的静态实例
	static PlayerScene* sharedPlayerScene();
	
	void onTouchMoved(Touch *pTouch, cocos2d::Event *pEvent);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
public:
	bool isPlayerChange;
	NewPlayer* getPlayer();
	void resetPlayer(float f);
	void setPlayer(int i);

	int BulletDelayCount;

	Array * arrayEnemy;//存放敌怪的数组

	void doPause(Object* psend);
	void lostGame();
	void autoCreateBullet(float f);
	void autoCreateEnemy(float f);
	void setEnemy(float f);
	void autoCreateGems(float f);
	void putGems(CCPoint point);
	void removeSupplyPlane();
	Array* getArrayForEnemy();//获取存放敌怪的数组

	void addPlaneProperty();

	int enemyType;
	int enemyType1TimeCount;
	int enemyType2TimeCount;
	int enemyType3TimeCount;
	int enemyType4TimeCount;
	int enemyType5TimeCount;
	int enemyType6TimeCount;
	int allTimeCount;
	int creatEnemyInterval;
	bool passCreatEnemy;

	const char* bulletType1;
	const char* bulletType2;
	const char* playerName;

	SpriteBatchNode *bulletBatchNode;
	SpriteBatchNode *enemyBatchNode;
	SpriteBatchNode *playersBatchNode;

	int M_Score;
	int chance;
	bool M_music;
};



#endif
