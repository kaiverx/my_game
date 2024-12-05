#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

class Button
{
public:
    // Конструктор кнопки принимает текст, шрифт, координаты x и y для размещения
    Button(const std::string& text, sf::Font& font, float x, float y)
    {
        setlocale(LC_ALL, "RU");
        // Размер кнопки
        button.setSize(sf::Vector2f(200.f, 50.0f));
        // Позиция кнопки
        button.setPosition(x, y);
        // Цвет кнопки
        button.setFillColor(sf::Color::Blue);
        // Шрифт кнопки
        buttonText.setFont(font);
        // Текст кнопки
        buttonText.setString(text);
        // Размер шрифта
        buttonText.setCharacterSize(24);
        // Цвет текста
        buttonText.setFillColor(sf::Color::White);
        // Установка текста внутри кнопки
        buttonText.setPosition(x + (button.getSize().x - buttonText.getGlobalBounds().width) / 2, y + (button.getSize().y - buttonText.getGlobalBounds().height) / 2);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(button); // Отрисовываем прямоугольник кнопки
        window.draw(buttonText); // Отрисовываем текст
    }

    bool isClicked(sf::Vector2f mousePos)
    {
        // Проверка нахождения мыши внутри прямоугольника кнопки
        return button.getGlobalBounds().contains(mousePos);
    }
private:
    sf::RectangleShape button; // Прямоугольник
    sf::Text buttonText; // Текст кнопки
};



int main()
{
    setlocale(LC_ALL, "RU");
    sf::RenderWindow window(sf::VideoMode(800, 600), "Roguelike Game Menu");

    sf::Font font; // Объект шрифта
    if (!font.loadFromFile("ComicSans.ttf")) // Загружаем шрифт из файла
    {
        std::cerr << "Ошибка загрузки шрифта" << std::endl; // Если загрузка шрифта не удалась, вывод ошибки
        return -1; // Завершение программы с кодом ошибки -1
    }

    // Загрузка музыки
    /*sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("settings")) // Убедитесь, что путь к файлу правильный
    {
        std::cerr << "Ошибка загрузки музыки" << std::endl;
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();*/

    // Создание кнопок меню
    Button newGameButton("New Game", font, 300.0f, 200.0f); // Кнопка новой игры
    Button settingButton("Setting", font, 300.0f, 300.0f); // Кнопка настроек
    Button exitButton("Exit", font, 300.0f, 400.0f); // Кнопка выхода из игры

    // Перечисление состояния игры
    enum GameState { MENU, GAME, SETTINGS, EXIT };
    GameState gameState = MENU; // Начальное значение игры - меню

    // Основной цикл программы выполнение пока окно не закрыто
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) // Обработка событий
        {
            if (event.type == sf::Event::Closed) // Если событие - закрытие окна
                window.close(); // Закрытие окна

            if (event.type == sf::Event::MouseButtonPressed) // Если нажали кнопку мыши
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // Получение координат мыши
                if (gameState == MENU)
                {
                    if (newGameButton.isClicked(mousePos)) // Если нажата кнопка новой игры
                        gameState = GAME; // Смена состояния игры на GAME
                    if (settingButton.isClicked(mousePos)) // Если нажата кнопка настроек
                        gameState = SETTINGS; // Смена состояния игры на настройки
                    if (exitButton.isClicked(mousePos)) // Если нажата кнопка выхода из игры
                        window.close(); // Закрытие окна
                }
            }
        }

        window.clear(sf::Color::White); // Очистка окна в белый цвет

        if (gameState == MENU) // Если текущее состояние - меню
        {
            newGameButton.draw(window); // Отрисовка кнопки "New Game"
            settingButton.draw(window); // Отрисовка кнопки "Setting"
            exitButton.draw(window); // Отрисовка кнопки "Exit"
        }
        else if (gameState == GAME) // Если текущее состояние - игра
        {
            // Игра
            sf::Text gameText; // Объект текста
            gameText.setFont(font);
            gameText.setFillColor(sf::Color::Black);
            gameText.setCharacterSize(24);
            gameText.setPosition(100.0f, 100.0f);
            gameText.setString("Игра запущена, для возврата в меню нажмите ESC");
            window.draw(gameText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                gameState = MENU; // Смена состояния игры на меню
            }
        }
        else if (gameState == SETTINGS) // Если текущее состояние - настройки
        {
            // Текст настроек
            sf::Text settingText;
            settingText.setFont(font);
            settingText.setFillColor(sf::Color::Black);
            settingText.setCharacterSize(24);
            settingText.setPosition(100.0f, 100.0f);
            settingText.setString("Настройки запущены, для возврата в меню нажмите ESC");
            window.draw(settingText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                gameState = MENU; // Смена состояния игры на меню
            }
        }

        window.display(); // Отображаем окно
    }

    return 0;
}