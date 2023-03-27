#include"acllib.h"
#include"UserSprite.h"
#include"AutoSprite.h"
#include"AvoidSprite.h"
#include"CatchSprite.h"
#include<time.h>
#include<stdio.h>
const int winWidth = 1000, winHeight =600;
int tomWidth = 80, tomHeight = 100;
int jerryWidth = 50, jerryHeight = 50;
int heartWidth = 30, heartHeight = 30;
int dogWidth = 110, dogHeight = 110;
const int maxNum = 100;
int curnum = 0;
UserSprite *Tom=NULL;
AutoSprite *Autosprite[maxNum] = { 0 };
int timerid = 0, movetimerinterval = 40;
int createid = 1, createtimerinterval = 1000;
ACL_Image tomimg, jerryimg, heartimg, dogimg;
ACL_Color color = RGB(225, 0, 0), color1 = RGB(28, 28, 28);
ACL_Sound ej, et, h, bk;
rect WinRect;
void create(AutoSprite **autosprite);
void create(UserSprite **usersprite);
void Paint();
void keyEvent(int key,int event);
void timerEvent(int id);
void Gameover();
int Setup()
{
	initWindow("UserSprite", 10, 10,winWidth,winHeight);
	srand((unsigned)time(NULL));
	loadImage("jerry.bmp", &jerryimg);
	loadImage("tom.bmp", &tomimg);
	loadImage("heart.bmp", &heartimg);
	loadImage("dog.bmp", &dogimg);
	loadSound("eat_jerry.wav", &ej);
	loadSound("eat_tom.wav", &et);
	loadSound("heart.wav", &h);
	loadSound("bk.wav", &bk);
	WinRect.x = DEFAULT; WinRect.y = DEFAULT; WinRect.w = winWidth; WinRect.h = winHeight;
	create(Autosprite);
	create(&Tom);
	playSound(bk, 1);
	registerKeyboardEvent(keyEvent);
	registerTimerEvent(timerEvent);
	startTimer(timerid, movetimerinterval);
	startTimer(createid, createtimerinterval);
	Paint();
	return 0;
}

void Paint()
{
	beginPaint();
	clearDevice();
	int i = 0;
	for (i = 0; i < curnum; i++)
	{
		if (Autosprite[i])
		{
			Autosprite[i]->PaintSprite();
		}
	}
	if (Tom)
	{
		//Tom->PaintSprite();
		int s = Tom->getScore();  // get tom current score
		switch (s/15)
		{
		case 0:
			Tom->PaintSprite();
			break;
		case 1:
			Tom->PaintSprite(1.1*tomWidth, 1.1*tomHeight);
			break;
		case 2:
			Tom->PaintSprite(1.2*tomWidth, 1.2*tomHeight);
			break;
		default:
			Tom->PaintSprite(1.2*tomWidth, 1.2*tomHeight);
			break;
		}
		char str[50],str3[50];
		sprintf_s(str, sizeof(str), "Score:%d  Life:%d", Tom->getScore(),Tom->getLife());
		setTextSize(20);
		setTextColor(color1);
		paintText((winWidth-150)/2, 0, str);
		line(0, 20, winWidth, 20);
		sprintf_s(str3, sizeof(str3), "Happy Game!");
		setTextSize(20);
		setTextColor(color);
		paintText(325, 21, str3);
	}
	endPaint();
}

void keyEvent(int key, int event)
{
	if (event != KEY_DOWN) return;
	if (Tom) Tom->move(key);
	for (int i = 0; i < curnum; i++)
	{
		if (Autosprite[i])
		{
			if (Tom->collision(Autosprite[i]->getRect()))// check if tom collide with auto sprites
			{
				switch (Autosprite[i]->getScore())
				{
				case 1:
					playSound(ej, 0);  // play corresponding sound, 1 for jerry, 2 for heart, -1 for doy
					Tom->addScore();
					break;
				case 2:
					playSound(h, 0);
					Tom->addLife();
					break;
				case -1:
					playSound(et, 0);
					Tom->loseLife();
					break;
				default:
					break;
				}
				delete(Autosprite[i]);
				Autosprite[i] = NULL;
			}
		}
	}
	Gameover();
}

