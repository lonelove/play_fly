
#include "UniqueSkill.h"
#include "PlayerScene.h"
#include "NewPlayer.h"
#include "NewBullet.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
int skill1Count = 0;
int skill2Count = 0;
int skill3Count = 0;
UniqueSkill* UniqueSkill::createUniqueSkill(const char* fileName, int _uniqueSkillType)
{
	UniqueSkill* uSkill = new UniqueSkill();
	if (uSkill)
	{
		uSkill->autorelease();
		uSkill->uniqueSkillInit(fileName, _uniqueSkillType);
		return uSkill;
	}
	CC_SAFE_DELETE(uSkill);
	return NULL;
}

void UniqueSkill::uniqueSkillInit(const char* fileName, int _uniqueSkillType)
{
	skill1TimeCount = 0;
	skill2TimeCount = 0;
	skill3TimeCount = 0;
	spritebatch = SpriteBatchNode::create("ui/wsparticle_guenonlighting.png", 50);
	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("ui/wsparticle_guenonlighting.plist");
	addChild(spritebatch, 1);

	switch (_uniqueSkillType)
	{
	case 1:
	{
		if (skill1Count == 0)
		{
			Size size = Director::getInstance()->getVisibleSize();
			MenuItemImage *skill = MenuItemImage::create(fileName, fileName, this, menu_selector(UniqueSkill::uniqueSkill1));
			//MenuItemImage *skill = MenuItemImage::create(fileName, fileName, CC_CALLBACK_1(UniqueSkill::uniqueSkill1,this));
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
		if (skill2Count == 0)
		{
			Size size = Director::getInstance()->getVisibleSize();
			MenuItemImage *skill = MenuItemImage::create(fileName, fileName, this, menu_selector(UniqueSkill::uniqueSkill2));
			//MenuItemImage *skill = MenuItemImage::create(fileName, fileName, CC_CALLBACK_1(UniqueSkill::uniqueSkill2, this));
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
		if (skill3Count == 0)
		{
			Size size = Director::getInstance()->getVisibleSize();
			MenuItemImage *skill = MenuItemImage::create(fileName, fileName, this, menu_selector(UniqueSkill::uniqueSkill3));
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

void UniqueSkill::uniqueSkill1(Object* psend)
{
	//CCLOG("aaa");
	this->removeChildByTag(tag_uniqueSkill1, true);
	skill1Count = 0;

	Size size = Director::getInstance()->getVisibleSize();
	for (int i = 1; i < 5; i++)
	{
		CallFunc *func = CallFunc::create(this, callfunc_selector(UniqueSkill::removeSprite));
		CallFunc *func1 = CallFunc::create(this, callfunc_selector(UniqueSkill::createBullet));
		CallFunc *func2 = CallFunc::create(this, callfunc_selector(UniqueSkill::finishBullet));

		Sprite *sp = Sprite::create("ui/plane6.png");
		sp->setPosition(ccp(sp->getContentSize().width + (i - 1) * 150, -sp->getContentSize().height));
		this->addChild(sp, 1, i + 1);
		sp->runAction(Sequence::create(MoveTo::create(1, CCPointMake(sp->getPositionX(), sp->getContentSize().height + 30)), func1, DelayTime::create(10), func2, MoveTo::create(1, CCPointMake(sp->getPositionX(), -sp->getContentSize().height)), func, NULL));
	}
}

void UniqueSkill::uniqueSkill2(Object* psend)
{
	this->removeChildByTag(tag_uniqueSkill2, true);
	skill2Count = 0;
	this->schedule(schedule_selector(UniqueSkill::changeAnimate));
}

void UniqueSkill::uniqueSkill3(Object* psend)
{
	this->removeChildByTag(tag_uniqueSkill3, true);
	skill3Count = 0;
	skill3 = Sprite::create("UI2/skill_3.png");
	this->addChild(skill3, 1, tag_skill_3);
	this->schedule(schedule_selector(UniqueSkill::strongSkill));
}

void UniqueSkill::removeSprite()
{
	for (int i = 1; i < 5; i++)
	{
		this->removeChildByTag(i + 1, true);
	}
}

void UniqueSkill::createBullet()
{
	this->schedule(schedule_selector(UniqueSkill::autoCreateBullet));
	//this->schedule(SEL_SCHEDULE(&UniqueSkill::autoCreateBullet));
}

void UniqueSkill::finishBullet()
{
	skill1TimeCount = 0;
	this->unschedule(schedule_selector(UniqueSkill::autoCreateBullet));
	//this->unschedule(SEL_SCHEDULE(&UniqueSkill::autoCreateBullet));
}

void UniqueSkill::autoCreateBullet(float f)
{
	skill1TimeCount++;
	if (skill1TimeCount % 30 == 0)
	{
		for (int i = 1; i<5; i++)
		{
			Sprite * player = (Sprite*)this->getChildByTag(i + 1);
			this->addChild(NewBullet::createBullet("11.png", 20, ccpAdd(player->getPosition(), ccp(15, 15)), 1));
			this->addChild(NewBullet::createBullet("11.png", 20, ccpSub(player->getPosition(), ccp(15, -15)), 1));
			//子弹音效
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ui/effect_bullet.mp3");
		}
	}
}

void UniqueSkill::createAnimate(NewEnemy* enemy)
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

void UniqueSkill::changeAnimate(float f)
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

			Array *array = PlayerScene::sharedPlayerScene()->getArrayForEnemy();
			for (int i = 0; i < array->count(); i++)
			{
				NewEnemy* enemy = (NewEnemy*)array->objectAtIndex(i);
				this->createAnimate(enemy);
				//闪电音效
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ui/shandian.wav");
			}
		}
	}
	else
	{
		skill2TimeCount = 0;
		this->unschedule(schedule_selector(UniqueSkill::changeAnimate));
		if (spritebatch->getChildrenCount() != 0)
		{
			spritebatch->removeAllChildrenWithCleanup(true);
			return;
		}
	}
}

void UniqueSkill::strongSkill(float f)
{
	skill3TimeCount++;
	NewPlayer *player = PlayerScene::sharedPlayerScene()->getPlayer();
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
		this->unschedule(schedule_selector(UniqueSkill::strongSkill));
	}
}

