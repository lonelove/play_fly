#include "SimpleAudioEngine.h"
#include"GameOver.h"
#include"MainScene.h"
#include"PlayerScene.h"
#include"LevelScene.h"

USING_NS_CC;
extern bool changscene;
extern bool music_key;
using namespace CocosDenshion;

GameOver::GameOver(){}
GameOver::~GameOver(){}


GameOver* GameOver::createScene(int possScore){
	GameOver *gameover = new GameOver();
	gameover->score = possScore;
	if (gameover&&gameover->init()){
		gameover->autorelease();
		return gameover;
	}
	else{
		CC_SAFE_DELETE(gameover);
		return NULL;
	}
}

bool GameOver::init(){
	if (!Scene::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getVisibleSize();

	//设置这个层的背景图片，并且设置其位置为整个屏幕的中点
	auto background = Sprite::create("UI2/Gameover/background.png");
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background);

	Size contentSize = background->getContentSize();
	/*auto coin = Sprite::create("UI2/Gameover/coin.png");
	coin->setPosition(ccp(contentSize.width*3/4, contentSize.height-50));
	background->addChild(coin);
	//当前金币加入layer中
	std::string strCoin = Convert2String(0);
	LabelTTF* labelCoin = LabelTTF::create(strCoin.c_str(), "fonts/KA1.ttf", 50);
	labelCoin->setColor(ccc3(255, 255, 0));
	labelCoin->setPosition(ccp(contentSize.width - 70, contentSize.height - 50));
	background->addChild(labelCoin);
	*/
	//分数数字加入layer中
	LabelTTF* labelScore = LabelTTF::create("SCORE", "fonts/KA1.ttf", 100);
	labelScore->setPosition(ccp(contentSize.width / 4, contentSize.height * 5 / 7));
	background->addChild(labelScore);

	std::string strScore = Convert2String(score);
	LabelTTF* labelScores = LabelTTF::create(strScore.c_str(), "fonts/KA1.ttf", 100);
	labelScores->setPosition(ccp(contentSize.width*3/4, contentSize.height * 5 / 7));
	background->addChild(labelScores);

	//存储分数
	int Score[6] = { 0 };
	Score[0] = score;
	Score[1] = atoi(UserDefault::getInstance()->getStringForKey("user_score2", "0").c_str());
	Score[2] = atoi(UserDefault::getInstance()->getStringForKey("user_score3", "0").c_str());
	Score[3] = atoi(UserDefault::getInstance()->getStringForKey("user_score4", "0").c_str());
	Score[4] = atoi(UserDefault::getInstance()->getStringForKey("user_score5", "0").c_str());
	Score[5] = atoi(UserDefault::getInstance()->getStringForKey("user_score6", "0").c_str());
	sort(Score, Score + 6);
	UserDefault::getInstance()->setStringForKey("user_score2", Convert2String(Score[5]));
	UserDefault::getInstance()->setStringForKey("user_score3", Convert2String(Score[4]));
	UserDefault::getInstance()->setStringForKey("user_score4", Convert2String(Score[3]));
	UserDefault::getInstance()->setStringForKey("user_score5", Convert2String(Score[2]));
	UserDefault::getInstance()->setStringForKey("user_score6", Convert2String(Score[1]));
	UserDefault::getInstance()->flush();



	auto image = ImageView::create("UI2/Gameover/best.png");
	image->setPosition(ccp(contentSize.width / 4, contentSize.height*3 / 5));
	background->addChild(image);
	//分数数字加入layer中
	std::string oldScore = Convert2String(UserDefault::getInstance()->getStringForKey("user_score2"));
	LabelTTF* MaxScores = LabelTTF::create(oldScore.c_str(), "fonts/KA1.ttf", 100);
	MaxScores->setPosition(ccp(contentSize.width*3 / 4, contentSize.height * 3 / 5));
	background->addChild(MaxScores);
	//奖励
	/*auto Reward = Sprite::create("UI2/Gameover/reward.png");
	Reward->setPosition(ccp(contentSize.width/2,contentSize.height*2/5));
	background->addChild(Reward);
	auto Money_coin = Sprite::create("UI2/Gameover/coin.png");
	Money_coin->setPosition(ccp(Reward->getContentSize().width/4,Reward->getContentSize().height*5/9));
	Reward->addChild(Money_coin);
	*/


	auto item1 = MenuItemImage::create("UI2/Gameover/play_1.png", "UI2/Gameover/play_2.png", CC_CALLBACK_1(GameOver::playAgain, this));
	auto item2 = MenuItemImage::create("UI2/Gameover/home_1.png", "UI2/Gameover/home_2.png", CC_CALLBACK_1(GameOver::backHome, this));
	auto item3 = MenuItemImage::create("UI2/Gameover/share_1.png", "UI2/Gameover/share_2.png", CC_CALLBACK_1(GameOver::Share, this));
	Menu * menu = Menu::create(item1, item2, item3, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(ccp(contentSize.width / 2, 100));
	background->addChild(menu);
	music_key = UserDefault::getInstance()->getBoolForKey("musickey_1");
	if (music_key)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_main.mp3", true);//播放背景音乐

	return true;
}

void GameOver::playAgain(Object * object){
	Director::getInstance()->resume();
	if (changscene)
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PlayerScene::scene()));
	else
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelScene::scene()));
}

void GameOver::backHome(Object * object){
	
	//继续游戏
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainScene::createScene()));
}

void GameOver::Share(Object * object){
	
}