#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "LevelScene.h"
#include "HPauseLayer.h"
#include "HMap.h"
#include "LevelNewBullet.h"
#include "LevelNewEnemy.h"
#include "LevelGems.h"
#include "LevelUniqueSkill.h"
#include "GameOver.h"
#include "LostGame.h"
#include "LevelSelect.h"


using namespace CocosDenshion;
using namespace cocos2d;

static LevelScene* sh;
extern int playType;
extern int playlevel2;
extern int playlevel3;
extern int skillCount1;
extern int skillCount2;
extern int skillCount3;
int playlevel = 1;

LevelScene* LevelScene::sharedLevelScene(){
	if (sh){
		return sh;
	}
	return NULL;
}

Scene* LevelScene::scene()
{
	auto scene = Scene::create();
	auto layer = LevelScene::create();
	scene->addChild(layer);
	return scene;
}

bool LevelScene::init(){
	if (!Layer::init()){ return false; }
	sh = this;
	playType = 1;
	allTimeCount = 0;
	BulletDelayCount = 0;

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading/player.plist");
	playersBatchNode = SpriteBatchNode::create("loading/player.png");
	this->addChild(playersBatchNode, 100);

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading/enemy.plist");
	enemyBatchNode = SpriteBatchNode::create("loading/enemy.png",50);
	this->addChild(enemyBatchNode, 100);

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading/bullet.plist");
	bulletBatchNode = SpriteBatchNode::create("loading/bullet.png", 50);
	this->addChild(bulletBatchNode, 100);
	m_music = UserDefault::getInstance()->getBoolForKey("musickey_1");
	switch (playlevel)
	{
	case 1:{
		//播放游戏中的音乐
		if (m_music){
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_zhandou1.mp3", true);
		}
		//添加地图
		HMap * map = HMap::createMap("back1.jpg");
		addChild(map);
		break; 
	}
	case 2:{
		//播放游戏中的音乐
		if (m_music){
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_zhandou2.mp3", true);
		}
		//添加地图
		HMap * map = HMap::createMap("back2.jpg");
		addChild(map);
		break;
	}
	case 3:{
		//播放游戏中的音乐
		if (m_music){
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_zhandou3.mp3", true);
		}
		//添加地图
		HMap * map = HMap::createMap("back3.jpg");
		addChild(map);
		break;
	}
	default:
		break;
	}
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
	LevelNewPlayer * player = LevelNewPlayer::createPlayer(playerName);
	player->setPosition(ccp(size.width*0.5, player->getContentSize().height*0.5));
	addChild(player, 1, tag_player);
	//添加主角属性
	this->addPlaneProperty();

	//创建子弹逻辑
	this->schedule(schedule_selector(LevelScene::autoCreateBullet));
	
	//初始化敌人数组
	arrayEnemy = CCArray::create();
	CC_SAFE_RETAIN(arrayEnemy);
	//添加敌人
	this->schedule(schedule_selector(LevelScene::autoCreateEnemy));
	//添加宝石
//	this->schedule(schedule_selector(LevelScene::autoCreateGems), 15);
	this->setTouchEnabled(true);
	// 我机触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(LevelScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LevelScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//暂停按钮
	MenuItemImage *pause = MenuItemImage::create("ui/pause.png", "ui/pause.png", this, menu_selector(LevelScene::doPause));
	pause->setAnchorPoint(ccp(1, 1));
	pause->setPosition(ccp(Director::getInstance()->getVisibleSize().width - 10, Director::getInstance()->getVisibleSize().height - 10));
	Menu *menu = Menu::create(pause, NULL);
	menu->setAnchorPoint(ccp(0, 0));
	addChild(menu, 1, 10);
	menu->setPosition(Point::ZERO);

	this->schedule(schedule_selector(LevelScene::resetPlayer));
	return true;
}

//暂停游戏
void LevelScene::doPause(Object* psend)
{
	Director::getInstance()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	HPauseLayer *pauseLayer = HPauseLayer::create();
	addChild(pauseLayer, 9999, 9999);
}

