/*****************************************************************//**
 * \file   Map.cpp
 * \brief  Map�ඨ���ļ�
 * Map���Pic���и�����Ա�����ʵ��
 * \author FrogDar
 * @change ���Map��Pic�� by wht
 * \date   June 30 2020
 *********************************************************************/

#include "Map.h"
#include "Control.h"
extern Control* now;



std::pair<int, int> operator+(std::pair<int, int> op1, std::pair<int, int> op2)
{
	return std::pair{ op1.first + op2.first, op1.second + op2.second };
}

/**
 * ��ȡĳPic���Ϸ�Pic.
 *
 * \param a Pic����
 * \return  Pic�Ϸ���Pic������nullptr
 */
bool Map::canMatch(Pic* a, Pic* b, bool erase)
{
	if (a->getKind() != b->getKind())
		return false;

	// ��ֱ�����ӵ����
	if (a->getX() == b->getX()) {
		bool flag = true; // ����û���ϰ�
		for (int i = std::min(a->getY(), b->getY()) + 1; i < std::max(a->getY(), b->getY()); i++) {
			if (true == map[(a->getX() - 1) * n + (i - 1)]->getIsVisible()) {
				flag = false;
			}
		}
		if (true == flag) {
			if (erase)
				connect_line = new ConnectLine(a, b);
			return true;
		}
	}
	else if (a->getY() == b->getY()) {
		bool flag = true; // ����û���ϰ�
		for (int i = std::min(a->getX(), b->getX()) + 1; i < std::max(a->getX(), b->getX()); i++) {
			if (true == map[(i - 1) * n + (a->getY() - 1)]->getIsVisible()) {
				flag = false;
			}
		}
		if (true == flag) {
			if (erase)
				connect_line = new ConnectLine(a, b);
			return true;
		}
	}

	// ��a,b����ֱ�ӷ��ʵ�������
	std::list<std::pair<int, int>> a_accessible;
	std::list<std::pair<int, int>> b_accessible;
	// �ϡ��ҡ��¡��� �ĸ�����
	std::list<std::pair<int, int>> direction{ std::pair {0,-1},std::pair {1,0},std::pair {0,1},std::pair {-1,0} };
	// �ҵ�a����ֱ�ӷ��ʵ�������(ʮ��)
	for (auto dir : direction) {
		std::pair now{ a->getX(),a->getY() };
		while (true) {
			now = now + dir;
			// �ж��Ƿ�Խ��
			if (now.first == 0 || now.first == m + 1 || now.second == 0 || now.second == n + 1) {
				break;
			}
			// (i,j)Ԫ����map�е�(i-1)*n+(j-1)��
			Pic* now_pic = map[(now.first - 1) * n + (now.second - 1)];
			if (false == now_pic->getIsVisible()) {
				a_accessible.push_back(now);
			}
			else {
				break;
			}
		}
	}
	// �ҵ�b����ֱ�ӷ��ʵ�������(ʮ��)
	for (auto dir : direction) {
		std::pair now{ b->getX(),b->getY() };
		while (true) {
			now = now + dir;
			// �ж��Ƿ�Խ��
			if (now.first == 0 || now.first == m + 1 || now.second == 0 || now.second == n + 1) {
				break;
			}
			// (i,j)Ԫ����map�е�(j-1)*n+(i-1)��
			Pic* now_pic = map[(now.first - 1) * n + (now.second - 1)];
			if (false == now_pic->getIsVisible()) {
				b_accessible.push_back(now);
			}
			else {
				break;
			}
		}
	}

	// �ڹ�һ�ε����
	for (auto a_ : a_accessible)
		for (auto b_ : b_accessible)
			if (a_ == b_) {
				if (erase)
					connect_line = new ConnectLine(a, b, map[(a_.first - 1) * n + (a_.second - 1)]);
				return true;
			}

	// �۹����ε����
	for (auto a_ : a_accessible) {
		for (auto b_ : b_accessible) {
			// �ܷ�����ֱ�ߵı��
			bool flag = false;
			if (a_.first == b_.first) {
				flag = true; // �������ϰ�
				for (int i = std::min(a_.second, b_.second) + 1; i < std::max(a_.second, b_.second); i++) {
					if (true == map[(a_.first - 1) * n + (i - 1)]->getIsVisible()) {
						flag = false;
					}
				}
			}
			else if (a_.second == b_.second) {
				flag = true; // �������ϰ�
				for (int i = std::min(a_.first, b_.first) + 1; i < std::max(a_.first, b_.first); i++) {
					if (true == map[(i - 1) * n + (a_.second - 1)]->getIsVisible()) {
						flag = false;
					}
				}
			}

			if (flag == true) {
				if (erase)
					connect_line = new ConnectLine(a, b, map[(a_.first - 1) * n + (a_.second - 1)], map[(b_.first - 1) * n + (b_.second - 1)]);
				return true;
			}
		}
	}

	return false;
}

