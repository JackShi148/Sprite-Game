#pragma once
#include"acllib.h"
class spriteBase
{
protected:        //����Ϊ������Ա�����м̳�ʱ�ɷ���
	int x, y, w, h;
	int ratex, ratey;
	ACL_Image *IMG;
	rect r;
public:
	spriteBase(int x, int y, int w, int h, int rx, int ry, ACL_Image *img, rect r1);//���ھ���
	spriteBase(spriteBase &base);
	virtual ~spriteBase();
	virtual void move(rect r)=0;//���麯�������������Լ�����
	void PaintSprite(int width, int height);
	void PaintSprite();
	rect getRect();//����ľ��ΰ�Χ��
};

