#ifndef __MYGAME_SCENE_H__
#define __MYGAME_SCENE_H__

#include "cocos2d.h"
#include"Card.h"
USING_NS_CC;
using namespace cocos2d;
class MyGame : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MyGame);
	/*******************自己添加的*************************/
	void autoCreatCard();//自动生成卡片
	void checkGameOver();//判断游戏是否结束
	//判断是否移动
	bool isMoveLeft();
	bool isMoveRight();
	bool isMoveUp();
	bool isMoveDown();
private:
	float startX, startY, offsetX, offsetY;//记录按下时的坐标和偏移量
	//创建触控监听
	bool onTouchBegan(Touch *t, Event *e);
	void onTouchEnded(Touch *t, Event *e);
	void createCrad(Size size);//创建卡片
	Card* cardArr[4][4];//存储卡片的二维数组，以便控制卡片移动
	int score;//分数
	LabelTTF *scoreLabel;//显示分数控件
	LabelTTF *restartBtn;//设置从新开始游戏按钮
	void menuCallback(Object *pSender);
};

#endif 
