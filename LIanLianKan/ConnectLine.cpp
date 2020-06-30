/*******************************************************************

 * @file ConnectLine.cpp
 * @brief ConnectLine���ʵ���ļ�
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

#include "ConnectLine.h"

ConnectLine::ConnectLine(): number_of_corner{0},start{nullptr},end{nullptr},corner1{ nullptr }, corner2{ nullptr }
{
}

ConnectLine::ConnectLine(Pic* start_, Pic* end_)
{
	number_of_corner = 0;
	start = start_;
	end = end_;
	corner1 = nullptr;
	corner2 = nullptr;
	geneLine_rect(start,end,0);

}

ConnectLine::ConnectLine(Pic* start_, Pic* end_, Pic* corner1_)
{
	number_of_corner = 1;
	start = start_;
	end = end_;
	corner1 = corner1_;
	corner2 = nullptr;
	geneLine_rect(start, corner1, 0);
	geneLine_rect(corner1, end, 1);
}

ConnectLine::ConnectLine(Pic* start_, Pic* end_, Pic* corner1_, Pic* corner2_)
{
	number_of_corner = 2;
	start = start_;
	end = end_;
	corner1 = corner1_;
	corner2 = corner2_;
	geneLine_rect(start, corner1, 0);
	geneLine_rect(corner1, corner2, 1);
	geneLine_rect(corner2, end, 2);
}

ConnectLine::~ConnectLine()
{
	start->setIsVisible(false);
	delete start;
	end->setIsVisible(false);
	delete end;
	delete corner1;
	delete corner2;
}


/*������������յ㣬����line_rect�ṹ������ƾ��εľ������꣬index��ʾ����������±�*/
void ConnectLine::geneLine_rect(Pic* s, Pic* e, int index)
{
	int x1, x2, y1, y2;
	x1 = s->getX() * Pic::width + Pic::width / 2;
	y1 = s->getY() * Pic::height + Pic::height / 2;
	x2 = e->getX() * Pic::width + Pic::width / 2;
	y2 = e->getY() * Pic::height + Pic::height / 2;;
	if (x1 == x2) { //x������ȣ��߶δ�ֱ����
		if (y1 - y2 > 0) {
			line_rect[index].x = x2;
			line_rect[index].y = y2;
			line_rect[index].w = 5;
			line_rect[index].h = y1 - y2;
		}
		else {
			line_rect[index].x = x1;
			line_rect[index].y = y1;
			line_rect[index].w = 5;
			line_rect[index].h = y2 - y1;
		}
	}
	else {//y������ȣ��߶�ˮƽ����
		if (x1 - x2 > 0) {
			line_rect[index].x = x2;
			line_rect[index].y = y2;
			line_rect[index].w = x1 - x2;
			line_rect[index].h = 5;
		}
		else {
			line_rect[index].x = x1;
			line_rect[index].y = y1;
			line_rect[index].w = x2 - x1;
			line_rect[index].h = 5;
		}

	}
}

/*���������ߣ�line_rect�ڵľ������Ϊ3����������ȫ����Ⱦ����*/
void ConnectLine::drawLine(Control* now)
{
	for (auto i : line_rect) {
		SDL_SetRenderDrawColor(now->getRenderer(), 0, 74, 140, 255);
		SDL_Rect* pline = &i;
		SDL_RenderFillRect(now->getRenderer(), pline);
	}
}
