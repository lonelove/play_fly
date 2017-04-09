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
	/*******************�Լ���ӵ�*************************/
	void autoCreatCard();//�Զ����ɿ�Ƭ
	void checkGameOver();//�ж���Ϸ�Ƿ����
	//�ж��Ƿ��ƶ�
	bool isMoveLeft();
	bool isMoveRight();
	bool isMoveUp();
	bool isMoveDown();
private:
	float startX, startY, offsetX, offsetY;//��¼����ʱ�������ƫ����
	//�������ؼ���
	bool onTouchBegan(Touch *t, Event *e);
	void onTouchEnded(Touch *t, Event *e);
	void createCrad(Size size);//������Ƭ
	Card* cardArr[4][4];//�洢��Ƭ�Ķ�ά���飬�Ա���ƿ�Ƭ�ƶ�
	int score;//����
	LabelTTF *scoreLabel;//��ʾ�����ؼ�
	LabelTTF *restartBtn;//���ô��¿�ʼ��Ϸ��ť
	void menuCallback(Object *pSender);
};

#endif 
