#pragma once
#include "Scene.h"
#include <stdio.h>
class OverScene :
	public Scene
{
private:
	/*��̬�����ĵ�ǰ֡��.*/
	int bgnow = 0;
	/*�ݴ�UI��ťͼƬ·�����ַ�����.*/
	char* background_pic = new char[50];
	/*�ݴ�������ַ�����.*/
	char buff[50];
public:
	OverScene(time_t t) {
		sprintf_s(buff, 50, "%4llds", t);
		sprintf_s(background_pic, 50, "./Pic/endgame.png");
	};
	void update();
	void onMouse(Sint32 x, Sint32 y);
	void onMouseMotion(Sint32 x, Sint32 y);
};
