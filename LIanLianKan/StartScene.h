#pragma once

#include"Scene.h"

class StartScene :public Scene {
private:
	/*��̬�����ĵ�ǰ֡��.*/
	int bgnow = 0;
	/*�ݴ�UI��ťͼƬ·�����ַ�����.*/
	char* background_pic = new char[50];
public:
	using Scene::Scene;
	StartScene();
	~StartScene() = default;
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};