bool LevelScene::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void LevelScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
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
void LevelScene::addPlaneProperty()
{

	LevelNewPlayer *player = this->getPlayer();
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
void LevelScene::autoCreateBullet(float f)
{
	BulletDelayCount++;//子弹延迟时间计数
	switch (playType)
	{
	case 1://飞机1子弹
	{

		if (BulletDelayCount % 20 == 0)
		{
			LevelNewPlayer * player = (LevelNewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(36, 15)), 1));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(36, -15)), 1));
			//子弹音效
			SimpleAudioEngine::sharedEngine()->playEffect("sound/effect_bullet.mp3");
		}
		break;
	}
	case 2://飞机2子弹
	{
		if (BulletDelayCount % 25 == 0)
		{
			LevelNewPlayer * player = (LevelNewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(20, 25)), 1));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(20, -25)), 1));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(48, 5)), 1));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(48, -5)), 1));
			SimpleAudioEngine::sharedEngine()->playEffect("sound/effect_bullet.mp3");
		}
		break;
	}
	case 3://飞机3子弹
	{
		if (BulletDelayCount % 20 == 0)
		{
			LevelNewPlayer * player = (LevelNewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(20, 25)), 1));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(20, -25)), 1));
			SimpleAudioEngine::sharedEngine()->playEffect("sound/effect_bullet.mp3");
		}
		if (BulletDelayCount % 90 == 0 && this->getArrayForEnemy()->count() != 0)
		{
			LevelNewPlayer * player = (LevelNewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType2, 6, ccpAdd(player->getPosition(), ccp(48, 5)), 2));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType2, 6, ccpSub(player->getPosition(), ccp(48, -5)), 2));
		}
		break;
	}
	case 4://飞机4子弹
	{
		if (BulletDelayCount % 15 == 0)
		{
			LevelNewPlayer * player = (LevelNewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(20, 25)), 1));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(20, -25)), 1));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpAdd(player->getPosition(), ccp(45, 5)), 4));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType1, 10, ccpSub(player->getPosition(), ccp(45, -5)), 3));
			SimpleAudioEngine::sharedEngine()->playEffect("sound/effect_bullet.mp3");
		}
		if (BulletDelayCount % 60 == 0 && this->getArrayForEnemy()->count() != 0)
		{
			LevelNewPlayer * player = (LevelNewPlayer*)this->getChildByTag(tag_player);
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType2, 6, ccpAdd(player->getPosition(), ccp(48, 5)), 2));
			bulletBatchNode->addChild(LevelNewBullet::createBullet(bulletType2, 6, ccpSub(player->getPosition(), ccp(48, -5)), 2));
		}
		break;
	}
		break;
	}
}

