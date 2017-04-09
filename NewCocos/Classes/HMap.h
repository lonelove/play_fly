#ifndef __HMap_H__
#define __HMap_H__

#include "cocos2d.h"
using namespace cocos2d;

typedef enum{
	tag_oneImg,
	tag_twoImg,
}tagMap;//枚举两张地图背景的交替出现

class HMap : public cocos2d::Layer
{
public:
	//实例化函数
	static HMap* createMap(const char* fileName);

private:
	//初始化
	void mapInit(const char* fileName);
	//逻辑
	void update(float time);
	//生命周期函数的退出
	virtual void onExit();
};
#endif
