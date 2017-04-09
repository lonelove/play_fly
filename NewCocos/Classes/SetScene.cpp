#include "SetScene.h"
#include "cocostudio/CocoStudio.h"
#include"MainScene.h"
#include "SimpleAudioEngine.h"
#include"HPlayer.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

Scene* SetScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SetScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SetScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("SettingScene.csb");
	addChild(rootNode);
	/*获取按钮*/
	auto button3 = (ui::Button*)rootNode->getChildByName("Button_1_1");
	button3->addTouchEventListener(this, toucheventselector(SetScene::OnClickAbout));
	auto button4 = (ui::Button*)rootNode->getChildByName("Button_4");
	button4->addTouchEventListener(this, toucheventselector(SetScene::OnClickReset));
	auto button5 = (ui::Button*)rootNode->getChildByName("Button_5");
	button5->addTouchEventListener(this, toucheventselector(SetScene::OnClickBack));

	/*获取滑动条*/
	slider1 = (ui::Slider*)rootNode->getChildByName("Slider_1");
	int percent1 = UserDefault::getInstance()->getIntegerForKey("percent_1");
	slider1->setPercent(percent1);
	slider1->addEventListenerSlider(this, sliderpercentchangedselector(SetScene::OnClickMusic));
	/*获取滑动条*/
	slider2 = (ui::Slider*)rootNode->getChildByName("Slider_2");
	int percent2 = UserDefault::getInstance()->getIntegerForKey("percent_2");
	slider2->setPercent(percent2);
	slider2->addEventListenerSlider(this, sliderpercentchangedselector(SetScene::OnClickEffect));
	/*获取滑动条*/
	slider3 = (ui::Slider*)rootNode->getChildByName("Slider_3");
	int percent3 = UserDefault::getInstance()->getIntegerForKey("percent_3");
	slider3->setPercent(percent3);
	slider3->addEventListenerSlider(this, sliderpercentchangedselector(SetScene::OnClickMovse));
	return true;
}

void SetScene::OnClickAbout(Ref* pSende, TouchEventType eventtype){
	auto rootNode = CSLoader::createNode("AboutLayer.csb");
	rootNode->setPosition(ccp(0,0));
	addChild(rootNode,2,1);
	auto button1 = (ui::Button*)rootNode->getChildByName("Button_1");
	button1->addTouchEventListener(this, toucheventselector(SetScene::OnClickClose));
}

void SetScene::OnClickClose(Ref* pSende, TouchEventType eventtype){
	this->removeChildByTag(1,true);
}

void SetScene::OnClickBack(Ref* pSende, TouchEventType eventtype){
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_fanhui.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f,MainScene::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}

}

void SetScene::OnClickReset(Ref* pSende, TouchEventType eventtype){
	int score = 0;
	UserDefault::getInstance()->setStringForKey("user_score2", Convert2String(score)); 
	UserDefault::getInstance()->setStringForKey("user_score3", Convert2String(score));
	UserDefault::getInstance()->setStringForKey("user_score4", Convert2String(score));
	UserDefault::getInstance()->setStringForKey("user_score5", Convert2String(score));
	UserDefault::getInstance()->setStringForKey("user_score6", Convert2String(score));

}

void SetScene::OnClickMusic(Ref* pSende, SliderEventType type){//slider滑动条回调函数
	if (type == SliderEventType::SLIDER_PERCENTCHANGED){
		Slider* slider = dynamic_cast<Slider*>(pSende);
		int percent = slider->getPercent();
		UserDefault::getInstance()->setIntegerForKey("percent_1",percent);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)percent / 100);
		CCLOG("slider_percent:%f", (float)percent/100);
	}
	
}

void SetScene::OnClickEffect(Ref* pSende, SliderEventType type){//slider滑动条回调函数
	if (type == SliderEventType::SLIDER_PERCENTCHANGED){
		Slider* slider = dynamic_cast<Slider*>(pSende);
		int percent = slider->getPercent();
		UserDefault::getInstance()->setIntegerForKey("percent_2", percent);
		SimpleAudioEngine::getInstance()->setEffectsVolume((float)percent / 100);
		CCLOG("slider_percent:%f", (float)percent / 100);
	}

}

void SetScene::OnClickMovse(Ref* pSende, SliderEventType type){//slider滑动条回调函数
	if (type == SliderEventType::SLIDER_PERCENTCHANGED){
		Slider* slider = dynamic_cast<Slider*>(pSende);
		int percent = slider->getPercent();
		UserDefault::getInstance()->setIntegerForKey("percent_3", percent);
	}
}
