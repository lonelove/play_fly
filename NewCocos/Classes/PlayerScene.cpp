#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "PlayerScene.h"
#include "HMap.h"
#include "HPauseLayer.h"
#include "NewBullet.h"
#include "NewEnemy.h"
#include "Gems.h"
#include "UniqueSkill.h"
#include "GameOver.h"

using namespace CocosDenshion;
using namespace cocos2d;

static PlayerScene* sh;
extern int playerType;
extern int skill1Count;
extern int skill2Count;
extern int skill3Count;
bool touchType = false;

PlayerScene* PlayerScene::sharedPlayerScene(){
	if (sh){
		return sh;
	}
	return NULL;
}

Scene* PlayerScene::scene()
{
	auto scene = Scene::create();
	auto layer = PlayerScene::create();
	scene->addChild(layer);
	return scene;
}

bool PlayerScene::init(){
	if (!Layer::init()){ return false; }
	sh = this;
	playerType = 1;
	allTimeCount = 0;
	BulletDelayCount = 0;
	enemyType1TimeCount = 0;
	enemyType2TimeCount = 0;
	enemyType3TimeCount = 0;
	enemyType4TimeCount = 0;
	enemyType5TimeCount = 0;
	enemyType6TimeCount = 0;

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading/player.plist");
	playersBatchNode = SpriteBatchNode::create("loading/player.png");
	this->addChild(playersBatchNode, 100);

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading/enemy.plist");
	enemyBatchNode = SpriteBatchNode::create("loading/enemy.png", 50);
	this->addChild(enemyBatchNode, 100);

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading/bullet.plist");
	bulletBatchNode = SpriteBatchNode::create("loading/bullet.png", 50);
	this->addChild(bulletBatchNode, 100);


	creatEnemyInterval = 240;//240正好
	passCreatEnemy = false;
	M_music = UserDefault::getInstance()->getBoolForKey("musickey_1");
	if (M_music){
		//播放游戏中的音乐
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_endless.mp3", true);
	}
	//添加地图
	HMap * map = HMap::createMap("back5.jpg");
	addChild(map);
	chance = UserDefault::getInstance()->getIntegerForKey("Fly_1");
	switch (chance)
	{
	case 1:playerName = "player1_1.png";
		bulletType1 = "14.png";
		bulletType2 = "15.png";
		break;
	case 2:playerName = "player3_1.png";
		bulletType1 = "12.png";
		bulletType2 = "16.png";
		break;
	case 3:playerName = "player2_1.png";
		bulletType1 = "13.png";
		bulletType2 = "18.png";
		break;
	case 4:playerName = "player4_1.png";
		bulletType1 = "10.png";
		bulletType2 = "19.png";
		break;
	default:playerName = "player1_1.png";
		bulletType1 = "14.png";
		bulletType2 = "15.png";
		break;
	}
	//主角
	Size size = Director::getInstance()->getWinSize();
	NewPlayer * player = NewPlayer::createPlayer(playerName);
	player->setPosition(ccp(size.width*0.5, player->getContentSize().height*0.5));
	addChild(player, 1, tag_player);
	//添加主角属性
	this->addPlaneProperty();
	//创建子弹逻辑
	this->schedule(schedule_selector(PlayerScene::autoCreateBullet));

	//初始化敌人数组
	arrayEnemy = Array::create();
	CC_SAFE_RETAIN(arrayEnemy);

	//添加敌人
	this->schedule(schedule_selector(PlayerScene::autoCreateEnemy));

	//添加宝石
//	this->schedule(schedule_selector(PlayerScene::autoCreateGems), 15);
	this->setTouchEnabled(true);
	// 我机触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PlayerScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//添加暂停按钮
	MenuItemImage *pause = MenuItemImage::create("ui/pause.png", "ui/pause.png", this, menu_selector(PlayerScene::doPause));
	pause->setAnchorPoint(ccp(1, 1));
	pause->setPosition(ccp(Director::getInstance()->getVisibleSize().width - 10, Director::getInstance()->getVisibleSize().height - 10));
	Menu *menu = Menu::create(pause, NULL);
	menu->setAnchorPoint(ccp(0, 0));
	addChild(menu, 1, 10);
	menu->setPosition(Point::ZERO);

	this->schedule(schedule_selector(PlayerScene::resetPlayer));

	
	return true;
}
//暂停游戏
void PlayerScene::doPause(Object* psend)
{
	Director::getInstance()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	HPauseLayer *pauseLayer = HPauseLayer::create();
	addChild(pauseLayer, 9999, 9999);
}

