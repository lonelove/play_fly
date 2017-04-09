#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__
#include"cocos2d.h"
using namespace cocos2d;
class GameOver :public Scene{
public:
	GameOver();
	~GameOver();
	static GameOver* createScene(int passScore);
	virtual bool init();
	//CREATE_FUNC(GameOver);
private:
	void playAgain(Object * object);
	void backHome(Object * object);
	void Share(Object * object);
	int score;
};



#endif