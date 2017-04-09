#include "HPauseLayer.h"
#include "SimpleAudioEngine.h"
#include <limits>
#include "MainScene.h"

using namespace CocosDenshion;

extern bool music_key;
Menu *menu;
bool HPauseLayer::init()
{
	if (!LayerColor::initWithColor(ccc4(0, 0, 0, 150))) {
		return  false;
	}
	Size winSize = Director::getInstance()->getVisibleSize();

	MenuItemImage *play = MenuItemImage::create("UI2/continue.png", "UI2/continue_anxia.png", this, menu_selector(HPauseLayer::backGame));
	play->setTag(10);
	play->setPosition(ccp(winSize.width / 2- 120, winSize.height / 2 ));

	MenuItemImage * back = MenuItemImage::create("UI2/back.png", "UI2/back_anxia.png", this, menu_selector(HPauseLayer::backHome));
	back->setTag(20);
	back->setPosition(ccp(winSize.width / 2+ 120, winSize.height / 2 ));

	menu = Menu::create(play, back, NULL);
	menu->setAnchorPoint(ccp(0, 0));
	menu->setPosition(Point::ZERO);
	addChild(menu, 1, 10);
	music_key = UserDefault::getInstance()->getBoolForKey("musickey_1");
	if (music_key)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_main.mp3", true);//���ű�������


	return true;

}

void HPauseLayer::backGame(Object *pSender)
{
	Director::getInstance()->resume();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	removeFromParentAndCleanup(true);
}

//����������
void HPauseLayer::backHome(Object *pSender){
	//ֹͣ��Ϸ
	Director::getInstance()->pause();
//	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();

	this->unscheduleAllSelectors();
	//������Ϸ
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(MainScene::createScene());
}

