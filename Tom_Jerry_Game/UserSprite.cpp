#include "UserSprite.h"
#include"acllib.h"

UserSprite::UserSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1)
	:spriteBase(x, y, w, h, rx, ry, img, r1) {
	score = 0;
	life = 5;
}
UserSprite::UserSprite(UserSprite &usersprite) : spriteBase(usersprite) { score = usersprite.score; life = usersprite.life; }
UserSprite::~UserSprite(){}
void UserSprite::move(int xx, int yy)
{
	x = xx; y = yy;
	if (x < r.x) x = r.x;
	if (x > (r.x + r.w - w)) x = (r.x + r.w - w);
	if (y < r.y) y = r.y;
	if (y > (r.y + r.h - h)) y = (r.y + r.h - h);
}
void UserSprite::move(int key)
{
	switch (key)
	{
	case VK_UP:
		y -= ratey;
		if (y < r.y) y = r.y;
		break;
	case VK_DOWN:
		y += ratey;
		if (y > (r.y + r.h - h)) y = (r.y + r.h - h);
		break;
	case VK_RIGHT:
		x += ratex;
		if (x > (r.x + r.w - w)) x = (r.x + r.w - w);
		break;
	case VK_LEFT:
		x -= ratex;
		if (x < r.x) x = r.x;
		break;
	default:
		break;
	}
}
void UserSprite::move(rect r1)
{
	x = r1.x; y = r1.y;
	if (x < r.x) x = r.x;
	if (x > (r.x + r.w - w)) x = (r.x + r.w - w);
	if (y < r.y) y = r.y;
	if (y > (r.y + r.h - h)) y = (r.y + r.h - h);
}
bool UserSprite::collision(rect a)
{
	rect user = { x,y,w,h };
	bool e = true;
	if (user.x<a.x&&user.x + user.w>a.x)//左边相碰
	{
		if (user.y > a.y&&user.y < a.y + a.h) return e;//r1在r2的左下
		if (user.y < a.y&&user.y + user.h > a.y) return e;//左上
	}
	else
	{
		if (user.x > a.x&&user.x < a.x + a.w)
		{
			if (user.y > a.y&&user.y < a.y + a.h) return e;//r1在r2的右下
			if (user.y < a.y&&user.y + user.h > a.y) return e;//右下
		}
	}
	e = false;
	return e;
}
int UserSprite::getScore()
{
	return score;
}
void UserSprite::addScore()
{
	score ++;
}
int UserSprite::getLife()
{
	return life;
}
void UserSprite::addLife()
{
	life++;
}
void UserSprite::loseLife()
{
	life--;
}