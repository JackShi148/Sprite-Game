#pragma once
#include "AutoSprite.h"
#include "acllib.h"
class AvoidSprite :public AutoSprite
{
protected:
	int orx, ory;
	bool first;
	int d;    //设置dist成员保证狗与红心躲避（追逐）的距离不一样
	bool closer(rect r);
public:
	AvoidSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1,int score);
	AvoidSprite(AvoidSprite &sprite);
	virtual ~AvoidSprite();
	virtual void move(rect r1);//狗的移动与心的移动虽然相似但是存在区别，定义为虚函数
};