bool PlayerScene::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void PlayerScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	//我们获取主要飞机作为触摸跟随对象
	Node* node = getChildByTag(tag_player);
	if (!node) {
		return;
	}
	//获取触摸轨迹距离，生成飞机的新坐标
	Point diff = pTouch->getDelta();
	Point currentPos = node->getPosition();
	Point targetPos = ccpAdd(currentPos, diff);
	//为让主要飞机始终在屏幕范围内，加上到达屏幕边缘的检测
	Size winSize = Director::getInstance()->getVisibleSize();
	Size nodeSize = node->getContentSize();
	if (targetPos.x < nodeSize.width / 2)
	{
		targetPos.x = nodeSize.width / 2;
	}
	else if (targetPos.x > winSize.width - nodeSize.width / 2)
	{
		targetPos.x = winSize.width - nodeSize.width / 2;
	}
	if (targetPos.y < nodeSize.height / 2)
	{
		targetPos.y = nodeSize.height / 2;
	}
	else if (targetPos.y > winSize.height - nodeSize.height / 2)
	{
		targetPos.y = winSize.height - nodeSize.height / 2;
	}
	//目标跟随
	node->setPosition(targetPos);
}

//添加飞机属性
void PlayerScene::addPlaneProperty()
{

	NewPlayer *player = this->getPlayer();
	player->hp = 3;//初始化当前血量为3
	player->score = 0;//初始化当前积分分数
	player->killCount = 0;
	int killCount = player->killCount;
	//初始化hp个血,加入到Layer中
	for (int i = 1; i <= player->hp; i++) {
		Sprite* spHp = Sprite::create("ui/icon_hp.png");
		spHp->setPosition(ccp(25 * i, spHp->getContentSize().height*0.5));
		if (i == 1){
			spHp->setTag(tag_playerHp1);
		}
		else if (i == 2){
			spHp->setTag(tag_playerHp2);
		}
		else if (i == 3){
			spHp->setTag(tag_playerHp3);
		}
		addChild(spHp, 10);
	}
	//初始化"分数"文字加入layer中
	LabelTTF* label = LabelTTF::create("Score:", "Helvetica-Blod", 24);
	label->setPosition(ccp(30, Director::getInstance()->getVisibleSize().height - 22));
	addChild(label, 10);

	//分数数字加入layer中
	std::string strScore = Convert2String(player->score);
	LabelTTF* labelScores = LabelTTF::create(strScore.c_str(), "Helvetica-Blod", 24);
	labelScores->setPosition(ccp(110, Director::getInstance()->getVisibleSize().height - 22));
	labelScores->setColor(ccc3(255, 255, 0));
	addChild(labelScores, 10, tag_scoreTTF);

	//杀敌人数
	LabelTTF* labelKill = LabelTTF::create("Kill:", "Helvetica-Blod", 24);
	labelKill->setPosition(ccp(30, Director::getInstance()->getVisibleSize().height - 52));
	addChild(labelKill, 10);

	//杀敌数字加入layer中
	std::string strKillCount = Convert2String(killCount);
	LabelTTF* labelKillCount = LabelTTF::create(strKillCount.c_str(), "Helvetica-Blod", 24);
	labelKillCount->setPosition(ccp(110, Director::getInstance()->getVisibleSize().height - 52));
	labelKillCount->setColor(ccc3(255, 255, 0));
	addChild(labelKillCount, 10, tag_killsCountTTF);
}

