#include"SimpleAudioEngine.h"
#include"LevelNewEnemy.h"
#include"LevelScene.h"
#include"LevelBulletEnemy.h"
#include "LevelGems.h"

LevelNewEnemy* LevelNewEnemy::createEnemy(const char* fileName, int _type, int _way){
	LevelNewEnemy* enemy = new LevelNewEnemy();
	if (enemy && enemy->initWithSpriteFrameName(fileName)){
		enemy->autorelease();
		enemy->enemyInit(fileName, _type, _way);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

//��ʼ��
void LevelNewEnemy::enemyInit(const char* fileName, int _type, int _way){
	way = _way;
	enemyType = _type;
	shootManyCount = 0;
	shootFourCount = 0;
	Size size = Director::getInstance()->getWinSize();
	int killCout = LevelScene::sharedLevelScene()->getPlayer()->killCount;
	isActed = false;
	switch (_type)
	{
	case 0:scoreValue = 2 + 2 * killCout / 100; hp = 4 + killCout / 50; break;
	case 1:scoreValue = 5 + 5 * killCout / 100; hp = 6 + killCout / 50; break;
	case 2:scoreValue = 10 + 10 * killCout / 100; hp = 10 + killCout / 50; break;
	case 3:scoreValue = 15 + 15 * killCout / 100; hp = 13 + killCout / 50; break;
	case 4:scoreValue = 100 + 100 * killCout / 100; hp = 200 + killCout / 10; break;
	default:
		break;
	}
	this->setPosition(ccp(CCRANDOM_0_1()*(size.width - 2 * this->getContentSize().width) + this->getContentSize().width, size.height + this->getContentSize().height));

	//�����߼�
	this->scheduleUpdate();
}

//���ֲ�ͬ���ƶ��߼�
void LevelNewEnemy::update(float time){

	timeCount1++;
	CallFunc *func = CallFunc::create(this, callfunc_selector(LevelNewEnemy::enemyShoot));
	Size size = Director::getInstance()->getVisibleSize();
	switch (way) {
	case 0://����
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(0, -3)));
		if (isActed)
		{
			break;
		}
		isActed = true;
		this->runAction(Sequence::create(DelayTime::create(4), func, DelayTime::create(4), func, NULL));
		break;
	}
	case 1://���������ƶ�
	{
		//�жϷ�ֹ�ظ����ô˶�������֤���߼�ֻ��ִ��һ��
		if (isActed)
		{
			break;
		}
		isActed = true;
		this->runAction(Sequence::create(MoveTo::create(1, CCPointMake(this->getPositionX(), CCRANDOM_0_1() * 200 + size.height / 2)), func, MoveBy::create(2, CCPointMake(CCRANDOM_0_1() * 300 - 150, 0)), func, MoveBy::create(2, CCPointMake(CCRANDOM_0_1() * 300 - 150, 0)), func, MoveBy::create(2, CCPointMake(CCRANDOM_0_1() * 300 - 150, 0)), func, MoveTo::create(1, CCPointMake(this->getPositionX(), size.height + 2 * this->getContentSize().height)), NULL));
		break;
	}
	case 2://��������
	{
		if (isActed)
		{
			break;
		}
		isActed = true;
		this->runAction(Sequence::create(MoveTo::create(2, CCPointMake(size.width / 2, size.height * 5 / 7)), func, DelayTime::create(4), func, DelayTime::create(4), func, DelayTime::create(4), func, DelayTime::create(4), func, DelayTime::create(4), func, DelayTime::create(3), func, DelayTime::create(3), func, DelayTime::create(3), func, DelayTime::create(2), func, DelayTime::create(4), MoveTo::create(2, CCPointMake(this->getPositionX(), size.height + 2 * this->getContentSize().height)), NULL));
		break;
	}
	case 3://�ϻ�
	{
		if (isActed)
		{
			break;
		}
		isActed = true;

		ccBezierConfig bezier; // ��������������
		bezier.controlPoint_1 = ccp(0, size.height + this->getContentSize().height); // ��ʼ��
		bezier.controlPoint_2 = ccp(size.width / 2, size.height / 5); //���Ƶ�
		bezier.endPosition = ccp(size.width + 2 * this->getContentSize().width, size.height + 2 * this->getContentSize().height); // ����λ��
		BezierTo *actionMove = BezierTo::create(4, bezier);
		FiniteTimeAction *sequence = Sequence::create(DelayTime::create(1), func, DelayTime::create(2), func, NULL);
		this->runAction(Spawn::create(actionMove, sequence, NULL));

		break;
	}
	case 4://��
	{
		if (isActed)
		{
			break;
		}
		isActed = true;
		ccBezierConfig bezier; // ��������������
		bezier.controlPoint_1 = ccp(size.width / 2, size.height + this->getContentSize().height); // ��ʼ��
		bezier.controlPoint_2 = ccp(size.width / 2, size.height / 2); //���Ƶ�
		bezier.endPosition = ccp(-2 * this->getContentSize().width, size.height / 2); // ����λ��
		BezierTo *actionMove = BezierTo::create(4, bezier);
		FiniteTimeAction *sequence = Sequence::create(DelayTime::create(0.5), func, DelayTime::create(0.5), func, DelayTime::create(0.5), func, NULL);
		this->runAction(Spawn::create(actionMove, sequence, NULL));

		break;
	}
	case 5://�һ�
	{
		if (isActed)
		{
			break;
		}
		isActed = true;
		ccBezierConfig bezier; // ��������������
		bezier.controlPoint_1 = ccp(size.width / 2, size.height + this->getContentSize().height); // ��ʼ��
		bezier.controlPoint_2 = ccp(size.width / 2, size.height / 2); //���Ƶ�
		bezier.endPosition = ccp(size.width + 2 * this->getContentSize().width, size.height / 2); // ����λ��
		BezierTo *actionMove = BezierTo::create(4, bezier);
		FiniteTimeAction *sequence = Sequence::create(DelayTime::create(0.5), func, DelayTime::create(0.5), func, DelayTime::create(0.5), func, NULL);
		this->runAction(Spawn::create(actionMove, sequence, NULL));

		break;
	}
	case 6://����
	{
		if (isActed)
		{
			break;
		}
		isActed = true;
		FiniteTimeAction *sequence = Sequence::create(DelayTime::create(2), func, DelayTime::create(1), func, NULL);
		this->runAction(Spawn::create(MoveTo::create(5, ccp(size.width + 2 * this->getContentSize().width, size.height / 2)), sequence, NULL));
		break;
	}
	case 7://����
	{
		if (isActed)
		{
			break;
		}
		isActed = true;
		FiniteTimeAction *sequence = Sequence::create(DelayTime::create(2), func, DelayTime::create(1), func, NULL);
		this->runAction(Spawn::create(MoveTo::create(5, ccp(-2 * this->getContentSize().width, size.height / 2)), sequence, NULL));
		break;
	}
		break;
	}
	//ɾ��
	if (this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height + this->getContentSize().height || this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width + this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
		LevelScene::sharedLevelScene()->getArrayForEnemy()->removeObject(this);
	}

	if (hp <= 0)
	{
		this->enemyDead();
	}

	//��ײ���
	LevelNewPlayer * player = LevelScene::sharedLevelScene()->getPlayer();
	if (!player->isDead)
	{
		if (player->boundingBox().intersectsRect(this->boundingBox()))
		{
			this->removeFromParentAndCleanup(true);
			player->downHp();
		}
	}
}

