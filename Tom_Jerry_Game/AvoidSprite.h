#pragma once
#include "AutoSprite.h"
#include "acllib.h"
class AvoidSprite :public AutoSprite
{
protected:
	int orx, ory;
	bool first;
	int d;    //����dist��Ա��֤������Ķ�ܣ�׷�𣩵ľ��벻һ��
	bool closer(rect r);
public:
	AvoidSprite(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1,int score);
	AvoidSprite(AvoidSprite &sprite);
	virtual ~AvoidSprite();
	virtual void move(rect r1);//�����ƶ����ĵ��ƶ���Ȼ���Ƶ��Ǵ������𣬶���Ϊ�麯��
};