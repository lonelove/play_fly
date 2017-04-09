#include"LevelSelect.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include"LevelScene.h"
#include"MainScene.h"

USING_NS_CC;
extern int playlevel;
int playlevel2 = 0;
int playlevel3 = 0;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

Scene* LevelSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelSelect::create();
	scene->addChild(layer);
	return scene;
}

bool LevelSelect::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("LevelScene.csb");
	addChild(rootNode);

	auto button1 = (ui::Button*)rootNode->getChildByName("Button_1");
	button1->addTouchEventListener(this, toucheventselector(LevelSelect::backMain));
	
	auto pageview = (ui::PageView*)rootNode->getChildByName("PageView_2");
	auto layout1 = (ui::Layout*)pageview->getChildByName("Panel_1");
	m_gif1 = (Sprite*)layout1->getChildByName("Sprite_8");
	runGif1();
	auto button5 = (ui::Button*)layout1->getChildByName("Button_5");
	button5->addTouchEventListener(this,toucheventselector(LevelSelect::PlayGo1));

	auto layout2 = (ui::Layout*)pageview->getChildByName("Panel_2");
	m_gif2 = (Sprite*)layout2->getChildByName("Sprite_9");
	runGif2();
	auto button9 = (ui::Button*)layout2->getChildByName("Button_9");
	if (playlevel2==1){
		button9->setBright(true);
		button9->setEnabled(true);
		button9->addTouchEventListener(this, toucheventselector(LevelSelect::PlayGo2));
	}
	auto layout3 = (ui::Layout*)pageview->getChildByName("Panel_3");
	m_gif3 = (Sprite*)layout3->getChildByName("Sprite_10");
	runGif3();
	auto button10 = (ui::Button*)layout3->getChildByName("Button_10");
	if (playlevel3==1){
		button10->setBright(true);
		button10->setEnabled(true);
		button10->addTouchEventListener(this, toucheventselector(LevelSelect::PlayGo3));
	}
	return true;
}

void LevelSelect::runGif1(){
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;
	for (int i = 1; i <= 20;i++){
		frame = SpriteFrame::create(StringUtils::format("UI2/gif1/%d.png", i), Rect(0, 0, 699, 529));
		frameList.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.5f);
	Animate* animate = Animate::create(animation);
	m_gif1->runAction(animate);
}
void LevelSelect::runGif2(){
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;
	for (int i = 1; i <= 11; i++){
		frame = SpriteFrame::create(StringUtils::format("UI2/gif2/%d.png", i), Rect(0, 0, 699, 699));
		frameList.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.5f);
	Animate* animate = Animate::create(animation);
	m_gif2->runAction(animate);
}
void LevelSelect::runGif3(){
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;
	for (int i = 1; i <= 9; i++){
		frame = SpriteFrame::create(StringUtils::format("UI2/gif3/%d.png", i), Rect(0, 0, 699, 529));
		frameList.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.5f);
	Animate* animate = Animate::create(animation);
	m_gif3->runAction(animate);
}

void LevelSelect::PlayGo1(Ref* pSende, TouchEventType eventtype){
	playlevel = 1;
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelScene::scene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void LevelSelect::PlayGo2(Ref* pSende, TouchEventType eventtype){
	playlevel = 2;
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelScene::scene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void LevelSelect::PlayGo3(Ref* pSende, TouchEventType eventtype){
	playlevel = 3;
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_jinru.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelScene::scene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

void LevelSelect::backMain(Ref* pSende, TouchEventType eventtype){
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_fanhui.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainScene::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}
}

