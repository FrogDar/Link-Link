#include "StartScene.h"
#include "Control.h"
#include "GameScene.h"
#include "SetScene.h"
#include <iostream>
extern Control* now;
StartScene::StartScene()
{
	sprintf_s(background_pic, 50, "./Pic/startgame.png");
}
void StartScene::update()
{
	bgnow++;
	if (bgnow == 49)bgnow = 0;
	char* s = new char[50];
	sprintf_s(s, 50, "./Pic/bgvideo/bgvideo%02d.png", bgnow);
	now->putImage(s, 0, 0, 960, 640);
	delete[] s;
	now->putImage(background_pic, 0, 0, 960, 640);
}

void StartScene::onMouse(Sint32 x, Sint32 y)
{
	/*�жϿ�ʼ�˵��İ���.*/
	if (x >= 400 && x <= 560 && y >= 300 && y <= 350) {
		/*Ӧ��������ѡ�ؽ���.*/
		//now->scene = sence_select;
		now->scene = new GameScene(this, 14, 11);
	}
	if (x >= 400 && x <= 560 && y >= 360 && y <= 410) {
		/*Ӧ�ý������ý���.*/
		new SetScene(this);
	}
	if (x >= 400 && x <= 560 && y >= 430 && y <= 470) {
		/*Ӧ�ý�����ڽ���.*/
		//new AboutScene(this);
		//delete this;
	}
	if (x >= 400 && x <= 560 && y >= 490 && y <= 540) {
		/*Ӧ���˳�.*/
		now->setQuit(true);
	}
}

void StartScene::onMouseMotion(Sint32 x, Sint32 y)
{
	/*�ж����λ����ʾ��Ӧ�İ�ťͼƬ.*/
	if (x >= 400 && x <= 560 && y >= 300 && y <= 350) {
		/*��ʼ��Ϸ��ť.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke1.png");
	}
	else if (x >= 400 && x <= 560 && y >= 360 && y <= 410) {
		/*���ð�ť.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke2.png");
	}
	else if (x >= 400 && x <= 560 && y >= 430 && y <= 470) {
		/*���ڰ�ť.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke3.png");
	}
	else if (x >= 400 && x <= 560 && y >= 490 && y <= 540) {
		/*�˳���ť.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke4.png");
	}
	else {
		/*���������λ�ã�����ʾ��ť.*/
		sprintf_s(background_pic, 50, "./Pic/startgame.png");
	}
}