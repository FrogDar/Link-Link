/*******************************************************************
 * @file   ConnectLine.h
 * @brief  ConnectLine������
 * ConnectLine�����������ͷ�ļ�
 * �������ɺͻ����������Ԫ�ؼ��������
 * @author wht
 * @date   June 30 2020
**********************************************************************/
#pragma once
#include "Pic.h"
#include "Control.h"

class ConnectLine {
private:
	/*����������*/
	int number_of_corner;
	/*������Pic����*/
	Pic* start;
	Pic* end;
	Pic* corner1;
	Pic* corner2;
	/*�������þ��λ��ƣ����������ߵľ�����Ϣ*/
	SDL_Rect line_rect[3]{ 0 };
	/*����ʱ*/

public:
	/*�������غ��������ݲ�������ȷ������������*/
	ConnectLine();
	ConnectLine(Pic* start_, Pic* end_); //�����յ���ͬһֱ����
	ConnectLine(Pic* start_, Pic* end_, Pic* corner1_);  //�����յ�֮�����һ�Σ�corner1Ϊ�����
	ConnectLine(Pic* start_, Pic* end_, Pic* corner1_, Pic* corner2_); //�����յ�֮��������Σ�corner1��2Ϊ�����
	~ConnectLine();
	void geneLine_rect(Pic* s, Pic* e, int index);
	void drawLine(Control* now);
	bool has(Pic* a);
	int cnt = 5;
};