//自动添加主角子弹
void PlayerScene::autoCreateBullet(float f)
{
	BulletDelayCount++;//子弹延迟时间计数
	switch (playerType)
	{
	case 1://飞机1子弹
	{

		if (BulletDelayCount % 10 == 0)
		{
			NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(36, 15)), 1));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(36, -15)), 1));
			//子弹音效
			SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bullet.mp3");
		}
		break;
	}
	case 2://飞机2子弹
	{
		if (BulletDelayCount % 25 == 0 )
		{
			NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(20, 25)), 1));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(20, -25)), 1));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(48, 5)), 1));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(48, -5)), 1));
			SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bullet.mp3");
		}
		break;
	}
	case 3://飞机3子弹
	{
		if (BulletDelayCount % 20 == 0 )
		{
			NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(20, 25)), 1));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(20, -25)), 1));
			SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bullet.mp3");
		}
		if (BulletDelayCount % 90 == 0 && this->getArrayForEnemy()->count() != 0)
		{
			NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType2, 6, ccpAdd(player->getPosition(), ccp(48, 5)), 2));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType2, 6, ccpSub(player->getPosition(), ccp(48, -5)), 2));
		}
		break;
	}
	case 4://飞机4子弹
	{
		if (BulletDelayCount % 15 == 0 )
		{
			NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(20, 25)), 1));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(20, -25)), 1));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(45, 5)), 4));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(45, -5)), 3));
			SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bullet.mp3");
		}
		if (BulletDelayCount % 60 == 0 && this->getArrayForEnemy()->count() != 0)
		{
			NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType2, 6, ccpAdd(player->getPosition(), ccp(48, 5)), 2));
			bulletBatchNode->addChild(NewBullet::createBullet(bulletType2, 6, ccpSub(player->getPosition(), ccp(48, -5)), 2));
		}
		break;
	}
		break;
	}
}

//自动产生敌人
void PlayerScene::autoCreateEnemy(float f)
{
	allTimeCount++;
	int killCount = this->getPlayer()->killCount;
	Size size = Director::getInstance()->getVisibleSize();
	if (killCount<15 && passCreatEnemy == false)
	{
		enemyType = 1;
		this->schedule(schedule_selector(PlayerScene::setEnemy));
	}
	else
	{	
		if (killCount % 100 == 0){
			passCreatEnemy = true;
			enemyType = 7;
			this->schedule(schedule_selector(PlayerScene::setEnemy));
		}
		else if (allTimeCount>creatEnemyInterval&&passCreatEnemy==false)
		{
			if (killCount % 50 == 0)
			{
				creatEnemyInterval -= 10;
			}
			allTimeCount = 0;
			int randomType = CCRANDOM_0_1() * 500;
			if (randomType<100)
			{
				enemyType = 2;
			}
			else if (randomType >= 100 && randomType<200)
			{
				enemyType = 3;
			}
			else if (randomType >= 200 && randomType<300)
			{
				enemyType = 4;
			}
			else if (randomType >= 300 && randomType<400)
			{
				enemyType = 5;
			}
			else if (randomType >= 400 && randomType<500)
			{
				enemyType = 6;
			}
			this->schedule(schedule_selector(PlayerScene::setEnemy));
		}		
	}
}

