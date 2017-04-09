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
	//添加游戏背景
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

	//添加游戏标题
	auto title = LabelTTF::create("My 2048", "Arial", 80);
	title->setColor(Color3B(255, 255, 153));
	title->setPosition(Point(visibleSize.width / 2, visibleSize.height - 50));
	addChild(title);
	//添加restart按钮
	restartBtn = LabelTTF::create("Restart", "Arial", 60);
	restartBtn->setColor(Color3B(204, 255, 153));
	restartBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height - 160));
	addChild(restartBtn);
	//添加游戏分数
	auto slabel = LabelTTF::create("Score", "Arial", 50);
	slabel->setPosition(Point(visibleSize.width / 5, visibleSize.height - 240));
	addChild(slabel);
	score = 0;
	scoreLabel = LabelTTF::create("0", "Arial", 50);
	scoreLabel->setPosition(Point(visibleSize.width*3 / 4, visibleSize.height - 240));
	addChild(scoreLabel);
	//创建触控监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MyGame::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MyGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//调用生成卡片方法
	createCrad(visibleSize);
	//开始生成随机数
	autoCreatCard();
	autoCreatCard();
	
	return true;
}

void MyGame::menuCallback(Object *pSender){
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainScene::createScene()));
}

bool MyGame::onTouchBegan(Touch *t, Event *e){
	//记录开始点击坐标
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
	//计算偏移量，判断用户滑动方向
	Point endPoint = t->getLocation();
	offsetX = startX - endPoint.x;
	offsetY = startY - endPoint.y;
	//判断移动方向
	if (abs(offsetX)>abs(offsetY)){
		//向左
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
		//向上
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
					//当前位置为空，而同一行的有不为空的数字，就把它移到空的位置,接着把原位置清零
					if (cardArr[x][y]->getNumber() <= 0){
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						//再扫描一次，确保所有结果正确 
						x--;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						//合并时同时加分  
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
				{   //当前位置为空，而同一行的有不为空的数字，就把它移到空的位置,接着把原位置清零  
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						//再扫描一次，确保所有结果正确  
						x++;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{//当前位置不为空，而且同一行有数字，相同的就叠加,并清空原位置  
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
				{   //当前位置为空，而同一行的有不为空的数字，就把它移到空的位置,接着把原位置清零  
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						//再扫描一次，确保所有结果正确  
						y--;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{//当前位置不为空，而且同一行有数字，相同的就叠加,并清空原位置  
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
				{   //当前位置为空，而同一行的有不为空的数字，就把它移到空的位置,接着把原位置清零  
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						//再扫描一次，确保所有结果正确  
						y++;
						moved = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{//当前位置不为空，而且同一行有数字，相同的就叠加,并清空原位置  
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
	//求出单元格的宽高  
	int cardLen = (size.width - 20) / 4;

	//4*4单元格  
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Card *cards = Card::createCard(0, cardLen, cardLen, cardLen*i + 12, cardLen*j + 12 + size.height / 6);
			addChild(cards);
			//把卡片存在一个二维数组里面  
			cardArr[i][j] = cards;
		}
	}
}

void MyGame::autoCreatCard()
{
	//随机生成横坐标和纵坐标  
	int row = CCRANDOM_0_1() * 4;
	int col = CCRANDOM_0_1() * 4;

	//判断位置是否已经存在数字  
	if (cardArr[row][col]->getNumber() > 0)
	{
		autoCreatCard();
	}
	else
	{   //4出现的几率是%10  
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
				isGameOver = false;//满足以上条件则游戏继续  
			}
		}
	}

	if (isGameOver)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, MyGame::createScene()));
	}
}
