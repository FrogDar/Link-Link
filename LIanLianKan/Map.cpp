/*****************************************************************//**
 * \file   Map.cpp
 * \brief  Map�ඨ���ļ�
 * Map���Pic���и�����Ա������ʵ��
 * \author FrogDar
 * @change ���Map��Pic�� by wht
 * \date   June 30 2020
 *********************************************************************/

#include "Map.h"
#include "Control.h"
#include <algorithm>
extern Control* now;

void Map::getAcross(Pic* aa, std::vector<Pic*>& v, bool extend = false) {
	v.push_back(aa);
	Pic* a = nullptr;
	a = aa;
	while (getPicup(a) != nullptr && getPicup(a)->getIsVisible() == false) {
		a = getPicup(a);
		v.push_back(a);
	}
	//if(extend && getPicup(a)!=nullptr&&)
	a = aa;
	while (getPicdown(a) != nullptr && getPicdown(a)->getIsVisible() == false) {
		a = getPicdown(a);
		v.push_back(a);
	}
	a = aa;
	while (getPicleft(a) != nullptr && getPicleft(a)->getIsVisible() == false) {
		a = getPicleft(a);
		v.push_back(a);
	}
	a = aa;
	while (getPicright(a) != nullptr && getPicright(a)->getIsVisible() == false) {
		a = getPicright(a);
		v.push_back(a);
	}
}

/**
 * @brief �ж�����Pic�ܷ�ƥ�䣬������ConnectLine����
 *
 * @param a Pic1
 * @param b Pic2
 * @param erase �Ƿ�Ҫ����������ConnectLine����
 * @return true ����ƥ��
 * @return false ����ƥ��
 */
bool Map::canMatch(Pic* a, Pic* b, bool erase)
{
	/*���Դ��룺 �������nullptr˵���������������*/
	if (a == nullptr || b == nullptr)
	{
		printf("����nullptr\n");
		return false;
	}
	/*���ͼ������Ч�ģ���Ȼ�޷�ƥ��*/
	if (a->getValid() == false || b->getValid() == false)
		return false;
	/*���ͼ�겻��ͬһ����Ȼ��ƥ��*/
	if (a->getKind() != b->getKind())
		return false;
	/*���ͼ����ͬһ����Ҳ��ƥ��*/
	if (a == b)return false;

	/*��ȡ��a��bΪԴ��ġ�ʮ�ּܡ��ϵ�ͼ��*/
	std::vector<Pic*>access_a;
	std::vector<Pic*>access_b;
	getAcross(a, access_a);
	getAcross(b, access_b);

	/*����ʮ�ּ�ֱ���ཻ��0��1������*/
	for (auto i : access_a)
		for (auto j : access_b)
			if (i == j) {
				if (erase)
					connect_line = new ConnectLine{ a,b,i };
				return true;
			}

	/*����ʮ�ּ��м�ͨ���������ཻ����������*/
	for (auto i : access_a)
		for (auto j : access_b)
			/*x��ȣ���һ��ֱ��*/
			if (i->getX() == j->getX()) {
				Pic* begin; Pic* end;
				if (i->getY() < j->getY()) {
					begin = i; end = j;
				}
				else {
					begin = j; end = i;
				}
				bool flag = true;
				do {
					begin = getPicright(begin);
					if (begin != end && begin->getIsVisible() == true) {
						flag = false;
						break;
					}
				} while (begin != end);
				if (flag == true) {
					if (erase)
						connect_line = new ConnectLine{ a,b,i,j };
					return true;
				}
			}
	/*y��ȣ���һ��ֱ��*/
			else if (i->getY() == j->getY()) {
				Pic* begin; Pic* end;
				if (i->getX() < j->getX()) {
					begin = i; end = j;
				}
				else {
					begin = j; end = i;
				}
				bool flag = true;
				do {
					begin = getPicdown(begin);
					if (begin != end && begin->getIsVisible() == true) {
						flag = false;
						break;
					}
				} while (begin != end);
				if (flag == true) {
					if (erase)
						connect_line = new ConnectLine{ a,b,i,j };
					return true;
				}
			}

	/*û���ҵ�ƥ��*/
	return false;
}

/**
 * ��ͼ��Ĺ��캯��
 * ����һ��m��n�еĵ�ͼ
 * \param _m  ��ͼ����
 * \param _n  ��ͼ����
 */