void PlayerScene::setEnemy(float f)
{
	Size size = Director::getInstance()->getVisibleSize();
	switch (enemyType)
	{
	case 1:
	{
		enemyType1TimeCount++;
		if (enemyType1TimeCount>60)
		{
			enemyType1TimeCount = 0;
			NewEnemy* enemy = NULL;
			enemy = NewEnemy::createEnemy("enemy1.png", 0, 0);
			arrayEnemy->addObject(enemy);
			enemyBatchNode->addChild(enemy, 33);
		}
		break;
	}
	case 2:
	{
		enemyType2TimeCount++;
		if (enemyType2TimeCount<400)
		{
			enemyType2TimeCount++;
			if (enemyType2TimeCount % 120 == 0)
			{
				NewEnemy* enemy = NULL;
				enemy = NewEnemy::createEnemy("enemy2.png", 1, 0);
				enemy->setPosition(ccp(CCRANDOM_0_1()*size.width / 2 + size.width / 4, size.height + enemy->getContentSize().height));
				arrayEnemy->addObject(enemy);
				enemyBatchNode->addChild(enemy);

				NewEnemy* enemy1 = NULL;
				enemy1 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy1->setPosition(ccp(enemy->getPositionX()+enemy->getContentSize().width, size.height + enemy1->getContentSize().height));
				arrayEnemy->addObject(enemy1);
				enemyBatchNode->addChild(enemy1);
				NewEnemy* enemy2 = NULL;
				enemy2 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy2->setPosition(ccp(enemy->getPositionX()-enemy->getContentSize().width, size.height + enemy2->getContentSize().height));
				arrayEnemy->addObject(enemy2);
				enemyBatchNode->addChild(enemy2);

			}
		}
		else{
			enemyType2TimeCount = 0;
		}
		break;
	}
	case 3:
	{
		enemyType3TimeCount++;
		if (enemyType3TimeCount<120)
		{
			if (enemyType3TimeCount % 60 == 0)
			{
				NewEnemy* enemy = NULL;
				enemy = NewEnemy::createEnemy("enemy3.png", 2, 0);
				enemy->setPosition(ccp(size.width/2, size.height + enemy->getContentSize().height));
				arrayEnemy->addObject(enemy);
				enemyBatchNode->addChild(enemy);
			}
			if (enemyType3TimeCount % 80 == 0){
				NewEnemy* enemy1 = NULL;
				enemy1 = NewEnemy::createEnemy("enemy2.png", 1, 0);
				enemy1->setPosition(ccp(size.width / 2 + enemy1->getContentSize().width, size.height + enemy1->getContentSize().height));
				arrayEnemy->addObject(enemy1);
				enemyBatchNode->addChild(enemy1);
				NewEnemy* enemy2 = NULL;
				enemy2 = NewEnemy::createEnemy("enemy2.png", 1, 0);
				enemy2->setPosition(ccp(size.width / 2 - enemy2->getContentSize().width, size.height + enemy2->getContentSize().height));
				arrayEnemy->addObject(enemy2);
				enemyBatchNode->addChild(enemy2);
			}
			if (enemyType3TimeCount % 100 == 0){
				NewEnemy* enemy3 = NULL;
				enemy3 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy3->setPosition(ccp(size.width / 2 + enemy3->getContentSize().width*2, size.height + enemy3->getContentSize().height));
				arrayEnemy->addObject(enemy3);
				enemyBatchNode->addChild(enemy3);
				NewEnemy* enemy4 = NULL;
				enemy4 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy4->setPosition(ccp(size.width /2 -enemy4->getContentSize().width*2, size.height + enemy4->getContentSize().height));
				arrayEnemy->addObject(enemy4);
				enemyBatchNode->addChild(enemy4);
			}
		}
		else{
			enemyType3TimeCount = 0;
		}
		break;
	}
	case 4:
	{
		enemyType4TimeCount++;
		if (enemyType4TimeCount<120)
		{
			if (enemyType4TimeCount % 40 == 0)
			{
				NewEnemy* enemy = NULL;
				enemy = NewEnemy::createEnemy("enemy4.png", 3, 4);
				enemy->setPosition(ccp(size.width / 2, size.height + enemy->getContentSize().height));
				arrayEnemy->addObject(enemy);
				enemyBatchNode->addChild(enemy);

				NewEnemy* enemy1 = NULL;
				enemy1 = NewEnemy::createEnemy("enemy4.png", 3, 5);
				enemy1->setPosition(ccp(size.width / 2, size.height + enemy1->getContentSize().height));
				arrayEnemy->addObject(enemy1);
				enemyBatchNode->addChild(enemy1);
			}
		}
		else{
			enemyType4TimeCount = 0;
		}
		break;
	}
	case 5:
	{
		enemyType5TimeCount++;
		if (enemyType5TimeCount<120)
		{
			if (enemyType5TimeCount % 40 == 0)
			{
				NewEnemy* enemy = NULL;
				enemy = NewEnemy::createEnemy("enemy5.png", 2, 6);
				enemy->setPosition(ccp(0, size.height + enemy->getContentSize().height));
				arrayEnemy->addObject(enemy);
				enemyBatchNode->addChild(enemy);
			}
			if (enemyType5TimeCount %60==0){
				NewEnemy* enemy1 = NULL;
				enemy1 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy1->setPosition(ccp(size.width/4, size.height + enemy1->getContentSize().height));
				arrayEnemy->addObject(enemy1);
				enemyBatchNode->addChild(enemy1);
				NewEnemy* enemy2 = NULL;
				enemy2 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy2->setPosition(ccp(enemy1->getPositionX()+enemy2->getContentSize().width+10, size.height + enemy2->getContentSize().height));
				arrayEnemy->addObject(enemy2);
				enemyBatchNode->addChild(enemy2);
				NewEnemy* enemy3 = NULL;
				enemy3 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy3->setPosition(ccp(enemy2->getPositionX()+enemy3->getContentSize().width+10, size.height + enemy3->getContentSize().height));
				arrayEnemy->addObject(enemy3);
				enemyBatchNode->addChild(enemy3);
				NewEnemy* enemy4 = NULL;
				enemy4 = NewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy4->setPosition(ccp(enemy3->getPositionX()+enemy4->getContentSize().width+10, size.height + enemy4->getContentSize().height));
				arrayEnemy->addObject(enemy4);
				enemyBatchNode->addChild(enemy4);
			}
		}
		else{
			enemyType5TimeCount = 0;
		}
		break;
	}
	case 6:
	{
		enemyType6TimeCount++;
		if (enemyType6TimeCount<120)
		{
			if (enemyType6TimeCount % 40 == 0)
			{
				NewEnemy* enemy = NULL;
				enemy = NewEnemy::createEnemy("enemy4.png", 2, 7);
				enemy->setPosition(ccp(size.width + enemy->getContentSize().width, size.height + enemy->getContentSize().height));
				arrayEnemy->addObject(enemy);
				enemyBatchNode->addChild(enemy);
			}
		}
		else{
			enemyType6TimeCount = 0;
		}
		break;
	}
	case 7:
	{
		if (!enemyBatchNode->getChildByTag(88))
		{
			int i = 7 + CCRANDOM_0_1() * 7;
			const char* enemyName = "";
			enemyName = CCString::createWithFormat("enemy%d.png", i)->getCString();
			NewEnemy* enemy = NULL;
			enemy = NewEnemy::createEnemy(enemyName, 4, 2);
			arrayEnemy->addObject(enemy);
			enemyBatchNode->addChild(enemy, 10, 88);
		}
		break;
	}
	default:
		break;
	}
}
/*
void PlayerScene::autoCreateGems(float f)
{
	CallFunc *func1 = CallFunc::create(this, callfunc_selector(PlayerScene::putGems));
	CallFunc *func2 = CallFunc::create(this, callfunc_selector(PlayerScene::removeSupplyPlane));
	Size size = Director::getInstance()->getVisibleSize();
	Sprite *supplyPlane = Sprite::create("ui/plane5.png");
	supplyPlane->setPosition(ccp(0, -supplyPlane->getContentSize().height));
	this->addChild(supplyPlane, 10, 100);
	supplyPlane->runAction(Sequence::create(MoveTo::create(2, ccp(size.width / 2, size.height / 3)), DelayTime::create(1), func1, DelayTime::create(1), MoveTo::create(2, ccp(size.width + supplyPlane->getContentSize().width, -supplyPlane->getContentSize().width)), func2, NULL));
}
*/
void PlayerScene::putGems(CCPoint point)
{
	Size size = Director::getInstance()->getVisibleSize();
	int randomGemType = CCRANDOM_0_1() * 100;
	//	log("randomGemType:%d", randomGemType);
	//    CCLOG("randomGemType:%d",randomGemType);
	if (randomGemType<20)
	{
		Gems *gem = Gems::createGem("ui/hp.png", 1);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 20 && randomGemType<35)
	{
		Gems *gem = Gems::createGem("ui/upLevel.png", 0);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 35 && randomGemType<55)
	{
		Gems *gem = Gems::createGem("ui/skill1.png", 2);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 55 && randomGemType<75)
	{
		Gems *gem = Gems::createGem("ui/skill2.png", 3);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 75 && randomGemType<100)
	{
		Gems *gem = Gems::createGem("ui/skill3.png", 4);
		gem->setPosition(point);
		addChild(gem, 9);
	}
}

