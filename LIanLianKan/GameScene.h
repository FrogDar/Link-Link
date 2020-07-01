#pragma once

#include"Scene.h"
#include"Map.h"
#include"Pic.h"
#include <ctime>

class GameScene :public Scene {
private:
	Map* map = nullptr;
	Pic* last = nullptr;
	time_t counterTime_start;
	time_t counterTime_stop;
	time_t counterTimePause_start;
	time_t counterTimePause_stop;
	time_t timer = 0;
	/*
	0 = counter stopped
	1 = counter started
	2 = counter paused
	*/
	int counterStatus = 0;
public:
	GameScene(int m, int n);
	~GameScene();
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	int getMousePositionOnMap(Sint32 x, Sint32 y);
	void startCounter();
	void stopCounter();
	void pauseCounter();
	time_t getTimer();
};
