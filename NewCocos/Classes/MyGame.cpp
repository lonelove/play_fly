#include "MyGame.h"
#include"MainScene.h"
USING_NS_CC;

Scene* MyGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MyGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MyGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	/************************************************/
	//�����Ϸ����
	auto layerClourBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerClourBG);

	auto closeItem = MenuItemImage::create(
		"Back.png",
		"Back.png",
		CC_CALLBACK_1(MyGame::menuCallback, this));

	closeItem->setPosition(ccp(20, 50));
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(50, 1150);
	addChild(menu);

	//�����Ϸ����
	auto title = LabelTTF::create("My 2048", "Arial", 80);
	title->setColor(Color3B(255, 255, 153));
	title->setPosition(Point(visibleSize.width / 2, visibleSize.height - 50));
	addChild(title);
	//���restart��ť
	restartBtn = LabelTTF::create("Restart", "Arial", 60);
	restartBtn->setColor(Color3B(204, 255, 153));
	restartBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height - 160));
	addChild(restartBtn);
	//�����Ϸ����
	auto slabel = LabelTTF::create("Score", "Arial", 50);
	slabel->setPosition(Point(visibleSize.width / 5, visibleSize.height - 240));
	addChild(slabel);
	score = 0;
	scoreLabel = LabelTTF::create("0", "Arial", 50);
	scoreLabel->setPosition(Point(visibleSize.width*3 / 4, visibleSize.height - 240));
	addChild(scoreLabel);
	//�������ؼ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MyGame::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MyGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//�������ɿ�Ƭ����
	createCrad(visibleSize);
	//��ʼ���������
	autoCreatCard();
	autoCreatCard();
	
	return true;
}

void MyGame::menuCallback(Object *pSender){
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainScene::createScene()));
}

bool MyGame::onTouchBegan(Touch *t, Event *e){
	//��¼��ʼ�������
	Point startPoint = t->getLocation();
	startX = startPoint.x;
	startY = startPoint.y;
	if (restartBtn->getBoundingBox().containsPoint(restartBtn->convertToNodeSpace(t->getLocation())))
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, MyGame::createScene()));
	}
	return true;
}

void MyGame::onTouchEnded(Touch *t, Event *e){
	//����ƫ�������ж��û���������
	Point endPoint = t->getLocation();
	offsetX = startX - endPoint.x;
	offsetY = startY - endPoint.y;
	//�ж��ƶ�����
	if (abs(offsetX)>abs(offsetY)){
		//����
		if (offsetX>-5){
			if (isMoveLeft())
				autoCreatCard();
			checkGameOver();
		}
		else{
			if (isMoveRight())
				autoCreatCard();
			checkGameOver();
		}
	}
	else{
		//����
		if (offsetY > -5){
			if (isMoveUp())
				autoCreatCard();
			checkGameOver();
		}
		else{
			if (isMoveDown())
				autoCreatCard();
			checkGameOver();
		}
	}

}

bool MyGame::isMoveLeft(){
	bool moved = false;
	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++){
			for (int x1 = x + 1; x1 < 4; x1++){
				if (cardArr[x1][y]->getNumber()>0){
					//��ǰλ��Ϊ�գ���ͬһ�е��в�Ϊ�յ����֣��Ͱ����Ƶ��յ�λ��,���Ű�ԭλ������
					if (cardArr[x][y]->getNumber() <= 0){
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						//��ɨ��һ�Σ�ȷ�����н����ȷ 
						x--;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						//�ϲ�ʱͬʱ�ӷ�  
						score += (cardArr[x][y]->getNumber());
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());
						moved = true;
					}
					break;
				}
			}
		}
	}
	return moved;
}
bool MyGame::isMoveRight()
{
	bool moved = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{   //��ǰλ��Ϊ�գ���ͬһ�е��в�Ϊ�յ����֣��Ͱ����Ƶ��յ�λ��,���Ű�ԭλ������  
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						//��ɨ��һ�Σ�ȷ�����н����ȷ  
						x++;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{//��ǰλ�ò�Ϊ�գ�����ͬһ�������֣���ͬ�ľ͵���,�����ԭλ��  
						cardArr[x][y]->setNumber((cardArr[x1][y]->getNumber()) * 2);
						cardArr[x1][y]->setNumber(0);
						score += (cardArr[x][y]->getNumber());
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());
						moved = true;
					}
					break;
				}
			}
		}
	}
	return moved;
}

bool MyGame::isMoveUp()
{
	bool moved = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{   //��ǰλ��Ϊ�գ���ͬһ�е��в�Ϊ�յ����֣��Ͱ����Ƶ��յ�λ��,���Ű�ԭλ������  
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						//��ɨ��һ�Σ�ȷ�����н����ȷ  
						y--;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{//��ǰλ�ò�Ϊ�գ�����ͬһ�������֣���ͬ�ľ͵���,�����ԭλ��  
						cardArr[x][y]->setNumber((cardArr[x][y1]->getNumber()) * 2);
						cardArr[x][y1]->setNumber(0);
						score += (cardArr[x][y]->getNumber());
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());
						moved = true;
					}
					break;
				}
			}
		}
	}
	return moved;

}

bool MyGame::isMoveDown()
{
	bool moved = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{   //��ǰλ��Ϊ�գ���ͬһ�е��в�Ϊ�յ����֣��Ͱ����Ƶ��յ�λ��,���Ű�ԭλ������  
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						//��ɨ��һ�Σ�ȷ�����н����ȷ  
						y++;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{//��ǰλ�ò�Ϊ�գ�����ͬһ�������֣���ͬ�ľ͵���,�����ԭλ��  
						cardArr[x][y]->setNumber((cardArr[x][y1]->getNumber()) * 2);
						cardArr[x][y1]->setNumber(0);
						score += (cardArr[x][y]->getNumber());
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());
						moved = true;
					}
					break;
				}
			}
		}
	}
	return moved;
}
void MyGame::createCrad(Size size)
{
	//�����Ԫ��Ŀ��  
	int cardLen = (size.width - 20) / 4;

	//4*4��Ԫ��  
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Card *cards = Card::createCard(0, cardLen, cardLen, cardLen*i + 12, cardLen*j + 12 + size.height / 6);
			addChild(cards);
			//�ѿ�Ƭ����һ����ά��������  
			cardArr[i][j] = cards;
		}
	}
}

void MyGame::autoCreatCard()
{
	//������ɺ������������  
	int row = CCRANDOM_0_1() * 4;
	int col = CCRANDOM_0_1() * 4;

	//�ж�λ���Ƿ��Ѿ���������  
	if (cardArr[row][col]->getNumber() > 0)
	{
		autoCreatCard();
	}
	else
	{   //4���ֵļ�����%10  
		cardArr[row][col]->setNumber(CCRANDOM_0_1() * 10<1 ? 4 : 2);
	}

}
void MyGame::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void MyGame::checkGameOver()
{
	bool isGameOver = true;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArr[x][y]->getNumber() == 0 ||
				(x>0 && (cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber())) ||
				(x<3 && (cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber())) ||
				(y>0 && (cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber())) ||
				(y<3 && (cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))){
				isGameOver = false;//����������������Ϸ����  
			}
		}
	}

	if (isGameOver)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, MyGame::createScene()));
	}
}
