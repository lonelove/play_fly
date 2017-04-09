#include "Card.h"  

USING_NS_CC;

Card* Card::createCard(int num, int cardWeight, int cardHeight, float positionX, float positionY)
{
	Card* card = new Card();
	if (card && card->init())
	{
		card->autorelease();
		card->cardInit(num, cardWeight, cardHeight, positionX, positionY);
		return card;
	}
	CC_SAFE_DELETE(card);
	return NULL;
}

bool Card::init()
{
	if (!Sprite::init())
		return false;
	return true;
}

void Card::setNumber(int num)
{
	number = num;
	//设置字体的大小  
	if (number >= 0 && number < 16)
	{
		cardLabel->setFontSize(50);

	}
	if (number >= 16 && number < 128)
	{
		cardLabel->setFontSize(40);

	}
	if (number >= 128 && number < 1024)
	{
		cardLabel->setFontSize(30);
	}
	if (number >= 1024)
	{
		cardLabel->setFontSize(20);
	}

	//设置数字颜色  
	if (number == 0){
		cardBgColour->setColor(Color3B(200, 190, 180));
	}
	if (number == 2){
		cardBgColour->setColor(Color3B(240, 230, 220));
	}
	if (number == 4){
		cardBgColour->setColor(Color3B(51, 153, 51));
	}
	if (number == 8){
		cardBgColour->setColor(Color3B(255, 153, 102));
	}
	if (number == 16){
		cardBgColour->setColor(Color3B(153, 204, 153));
	}
	if (number == 32){
		cardBgColour->setColor(Color3B(153, 204, 255));
	}
	if (number == 64){
		cardBgColour->setColor(Color3B(255, 204, 204));
	}
	if (number == 128){
		cardBgColour->setColor(Color3B(204, 102, 0));
	}
	if (number == 256){
		cardBgColour->setColor(Color3B(153, 204, 51));
	}
	if (number == 512){
		cardBgColour->setColor(Color3B(255, 102, 102));
	}
	if (number == 1024){
		cardBgColour->setColor(Color3B(204, 204, 255));
	}
	if (number == 2048){
		cardBgColour->setColor(Color3B(255, 204, 00));
	}

	//显示数字  
	if (number > 0)
		cardLabel->setString(__String::createWithFormat("%d", number)->getCString());
	else
		cardLabel->setString("");
}

int Card::getNumber()
{
	return number;
}

void Card::cardInit(int num, int cardWeight, int cardHeight, float positionX, float positionY)
{
	number = num;

	//添加卡片背景颜色  
	cardBgColour = LayerColor::create(Color4B(200, 190, 180, 255), cardWeight - 5, cardHeight - 5);
	cardBgColour->setPosition(Point(positionX, positionY));

	//判断num是否大于0，是就显示，否则显示空  
	if (num > 0)
	{
		//设置字体  
		cardLabel = LabelTTF::create(__String::createWithFormat("%d", number)->getCString(), "Arial", 50);
		cardLabel->setPosition(Point(cardBgColour->getContentSize().width / 2, cardBgColour->getContentSize().height / 2));
		cardBgColour->addChild(cardLabel);
	}
	else
	{
		cardLabel = LabelTTF::create("", "Arial", 50);
		cardLabel->setPosition(Point(cardBgColour->getContentSize().width / 2, cardBgColour->getContentSize().height / 2));
		cardBgColour->addChild(cardLabel);
	}

	this->addChild(cardBgColour);
}