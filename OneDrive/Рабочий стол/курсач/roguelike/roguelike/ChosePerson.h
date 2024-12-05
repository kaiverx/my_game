#ifndef CHOSEPERSON_H
#define CHOSEPERSON_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class ChosePerson {
public:
	ChosePerson();
	void runPerson();

private:
	RenderWindow window;   // ���� ��� ���������
	Font font;             // ����� ��� ������

	Texture mageCharecterTexture; // �������� ��� ����
	Sprite mageCharecterSprite;   // ������ ��� ����
	Texture warriorCharecterTexture; // �������� ��� �����
	Sprite warriorCharecterSprite;   // ������ ��� �����
	Texture archerCharecterTexture; // �������� ��� �������
	Sprite archerCharecterSprite;   // ������ ��� ������
	Texture thiefCharecterTexture; // �������� ��� ����
	Sprite thiefCharecterSprite;   // ������ ��� ���a	

	Text chooseText;

	void render();
	void handleEvents();
};

#endif