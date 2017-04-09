#include "PopScene.h"

bool PopScene::init()
{
	if (!LayerColor::initWithColor(ccc4(0, 0, 0, 200))) {
		return  false;
	}
	
	Size winSize = Director::getInstance()->getVisibleSize();

	//设置这个层的背景图片，并且设置其位置为整个屏幕的中点
	Sprite * background = Sprite::create("quit_outer.png");
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background);
	//获得背景图片的大小
	Size contentSize = background->getContentSize();

	//添加俩个菜单在这个层中
	auto item1 = MenuItemImage::create("YES.png", "YES2.png",CC_CALLBACK_1(PopScene::yesButton, this));

	auto item2 = MenuItemImage::create("NO.png", "NO2.png",CC_CALLBACK_1(PopScene::noButton, this));

	
	Menu * menu = Menu::create(item1, item2, NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(ccp(contentSize.width / 2, contentSize.height / 4));
	//kCCMenuHandlerPriority的值为-128，代表的是菜单按钮的触摸优先级
	//设置menu优先级，这里设置为普通menu的二倍减一，原因看下边
//		menu->setTouchPriority(kCCMenuHandlerPriority * 2 - 1);
	
	background->addChild(menu);
	
	return true;
}

//点击菜单按钮的时候调用的事件处理函数
void PopScene::yesButton(Object * object)
{
	//this->removeFromParentAndCleanup(true);
	Director::getInstance()->end();
}

void PopScene::noButton(Object * object)
{
	this->removeFromParentAndCleanup(true);
}


