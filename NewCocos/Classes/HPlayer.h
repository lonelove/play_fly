#ifndef __HPLAYER_H__
#define __HPLAYER_H__

#include "cocos2d.h"
#include <sstream>
using namespace std;
using namespace cocos2d;

typedef enum{
	tag_player,//主角
	tag_playerHp1,//血量1
	tag_playerHp2,//血量2
	tag_playerHp3,//血量3
	tag_scoreTTF,//分数
	tag_killsCountTTF,//杀敌数
	tag_uniqueSkill1,//大招1
	tag_uniqueSkill2,//大招2
	tag_uniqueSkill3,//大招3
	tag_skill_3,//大招3的效果
}tagPlayer;//枚举变量

//主要用于将int float 等数字转换成string类型
template<typename T>
string Convert2String(const T &value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

#endif
