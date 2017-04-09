#ifndef __HMap_H__
#define __HMap_H__

#include "cocos2d.h"
using namespace cocos2d;

typedef enum{
	tag_oneImg,
	tag_twoImg,
}tagMap;//ö�����ŵ�ͼ�����Ľ������

class HMap : public cocos2d::Layer
{
public:
	//ʵ��������
	static HMap* createMap(const char* fileName);

private:
	//��ʼ��
	void mapInit(const char* fileName);
	//�߼�
	void update(float time);
	//�������ں������˳�
	virtual void onExit();
};
#endif
