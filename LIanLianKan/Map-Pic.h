/*****************************************************************//**
 * \file   Map-Pic.h
 * \brief  Map���Pic�������
 * �ڴ�ͷ�ļ�����Map���Pic��
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/
#pragma once
#include<vector>
#include<list>
/**
 * ͼ����.
 * �洢ÿһ��Сͼ�����Ϣ
 */
class Pic{
private:
    /**
     * ͼ���ڵ�ͼ�е�����.
     */
    int x, y;
    /**
     * ͼ�������.
     * 0Ϊ�ϰ���
     * �������ֶ�Ӧĳ�ֿ��������ķ���
     */
    int kind;
    /**
     * �Ƿ�ɼ�.
     * һ��ͼ�걻������Ҫ����Ϊ���ɼ�
     */
    bool isVisible;
    /**
     * ����Ƿ��б߿�.
     * ��ѡ��ʱ����Ҫ�����߿���ʾ����
     */
    bool isStroke;
public:
    Pic(int _kind, int _x, int _y);

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    int getKind() const;

    bool getIsVisible() const;
    void setIsVisible(bool isVisible);

    bool getIsStroke() const;
    void setIsStroke(bool isStroke);

    bool getValid() const;

    void draw();

    bool operator<(const Pic& b);

    static int width, height;
};

/*��ͼ��С����*/
const int N = 100;

/**
 * ��ͼ��.
 */
class Map{
private:
    /**
     * ��ͼ��С.
     */
    int m, n;
    /**
     * ͼƬ��С.
     */

    /**
     * �洢��ͼ�е�ͼ��.
     * ����ָ��ķ�ʽ
     * ����֮��λ��(x,y)��Ӧ[(x-1)*n+y-1]
     */
    std::vector<Pic*>map;
    /**
     * �洢��ͼ�п���ƥ�������.
     * ����list+pair
     */

    std::list<std::pair<Pic*, Pic*> >matchedlist;
    bool canMatch(Pic*, Pic*, bool);
    Pic* getPicup(Pic* a);
    Pic* getPicdown(Pic* a);
    Pic* getPicleft(Pic* a);
    Pic* getPicright(Pic* a);
public:
    /*����m*n�ĵ�ͼ*/
    Map(int _m, int _n);
    /*���¸���matchedlist*/
    void updateMatchedlist();
    void updateMatchedlist(Pic*);
    /*��������*/
    void RandomOrder();
    /*�Ƿ���������*/
    bool isMatch(Pic* a, Pic* b);
    /*��ͼ���Ƿ��ܹ���*/
    bool anyMatch();
    /*���Ƶ�ͼ*/
    void draw();
    /*�������غ��������ݲ�����������������*/
    void drawMatchedLine(Pic* start, Pic* end); //�����յ���ͬһֱ����
    void drawMatchedLine(Pic* start, Pic* end, Pic* corner1);  //�����յ�֮�����һ�Σ�corner1Ϊ�����pic
    void drawMatchedLine(Pic* start, Pic* end, Pic* corner1, Pic* corner2);//�����յ�֮��������Σ�corner1��2Ϊ�����pic
};