//自动产生敌人
void LevelScene::autoCreateEnemy(float f)
{
	allTimeCount++;
	int killCount = this->getPlayer()->killCount;
	Size size = Director::getInstance()->getVisibleSize();
	int enemyType = CCRANDOM_0_1() * 200;
	if (allTimeCount>120){
		allTimeCount = 0;
		if (killCount>200){
			int i = 6+playlevel;
			const char* enemyName = "";
			enemyName = CCString::createWithFormat("enemy%d.png", i)->getCString();
			LevelNewEnemy* enemy = NULL;
			enemy = LevelNewEnemy::createEnemy(enemyName, 4, 2);
			arrayEnemy->addObject(enemy);
			enemyBatchNode->addChild(enemy, 10, 88);
			if (playlevel==1)
				SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_jizhanboss1.mp3", true);
			if (playlevel==2)
				SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_jizhanboss2.mp3", true);
			if (playlevel==3)
				SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm_jizhanboss3.mp3", true);
			this->unschedule(schedule_selector(LevelScene::autoCreateEnemy));
		}
		else{
			if (enemyType<50){
				LevelNewEnemy* enemy = NULL;
				enemy = LevelNewEnemy::createEnemy("enemy1.png", 0, 0);
				arrayEnemy->addObject(enemy);
				enemyBatchNode->addChild(enemy, 33);
			}
			if (enemyType >=50&&enemyType<100){
				LevelNewEnemy* enemy = NULL;
				enemy = LevelNewEnemy::createEnemy("enemy2.png", 1, 0);
				enemy->setPosition(ccp(CCRANDOM_0_1()*size.width / 2 + size.width / 4, size.height + enemy->getContentSize().height));
				arrayEnemy->addObject(enemy);
				enemyBatchNode->addChild(enemy);

				LevelNewEnemy* enemy1 = NULL;
				enemy1 = LevelNewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy1->setPosition(ccp(enemy->getPositionX() + enemy->getContentSize().width, size.height + enemy1->getContentSize().height));
				arrayEnemy->addObject(enemy1);
				enemyBatchNode->addChild(enemy1);

				LevelNewEnemy* enemy2 = NULL;
				enemy2 = LevelNewEnemy::createEnemy("enemy1.png", 0, 0);
				enemy2->setPosition(ccp(enemy->getPositionX() - enemy->getContentSize().width, size.height + enemy2->getContentSize().height));
				arrayEnemy->addObject(enemy2);
				enemyBatchNode->addChild(enemy2);
			}
		}
	}
	else{
		if (killCount <= 200){
			if (enemyType >=100&&enemyType<150){
				if (allTimeCount % 60 == 0)
				{
					LevelNewEnemy* enemy = NULL;
					enemy = LevelNewEnemy::createEnemy("enemy3.png", 2, 0);
					enemy->setPosition(ccp(size.width / 2, size.height + enemy->getContentSize().height));
					arrayEnemy->addObject(enemy);
					enemyBatchNode->addChild(enemy);
				}
				if (allTimeCount % 80 == 0){
					LevelNewEnemy* enemy1 = NULL;
					enemy1 = LevelNewEnemy::createEnemy("enemy2.png", 1, 0);
					enemy1->setPosition(ccp(size.width / 2 + enemy1->getContentSize().width, size.height + enemy1->getContentSize().height));
					arrayEnemy->addObject(enemy1);
					enemyBatchNode->addChild(enemy1);
					LevelNewEnemy* enemy2 = NULL;
					enemy2 = LevelNewEnemy::createEnemy("enemy2.png", 1, 0);
					enemy2->setPosition(ccp(size.width / 2 - enemy2->getContentSize().width, size.height + enemy2->getContentSize().height));
					arrayEnemy->addObject(enemy2);
					enemyBatchNode->addChild(enemy2);
				}
				if (allTimeCount % 100 == 0){
					LevelNewEnemy* enemy3 = NULL;
					enemy3 = LevelNewEnemy::createEnemy("enemy1.png", 0, 0);
					enemy3->setPosition(ccp(size.width / 2 + enemy3->getContentSize().width * 2, size.height + enemy3->getContentSize().height));
					arrayEnemy->addObject(enemy3);
					enemyBatchNode->addChild(enemy3);
					LevelNewEnemy* enemy4 = NULL;
					enemy4 = LevelNewEnemy::createEnemy("enemy1.png", 0, 0);
					enemy4->setPosition(ccp(size.width / 2 - enemy4->getContentSize().width * 2, size.height + enemy4->getContentSize().height));
					arrayEnemy->addObject(enemy4);
					enemyBatchNode->addChild(enemy4);
				}
			}
			if (enemyType>=150&&enemyType<200){
				if (allTimeCount % 60 == 0){
					LevelNewEnemy* enemy = NULL;
					enemy = LevelNewEnemy::createEnemy("enemy4.png", 2, 7);
					enemy->setPosition(ccp(size.width + enemy->getContentSize().width, size.height + enemy->getContentSize().height));
					arrayEnemy->addObject(enemy);
					enemyBatchNode->addChild(enemy);

					LevelNewEnemy* enemy2 = NULL;
					enemy2 = LevelNewEnemy::createEnemy("enemy5.png", 2, 6);
					enemy2->setPosition(ccp(0, size.height + enemy->getContentSize().height));
					arrayEnemy->addObject(enemy2);
					enemyBatchNode->addChild(enemy2);
				}
			}
		}
	}
}
/*
void LevelScene::autoCreateGems(float f)
{
	CallFunc *func1 = CallFunc::create(this, callfunc_selector(LevelScene::putGems));
	CallFunc *func2 = CallFunc::create(this, callfunc_selector(LevelScene::removeSupplyPlane));
	Size size = Director::getInstance()->getVisibleSize();
	Sprite *supplyPlane = Sprite::create("ui/plane5.png");
	supplyPlane->setPosition(ccp(0, -supplyPlane->getContentSize().height));
	this->addChild(supplyPlane, 10, 100);
	supplyPlane->runAction(Sequence::create(MoveTo::create(2, ccp(size.width / 2, size.height / 3)), DelayTime::create(1), func1, DelayTime::create(1), MoveTo::create(2, ccp(size.width + supplyPlane->getContentSize().width, -supplyPlane->getContentSize().width)), func2, NULL));
}
*/
void LevelScene::putGems(CCPoint point)
{
	Size size = Director::getInstance()->getVisibleSize();
	int randomGemType = CCRANDOM_0_1() * 100;
	if (randomGemType<20)
	{
		LevelGems *gem = LevelGems::createGem("ui/hp.png", 1);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 20 && randomGemType<35)
	{
		LevelGems *gem = LevelGems::createGem("ui/upLevel.png", 0);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 35 && randomGemType<55)
	{
		LevelGems *gem = LevelGems::createGem("ui/skill1.png", 2);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 55 && randomGemType<75)
	{
		LevelGems *gem = LevelGems::createGem("ui/skill2.png", 3);
		gem->setPosition(point);
		addChild(gem, 9);
	}
	else if (randomGemType >= 75 && randomGemType<100)
	{
		LevelGems *gem = LevelGems::createGem("ui/skill3.png", 4);
		gem->setPosition(point);
		addChild(gem, 9);
	}
}

