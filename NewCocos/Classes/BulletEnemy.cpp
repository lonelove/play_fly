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

//子弹逻辑
void BulletEnemy::update(float time){
	Size size = Director::getInstance()->getWinSize();
	switch (bulletType)
	{
	case 1:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(0, -speed)));//竖直向下
		break;
	}
	case 2:
	{
		this->aimAt();
		break;
	}
	case 3:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(-speed, -speed)));//左下
		break;
	}
	case 4:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(speed, -speed)));//右下
		break;
	}
	case 5:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(-speed / 3, -speed)));//左下下
		break;
	}
	case 6:
	{
		this->setPosition(ccpAdd(this->getPosition(), ccp(speed / 3, -speed)));//右下下
		break;
	}
	default:
		break;
	}
	//删除
	if (this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height + this->getContentSize().height || this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width + this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
		return;
	}

	//处理子弹击中
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

//生命周期-退出
void BulletEnemy::onExit(){
	//取消更新函数
	this->unscheduleUpdate();
	Sprite::onExit();
}
