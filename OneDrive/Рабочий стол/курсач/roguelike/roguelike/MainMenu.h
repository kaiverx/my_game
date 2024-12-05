#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
class MainMenu {
public:
    // Конструктор принимает ссылки на окно и шрифт
    MainMenu();
    void runMenu();

private:
    RenderWindow window;   // Окно для отрисовки
    Font font;             // Шрифт для кнопок

    RectangleShape playButtonShape;
    RectangleShape exitButtonShape;
    RectangleShape liaderBoardButtonShape;
    RectangleShape howPlayButtonShape;

    Texture backgroundTexture; // Текстура для фона
    Sprite backgroundSprite;   // Спрайт для фона

    FloatRect textBounds;
    FloatRect buttonBounds;

    Text howPlayButtonText;
    Text exitButtonText;
    Text liaderBoardButtonText;
    Text gameText;
    Text playButtonText;
    bool playing;               // Статус игры


    // Обработчик событий
    void handleEvents();

    // Отрисовка главного меню
    void render();

    // Возвращает статус, играет ли пользователь (кнопка нажата)
    bool isPlaying() const;
};

#endif // MAINMENU_H
