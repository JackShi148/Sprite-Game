#pragma once
#include "spriteBase.h"
#include"acllib.h"
class AutoSprite :public spriteBase
{
protected:
		int score;
public:
	AutoSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1,int socre);
	AutoSprite(AutoSprite &autosprite);
	virtual ~AutoSprite();
	void move(rect r1);
	int getScore();
};
