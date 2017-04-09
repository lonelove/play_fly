#ifndef __HPauseLayer_H__
#define __HPauseLayer_H__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class HPauseLayer : public LayerColor {

public:
	virtual bool init();

	void backGame(Object *pSender);
	void backHome(Object *pSender);
	CREATE_FUNC(HPauseLayer);

};
#endif