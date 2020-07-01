#include "GameScene.h"
#include "Control.h"
#include "StartScene.h"
#include "SetScene.h"

static int count = 0;
extern Control* now;

/**
 * @brief Construct a new Game Scene:: Game Scene object
 * ����һ��m��n�еĵ�ͼ
 * @param m ��ͼx����ͼ�����
 * @param n ��ͼy����ͼ�����
 */
GameScene::GameScene(int m, int n)
{
	map = new Map{ m,n };

	map->setConnectLine(nullptr);
}

/**
 * @brief Destroy the Game Scene:: Game Scene object
 *
 */
GameScene::~GameScene()
{
	delete map;
}

/**
 * @brief ���»���
 * ��˳��ӵײ㵽������һ���»���
 */

void GameScene::update()
{
	/*���ƻ���ײ�*/
	now->putImage("./Pic/Game.png", 0, 0, 960, 640);
	/*���ƻ��水ť*/
	now->putImage("./Pic/Set/home.png", 890, 100, 50, 50);
	now->putImage("./Pic/Set/cogwheel.png", 890, 180, 50, 50);
	if (0 == now->pause)now->putImage("./Pic/Set/pause.png", 890, 260, 50, 50);
	if (1 == now->pause)now->putImage("./Pic/Set/play.png", 890, 260, 50, 50);
	now->putImage("./Pic/Set/blub.png", 890, 340, 50, 50);
	now->putImage("./Pic/Set/refresh.png", 890, 420, 50, 50);
	if (count < 10 && now->click != 0) {
		if (5 == now->click)now->putImage("./Pic/Set/blub_.png", 890, 340, 50, 50);
		if (6 == now->click)now->putImage("./Pic/Set/refresh_.png", 890, 420, 50, 50);
		count++;
	}
	if (10 == count) {
		count = 0;
		now->click = 0;
	}
	/*����ͼ�����*/
	if (map->anyMatch() == false)map->RandomOrder();
	map->draw();

	/*����ConnectLine*/

	/*��������µ�ConnectLine����*/
	auto conline = map->getConnectLine();
	if (conline != nullptr) {
		line_list.push_back(conline);
		map->setConnectLine(nullptr);
	}
	/*���Ƶ�ǰ����ConnectLine����*/
	if (line_list.empty() == false)
		for (auto line : line_list) {
			line->drawLine(now);
			line->cnt--;
		}
	/*����������ݵ�ConnectLine����*/
	while (line_list.empty() == false && line_list.front()->cnt == 0) {
		delete line_list.front();
		line_list.pop_front();
	}


}

/**
 * @brief �ж�������
 *
 * @param x �������x
 * @param y �������y
 */
void GameScene::onMouse(Sint32 x, Sint32 y)
{
	/*����ͼ����ж�*/
	int linearMousePositionOnMap = getMousePositionOnMap(x, y);
	if (linearMousePositionOnMap >= 0 && map->map[linearMousePositionOnMap]->getValid())
	{
		if(last==nullptr){
			/*���ǵ�һ�ΰ�ͼ�꣬��ͼ��ӿ�*/
			last = map->map[linearMousePositionOnMap];
			last->setIsStroke(true);
		}
		else if(map->isMatch(last, map->map[linearMousePositionOnMap])==false){
			/*����޷�ƥ�䣬���л��ӿ��ͼ��*/
			last->setIsStroke(false);
			last = map->map[linearMousePositionOnMap];
			last->setIsStroke(true);
		}else{
			/*������ƥ�䣬��ôҪ���last������������ƥ�亯���������*/
			last = nullptr;
		}
	//	printf("%d %d\n", map->map[linearMousePositionOnMap]->getX(), map->map[linearMousePositionOnMap]->getY());
	}

	/*���ܰ������ж�*/
	if (x >= 890 && x <= 940 && y >= 100 && y <= 150) {
		//���ﷵ�����˵�.
	}
	if (x >= 890 && x <= 940 && y >= 180 && y <= 230) {
		new SetScene(this);
	}
	if (x >= 890 && x <= 940 && y >= 260 && y <= 310) {
		now->pause = (now->pause + 1) % 2;
	}
	if (x >= 890 && x <= 940 && y >= 340 && y <= 390) {
		now->click = 5;
		//��������ʾ����.
	}
	if (x >= 890 && x <= 940 && y >= 420 && y <= 470) {
		now->click = 6;
		//���������Ź���.
	}
	if (1 == now->pause) {
		//��������ͣ����.
	}
	if (0 == now->pause) {
		//������ȡ����ͣ����.
	}
}

/*
*this function returns the index in map which represents the picture
*that has benn clicked.
*It returns **-1** if the spot that has been clicked is outside the map.
*/
int GameScene::getMousePositionOnMap(Sint32 x, Sint32 y)
{
	// how many pictures are there horizontally
	const int NUM_OF_HORIZONTAL_PICTURES = 16;
	// how many pictures are there vertically
	const int NUM_OF_VERTICAL_PICTURES = 13;

	// consider the map as a rectangle
	// this is the coordinate of the upper left corner
	const int MAP_START_POSOTION_X = 50;
	const int MAP_START_POSOTION_Y = 50;
	// this is the coordinate of the lower right corner
	const int MAP_END_POSOTION_X = 50 * (NUM_OF_HORIZONTAL_PICTURES);
	const int MAP_END_POSOTION_Y = 50 * (NUM_OF_VERTICAL_PICTURES);

	int ln, col;
	// return value
	int ret = -1;

	if ((x >= MAP_START_POSOTION_X)
		&& (y >= MAP_START_POSOTION_Y)
		&& (x <= MAP_END_POSOTION_X)
		&& (y <= MAP_END_POSOTION_Y))
	{
		ln = (y - MAP_START_POSOTION_Y) / Pic::height + 1; // line index
		col = (x - MAP_START_POSOTION_X) / Pic::width + 1; // column index

		// index in map to return
		ret = col * NUM_OF_VERTICAL_PICTURES + ln;
	}

	return ret;
}