void LevelNewEnemy::enemyShoot()
{
	Point playerPoint = LevelScene::sharedLevelScene()->getPlayer()->getPosition();
	if (way == 0 || way == 3 || way == 6 || way == 7)
	{
		way = 0;
	}
	switch (way)
	{
	case 0:
	{
		this->shootOne(playerPoint);
		break;
	}
	case 1:
	{
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("6.png", 2, ccpAdd(this->getPosition(), ccp(this->getContentSize().width / 2, 0)), playerPoint, 1));
		break;
	}
	case 2:
	{
		int randomType = CCRANDOM_0_1() * 30;
		if (randomType >= 0 && randomType<10)
		{
			randomType = 1;
		}
		else if (randomType >= 10 && randomType<20)
		{
			randomType = 2;
		}
		else{
			randomType = 3;
		}
		switch (randomType)
		{
		case 1:
		{
			this->schedule(schedule_selector(LevelNewEnemy::shootMany));
			break;
		}
		case 2:
		{
			this->shootFive(playerPoint);
			break;
		}
		case 3:{
			this->schedule(schedule_selector(LevelNewEnemy::shootFour));
			break;
		}
		default:
			break;
		}
		break;
	}
	case 4:
	{
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("6.png", 2, this->getPosition(), playerPoint, 6));
		break;
	}
	case 5:
	{
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("6.png", 2, this->getPosition(), playerPoint, 5));
		break;
	}
	}
}

