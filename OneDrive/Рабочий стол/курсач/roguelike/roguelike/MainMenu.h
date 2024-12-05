#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
class MainMenu {
public:
    // ����������� ��������� ������ �� ���� � �����
    MainMenu();
    void runMenu();

private:
    RenderWindow window;   // ���� ��� ���������
    Font font;             // ����� ��� ������

    RectangleShape playButtonShape;
    RectangleShape exitButtonShape;
    RectangleShape liaderBoardButtonShape;
    RectangleShape howPlayButtonShape;

    Texture backgroundTexture; // �������� ��� ����
    Sprite backgroundSprite;   // ������ ��� ����

    FloatRect textBounds;
    FloatRect buttonBounds;

    Text howPlayButtonText;
    Text exitButtonText;
    Text liaderBoardButtonText;
    Text gameText;
    Text playButtonText;
    bool playing;               // ������ ����


    // ���������� �������
    void handleEvents();

    // ��������� �������� ����
    void render();

    // ���������� ������, ������ �� ������������ (������ ������)
    bool isPlaying() const;
};

#endif // MAINMENU_H
