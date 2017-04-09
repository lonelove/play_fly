#include "MainScene.h"
#include "SetScene.h"
#include "MyHanagerScene.h"
#include "PopScene.h"
#include "RnakLayer.h"
#include "PlayerScene.h"
#include "SignLayer.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include"LevelSelect.h"
#include"MyGame.h"

USING_NS_CC;
bool changscene = true;
bool music_key = true;

using namespace cocostudio::timeline;
using namespace CocosDenshion;


Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);


	Layout* layout = (ui::Layout*)rootNode->getChildByName("Panel_1");
	//获取按钮
	auto button1 = (ui::Button*)layout->getChildByName("Button_1");
	button1->addTouchEventListener(this, toucheventselector(MainScene::OnClickEndless));//设置按钮事件
	auto button2 = (ui::Button*)layout->getChildByName("Button_2");
	button2->addTouchEventListener(this, toucheventselector(MainScene::OnClickStory));//设置按钮事件
	auto button4 = (ui::Button*)layout->getChildByName("Button_4");
	button4->addTouchEventListener(this, toucheventselector(MainScene::OnClickOptions));
	auto button3 = (ui::Button*)layout->getChildByName("Button_3");
	button3->addTouchEventListener(this, toucheventselector(MainScene::OnClickMyHangar));
	//auto button5 = (ui::Button*)layout->getChildByName("Button_5");
	//button5->addTouchEventListener(this, toucheventselector(MainScene::OnClickShare));
	auto button6 = (ui::Button*)layout->getChildByName("Button_6");
	button6->addTouchEventListener(this, toucheventselector(MainScene::OnClickRank));
	//auto button7 = (ui::Button*)layout->getChildByName("Button_7");
	//button7->addTouchEventListener(this,toucheventselector(MainScene::OnClickSign));

	music_key = UserDefault::getInstance()->getBoolForKey("musickey_1");
	button8 = (ui::Button*)layout->getChildByName("Button_8");
	if (music_key){
		button8->setBright(true);
	}
	else
		button8->setBright(false);
	button8->addTouchEventListener(this, toucheventselector(MainScene::OnClickMyMusic));	
	//获取文本框
	auto MaxScore = (ui::Text*)rootNode->getChildByName("Text_2");
	MaxScore->setText(UserDefault::getInstance()->getStringForKey("user_score2"));
	
	
	auto closeItem = MenuItemImage::create(
		"Back.png",
		"Back.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(ccp(20,50));
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(50,1150);
	this->addChild(menu);
	return true;
}

void MainScene::OnClickEndless(Ref* pSende, TouchEventType eventtype){
	changscene = true;
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PlayerScene::scene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void MainScene::OnClickStory(Ref* pSende, TouchEventType eventtype){
	changscene = false;
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelSelect::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void MainScene::OnClickOptions(Ref* pSende, TouchEventType eventtype){

	//Director::getInstance()->end();
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3");  break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SetScene::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void MainScene::OnClickMyHangar(Ref* pSende, TouchEventType eventtype){

	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break; 
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MyHanager::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}

}
/**
* 截图功能
*/
void MainScene::saveScreenshot() {
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCRenderTexture* texture = CCRenderTexture::create((int)size.width,
		(int)size.height);
	texture->setPosition(ccp(size.width / 2, size.height / 2));
	texture->begin();
	CCDirector::sharedDirector()->getRunningScene()->visit();
	texture->end();
	string imagePath =
		CCFileUtils::sharedFileUtils()->getWritablePath().c_str();
	//保存为png
	bool result = texture->saveToFile("screenshot.png", kCCImageFormatPNG);
	if (result) {
		imagePath += "screenshot.png";
	}

}
/*void MainScene::OnClickShare(Ref* pSende, TouchEventType eventtype){
	
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MyGame::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}
*/
void MainScene::OnClickRank(Ref* pSende, TouchEventType eventtype){
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f, RankLayer::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void MainScene::OnClickMyMusic(Ref* pSende, TouchEventType eventtype){
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN: break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (music_key){
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();//暂停播放
			music_key = false;
			UserDefault::getInstance()->setBoolForKey("musickey_1",music_key);		
			button8->setBright(false);
		}
		else{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_main.mp3", true);//播放背景音乐
			music_key = true;
			UserDefault::getInstance()->setBoolForKey("musickey_1", music_key);
			button8->setBright(true);
		}
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}

}	

void MainScene::OnClickSign(Ref* pSende, TouchEventType eventtype){
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SignLayer::scene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void MainScene::menuCloseCallback(Object *pSender){
	PopScene* popLayer = PopScene::create();
	this->addChild(popLayer);
}