void timerEvent(int id)  // timerEvent to decide do what action on auto sprites: check collision or create new one
{
	int i = 0;
	switch (id)
	{
	case 0:
		for (i = 0; i < curnum; i++)
		{
			if (Autosprite[i])
			{
				Autosprite[i]->move(Tom->getRect());
				if (Tom->collision(Autosprite[i]->getRect()))
				{
					switch (Autosprite[i]->getScore())
					{
					case 1:
						playSound(ej, 0);
						Tom->addScore();
						break;
					case 2:
						playSound(h, 0);
						Tom->addLife();
						break;
					case -1:
						playSound(et, 0);
						Tom->loseLife();
						break;
					default:
						break;
						}
					delete(Autosprite[i]);
					Autosprite[i] = NULL;
				}
			}
		}
		break;
	case 1:
		if (curnum < maxNum)
		{
			create(Autosprite);
		}
		break;
	default:
		break;
	}
	Paint();
	Gameover();
}

void create(AutoSprite **autosprite)
{
	int jx, jy, jrx = 3, jry = 3;	// jerry
	int hx, hy, hrx = 2, hry = 2;	// heart
	int dx, dy, drx = 2, dry = 2;	// dog
	jx = rand() % winWidth - jerryWidth;
	if (jx < 0) jx = 0;
	jy = rand() % winHeight - jerryHeight;
	if (jy < 0)jy = 0;
	hx = rand() % winWidth - heartWidth;
	if (hx < 0) hx = 0;
	hy = rand() % winHeight - heartHeight;
	if (hy < 0) hy = 0;
	dx = rand() % winWidth - dogWidth;
	if (dx < 0) dx = 0;
	dy = rand() % winHeight - dogHeight;
	if (dy < 0)dy = 0;
	int t = rand() % 100;
	if (t <= 85)
		autosprite[curnum++] = new AutoSprite(jx, jy, jerryWidth, jerryHeight, jrx, jry, &jerryimg, WinRect, 1);
	else if(t>85&&t<=95)
		autosprite[curnum++] = new CatchSprite(dx, dy, dogWidth, dogHeight, drx, dry, &dogimg, WinRect, -1);
	else
		autosprite[curnum++] = new AvoidSprite(hx, hy, heartWidth, heartHeight, hrx, hry, &heartimg, WinRect, 2);
	Paint();
}

void create(UserSprite **usersprite)
{
	int x, y, rx = 5, ry = 5;
	x = rand() % winWidth - tomWidth;
	if (x < 0) x = 0;
	y = rand() % winHeight - tomHeight;
	if (y < 0)y = 0;
	*usersprite = new UserSprite(x, y, tomWidth, tomHeight, rx, ry, &tomimg, WinRect);
	Paint();
}

void Gameover()
{
	int l = Tom->getLife();
	if (l == 0)  // tom died
	{
		char str1[20];
		sprintf_s(str1, sizeof(str1), "You lost!");
		cancelTimer(timerid);
		cancelTimer(createid);
		stopSound(bk);
		beginPaint();
		setTextSize(50);
		setTextColor(color1);
		paintText(winWidth / 2 - 100, winHeight / 2 - 20, str1);
		endPaint();
	}
	else
	{
		int sco = Tom->getScore();
		if (sco == 50)  // get the target point
		{
			char str2[50];
			sprintf_s(str2, sizeof(str2), "Congratulations! You WIN!");
			cancelTimer(timerid);
			cancelTimer(createid);
			stopSound(bk);
			beginPaint();
			setTextSize(50);
			setTextColor(color);
			paintText(winWidth / 2 - 100, winHeight / 2 - 20, str2);
			endPaint();
		}
	}
}
