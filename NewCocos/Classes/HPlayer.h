#ifndef __HPLAYER_H__
#define __HPLAYER_H__

#include "cocos2d.h"
#include <sstream>
using namespace std;
using namespace cocos2d;

typedef enum{
	tag_player,//����
	tag_playerHp1,//Ѫ��1
	tag_playerHp2,//Ѫ��2
	tag_playerHp3,//Ѫ��3
	tag_scoreTTF,//����
	tag_killsCountTTF,//ɱ����
	tag_uniqueSkill1,//����1
	tag_uniqueSkill2,//����2
	tag_uniqueSkill3,//����3
	tag_skill_3,//����3��Ч��
}tagPlayer;//ö�ٱ���

//��Ҫ���ڽ�int float ������ת����string����
template<typename T>
string Convert2String(const T &value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

#endif