void PlayerScene::removeSupplyPlane()
{
	this->removeChildByTag(100, true);
}

void PlayerScene::resetPlayer(float f)
{
	switch (playerType)
	{
	case 1:
	{
		this->setPlayer(1);
		break;
	}
	case 2:
	{
		this->setPlayer(2);
		break;
	}
	case 3:
	{
		this->setPlayer(3);
		break;
	}
	case 4:
	{
		this->setPlayer(4);
		break;
	}
		break;
	}
}
void PlayerScene::setPlayer(int i)
{
	if (!isPlayerChange)
	{
		return;
	}
	isPlayerChange = false;
	Point currentPos = this->getPlayer()->getPosition();
	int hp = this->getPlayer()->hp;
	int score = this->getPlayer()->score;
	int killCount = this->getPlayer()->killCount;
	this->unschedule(schedule_selector(PlayerScene::autoCreateBullet));
	this->removeChildByTag(tag_player, true);

	const char* planeName = "";
	switch (chance)
	{
	case 1:planeName = CCString::createWithFormat("player1_%d.png", i)->getCString(); break;
	case 2:planeName = CCString::createWithFormat("player3_%d.png", i)->getCString(); break;
	case 3:planeName = CCString::createWithFormat("player2_%d.png", i)->getCString(); break;
	case 4:planeName = CCString::createWithFormat("player4_%d.png", i)->getCString(); break;
	default:
		planeName = CCString::createWithFormat("player1_%d.png", i)->getCString();break;
	}


	NewPlayer * player = NewPlayer::createPlayer(planeName);
	player->hp = hp;
	player->score = score;
	player->killCount = killCount;
	player->setPosition(currentPos);
	addChild(player, 1, tag_player);
	this->schedule(schedule_selector(PlayerScene::autoCreateBullet));
}

void PlayerScene::lostGame()
{
	//添加结束界面
	Size size = Director::getInstance()->getVisibleSize();
	//停止游戏
	Director::getInstance()->pause();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	this->unscheduleAllSelectors();
	GameOver* gameover = GameOver::createScene(M_Score);
	Director::getInstance()->replaceScene(gameover);
}

//获取主角
NewPlayer* PlayerScene::getPlayer()
{
	NewPlayer* player = (NewPlayer*)PlayerScene::sharedPlayerScene()->getChildByTag(tag_player);
	return player;
}

//获取敌人数组
Array* PlayerScene::getArrayForEnemy()
{
	return arrayEnemy;
}

PlayerScene::~PlayerScene()
{
	CC_SAFE_RELEASE(arrayEnemy);
}


