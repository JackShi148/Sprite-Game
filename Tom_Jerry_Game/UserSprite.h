#pragma once
#include "spriteBase.h"
#include"acllib.h"
class UserSprite :public spriteBase
{
	int score;
	int life;
public:
	UserSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1);
	UserSprite(UserSprite &usersprite);
	~UserSprite();
	void move(int xx, int yy);
	void move(int key);
	void move(rect r);
	bool collision(rect a);
	int getScore();
	void addScore();
	int getLife();
	void addLife();
	void loseLife();
};

