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
	virtual ~LevelScene();//析构函数
	//获取当前的静态实例
	static LevelScene* sharedLevelScene();

	void onTouchMoved(Touch *pTouch, cocos2d::Event *pEvent);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
public:
	bool isPlayerChange;
	LevelNewPlayer* getPlayer();
	void addPlaneProperty();//添加主角属性
	void resetPlayer(float f);
	void setPlayer(int i);
	const char* bulletType1;//子弹1名字
	const char* bulletType2;//子弹2名字
	const char* playerName;
	int BulletDelayCount;//子弹延迟
	void autoCreateBullet(float f);//添加主角子弹

	Array * arrayEnemy;//存放敌怪的数组
	Array* getArrayForEnemy();//获取存放敌怪的数组
	int allTimeCount;
	void autoCreateEnemy(float f);//添加敌人

	void autoCreateGems(float f);//添加道具
	void putGems(CCPoint point);
	void removeSupplyPlane();

	void doPause(Object* psend);//暂停界面
	void lostGame();//失败界面
	void winGame();//结束界面

	SpriteBatchNode *bulletBatchNode;
	SpriteBatchNode *enemyBatchNode;
	SpriteBatchNode *playersBatchNode;

	int M_Score;//当前得分
	int chance;
	bool m_music;
};

#endif