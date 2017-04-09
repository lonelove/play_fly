#include "SimpleAudioEngine.h"
#include "LevelBulletEnemy.h"
#include "LevelScene.h"
#include "LevelNewEnemy.h"

using namespace CocosDenshion;

LevelBulletEnemy* LevelBulletEnemy::createBullet(const char* _fileName, float _speed, Point _position, Point _playerPosition, int _type){
	LevelBulletEnemy* bullet = new LevelBulletEnemy();
	if (bullet && bullet->initWithSpriteFrameName(_fileName)){
		bullet->autorelease();
		bullet->bulletInit(_speed, _position, _playerPosition, _type);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}
void LevelBulletEnemy::bulletInit(float _speed, Point _position, Point _playerPosition, int _type){
	speed = _speed;
	bulletType = _type;
	goalPoint = _playerPosition;
	bulletShootDelay = 0;
	isAimAt = false;
	this->setPosition(_position);
	this->scheduleUpdate();
}

//�ӵ��߼�
void LevelBulletEnemy::update(float time){
	Size size = Director::getInstance()->getWinSize();
	switch (bulletType)
	{
	case 1:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(0, -speed)));//��ֱ����
		break;
	}
	case 2:
	{
		this->aimAt();
		break;
	}
	case 3:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(-speed, -speed)));//����
		break;
	}
	case 4:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(speed, -speed)));//����
		break;
	}
	case 5:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(-speed / 3, -speed)));//������
		break;
	}
	case 6:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(speed / 3, -speed)));//������
		break;
	}
	default:
		break;
	}
	if (this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height + this->getContentSize().height || this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width + this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
		return;
	}

	//�����ӵ�����
	LevelNewPlayer *player = LevelScene::sharedLevelScene()->getPlayer();
	if (player->boundingBox().intersectsRect(this->boundingBox()))
	{
		this->removeFromParentAndCleanup(true);
		player->downHp();
	}
}

void LevelBulletEnemy::aimAt()
{
	if (!isAimAt)
	{
		startingPoint = this->getPosition();
		slope = (goalPoint.y - startingPoint.y) / (goalPoint.x - startingPoint.x);
	}
	isAimAt = true;

	Point v = ccpSub(goalPoint, startingPoint);
	velocity = ccpMult(ccpNormalize(v), 2.5);
	this->setPosition(ccpAdd(this->getPosition(), velocity));
}

//��������-�˳�
void LevelBulletEnemy::onExit(){
	//ȡ�����º���
	this->unscheduleUpdate();
	Sprite::onExit();
}
