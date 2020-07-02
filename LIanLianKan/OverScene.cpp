#include "OverScene.h"
#include "Control.h"
#include "StartScene.h"
#include <SDL.h>
#include <SDL_image.h>

extern Control* now;

OverScene::OverScene(Scene* last_scene_, time_t t, int level) :last_scene{ last_scene_ } {
	if (now->level == level)now->level++;
	sprintf_s(buff, 50, "%4llds", t);
	sprintf_s(background_pic, 50, "./Pic/endgame.png");

	std::ifstream fin;
	std::string fname = std::string{ "./Level_" } +std::to_string(level) + std::string{ "_Rank.dat" };
	if (fs::exists(fname) == false) {
		std::ofstream fout(fname);
		if (fout) 	fout.close();
	}
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
}

void OverScene::update() {
	now->bgnow++;
	if (now->bgnow == 49)now->bgnow = 0;
	char* s = new char[50];
	sprintf_s(s, 50, "./Pic/bgvideo/bgvideo%02d.png", now->bgnow);
	now->putImage(s, 0, 0, 960, 640);
	delete[] s;
	now->putImage(background_pic, 0, 0, 960, 640);
	now->xyprintf(300, 300, buff, 40);

	int i = 0;
	for (auto score : rank) {
		now->xyprintf(700, 200 + i * 30, (std::to_string(score) + "s").c_str(), 40);
		if (++i == MAX_SCORES_NUM) {
			break;
		}
	}
}
void OverScene::onMouse(Sint32 x, Sint32 y) {
	/*�жϽ����˵��İ���.*/
	if (x >= 390 && x <= 580 && y >= 520 && y <= 570) {
		/*Ӧ�ûص�������.*/
		now->scene = last_scene;
		delete this;
	}
}

void OverScene::onMouseMotion(Sint32 x, Sint32 y)
{
	if (x >= 390 && x <= 580 && y >= 520 && y <= 570) {
		sprintf_s(background_pic, 50, "./Pic/endgame_stroke1.png");
	}
	else {
		sprintf_s(background_pic, 50, "./Pic/endgame.png");
	}
}