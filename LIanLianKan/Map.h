/*******************************************************************
 * @file   Map-Pic.h
 * @brief  Map���Pic�������
 * �ڴ�ͷ�ļ�����Map���Pic��
 * @author FrogDar
 * @date   June 29 2020

 * @file Map.h
 * @change ����࣬��Map��Pic����Ϊ����ͷ�ļ�
 * @author wht
 * @date   June 30 2020
 *********************************************************************/
#pragma once
#include<vector>
#include<list>
#include "Pic.h"
#include "ConnectLine.h"


/*��ͼ��С����*/
const int N = 100;

/**
 * ��ͼ��.
 * @change ����һ��ConnectLine������get���� by wht
 * @date   June 30 2020
 */
class Map {
private:
	/**
	 * ��ͼ��С.
	 */
	int m, n;
	/**
	 * ͼƬ��С.
	 */



	 /**
	   * �洢���Ԫ�ص�������.
	  */
	ConnectLine* connect_line;


	/**
	 * �洢��ͼ�п���ƥ�������.
	 * ����list+pair
	 */

	std::list<std::pair<Pic*, Pic*> >matchedlist;

	/**
	 * �ж�a��b�Ƿ����������erase��ʾ�Ƿ�Ҫ����
	 */
	bool canMatch(Pic* a, Pic* b, bool erase);

	Pic* getPicup(Pic* a);
	Pic* getPicdown(Pic* a);
	Pic* getPicleft(Pic* a);
	Pic* getPicright(Pic* a);
public:
	/**
	 * �洢��ͼ�е�ͼ��.
	 * ����ָ��ķ�ʽ
	* ����֮��λ��(x,y)��Ӧ[x*n+y]
	*/
	std::vector<Pic*>map;
	/*����m*n�ĵ�ͼ*/
	Map(int _m, int _n);
	/*���¸���matchedlist*/
	void updateMatchedlist();
	void updateMatchedlist(Pic*);
	/*������ָ���get��set����*/
	void setConnectLine(ConnectLine* line_);
	ConnectLine* getConnectLine();
	/*��������*/
	void RandomOrder();
	/*�Ƿ���������*/
	bool isMatch(Pic* a, Pic* b);
	/*��ͼ���Ƿ��ܹ���*/
	bool anyMatch();
	/*���Ƶ�ͼ*/
	void draw();
	/*��ȡPicʮ����·�Ŀ���Pic*/
	void getAcross(Pic* aa, std::vector<Pic*>& v);
};