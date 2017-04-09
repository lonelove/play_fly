#include "PopScene.h"

bool PopScene::init()
{
	if (!LayerColor::initWithColor(ccc4(0, 0, 0, 200))) {
		return  false;
	}
	
	Size winSize = Director::getInstance()->getVisibleSize();

	//���������ı���ͼƬ������������λ��Ϊ������Ļ���е�
	Sprite * background = Sprite::create("quit_outer.png");
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background);
	//��ñ���ͼƬ�Ĵ�С
	Size contentSize = background->getContentSize();

	//��������˵����������
	auto item1 = MenuItemImage::create("YES.png", "YES2.png",CC_CALLBACK_1(PopScene::yesButton, this));

	auto item2 = MenuItemImage::create("NO.png", "NO2.png",CC_CALLBACK_1(PopScene::noButton, this));

	
	Menu * menu = Menu::create(item1, item2, NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(ccp(contentSize.width / 2, contentSize.height / 4));
	//kCCMenuHandlerPriority��ֵΪ-128��������ǲ˵���ť�Ĵ������ȼ�
	//����menu���ȼ�����������Ϊ��ͨmenu�Ķ�����һ��ԭ���±�
//		menu->setTouchPriority(kCCMenuHandlerPriority * 2 - 1);
	
	background->addChild(menu);
	
	return true;
}

//����˵���ť��ʱ����õ��¼�������
void PopScene::yesButton(Object * object)
{
	//this->removeFromParentAndCleanup(true);
	Director::getInstance()->end();
}

void PopScene::noButton(Object * object)
{
	this->removeFromParentAndCleanup(true);
}


