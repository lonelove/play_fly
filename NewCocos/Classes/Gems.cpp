#include "Gems.h"
#include "PlayerScene.h"
#include "NewPlayer.h"
#include "UniqueSkill.h"
using namespace cocos2d;

extern int playerType;
extern int skill1Count;
extern int skill2Count;
extern int skill3Count;

Gems* Gems::createGem(const char* fileName, int gemTypeTemp){
	Gems* gem = new Gems();
	if (gem && gem->initWithFile(fileName)){
		gem->autorelease();
		gem->gemInit(gemTypeTemp);
		return gem;
	}
	CC_SAFE_DELETE(gem);
	return NULL;
}

void Gems::gemInit(int gemTypeTemp){
	gemType = gemTypeTemp;
	glintTime = 15 * 60;
	glintCount = 0;
	isDisappear = false;
	chaneMove = true;
	this->scheduleUpdate();
}

void Gems::update(float dt)
{
	Size size = Director::getInstance()->getWinSize();
	float x = this->getPositionX();
	float thisX = this->getContentSize().width / 2;
	if (x > size.width - thisX)
		chaneMove = false;
	if (x < thisX)
		chaneMove = true;
	//��ʯ�ƶ�
	gemMoveCount++;
	if (gemMoveCount > 30)
	{
		gemMoveCount = 0;
		//gemMove();
		if (chaneMove){
			Action * action = MoveBy::create(1, ccp(50,-50));
			this->runAction(action);
		}
		else{
			Action * action = MoveBy::create(1, ccp(-50, -50));
			this->runAction(action);
		}
	}

	//��ʯ��˸
	glintCount++;
	if (glintCount >= glintTime){
		this->setVisible(true);
		isDisappear = true;
//		this->unscheduleUpdate();
//		this->removeFromParentAndCleanup(true);
	}
	else{
		//��ʯ����˸Ч��
		if (glintCount % 20 == 0){
			this->setVisible(false);
		}
		else{
			this->setVisible(true);
		}
	}
	//ɾ��
	if (this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height + this->getContentSize().height || this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width + this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
		return;
	}
	//��ײ���
	NewPlayer *player = PlayerScene::sharedPlayerScene()->getPlayer();
	if (!player->isDead)
	{
		if (player->boundingBox().intersectsRect(this->boundingBox()))
		{
			this->removeFromParentAndCleanup(true);
			switch (gemType)
			{
			case 0:    //�ı�ɻ�����
			{
				if (playerType <= 3)
				{
					PlayerScene::sharedPlayerScene()->isPlayerChange = true;
					playerType++;
				}
				break;
			}
			case 1:    //��Ѫ
			{
				if (player->hp<3)
				{
					player->addHp();
					player->hp++;
				}
				break;
			}
			case 2:    //�Ӵ���1
			{
				Node *skill = UniqueSkill::createUniqueSkill("4.png", 1);
				PlayerScene::sharedPlayerScene()->addChild(skill);
				skill1Count++;
				break;
			}
			case 3:    //�Ӵ���2
			{
				Node *skill = UniqueSkill::createUniqueSkill("1.png", 2);
				PlayerScene::sharedPlayerScene()->addChild(skill);
				skill2Count++;
				break;
			}
			case 4:    //�Ӵ���3
			{
				Node *skill = UniqueSkill::createUniqueSkill("2.png", 3);
				PlayerScene::sharedPlayerScene()->addChild(skill);
				skill3Count++;
				break;
			}
			default:
				break;
			}
		}
	}
}
//��������-�˳�
void Gems::onExit(){
	//ȡ�����º���
	this->unscheduleUpdate();
	Sprite::onExit();
}
