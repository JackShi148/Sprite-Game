#include "AutoSprite.h"

AutoSprite::AutoSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1, int score) :spriteBase(x, y, w, h, rx, ry, img, r1)
{
	this->score = score;
}
AutoSprite::AutoSprite(AutoSprite &autosprite):spriteBase(autosprite){}

AutoSprite::~AutoSprite()
{
}
void AutoSprite::move(rect r1)
{
	if (x<r.x || x>(r.x + r.w - w)) ratex *= -1;
	if (y<r.y || y>(r.y + r.h - h)) ratey *= -1;
	x += ratex; y += ratey;
}
int AutoSprite::getScore()
{
	return score;
}