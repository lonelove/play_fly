#include "LoadScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
extern bool music_key;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

Scene* LoadScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoadScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("LoadingScene.csb");
	addChild(rootNode);
	image = (ui::ImageView*)rootNode->getChildByName("Image_1");
	PreloadMusicAndPicture();
	auto button = (ui::Button*)rootNode->getChildByName("Button_1");//获取按钮
	button->addTouchEventListener(this, toucheventselector(LoadScene::OnClickStart));//设置按钮事件
	music_key = UserDefault::getInstance()->getBoolForKey("musickey_1");
	percent1 = UserDefault::getInstance()->getIntegerForKey("percent_1");
	percent2 = UserDefault::getInstance()->getIntegerForKey("percent_2");
	if (music_key){
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_main.mp3", true);//播放背景音乐
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)percent1 / 100);
	}
	Size size = Director::getInstance()->getVisibleSize();
	Sprite* top_start = Sprite::create("UI2/loading/tap-the-start.png");//添加提示信息
	top_start->setPosition(ccp(size.width/2,size.height/6));
	image->addChild(top_start);
	ActionInterval *action1 = FadeIn::create(1);
	ActionInterval *action2 = FadeOut::create(1);
	top_start->runAction(RepeatForever::create(Sequence::create(action1,action2,NULL)));//执行闪烁动作
	Sprite* xin1 = Sprite::create("UI2/loading/2.1.png");
	xin1->setPosition(ccp(240,1020));
	image->addChild(xin1);
	star1 = Sprite::create("UI2/loading/star1.png");
	star2 = Sprite::create("UI2/loading/star2.png");
	star3 = Sprite::create("UI2/loading/star3.png");
	star4 = Sprite::create("UI2/loading/star4.png");
	time = 0;
	this->scheduleUpdate();
	image->addChild(star1);
	image->addChild(star2);
	image->addChild(star3);
	image->addChild(star4);
	ActionInterval *action3 = FadeIn::create(1);
	ActionInterval *action4 = FadeOut::create(1);
	Action* action = RepeatForever::create(Sequence::create(action3, action4, NULL));
	xin1->runAction(action);
	ActionInterval *blinkAction = Blink::create(1, 2);
	Action* actionStar = RepeatForever::create(blinkAction);//执行动作
	star1->runAction(actionStar);
	star2->runAction(actionStar);
	star3->runAction(actionStar);
	star4->runAction(actionStar);
	return true;
}
void LoadScene::update(float dt){//星星出现的位置
	time++;
	if (time % 60 == 0){
		int x, y;
		x = 200 + CCRANDOM_0_1() * 400;
		y = 200 + CCRANDOM_0_1() * 900;
		star1->setPosition(ccp(x + CCRANDOM_0_1() * 50, y - CCRANDOM_0_1() - 50));
		star2->setPosition(ccp(x + CCRANDOM_0_1() * 100 - 50, y - CCRANDOM_0_1() * 100 + 50));
		star3->setPosition(ccp(x - CCRANDOM_0_1() * 100, y + CCRANDOM_0_1() * 50));
		star4->setPosition(ccp(x - CCRANDOM_0_1() * 100 + 50, y + CCRANDOM_0_1() * 100 - 50));
		time = 0;
	}
}
void LoadScene::OnClickStart(Ref* pSende, TouchEventType eventtype){

	
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3");
		SimpleAudioEngine::getInstance()->setEffectsVolume((float)percent2 / 100);
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainScene::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}

}

void LoadScene::PreloadMusicAndPicture(){
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bgm_main.mp3");
}