void LevelNewEnemy::shootMany(float f)
{
	Point playerPoint = LevelScene::sharedLevelScene()->getPlayer()->getPosition();
	shootManyCount++;
	if (shootManyCount % 12 == 0)
	{
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("3.png", 2.5, this->getPosition(), playerPoint, 1));
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("3.png", 2.5, this->getPosition(), playerPoint, 3));
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("3.png", 2.5, this->getPosition(), playerPoint, 4));
	}
	if (shootManyCount>90)
	{
		shootManyCount = 0;
		this->unschedule(schedule_selector(LevelNewEnemy::shootMany));
	}
}

void LevelNewEnemy::shootFour(float f){
	Point playerPoint = LevelScene::sharedLevelScene()->getPlayer()->getPosition();
	shootFourCount++;
	if (shootFourCount % 40 == 0){
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, this->getPosition(), playerPoint, 3));
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, this->getPosition(), playerPoint, 4));
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, this->getPosition(), playerPoint, 5));
		LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, this->getPosition(), playerPoint, 6));
	}
	if (shootFourCount > 120){
		shootFourCount = 0;
		this->unschedule(schedule_selector(LevelNewEnemy::shootFour));
	}
}

void LevelNewEnemy::shootFive(CCPoint playerPoint)
{
	LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, ccp(this->getPositionX(), this->getPositionY() + 10), playerPoint, 2));
	LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, ccp(this->getPositionX() + 30, this->getPositionY() + 9), playerPoint, 2));
	LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("2.png", 2.5, ccp(this->getPositionX() - 30, this->getPositionY() + 9), playerPoint, 2));
	LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, ccp(this->getPositionX() - 18, this->getPositionY() - 18), playerPoint, 2));
	LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("1.png", 2.5, ccp(this->getPositionX() + 18, this->getPositionY() - 18), playerPoint, 2));
}

void LevelNewEnemy::shootOne(CCPoint playerPoint)
{
	LevelScene::sharedLevelScene()->bulletBatchNode->addChild(LevelBulletEnemy::createBullet("5.png", 3.5, ccpAdd(this->getPosition(), ccp(this->getContentSize().width / 2, 0)), playerPoint, 2));
}

void LevelNewEnemy::enemyDead()
{
	//��ը��Ч
	if (enemyType == 4)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bigBoom.wav");
		//��ը����Ч��
		ParticleSystemQuad * particle = ParticleSystemQuad::create("ui/particle_boom.plist");
		particle->setPosition(this->getPosition());//�ֵ�λ��
		particle->setAutoRemoveOnFinish(true);//�Զ��ͷ�
		LevelScene::sharedLevelScene()->addChild(particle);//���ӵ���layer

		ParticleSystemQuad * particle1 = ParticleSystemQuad::create("ui/particle_boom.plist");
		particle1->setPosition(this->getPositionX()+100, this->getPositionY()+10);//�ֵ�λ��
		particle1->setAutoRemoveOnFinish(true);//�Զ��ͷ�
		LevelScene::sharedLevelScene()->addChild(particle1);//���ӵ���layer

		ParticleSystemQuad * particle2 = ParticleSystemQuad::create("ui/particle_boom.plist");
		particle2->setPosition(this->getPositionX() - 100, this->getPositionY() + 10);//�ֵ�λ��
		particle2->setAutoRemoveOnFinish(true);//�Զ��ͷ�
		LevelScene::sharedLevelScene()->addChild(particle2);//���ӵ���layer
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_boom.mp3");
		//��ը����Ч��
		ParticleSystemQuad * particle = ParticleSystemQuad::create("ui/particle_boom.plist");
		particle->setPosition(this->getPosition());//�ֵ�λ��
		particle->setAutoRemoveOnFinish(true);//�Զ��ͷ�
		LevelScene::sharedLevelScene()->addChild(particle);//���ӵ���layer
	}
	//���ӷ���
	LevelScene::sharedLevelScene()->getPlayer()->addScore(scoreValue);
	//����ɱ����
	LevelScene::sharedLevelScene()->getPlayer()->addKillCount(1);

	if (enemyType == 4)
	{
		LevelScene::sharedLevelScene()->M_Score = LevelScene::sharedLevelScene()->getPlayer()->score;
		LevelScene::sharedLevelScene()->winGame();
	}
	else{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCPoint point = this->getPosition();
		//���ӵ���
		int randomGemType = CCRANDOM_0_1() * 10;
		if (randomGemType>8)
			LevelScene::sharedLevelScene()->putGems(point);
	}

	//�ӵ������齫�������ĵй�ɾ��
	Array * array = LevelScene::sharedLevelScene()->getArrayForEnemy();
	array->removeObject(this);
	//ɾ���й�
	this->removeFromParentAndCleanup(true);
}
//��������-�˳�
void LevelNewEnemy::onExit(){
	//ȡ�����º���
	this->unscheduleUpdate();
	Sprite::onExit();
}