Map::Map(int _m, int _n) :m{ _m + 2 }, n{ _n + 2 }
{
	/*
	ÿ��ͼ����Ҫ�ɶԳ���
	�������������为�����������µ������ķ���
	ʵ�ֳɶԳ���
	*/
	int t{ 0 };
	for (int i = 1; i <= _m; i++)
		for (int j = 1; j <= _n; j++) {
			if (t > 0)t = -t;
			else t = now->getRand() % 20 + 1;
			map.push_back(new Pic{ abs(t),i,j });
		}
	/*������ΧһȦ�����ڵġ��ڱ���*/
	for (int i = 0; i < m; i++) {
		map.push_back(new Pic{ -1,i,0 });
		map.back()->setIsVisible(false);
	}
	for (int i = 0; i < m; i++) {
		map.push_back(new Pic{ -1,i,_n + 1 });
		map.back()->setIsVisible(false);
	}
	for (int i = 1; i < n - 1; i++) {
		map.push_back(new Pic{ -1,0,i });
		map.back()->setIsVisible(false);
	}
	for (int i = 1; i < n - 1; i++) {
		map.push_back(new Pic{ -1,_m + 1,i });
		map.back()->setIsVisible(false);
	}
	for (unsigned int i = 0; i < map.size(); i++)
		for (unsigned int j = 0; j < map.size(); j++)
			if ((*map[j]) < (*map[i]))
				std::swap(map[i], map[j]);

	RandomOrder();
}

Map::~Map()
{
	for (auto i : map)
		delete i;
}

/**
 * ����ƥ���б�ȫ�壩.
 * ö�����е�ԣ�һһ�ж����Ƿ��ܹ�����ƥ��
 */
void Map::updateMatchedlist()
{
	matchedlist.clear();
	for (unsigned int i = 0; i < map.size(); i++)
		if (map[i]->getValid())
			for (unsigned int j = i + 1; j < map.size(); j++)
				if (map[j]->getValid())
					if (canMatch(map[i], map[j], false))
						matchedlist.push_back(std::pair<Pic*, Pic*>{map[i], map[j]});
	sort(matchedlist.begin(), matchedlist.end());
	matchedlist.erase(unique(matchedlist.begin(), matchedlist.end()), matchedlist.end());
	/*	for (auto i : matchedlist)
			printf("%d %d %d %d\n", i.first->getX(), i.first->getY(), i.second->getX(), i.second->getY());*/
}

/**
 * ����ƥ���б�ͨ��һ��Pic.
 * ����Pic������������Ч���ƥ����Ϣ
 * \param a ͨ����λ�ø���ƥ���б�
 */
void Map::updateMatchedlist(Pic* a)
{
	/*ɾ���ͱ�ͼ���йص�ƥ��*/
	for (auto it = matchedlist.begin(); it != matchedlist.end();)
		if (it->first == a || it->second == a)
			it = matchedlist.erase(it);
		else it++;

	/*̽Ѱ��ͼ���ܱߵĵ�*/
	std::vector<Pic*>v;
	if (getPicup(a) != nullptr)v.push_back(getPicup(a));
	if (getPicdown(a) != nullptr)v.push_back(getPicdown(a));
	if (getPicleft(a) != nullptr)v.push_back(getPicleft(a));
	if (getPicright(a) != nullptr)v.push_back(getPicright(a));
	for (auto i : v)
		if (i->getValid() && i->getIsStroke() == false)
			for (auto j : map)
				if (j->getValid() && i != j && canMatch(i, j, false))
					matchedlist.push_back(std::pair<Pic*, Pic*>{i, j});
	sort(matchedlist.begin(), matchedlist.end());
	matchedlist.erase(unique(matchedlist.begin(), matchedlist.end()), matchedlist.end());
	printf("---------\n");
	for (auto i : matchedlist)
		printf("%d %d %d %d\n", i.first->getX(), i.first->getY(), i.second->getX(), i.second->getY());
}

/**
 * �������
 *
 * ������������Pic��λ�ò������µ�MatchedList *
 */
