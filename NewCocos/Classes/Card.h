#include "cocos2d.h"  

USING_NS_CC;

class  Card : public Sprite
{
public:
	//初始化框架三件套  
	static Card* createCard(int num, int cardWeight, int cardHeight, float positionX, float positionY);
	virtual bool init();
	CREATE_FUNC(Card);

	//设置数字并显示的方法  
	void setNumber(int num);

	//获取数字的方法  
	int getNumber();

private:
	//卡片中的数字  
	int number;
	void cardInit(int num, int cardWeight, int cardHeight, float positionX, float positionY);

	//用于显示数字的控件  
	LabelTTF *cardLabel;

	//控件的背景颜色  
	LayerColor *cardBgColour;

};