void LevelScene::removeSupplyPlane()
{
	this->removeChildByTag(100, true);
}

void LevelScene::resetPlayer(float f)
{
	switch (playType)
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
void LevelScene::setPlayer(int i)
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
	this->unschedule(schedule_selector(LevelScene::autoCreateBullet));
	this->removeChildByTag(tag_player, true);

	const char* planeName = "";
	switch (chance)
	{
	case 1:planeName = CCString::createWithFormat("player1_%d.png", i)->getCString(); break;
	case 2:planeName = CCString::createWithFormat("player3_%d.png", i)->getCString(); break;
	case 3:planeName = CCString::createWithFormat("player2_%d.png", i)->getCString(); break;
	case 4:planeName = CCString::createWithFormat("player4_%d.png", i)->getCString(); break;
	default:
		planeName = CCString::createWithFormat("player1_%d.png", i)->getCString(); break;
	}

	LevelNewPlayer * player = LevelNewPlayer::createPlayer(planeName);
	player->hp = hp;
	player->score = score;
	player->killCount = killCount;
	player->setPosition(currentPos);
	addChild(player, 1, tag_player);
	this->schedule(schedule_selector(LevelScene::autoCreateBullet));
}

void LevelScene::winGame()
{
	//添加结束界面
	Size size = Director::getInstance()->getVisibleSize();
	LevelNewPlayer* player = LevelScene::sharedLevelScene()->getPlayer();
	player->runAction(Sequence::create(MoveTo::create(3.0f, ccp(player->getPositionX(), size.height + player->getContentSize().height * 2)), DelayTime::create(2), NULL));
	//停止游戏
	Director::getInstance()->pause();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	this->unscheduleAllSelectors();
	if (playlevel==1){
		playlevel2 = 1;
	}
	if (playlevel == 2){
		playlevel3 = 1;
	}
	GameOver* gameover = GameOver::createScene(M_Score);
	Director::getInstance()->replaceScene(gameover);
}

void LevelScene::lostGame()
{
	//添加失败界面
	Size size = Director::getInstance()->getVisibleSize();
	//停止游戏
	Director::getInstance()->pause();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	this->unscheduleAllSelectors();
	Director::getInstance()->replaceScene(LostGame::scene());
}

//获取主角
LevelNewPlayer* LevelScene::getPlayer()
{
	LevelNewPlayer* player = (LevelNewPlayer*)LevelScene::sharedLevelScene()->getChildByTag(tag_player);
	return player;
}

//获取敌人数组
Array* LevelScene::getArrayForEnemy()
{
	return arrayEnemy;
}


LevelScene::~LevelScene()
{
	CC_SAFE_RELEASE(arrayEnemy);
}
