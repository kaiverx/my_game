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
	RenderWindow window;   // Окно для отрисовки
	Font font;             // Шрифт для кнопок

	Texture mageCharecterTexture; // Текстура для мага
	Sprite mageCharecterSprite;   // Спрайт для мага
	Texture warriorCharecterTexture; // Текстура для воина
	Sprite warriorCharecterSprite;   // Спрайт для воина
	Texture archerCharecterTexture; // Текстура для лучника
	Sprite archerCharecterSprite;   // Спрайт для лучник
	Texture thiefCharecterTexture; // Текстура для вора
	Sprite thiefCharecterSprite;   // Спрайт для ворa	

	Text chooseText;

	void render();
	void handleEvents();
};

#endif