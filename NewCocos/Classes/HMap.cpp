#include "HMap.h"
using namespace cocos2d;

HMap* HMap::createMap(const char* fileName){
	HMap* map = new HMap();
	if (map && map->create()){
		map->autorelease();
		map->mapInit(fileName);
		return map;
	}
	CC_SAFE_DELETE(map);
	return NULL;
}

void HMap::mapInit(const char* fileName){
	Size vs = Director::getInstance()->getVisibleSize();
	Sprite* m_sp1 = Sprite::create(fileName);
	Sprite* m_sp2 = Sprite::create(fileName);
	m_sp1->setPosition(Point(vs.width / 2, vs.height / 2));
	//m_sp2->setPosition(Point(vs.width / 2, vs.height + vs.height / 2));
	m_sp2->setPosition(Point(vs.width / 2, m_sp1->getContentSize().height + vs.height / 2));
	this->addChild(m_sp1, 0, 100);
	this->addChild(m_sp2, 0, 101);
	this->scheduleUpdate();
}

void HMap::update(float time){
	int posY1 = this->getChildByTag(100)->getPositionY();//����1��Y����
	int posY2 = this->getChildByTag(101)->getPositionY();//����1��Y����
	int iSpeed = 2;	//��ͼ�����ٶ�
	posY1 -= iSpeed;
	posY2 -= iSpeed;
	Size mapSize = this->getChildByTag(100)->getContentSize();
	if (posY1 <= -mapSize.height / 2){
		posY1 = mapSize.height + mapSize.height / 2;
	}
	if (posY2 <= -mapSize.height / 2){
		posY2 = mapSize.height + mapSize.height / 2;
	}
	this->getChildByTag(100)->setPositionY(posY1);
	this->getChildByTag(101)->setPositionY(posY2);
}

void HMap::onExit(){
	//������º���
	this->unscheduleUpdate();
	Layer::onExit();
}
