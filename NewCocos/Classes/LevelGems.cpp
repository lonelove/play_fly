#include "LevelGems.h"
#include "LevelScene.h"
#include "LevelNewPlayer.h"
#include "LevelUniqueSkill.h"
using namespace cocos2d;

extern int playType;
extern int skillCount1;
extern int skillCount2;
extern int skillCount3;

LevelGems* LevelGems::createGem(const char* fileName, int gemTypeTemp){
	LevelGems* gem = new LevelGems();
	if (gem && gem->initWithFile(fileName)){
		gem->autorelease();
		gem->gemInit(gemTypeTemp);
		return gem;
	}
	CC_SAFE_DELETE(gem);
	return NULL;
}

void LevelGems::gemInit(int gemTypeTemp){
	gemType = gemTypeTemp;
	glintTime = 15 * 60;
	glintCount = 0;
	isDisappear = false;
	chaneMove = false;
	this->scheduleUpdate();
}

void LevelGems::update(float dt)
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
		if (chaneMove){
			Action * action = MoveBy::create(1, ccp(50, -50));
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
	LevelNewPlayer *player = LevelScene::sharedLevelScene()->getPlayer();
	if (!player->isDead)
	{
		if (player->boundingBox().intersectsRect(this->boundingBox()))
		{
			this->removeFromParentAndCleanup(true);
			switch (gemType)
			{
			case 0:    //�ı�ɻ�����
			{
				if (playType <= 3)
				{
					LevelScene::sharedLevelScene()->isPlayerChange = true;
					playType++;
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
				Node *skill = LevelUniqueSkill::createUniqueSkill("4.png", 1);
				LevelScene::sharedLevelScene()->addChild(skill);
				skillCount1++;
				break;
			}
			case 3:    //�Ӵ���2
			{
				Node *skill = LevelUniqueSkill::createUniqueSkill("1.png", 2);
				LevelScene::sharedLevelScene()->addChild(skill);
				skillCount2++;
				break;
			}
			case 4:    //�Ӵ���3
			{
				Node *skill = LevelUniqueSkill::createUniqueSkill("2.png", 3);
				LevelScene::sharedLevelScene()->addChild(skill);
				skillCount3++;
				break;
			}
			default:
				break;
			}
		}
	}
}
//��������-�˳�
void LevelGems::onExit(){
	//ȡ�����º���
	this->unscheduleUpdate();
	Sprite::onExit();
}