/**
 * ��ͼ��Ĺ��캯��
 * ����һ��m��n�еĵ�ͼ
 * \param _m  ��ͼ����
 * \param _n  ��ͼ����
 */
Map::Map(int _m, int _n) :m{ _m }, n{ _n }
{
	/*
	ÿ��ͼ����Ҫ�ɶԳ���
	�������������为�����������µ������ķ���
	ʵ�ֳɶԳ���
	*/
	int t{ 0 };
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			if (t > 0)t = -t;
			else t = now->getRand() % 20 + 1;
			map.push_back(new Pic{ abs(t),i,j });
		}
	RandomOrder();
}
/**
 * ����ƥ���б�ȫ�壩.
 * ö�����е�ԣ�һһ�ж����Ƿ��ܹ�����ƥ��
 */
void Map::updateMatchedlist()
{
	matchedlist.clear();
	for (unsigned int i = 0; i < map.size(); i++)
		for (unsigned int j = i + 1; j < map.size(); j++)
			if (map[i]->getValid() && map[j]->getValid() && canMatch(map[i], map[j], false))
				matchedlist.push_back(std::pair<Pic*, Pic*>{map[i], map[j]});
	matchedlist.unique();
}

/**
 * ����ƥ���б�ͨ��һ��Pic.
 * ����Pic������������Ч���ƥ����Ϣ
 * \param a ͨ����λ�ø���ƥ���б�
 */
void Map::updateMatchedlist(Pic* a)
{
	std::vector<Pic*>v;
	if (getPicup(a) != nullptr && getPicup(a)->getValid())v.push_back(getPicup(a));
	if (getPicdown(a) != nullptr && getPicdown(a)->getValid())v.push_back(getPicdown(a));
	if (getPicleft(a) != nullptr && getPicleft(a)->getValid())v.push_back(getPicleft(a));
	if (getPicright(a) != nullptr && getPicright(a)->getValid())v.push_back(getPicright(a));
	for (auto i : v)
		for (auto j : map)
			if (j->getValid() && i != j && canMatch(i, j, false))
				matchedlist.push_back(std::pair<Pic*, Pic*>{i, j});
	matchedlist.unique();
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

	// update map
	draw();

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
	auto p{ std::pair<Pic*,Pic*>{a,b} };
	for (auto i : matchedlist)
		if (i == p)return true;
	return false;
}

/**
 * �жϵ�ͼ���Ƿ��ܽ���ƥ��.
 * ͨ���ж�matchedlist�Ƿ�Ϊ�վͿ���֪����ͼ���Ƿ���ƥ��
 * \return �ܷ�ƥ��
 */
bool Map::anyMatch()
{
	return !matchedlist.empty();
}

/**
 * �滭��ͼ.
 * �滭��ͼ�е�ÿһ��ͼ��
 */
void Map::draw()
{
	for (auto p : map)p->draw();
}


Pic* Map::getPicup(Pic* a)
{
	if (a->getX() == 1) return nullptr;
	return map[n * (a->getX() - 2) + a->getY() - 1];
}

/**
 * ��ȡĳPic���·�Pic.
 *
 * \param a Pic����
 * \return  Pic�·���Pic������nullptr
 */
Pic* Map::getPicdown(Pic* a)
{
	if (a->getY() == m) return nullptr;
	return map[n * (a->getX()) + a->getY() - 1];
}

/**
 * ��ȡĳPic�����Pic.
 *
 * \param a Pic����
 * \return  Pic����Pic������nullptr
 */
Pic* Map::getPicleft(Pic* a)
{
	if (a->getY() == 1)return nullptr;
	return map[n * (a->getX() - 1) + a->getY() - 2];
}

/**
 * ��ȡĳPic���Ҳ�Pic.
 *
 * \param a Pic����
 * \return  Pic�Ҳ��Pic������nullptr
 */
Pic* Map::getPicright(Pic* a)
{
	if (a->getY() == n)return nullptr;
	return map[n * (a->getX() - 1) + a->getY()];
}

void Map::setConnectLine(ConnectLine* line_)
{
	connect_line = line_;
}

ConnectLine* Map::getConnectLine()
{
	return connect_line;
}