void Map::RandomOrder()
{
	// used to store the index of all visible objects
	std::vector <int> visibleObjIdx;

	// store the index of all visible objects
	for (size_t i = 0; i < map.size(); i++)
	{
		if (map[i]->getIsVisible())
		{
			visibleObjIdx.push_back(i);
		}
	}

	// if there is no more than 2 objects left,
	// then there is no need for a rearrangement.
	if (visibleObjIdx.size() > 2)
	{
		for (size_t i = 0; i < visibleObjIdx.size(); i++)
		{
			Pic* tmpPic = nullptr;

			// generate two random numbers to determine which objects to swap
			int randomIdx1 = now->getRand() % visibleObjIdx.size();
			int randomIdx2 = now->getRand() % visibleObjIdx.size();
			int tmpX, tmpY;

			// swap X and Y
			tmpX = map[visibleObjIdx[randomIdx1]]->getX();
			map[visibleObjIdx[randomIdx1]]->setX(map[visibleObjIdx[randomIdx2]]->getX());
			map[visibleObjIdx[randomIdx2]]->setX(tmpX);

			tmpY = map[visibleObjIdx[randomIdx1]]->getY();
			map[visibleObjIdx[randomIdx1]]->setY(map[visibleObjIdx[randomIdx2]]->getY());
			map[visibleObjIdx[randomIdx2]]->setY(tmpY);

			// swap the indexes of two objects
			tmpPic = map[visibleObjIdx[randomIdx1]];
			map[visibleObjIdx[randomIdx1]] = map[visibleObjIdx[randomIdx2]];
			map[visibleObjIdx[randomIdx2]] = tmpPic;
		}
	}

	// update matched list
	updateMatchedlist();
}

/**
 * .�ж��Ƿ��ܹ�����
 * ͨ��Matchedlist�ж�����ͼ���Ƿ��ܹ�����������
 * \param a ͼ��1
 * \param b ͼ��2
 * \return  �Ƿ��ܹ�ƥ��
 */
bool Map::isMatch(Pic* a, Pic* b)
{
	auto p{ std::pair<Pic*,Pic*>{a,b} }, q{ std::pair<Pic*,Pic*>{b,a} };
	for (auto i = matchedlist.begin(); i != matchedlist.end(); i++)
		if (*i == p || *i == q) {
			this->canMatch(a, b, true);
			a->setIsStroke(true);
			b->setIsStroke(true);
			a->setIsVisible(false);
			b->setIsVisible(false);
			/*	updateMatchedlist(a);
				updateMatchedlist(b);*/
			matchedlist.clear();
			updateMatchedlist();
			a->setIsVisible(true);
			b->setIsVisible(true);
			return true;
		}
	return false;
}

/**
 * �жϵ�ͼ���Ƿ��ܽ���ƥ��.
 * ͨ���ж�matchedlist�Ƿ�Ϊ�վͿ���֪����ͼ���Ƿ���ƥ��
 * \return �ܷ�ƥ��
 */
bool Map::anyMatch()
{
	return !matchedlist.empty() || isWin();
}

/**
 * �滭��ͼ.
 * �滭��ͼ�е�ÿһ��ͼ��
 */
void Map::draw()
{
	for (auto p : map)p->draw();
}

void Map::openHelp()
{
	if (help.first != nullptr || help.second != nullptr)closeHelp();
	help = matchedlist.front();
	help.first->setIsStroke(true);
	help.second->setIsStroke(true);
}

void Map::closeHelp()
{
	help.first->setIsStroke(false);
	help.second->setIsStroke(false);
	help = { nullptr,nullptr };
}

bool Map::isWin()
{
	for (auto i : map)
		if (i->getIsVisible())return false;
	return true;
}

std::pair<Pic*, Pic*> Map::getFirstMatchedPair()
{
	return matchedlist.front();
}

/**
 * ��ȡĳPic���Ϸ�Pic.
 *
 * \param a Pic����
 * \return  Pic�Ϸ���Pic������nullptr
 */
Pic* Map::getPicup(Pic* a)
{
	if (a->getX() == 0) return nullptr;
	return map[n * (a->getX() - 1) + a->getY()];
}

/**
 * ��ȡĳPic���·�Pic.
 *
 * \param a Pic����
 * \return  Pic�·���Pic������nullptr
 */
Pic* Map::getPicdown(Pic* a)
{
	if (a->getX() == m - 1) return nullptr;
	return map[n * (a->getX() + 1) + a->getY()];
}

/**
 * ��ȡĳPic�����Pic.
 *
 * \param a Pic����
 * \return  Pic����Pic������nullptr
 */
Pic* Map::getPicleft(Pic* a)
{
	if (a->getY() == 0)return nullptr;
	return map[n * (a->getX()) + a->getY() - 1];
}

/**
 * ��ȡĳPic���Ҳ�Pic.
 *
 * \param a Pic����
 * \return  Pic�Ҳ��Pic������nullptr
 */
Pic* Map::getPicright(Pic* a)
{
	if (a->getY() == n - 1)return nullptr;
	return map[n * (a->getX()) + a->getY() + 1];
}

void Map::setConnectLine(ConnectLine* line_)
{
	connect_line = line_;
}

ConnectLine* Map::getConnectLine()
{
	return connect_line;
}