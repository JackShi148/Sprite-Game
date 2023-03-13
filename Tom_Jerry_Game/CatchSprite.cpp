#include "CatchSprite.h"
#include"acllib.h"
#include<math.h>

CatchSprite::CatchSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1, int score)
	:AvoidSprite(x, y, w, h, rx, ry, img, r1, score) {
	d = 100;
}
CatchSprite::CatchSprite(CatchSprite &sprite):AvoidSprite(sprite){}
CatchSprite::~CatchSprite() {}
void CatchSprite::move(rect r1)
{
	if (closer(r1))
	{
		if (first)
		{
			orx = ratex; ory = ratey;
			ratex *= 2; ratey *= 2;//速度加快
			first = false;
		}
		if (x < r1.x) ratex = abs(ratex);
		else ratex = -abs(ratex);
		if (y < r1.y) ratey = abs(ratey);
		else ratey = -abs(ratey);
		x += ratex; y += ratey;
		if (x < r.x) x = (r.x + r.w - w);
		if (x > (r.x + r.w - w)) x = r.x;
		if (y < r.y) y = (r.y + r.h - h);
		if (y > (r.y + r.h - h)) y = r.y;
	}
	else
	{
		if (first == false)
		{
			ratex = orx;
			ratey = ory;
		}
		first = true;
		AutoSprite::move(r1);
	}
}
