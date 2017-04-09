#include "SimpleAudioEngine.h"
#include "LevelNewBullet.h"
#include "LevelScene.h"
#include "LevelNewEnemy.h"

using namespace CocosDenshion;

LevelNewBullet* LevelNewBullet::createBullet(const char* _fileName, float _speed, Point _position, int _type){
	LevelNewBullet* bullet = new LevelNewBullet();
	if (bullet && bullet->initWithSpriteFrameName(_fileName)){
		bullet->autorelease();
		bullet->bulletInit(_speed, _position, _type);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}

void LevelNewBullet::bulletInit(float _speed, Point _position, int _type){
	speed = _speed;
	bulletType = _type;
	this->setPosition(_position);

	rotation += 180;
	rotation *= -1;

	this->scheduleUpdate();
}

//子弹逻辑
void LevelNewBullet::update(float time){

	Size size = Director::getInstance()->getWinSize();
	switch (bulletType)
	{
	case 1:
		//子弹向上运动
		this->setPosition(ccpAdd(this->getPosition(), ccp(0, speed)));
		break;
	case 2:
	{
		Array *enemyArray = LevelScene::sharedLevelScene()->getArrayForEnemy();
		for (int i = 0; i <enemyArray->count(); i++)
		{
			LevelNewEnemy *enemy = (LevelNewEnemy*)enemyArray->objectAtIndex(i);

			bulletPoint = this->getPosition();
			enemyPoint = enemy->getPosition();

			Point v = ccpSub(enemyPoint, bulletPoint);
			float angel = 3.14 / 2 - ccpToAngle(v);
			this->setRotation(CC_RADIANS_TO_DEGREES(angel));
			velocity = ccpMult(ccpNormalize(v), 4.0);
		}

		this->setPosition(ccpAdd(this->getPosition(), velocity));

		break;
	}
	case 3:this->setPosition(ccpAdd(this->getPosition(), ccp(-1, speed))); break;
	case 4:this->setPosition(ccpAdd(this->getPosition(), ccp(1, speed))); break;
	default:
		break;

	}
	if (this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height + this->getContentSize().height || this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width + this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
		return;
	}

	//处理子弹击中
	Array * array = LevelScene::sharedLevelScene()->getArrayForEnemy();
	for (int i = 0; i<array->count(); i++) {
		LevelNewEnemy* enemy = (LevelNewEnemy*)array->objectAtIndex(i);
		if (enemy->boundingBox().intersectsRect(this->boundingBox()))
		{
			switch (bulletType)
			{
			case 1:
				(enemy->hp) -= 2;
				break;
			case 2:
				(enemy->hp) -= 4;
			default:
				break;
			}

			if (enemy->hp <= 0)
			{
				//爆炸音效
				/*if (enemy->enemyType == 4)
				{
				SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bigBoom.wav");
				}
				else
				{
				SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_boom.mp3");
				}
				//爆炸粒子效果
				ParticleSystemQuad * particle = ParticleSystemQuad::create("ui/particle_boom.plist");
				particle->setPosition(enemy->getPosition());//怪的位置
				particle->setAutoRemoveOnFinish(true);//自动释放
				PlayerScene::sharedPlayerScene()->addChild(particle);//添加到主layer
				//增加分数
				PlayerScene::sharedPlayerScene()->getPlayer()->addScore(enemy->scoreValue);
				//添加杀人数
				PlayerScene::sharedPlayerScene()->getPlayer()->addKillCount(1);
				*/
				//从敌人数组将被攻击的敌怪删除
				array->removeObject(enemy);
				//删除子弹与敌怪
				LevelScene::sharedLevelScene()->removeChild(enemy, true);
				this->removeFromParentAndCleanup(true);
				break;
			}
			else
			{
				this->removeFromParentAndCleanup(true);
				break;
			}

		}
	}
}
//生命周期-退出
void LevelNewBullet::onExit(){
	//取消更新函数
	this->unscheduleUpdate();
	Sprite::onExit();
}
