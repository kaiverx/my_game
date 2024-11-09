#include "Game.h"
#include "iostream"

Game::Game() : playerActionPoints(1), enemyActionPoints(1), maxMovesPerTurn(6) {
    window.create(VideoMode(1920, 1080), "RPG Game");
    window.setFramerateLimit(60);

    player.setSize(Vector2f(50, 50)); // TILE_SIZE
    player.setFillColor(Color::Green);
    player.setPosition(2 * 50, 2 * 50); // TILE_SIZE

    playerHealthCircle.setRadius(70);
    playerHealthCircle.setFillColor(Color::Red);
    playerHealthCircle.setOutlineThickness(5);
    playerHealthCircle.setOutlineColor(Color::White);
    playerHealthCircle.setPosition(305, 885);
    playerMaxHealth = 100;
    playerHealth = 100;

    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Error loading font\n";
    }

    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(24);
    playerHealthText.setFillColor(Color::White);
    playerHealthText.setStyle(Text::Bold);
    playerHealthText.setPosition(320, 940);
    updateHealthText();

    endTurnButton.setRadius(70);
    endTurnButton.setOutlineThickness(5);
    endTurnButton.setOutlineColor(Color::White);
    endTurnButton.setFillColor(Color(0, 200, 0)); // Цвет кнопки
    endTurnButton.setPosition(1500, 885); // Позиция кнопки

    endTurnButtonText.setFont(font);
    endTurnButtonText.setString("End Turn");
    endTurnButtonText.setCharacterSize(24);
    endTurnButtonText.setStyle(Text::Bold);
    endTurnButtonText.setFillColor(Color::White);
    endTurnButtonText.setPosition(1515, 940); // Позиция текста

    createMap();

    mapShape.setSize(Vector2f(230, 230));
    mapShape.setFillColor(Color::White);
    mapShape.setPosition(0, 850);

    playerMovesLeft = maxMovesPerTurn;
    enemyMovesLeft = maxMovesPerTurn;
    playerTurn = true;

    // Настройка текста "Ваш ход"
    turnText.setFont(font);
    turnText.setString("YOUR TURN");
    turnText.setCharacterSize(100);
    turnText.setFillColor(Color::White);
    turnText.setStyle(Text::Bold);

    // Центрирование текста на игровом поле
    FloatRect textRect = turnText.getLocalBounds();
    turnText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    turnText.setPosition(GRID_WIDTH * TILE_SIZE / 2.0f, GRID_HEIGHT * TILE_SIZE / 2.0f);
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::createMap() {
    grid.resize(GRID_HEIGHT, vector<Tile>(GRID_WIDTH));
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            grid[y][x] = Tile(x, y);
        }
    }

    auto enemy = make_shared<Enemy>(5, 5);
    enemies.push_back(enemy);
    grid[5][5].hasEnemy = true;
    grid[5][5].isOccupied = true;
}

void Game::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::KeyPressed && playerTurn && playerMovesLeft > 0) {
            Vector2i moveDirection(0, 0);

            if (event.key.code == Keyboard::W) moveDirection.y = -1;
            if (event.key.code == Keyboard::S) moveDirection.y = 1;
            if (event.key.code == Keyboard::A) moveDirection.x = -1;
            if (event.key.code == Keyboard::D) moveDirection.x = 1;

            if (moveDirection.x != 0 || moveDirection.y != 0) {
                int newX = (player.getPosition().x / 50) + moveDirection.x; // TILE_SIZE
                int newY = (player.getPosition().y / 50) + moveDirection.y; // TILE_SIZE

                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT && !grid[newY][newX].isOccupied) {
                    player.setPosition(newX * 50, newY * 50); // TILE_SIZE
                    playerMovesLeft--;
                }
            }
        }

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (endTurnButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    endTurn();
                }
            }
        }
    }
}

void Game::endTurn() {
    playerTurn = false;
    enemyAction();
    playerMovesLeft = maxMovesPerTurn;
    playerTurn = true;

    // Отображение текста "Ваш ход" и сброс таймера
    showTurnText = true;
    turnTextTimer.restart();
}

void Game::enemyAction() {
    for (auto& enemy : enemies) {
        enemyMovesLeft = 4; // Устанавливаем максимальное количество ходов врага
        Vector2f playerPos = player.getPosition();
        Vector2f enemyPos = enemy->getShape().getPosition();

        while (enemyMovesLeft > 0) {
            Vector2f direction = playerPos - enemyPos;

            if (std::abs(direction.x) > std::abs(direction.y)) {
                // Двигаем по горизонтали
                direction.x = (direction.x > 0) ? TILE_SIZE : -TILE_SIZE;
                direction.y = 0;
            }
            else {
                // Двигаем по вертикали
                direction.y = (direction.y > 0) ? TILE_SIZE : -TILE_SIZE;
                direction.x = 0;
            }

            Vector2f newEnemyPos = enemyPos + direction;
            int newX = newEnemyPos.x / TILE_SIZE;
            int newY = newEnemyPos.y / TILE_SIZE;

            // Проверяем, что клетка свободна и находится в пределах сетки
            if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT && !grid[newY][newX].isOccupied) {
                enemy->setPosition(newX, newY);
                grid[static_cast<int>(enemyPos.y / TILE_SIZE)][static_cast<int>(enemyPos.x / TILE_SIZE)].hasEnemy = false;
                grid[newY][newX].hasEnemy = true;
                enemyPos = newEnemyPos;
                enemyMovesLeft--;
            }
            else {
                break; // Останавливаем движение, если ход невозможен
            }
        }
    }
    playerTurn = true; // Передача хода игроку
}


void Game::update() {
    updateHealthText();

    // Проверка таймера для скрытия текста "Ваш ход"
    if (showTurnText && turnTextTimer.getElapsedTime().asSeconds() > 1.0f) {
        showTurnText = false; // Скрыть текст через 1 секунду
    }
}


void Game::updateHealthText() {
    playerHealthText.setString(" " + to_string(playerHealth) + "/" + to_string(playerMaxHealth));
}

void Game::render() {
    window.clear();
    window.draw(mapShape);

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            window.draw(grid[y][x].shape);
        }
    }

    window.draw(player);
    for (const auto& enemy : enemies) {
        window.draw(enemy->getShape());
        window.draw(enemy->getHealthBar());
    }

    window.draw(endTurnButton);
    window.draw(endTurnButtonText);
    window.draw(playerHealthCircle);
    window.draw(playerHealthText);

    // Отображение текста "Ваш ход" по центру экрана
    if (showTurnText) {
        window.draw(turnText);
    }

    window.display();
}
