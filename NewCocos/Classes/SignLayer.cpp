#include"SignLayer.h"
#include"MainScene.h"
#include"SimpleAudioEngine.h"


using namespace CocosDenshion;

Scene* SignLayer::scene()
{
	auto scene = Scene::create();
	auto layer = SignLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SignLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	daycont = 0;
	Size winSize = Director::getInstance()->getVisibleSize();

	//设置这个层的背景图片，并且设置其位置为整个屏幕的中点
	background = Sprite::create("UI2/Sign_In/background.png");
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background);
	m_cat = Sprite::create("UI2/Sign_In/cat.png");

	run();
	Size contentSize = background->getContentSize();

	auto image1 = ImageView::create("UI2/Sign_In/DAUKY-REWARD.png");
	image1->setPosition(ccp(contentSize.width/2,contentSize.height/4));
	background->addChild(image1);
	auto image2 = ImageView::create("UI2/Sign_In/code.png");
	image2->setPosition(ccp(image1->getContentSize().width / 4, image1->getContentSize().height*3/5));
	image1->addChild(image2);
	if (daycont==1){
		auto image3 = ImageView::create("UI2/Sign_In/100.png");
		image3->setPosition(ccp(image1->getContentSize().width * 3 / 5, image1->getContentSize().height * 3 / 5));
		image1->addChild(image3);
	}
	else{
		auto image3 = ImageView::create("UI2/Sign_In/100.png");
		image3->setPosition(ccp(image1->getContentSize().width * 3 / 5, image1->getContentSize().height * 3 / 5));
		image1->addChild(image3);
	}

	auto closeItem = MenuItemImage::create("Back.png","Back.png",CC_CALLBACK_1(SignLayer::backMain, this));
	closeItem->setPosition(ccp(20, 50));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(50, 1150);
	background->addChild(menu);
	return true;
}

void SignLayer::run(){
	//获得背景图片的大小
	Size contentSize = background->getContentSize();

	struct tm *tm;
	time_t timep;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	time(&timep);
#else
	struct timeval tv;
	gettimeofday(&tv,NULL);
	timep = tv.tv_sec;
#endif
	tm = localtime(&timep);
	day = tm->tm_mday;
	int oldday = UserDefault::getInstance()->getIntegerForKey("time_1");
	daycont = UserDefault::getInstance()->getIntegerForKey("timecont_1");
	CCLOG("%d",daycont);
	if (day!=oldday){
		
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*>frameList;
		for (int i = 1; i <= 2; i++){
			frame = SpriteFrame::create(StringUtils::format("UI2/Sign_In/cat_%d.png", i), Rect(0, 0, 721, 642));
			frameList.pushBack(frame);
		}
		Animation* animation = Animation::createWithSpriteFrames(frameList);
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.5f);
		Animate* animate = Animate::create(animation);
		m_cat->runAction(animate);		
		m_cat->setPosition(ccp(contentSize.width / 2, contentSize.height * 2 / 3));
		background->addChild(m_cat);

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(SignLayer::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(SignLayer::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	}
	else{
		m_cat->setTexture("UI2/Sign_In/cat_down.png");
		m_cat->setPosition(ccp(contentSize.width / 2, contentSize.height * 2 / 3));
		background->addChild(m_cat);
	}

}

bool SignLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
	return true;
}

void SignLayer::onTouchEnded(Touch *pTouch, Event *pEvent){
	Point pos = pTouch->getLocation();
	if (m_cat->boundingBox().containsPoint(pos)){
		m_cat->stopAllActions();
	}
	m_cat->setTexture("UI2/Sign_In/cat_down.png");
	daycont++;
	if (daycont % 8 == 0)
		daycont = 1;

	UserDefault::getInstance()->setIntegerForKey("time_1", day);
	UserDefault::getInstance()->setIntegerForKey("timecont_1", daycont);
	UserDefault::getInstance()->flush();
	
	SimpleAudioEngine::sharedEngine()->playEffect("sound/effcet_ui_jinbibaoji.mp3");
}

void SignLayer::backMain(Object *pSender){
	SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_fanhui.mp3");
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainScene::createScene()));
}
