#include "SimpleAudioEngine.h"
#include "BulletEnemy.h"
#include "PlayerScene.h"
#include "NewEnemy.h"

using namespace CocosDenshion;

BulletEnemy* BulletEnemy::createBullet(const char* _fileName, float _speed, Point _position, Point _playerPosition, int _type){
	BulletEnemy* bullet = new BulletEnemy();
	if (bullet && bullet->initWithSpriteFrameName(_fileName)){
		bullet->autorelease();
		bullet->bulletInit(_speed, _position, _playerPosition, _type);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}
void BulletEnemy::bulletInit(float _speed, Point _position, Point _playerPosition, int _type){
	speed = _speed;
	bulletType = _type;
	goalPoint = _playerPosition;
	bulletShootDelay = 0;
	isAimAt = false;
	this->setPosition(_position);
	this->scheduleUpdate();
}

//�ӵ��߼�
void BulletEnemy::update(float time){
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
	//ɾ��
	if (this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height + this->getContentSize().height || this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width + this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
		return;
	}

	//�����ӵ�����
	NewPlayer *player = PlayerScene::sharedPlayerScene()->getPlayer();
	if (player->boundingBox().intersectsRect(this->boundingBox()))
	{
		this->removeFromParentAndCleanup(true);
		player->downHp();
	}
}

void BulletEnemy::aimAt()
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
void BulletEnemy::onExit(){
	//ȡ�����º���
	this->unscheduleUpdate();
	Sprite::onExit();
}