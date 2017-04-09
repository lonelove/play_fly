#include "MyHanagerScene.h"
#include "cocostudio/CocoStudio.h"
#include"MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace CocosDenshion;

int fly=1;

Scene* MyHanager::createScene()
{
	auto scene = Scene::create();
	auto layer = MyHanager::create();
	scene->addChild(layer);
	return scene;
}

bool MyHanager::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
		
	auto rootNode = CSLoader::createNode("StoreScene.csb");
	addChild(rootNode);
	IM = (ui::Scale9Sprite*)rootNode->getChildByName("Sprite_2");
	auto button1 = (ui::Button*)rootNode->getChildByName("Button_1");
	button1->addTouchEventListener(this, toucheventselector(MyHanager::OnClickfly1));
	auto button2 = (ui::Button*)rootNode->getChildByName("Button_2");
	button2->addTouchEventListener(this, toucheventselector(MyHanager::OnClickfly2));
	auto button3 = (ui::Button*)rootNode->getChildByName("Button_3");
	button3->addTouchEventListener(this, toucheventselector(MyHanager::OnClickfly3));
	auto button4 = (ui::Button*)rootNode->getChildByName("Button_4");
	button4->addTouchEventListener(this, toucheventselector(MyHanager::OnClickfly4));
	
	checkbox1 = (ui::CheckBox*)rootNode->getChildByName("CheckBox_1");
	checkbox1->addEventListenerCheckBox(this, checkboxselectedeventselector(MyHanager::checkBoxCallback1));
	checkbox2 = (ui::CheckBox*)rootNode->getChildByName("CheckBox_2");
	checkbox2->addEventListenerCheckBox(this, checkboxselectedeventselector(MyHanager::checkBoxCallback2));
	checkbox3 = (ui::CheckBox*)rootNode->getChildByName("CheckBox_3");
	checkbox3->addEventListenerCheckBox(this, checkboxselectedeventselector(MyHanager::checkBoxCallback3));
	checkbox4 = (ui::CheckBox*)rootNode->getChildByName("CheckBox_4");
	checkbox4->addEventListenerCheckBox(this, checkboxselectedeventselector(MyHanager::checkBoxCallback4));
	int chance = UserDefault::getInstance()->getIntegerForKey("Fly_1");
	switch (chance)
	{
	case 1:checkbox1->setSelectedState(true);checkbox2->setSelectedState(false);
		   checkbox3->setSelectedState(false);checkbox4->setSelectedState(false); break;
	case 2:checkbox1->setSelectedState(false);checkbox2->setSelectedState(true);
		   checkbox3->setSelectedState(false);checkbox4->setSelectedState(false); break;
	case 3:checkbox1->setSelectedState(false);checkbox2->setSelectedState(false);
		   checkbox3->setSelectedState(true);checkbox4->setSelectedState(false); break;
	case 4:checkbox1->setSelectedState(false);checkbox2->setSelectedState(false);
		   checkbox3->setSelectedState(false);checkbox4->setSelectedState(true); break;
	default:
		break;
	}
	auto button5 = (ui::Button*)rootNode->getChildByName("Button_5");
	auto button6 = (ui::Button*)rootNode->getChildByName("Button_6");

	auto button7 = (ui::Button*)rootNode->getChildByName("Button_7");
	button7->addTouchEventListener(this, toucheventselector(MyHanager::OnClickBack));
	return true;
}
void MyHanager::checkBoxCallback1(Ref* sender, CheckBoxEventType type){
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:{
		fly = 1;
		UserDefault::getInstance()->setIntegerForKey("Fly_1", fly);checkbox2->setSelectedState(false);
		checkbox3->setSelectedState(false);checkbox4->setSelectedState(false);
	}break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:break;
	default:
		break;
	}
}
void MyHanager::checkBoxCallback2(Ref* sender, CheckBoxEventType type){
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:{
		fly = 2;
		UserDefault::getInstance()->setIntegerForKey("Fly_1", fly); checkbox1->setSelectedState(false);
		checkbox3->setSelectedState(false); checkbox4->setSelectedState(false);
	}break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:break;
	default:
		break;
	}
}
void MyHanager::checkBoxCallback3(Ref* sender, CheckBoxEventType type){
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:{
		fly = 3;
		UserDefault::getInstance()->setIntegerForKey("Fly_1", fly); checkbox1->setSelectedState(false);
		checkbox2->setSelectedState(false); checkbox4->setSelectedState(false);
	}break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:break;
	default:
		break;
	}
}
void MyHanager::checkBoxCallback4(Ref* sender, CheckBoxEventType type){
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:{
		fly = 4;
		UserDefault::getInstance()->setIntegerForKey("Fly_1", fly); checkbox1->setSelectedState(false);
		checkbox2->setSelectedState(false); checkbox3->setSelectedState(false);
	}break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:break;
	default:
		break;
	}
}

