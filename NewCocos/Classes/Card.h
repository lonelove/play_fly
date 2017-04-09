#include "cocos2d.h"  

USING_NS_CC;

class  Card : public Sprite
{
public:
	//��ʼ�����������  
	static Card* createCard(int num, int cardWeight, int cardHeight, float positionX, float positionY);
	virtual bool init();
	CREATE_FUNC(Card);

	//�������ֲ���ʾ�ķ���  
	void setNumber(int num);

	//��ȡ���ֵķ���  
	int getNumber();

private:
	//��Ƭ�е�����  
	int number;
	void cardInit(int num, int cardWeight, int cardHeight, float positionX, float positionY);

	//������ʾ���ֵĿؼ�  
	LabelTTF *cardLabel;

	//�ؼ��ı�����ɫ  
	LayerColor *cardBgColour;

};