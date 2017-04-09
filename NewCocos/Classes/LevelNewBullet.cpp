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

//�ӵ��߼�
void LevelNewBullet::update(float time){

	Size size = Director::getInstance()->getWinSize();
	switch (bulletType)
	{
	case 1:
		//�ӵ������˶�
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

	//�����ӵ�����
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
				//��ը��Ч
				/*if (enemy->enemyType == 4)
				{
				SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bigBoom.wav");
				}
				else
				{
				SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_boom.mp3");
				}
				//��ը����Ч��
				ParticleSystemQuad * particle = ParticleSystemQuad::create("ui/particle_boom.plist");
				particle->setPosition(enemy->getPosition());//�ֵ�λ��
				particle->setAutoRemoveOnFinish(true);//�Զ��ͷ�
				PlayerScene::sharedPlayerScene()->addChild(particle);//��ӵ���layer
				//���ӷ���
				PlayerScene::sharedPlayerScene()->getPlayer()->addScore(enemy->scoreValue);
				//���ɱ����
				PlayerScene::sharedPlayerScene()->getPlayer()->addKillCount(1);
				*/
				//�ӵ������齫�������ĵй�ɾ��
				array->removeObject(enemy);
				//ɾ���ӵ���й�
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
//��������-�˳�
void LevelNewBullet::onExit(){
	//ȡ�����º���
	this->unscheduleUpdate();
	Sprite::onExit();
}