void MyHanager::OnClickfly1(Ref* pSende, TouchEventType eventtype){
	IM->removeChildByTag(1, true);
	IM->removeChildByTag(2, true);
	IM->removeChildByTag(3, true);
	IM->removeChildByTag(4, true);
	IM->removeChildByTag(11, true);
	IM->removeChildByTag(22, true);
	IM->removeChildByTag(33, true);
	IM->removeChildByTag(44, true);
	Size winSize = Director::getInstance()->getVisibleSize();
	Sprite* name = Sprite::create("UI2/Kinzu.png");
	name->setPosition(ccp(winSize.width / 3, winSize.height * 3 / 5));
	IM->addChild(name,10,1);
	Sprite* introduce = Sprite::create("UI2/kinzu_txt.png");
	introduce->setPosition(ccp(winSize.width / 2, winSize.height / 8));
	IM->addChild(introduce, 10, 11);

}
void MyHanager::OnClickfly2(Ref* pSende, TouchEventType eventtype){
	IM->removeChildByTag(1, true);
	IM->removeChildByTag(2, true);
	IM->removeChildByTag(3, true);
	IM->removeChildByTag(4, true);
	IM->removeChildByTag(11, true);
	IM->removeChildByTag(22, true);
	IM->removeChildByTag(33, true);
	IM->removeChildByTag(44, true);
	Size winSize = Director::getInstance()->getVisibleSize();
	Sprite* name = Sprite::create("UI2/Buzzard.png");
	name->setPosition(ccp(winSize.width / 3, winSize.height * 3 / 5));
	IM->addChild(name, 10, 2);
	Sprite* introduce = Sprite::create("UI2/blizzard_txt.png");
	introduce->setPosition(ccp(winSize.width / 2, winSize.height / 8));
	IM->addChild(introduce, 10, 22);
}
void MyHanager::OnClickfly3(Ref* pSende, TouchEventType eventtype){
	IM->removeChildByTag(1, true);
	IM->removeChildByTag(2, true);
	IM->removeChildByTag(3, true);
	IM->removeChildByTag(4, true);
	IM->removeChildByTag(11, true);
	IM->removeChildByTag(22, true);
	IM->removeChildByTag(33, true);
	IM->removeChildByTag(44, true);
	Size winSize = Director::getInstance()->getVisibleSize();
	Sprite* name = Sprite::create("UI2/Sakura.png");
	name->setPosition(ccp(winSize.width / 3, winSize.height * 3 / 5));
	IM->addChild(name, 10, 3);
	Sprite* introduce = Sprite::create("UI2/sakura_txt.png");
	introduce->setPosition(ccp(winSize.width / 2, winSize.height / 8));
	IM->addChild(introduce, 10, 33);
}
void MyHanager::OnClickfly4(Ref* pSende, TouchEventType eventtype){
	IM->removeChildByTag(1, true);
	IM->removeChildByTag(2, true);
	IM->removeChildByTag(3, true);
	IM->removeChildByTag(4, true);
	IM->removeChildByTag(11, true);
	IM->removeChildByTag(22, true);
	IM->removeChildByTag(33, true);
	IM->removeChildByTag(44, true);
	Size winSize = Director::getInstance()->getVisibleSize();
	Sprite* name = Sprite::create("UI2/Blaze.png");
	name->setPosition(ccp(winSize.width / 3, winSize.height * 3 / 5));
	IM->addChild(name, 10, 4);
	Sprite* introduce = Sprite::create("UI2/blaze_txt.png");
	introduce->setPosition(ccp(winSize.width / 2, winSize.height / 8));
	IM->addChild(introduce, 10, 44);
}

void MyHanager::OnClickBack(Ref* pSende, TouchEventType eventtype){

	//UserDefault::getInstance()->setIntegerForKey("Chance_1", chance);
	//UserDefault::getInstance()->setIntegerForKey("timecont_1", daycont);
	//UserDefault::getInstance()->flush();
	//Director::getInstance()->end();
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_fanhui.mp3");break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f,MainScene::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}

}
