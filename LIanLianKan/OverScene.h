#pragma once
#include "Scene.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

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
	/*������*/
	std::vector<int> rank;
	/* ���洢/��ʾ�ķ�����¼���� */
	const int MAX_SCORES_NUM = 5;
public:
	OverScene(time_t t, int level) {
		sprintf_s(buff, 50, "%4llds", t);
		sprintf_s(background_pic, 50, "./Pic/endgame.png");

		
		std::ifstream fin;
		std::string fname = std::string{ "Level_" } + std::to_string(level) + std::string{ "_Rank.dat" };
		fin.open(fname.c_str());
		int score;
		while (true) {
			fin >> score;
			if (fin.eof())
				break;
			rank.push_back(score);
		}
		fin.close();
		rank.push_back(t);
		std::sort(rank.begin(), rank.end());

		std::ofstream fout;
		fout.open(fname.c_str());
		int i = 0;
		for (auto score : rank) {
			fout << score << std::endl;
			if (++i == MAX_SCORES_NUM) {
				break;
			}
		}
		fout.close();
	};
	void update();
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};
