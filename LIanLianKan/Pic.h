#pragma once

/*********************************************************************
 * @file Pic.h
 * @brief Pic��������ļ�
 * @change ����࣬��Map��Pic����Ϊ����ͷ�ļ�
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

 /**
  * ͼ����.
  * �洢ÿһ��Сͼ�����Ϣ
  */
class Pic {
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