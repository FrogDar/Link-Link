#pragma once
#include "Scene.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

class OverScene : public Scene
{
private:
	/*�ݴ�UI��ťͼƬ·�����ַ�����.*/
	char* background_pic = new char[50];
	/*�ݴ�������ַ�����.*/
	char buff[50];
	/*������*/
	std::vector<int> rank;
	/* ���洢/��ʾ�ķ�����¼���� */
	const int MAX_SCORES_NUM = 5;
	/*�ϸ����������˵� */
	Scene* last_scene;
	/*�Ƿ�ʱ*/
	bool tle;
public:
	OverScene(Scene* last_scene_, time_t t, int level);
	void update();
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};
