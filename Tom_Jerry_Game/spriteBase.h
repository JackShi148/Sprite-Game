#pragma once
#include"acllib.h"
class spriteBase
{
protected:        //设置为保护成员，公有继承时可访问
	int x, y, w, h;
	int ratex, ratey;
	ACL_Image *IMG;
	rect r;
public:
	spriteBase(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1);//窗口矩形
	spriteBase(spriteBase &base);
	virtual ~spriteBase();
	virtual void move(rect r)=0;//纯虚函数——派生类自己定义
	void PaintSprite(int width, int height);
	void PaintSprite();
	rect getRect();//自身的矩形包围框
};

