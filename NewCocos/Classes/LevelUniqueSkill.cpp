#include "LevelUniqueSkill.h"
#include "LevelScene.h"
#include "LevelNewPlayer.h"
#include "LevelNewBullet.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
int skillCount1 = 0;
int skillCount2 = 0;
int skillCount3 = 0;
LevelUniqueSkill* LevelUniqueSkill::createUniqueSkill(const char* fileName, int _uniqueSkillType)
{
	LevelUniqueSkill* uSkill = new LevelUniqueSkill();
	if (uSkill)
	{
		uSkill->autorelease();
		uSkill->uniqueSkillInit(fileName, _uniqueSkillType);
		return uSkill;
	}
	CC_SAFE_DELETE(uSkill);
	return NULL;
}

void LevelUniqueSkill::uniqueSkillInit(const char* fileName, int _uniqueSkillType)
{
	skill1TimeCount = 0;
	skill2TimeCount = 0;
	skill3TimeCount = 0;
	spritebatch = SpriteBatchNode::create("ui/wsparticle_guenonlighting.png",50);
	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("ui/wsparticle_guenonlighting.plist");
	addChild(spritebatch, 1);

	switch (_uniqueSkillType)
	{
	case 1:
	{
		if (skillCount1 == 0)
		{
			Size size = Director::getInstance()->getVisibleSize();
			MenuItemImage *skill = MenuItemImage::create(fileName, fileName, this, menu_selector(LevelUniqueSkill::uniqueSkill1));
			skill->setPosition(ccp(size.width - skill->getContentSize().width*_uniqueSkillType, skill->getContentSize().height*0.5));
			Menu *menu = Menu::create(skill, NULL);
			menu->setAnchorPoint(ccp(0, 0));
			menu->setPosition(Point::ZERO);
			this->addChild(menu, 1, tag_uniqueSkill1);
		}
		break;
	}
	case 2:
	{
		if (skillCount2 == 0)
		{
			Size size = Director::getInstance()->getVisibleSize();
			MenuItemImage *skill = MenuItemImage::create(fileName, fileName, this, menu_selector(LevelUniqueSkill::uniqueSkill2));
			skill->setPosition(ccp(size.width - skill->getContentSize().width*_uniqueSkillType - 10, skill->getContentSize().height*0.5));
			Menu *menu = Menu::create(skill, NULL);
			menu->setAnchorPoint(ccp(0, 0));
			menu->setPosition(Point::ZERO);
			this->addChild(menu, 1, tag_uniqueSkill2);
		}
		break;
	}
	case 3:
	{
		if (skillCount3 == 0)
		{
			Size size = Director::getInstance()->getVisibleSize();
			MenuItemImage *skill = MenuItemImage::create(fileName, fileName, this, menu_selector(LevelUniqueSkill::uniqueSkill3));
			skill->setPosition(ccp(size.width - skill->getContentSize().width*_uniqueSkillType - 20, skill->getContentSize().height*0.5));
			Menu *menu = Menu::create(skill, NULL);
			menu->setAnchorPoint(ccp(0, 0));
			menu->setPosition(Point::ZERO);
			this->addChild(menu, 1, tag_uniqueSkill3);
		}
		break;
	}
	default:
		break;
	}
}

void LevelUniqueSkill::uniqueSkill1(Object* psend)
{
	//CCLOG("aaa");
	this->removeChildByTag(tag_uniqueSkill1, true);
	skillCount1 = 0;

	Size size = Director::getInstance()->getVisibleSize();
	for (int i = 1; i < 5; i++)
	{
		CallFunc *func = CallFunc::create(this, callfunc_selector(LevelUniqueSkill::removeSprite));
		CallFunc *func1 = CallFunc::create(this, callfunc_selector(LevelUniqueSkill::createBullet));
		CallFunc *func2 = CallFunc::create(this, callfunc_selector(LevelUniqueSkill::finishBullet));
		Sprite *sp = Sprite::create("ui/plane6.png");
		sp->setPosition(ccp(sp->getContentSize().width + (i - 1) * 70, -sp->getContentSize().height));
		this->addChild(sp, 1, i + 1);
		sp->runAction(Sequence::create(MoveTo::create(1, CCPointMake(sp->getPositionX(), sp->getContentSize().height + 30)), func1, DelayTime::create(10), func2, MoveTo::create(1, CCPointMake(sp->getPositionX(), -sp->getContentSize().height)), func, NULL));
	}
}

