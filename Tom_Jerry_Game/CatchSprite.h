#pragma once
#include "AvoidSprite.h"
class CatchSprite :
	public AvoidSprite
{
public:
	CatchSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1, int score);
	CatchSprite(CatchSprite &sprite);
	virtual ~CatchSprite();
	void move(rect r1);
};

