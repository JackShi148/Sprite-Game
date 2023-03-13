#include "AvoidSprite.h"
#include "acllib.h"
#include<math.h>
AvoidSprite::AvoidSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1,int score):AutoSprite(x,y,w,h,rx,ry,img,r1,score)
{
	orx = rx; ory = ry; first = true; d = 70;
}
AvoidSprite::AvoidSprite(AvoidSprite &sprite):AutoSprite(sprite)
{
	orx = ratex; ory = ratey; first = true;
}
AvoidSprite::~AvoidSprite(){}

void AvoidSprite::move(rect r1)
{
	if (closer(r1))
	{
		if (first)
		{
			orx = ratex; ory = ratey;
			ratex *= 1.5; ratey *= 1.5;//速度加快
			first = false;
		}
		if (x < r1.x) ratex = -abs(ratex);
		else ratex = abs(ratex);
		if (y < r1.y) ratey = -abs(ratey);
		else ratey = abs(ratey);
		x += ratex; y += ratey;
		if (x < r.x) x = (r.x);
		if (x > (r.x + r.w - w)) x = (r.x + r.w - w);
		if (y < r.y) y = (r.y);
		if (y > (r.y + r.h - h)) y = (r.y + r.h - h);
	}
	else
	{
		if (first == false)//弹走后方向也要变！！！
		{
			ratex = -orx;
			ratey = -ory;
		}
		first = true;
		AutoSprite::move(r1);
	}
}
bool AvoidSprite::closer(rect r)
{
	int cx = (x + w) / 2;
	int cy = (y + h) / 2;
	int ux = (r.x + r.w) / 2;
	int uy = (r.y + r.h) / 2;
	int dist = sqrt((cx - ux)*(cx - ux) + (cy - uy)*(cy - uy));
	if (dist < d) return true;
	else return false;
}