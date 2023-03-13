#include "spriteBase.h"
#include"acllib.h"
spriteBase::spriteBase(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1)
{
	this->x = x; this->y = y; this->w = w; this->h = h;
	ratex = rx; ratey = ry; IMG = img; r = r1;
}
spriteBase::spriteBase(spriteBase &base)
{
	x = base.x; y = base.y; w = base.w; h = base.h; ratex = base.ratex; ratey = base.ratey;
	IMG = base.IMG, r = base.r;
}
spriteBase::~spriteBase(){}
void spriteBase::PaintSprite(int width, int height)
{
	putImageScale(IMG, x, y, width, height);
}
void spriteBase::PaintSprite()
{
	putImageScale(IMG, x, y, w, h);
}
rect spriteBase::getRect()
{
	rect r = { x,y,w,h };
	return r;
}
