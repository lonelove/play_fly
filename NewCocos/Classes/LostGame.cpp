#include "SimpleAudioEngine.h"
#include"LostGame.h"
#include"MainScene.h"
#include"LevelScene.h"

USING_NS_CC;
extern bool music_key;
using namespace CocosDenshion;

Scene* LostGame::scene(){
	auto scene = Scene::create();
	auto layer = LostGame::create();
	scene->addChild(layer);
	return scene;
}

bool LostGame::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getVisibleSize();

	//设置这个层的背景图片，并且设置其位置为整个屏幕的中点
	background = Sprite::create("UI2/lostGame/background.jpg");
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background);
	Size contentSize = background->getContentSize();

	auto coin = Sprite::create("UI2/Gameover/coin.png");
	coin->setPosition(ccp(contentSize.width * 3 / 4, contentSize.height - 50));
	background->addChild(coin);
	//当前金币加入layer中
	std::string strCoin = Convert2String(0);
	LabelTTF* labelCoin = LabelTTF::create(strCoin.c_str(), "fonts/KA1.ttf", 50);
	labelCoin->setColor(ccc3(255, 255, 0));
	labelCoin->setPosition(ccp(contentSize.width - 70, contentSize.height - 50));
	background->addChild(labelCoin);

	auto image = ImageView::create("UI2/lostGame/failed.png");
	image->setPosition(ccp(contentSize.width / 2, contentSize.height*2/3));
	background->addChild(image);

	sad = Sprite::create("UI2/lostGame/0.png");
	run();

	auto item1 = MenuItemImage::create("UI2/continue.png", "UI2/continue_anxia.png", CC_CALLBACK_1(LostGame::playAgain, this));
	auto item2 = MenuItemImage::create("UI2/back.png", "UI2/back_anxia.png", CC_CALLBACK_1(LostGame::backHome, this));
	Menu * menu = Menu::create(item1, item2, NULL);
	menu->alignItemsHorizontallyWithPadding(70);
	menu->setPosition(ccp(contentSize.width / 2, 130));
	background->addChild(menu);
	music_key = UserDefault::getInstance()->getBoolForKey("musickey_1");
	if (music_key)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_main.mp3", true);//播放背景音乐

	return true;
}

void LostGame::run(){
	Size contentSize = background->getContentSize();
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*>frameList;
	for (int i = 1; i <= 14; i++){
		frame = SpriteFrame::create(StringUtils::format("UI2/lostGame/%d.png", i), Rect(0, 0, 586, 80));
		frameList.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.5f);
	Animate* animate = Animate::create(animation);
	sad->runAction(animate);
	sad->setPosition(ccp(contentSize.width / 2, contentSize.height / 2));
	background->addChild(sad);
}

void LostGame::playAgain(Object * object){
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelScene::scene()));
}

void LostGame::backHome(Object * object){
	//继续游戏
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainScene::createScene()));
}
