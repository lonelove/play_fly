#include"NewPlayer.h"
#include"HPlayer.h"
#include"PlayerScene.h"
#include<iostream>
using namespace cocos2d;

int playerType = 1;

NewPlayer* NewPlayer::createPlayer(const char* fileName){
	NewPlayer* player = new NewPlayer();
	if (player && player->initWithSpriteFrameName(fileName)){
		player->autorelease();
		player->playerInit();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void NewPlayer::playerInit()
{
	isDead = false;
	isStrong = false;
	hpMax = 3;//初始化血量上限为3
	strongTime = 5 * 60;//初始化无敌时间5秒
}


//添加积分分数
void NewPlayer::addScore(float _value){
	score += _value;
	//String* strScore = String::createWithFormat("%d", score);
	std::string strScore = Convert2String(score);
	LabelTTF* ttf = (LabelTTF*)PlayerScene::sharedPlayerScene()->getChildByTag(tag_scoreTTF);
	ttf->setString(strScore.c_str());
	
}


//添加杀敌数
void NewPlayer::addKillCount(float _value)
{
	killCount += _value;
	String* strKillCount = String::createWithFormat("%d",killCount);
	LabelTTF* ttf = (LabelTTF*)PlayerScene::sharedPlayerScene()->getChildByTag(tag_killsCountTTF);
	ttf->setString(strKillCount->getCString());

	
}

//主角掉血函数（默认每次掉一点血）
void NewPlayer::downHp(){
	if (isStrong){
		return;
	}
	hp -= 1;
	if (hp <= 0){
		this->setVisible(false);
		isDead = true;
		PlayerScene::sharedPlayerScene()->M_Score = score;
		//调用失败界面
		PlayerScene::sharedPlayerScene()->lostGame();
	}
	else{
		//将界面的血量icon数量进行更新
		switch (hp) {
		case 1:
			PlayerScene::sharedPlayerScene()->removeChildByTag(tag_playerHp2, true);
			break;

		case 2:
			PlayerScene::sharedPlayerScene()->removeChildByTag(tag_playerHp3, true);
			break;
		}
		//主角无敌时间
		isStrong = true;
		strongCount = 0;
		this->schedule(schedule_selector(NewPlayer::strongIng));
	}
}

//主角加血函数（默认每次加一点血）
void NewPlayer::addHp()
{
	switch (hp)
	{
	case 1:
	{
		Sprite* spHp = Sprite::create("ui/icon_hp.png");
		spHp->setPosition(ccp(25 * 2, spHp->getContentSize().height*0.5));
		spHp->setTag(tag_playerHp2);
		PlayerScene::sharedPlayerScene()->addChild(spHp, 10);
		break;
	}
	case 2:
	{
		Sprite* spHp = Sprite::create("ui/icon_hp.png");
		spHp->setPosition(ccp(25 * 3, spHp->getContentSize().height*0.5));
		spHp->setTag(tag_playerHp3);
		PlayerScene::sharedPlayerScene()->addChild(spHp, 10);
		break;
	}
	default:
		break;
	}
}

//处于无敌时间时的处理函数
void NewPlayer::strongIng(float dt){
	strongCount++;
	if (strongCount >= strongTime){
		this->setVisible(true);
		isStrong = false;
		this->unschedule(schedule_selector(NewPlayer::strongIng));
	}
	else{
		//主角处于无敌时间时的闪烁效果
		if (strongCount % 2 == 0){
			this->setVisible(false);
		}
		else{
			this->setVisible(true);
		}
	}
}