void LevelUniqueSkill::uniqueSkill2(Object* psend)
{
	this->removeChildByTag(tag_uniqueSkill2, true);
	skillCount2 = 0;
	this->schedule(schedule_selector(LevelUniqueSkill::changeAnimate));
}

void LevelUniqueSkill::uniqueSkill3(Object* psend)
{
	this->removeChildByTag(tag_uniqueSkill3, true);
	skillCount3 = 0;
	skill3 = Sprite::create("UI2/skill_3.png");
	this->addChild(skill3, 1, tag_skill_3);
	this->schedule(schedule_selector(LevelUniqueSkill::strongSkill));
}

void LevelUniqueSkill::removeSprite()
{
	for (int i = 1; i < 5; i++)
	{
		this->removeChildByTag(i + 1, true);
	}
}

void LevelUniqueSkill::createBullet()
{
	this->schedule(schedule_selector(LevelUniqueSkill::autoCreateBullet));
}

void LevelUniqueSkill::finishBullet()
{
	skill1TimeCount = 0;
	this->unschedule(schedule_selector(LevelUniqueSkill::autoCreateBullet));
}

void LevelUniqueSkill::autoCreateBullet(float f)
{
	skill1TimeCount++;
	if (skill1TimeCount % 30 == 0)
	{
		for (int i = 1; i<5; i++)
		{
			Sprite * player = (Sprite*)this->getChildByTag(i + 1);
			this->addChild(LevelNewBullet::createBullet("11.png", 20, ccpAdd(player->getPosition(), ccp(15, 15)), 1));
			this->addChild(LevelNewBullet::createBullet("11.png", 20, ccpSub(player->getPosition(), ccp(15, -15)), 1));
			//子弹音效
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bullet.mp3");
		}
	}
}

void LevelUniqueSkill::createAnimate(LevelNewEnemy* enemy)
{
	Size s = Director::getInstance()->getVisibleSize();
	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	//cache->addSpriteFramesWithFile("wsparticle_guenonlighting.plist");
	Sprite *sprite = Sprite::createWithSpriteFrameName("guenon_00000.png");
	sprite->setPosition(ccp(enemy->getPositionX(), enemy->getPositionY() + 40));
	spritebatch->addChild(sprite, 1);

	//Array* animFrames = Array::createWithCapacity(15);
	Vector<SpriteFrame*> frameVec;
	char str[100] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		sprintf(str, "guenon_0000%d.png", i);
		SpriteFrame* frame = cache->spriteFrameByName(str);
		//animFrames->addObject(frame);
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.05f);
	// Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	sprite->runAction(RepeatForever::create(Animate::create(animation)));

	enemy->hp -= 2;
}

void LevelUniqueSkill::changeAnimate(float f)
{
	skill2TimeCount++;
	if (skill2TimeCount < 600)
	{
		if (skill2TimeCount % 10 == 0)
		{
			if (spritebatch->getChildrenCount() != 0)
			{
				spritebatch->removeAllChildrenWithCleanup(true);
				return;
			}

			Array *array = LevelScene::sharedLevelScene()->getArrayForEnemy();
			for (int i = 0; i < array->count(); i++)
			{
				LevelNewEnemy* enemy = (LevelNewEnemy*)array->objectAtIndex(i);
				this->createAnimate(enemy);
				//闪电音效
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ui/shandian.wav");
			}
		}
	}
	else
	{
		skill2TimeCount = 0;
		this->unschedule(schedule_selector(LevelUniqueSkill::changeAnimate));
		if (spritebatch->getChildrenCount() != 0)
		{
			spritebatch->removeAllChildrenWithCleanup(true);
			return;
		}
	}
}

void LevelUniqueSkill::strongSkill(float f)
{
	skill3TimeCount++;
	LevelNewPlayer *player = LevelScene::sharedLevelScene()->getPlayer();
	if (skill3TimeCount < 600)
	{
		skill3->setPosition(player->getPosition());
		player->isStrong = true;
	}
	else
	{
		this->removeChildByTag(tag_skill_3, true);
		skill3TimeCount = 0;
		player->isStrong = false;
		this->unschedule(schedule_selector(LevelUniqueSkill::strongSkill));
	}
}

