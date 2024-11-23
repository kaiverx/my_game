#include "Game.h"
#include <iostream>

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
        std::cout << "Error loading font\n";
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

    attackDamage = 20; // Урон, наносимый игроком

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

    // Создаем кнопку для удара
    attackButton.setRadius(40);
    attackButton.setPosition(700, 500); // Позиция кнопки на экране
    attackButton.setFillColor(Color::Red);
    attackButtonText.setString("Attack");
    attackButtonText.setFont(font);
    attackButtonText.setCharacterSize(20);
    attackButtonText.setFillColor(Color::White);
    attackButtonText.setPosition(710, 510); // Центрируем текст на кнопке

    isAttacking = false;  // По умолчанию атака не активна
    canAttack = true;
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
                int newX = (player.getPosition().x / TILE_SIZE) + moveDirection.x;
                int newY = (player.getPosition().y / TILE_SIZE) + moveDirection.y;

                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT && !grid[newY][newX].isOccupied) {
                    int oldX = player.getPosition().x / TILE_SIZE;
                    int oldY = player.getPosition().y / TILE_SIZE;
                    grid[oldY][oldX].isOccupied = false;

                    player.setPosition(newX * TILE_SIZE, newY * TILE_SIZE);
                    playerMovesLeft--;
                    grid[newY][newX].isOccupied = true;
                }
            }
        }

        if (event.key.code == Keyboard::Space && playerTurn && canAttack) {
            playerAttack();
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
    canAttack = true;
    playerTurn = true;

    showTurnText = true;
    turnTextTimer.restart();
}

void Game::enemyAction() {
    sf::Vector2i playerPos(player.getPosition().x / TILE_SIZE, player.getPosition().y / TILE_SIZE);

    for (auto& enemy : enemies) {
        if (enemy->isAlive()) {
            sf::Vector2i enemyPos(enemy->getShape().getPosition().x / TILE_SIZE, enemy->getShape().getPosition().y / TILE_SIZE);
            std::vector<sf::Vector2i> path = enemy->findPath(grid, enemyPos, playerPos);

            int moves = 0;
            for (const auto& step : path) {
                if (moves >= 4) break;

                if (grid[step.y][step.x].isOccupied || grid[step.y][step.x].hasEnemy) {
                    continue;
                }

                grid[enemyPos.y][enemyPos.x].hasEnemy = false;
                grid[enemyPos.y][enemyPos.x].isOccupied = false;

                enemy->setPosition(step.x, step.y);

                grid[step.y][step.x].hasEnemy = true;
                grid[step.y][step.x].isOccupied = true;

                enemyPos = step;
                moves++;
            }

            if (!enemy->isAlive()) {
                grid[enemyPos.y][enemyPos.x].hasEnemy = false;
                grid[enemyPos.y][enemyPos.x].isOccupied = false;
            }
        }
    }
}

void Game::update() {
    updateHealthText();

    if (showTurnText && turnTextTimer.getElapsedTime().asSeconds() > 1.0f) {
        showTurnText = false;
    }
}

void Game::updateHealthText() {
    playerHealthText.setString(" " + std::to_string(playerHealth) + "/" + std::to_string(playerMaxHealth));
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

    if (showTurnText) {
        window.draw(turnText);
    }

    window.display();
}

void Game::playerAttack() {
    if (!canAttack) return;

    int playerX = player.getPosition().x / TILE_SIZE;
    int playerY = player.getPosition().y / TILE_SIZE;

    // Используем итератор для безопасного удаления из вектора
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        RectangleShape shape = (*it)->getShape();
        int enemyX = shape.getPosition().x / TILE_SIZE;
        int enemyY = shape.getPosition().y / TILE_SIZE;

        if (abs(playerX - enemyX) <= 1 && abs(playerY - enemyY) <= 1) {
            (*it)->takeDamage(attackDamage); // Наносим урон

            if (!(*it)->isAlive()) { // Если враг умер
                // Освобождаем клетку
                grid[enemyY][enemyX].isOccupied = false;

                // Удаляем врага из списка
                it = enemies.erase(it);
            }
            else {
                ++it; // Переходим к следующему врагу
            }

            break; // Прерываем, так как атака возможна только по одному врагу за ход
        }
        else {
            ++it; // Переходим к следующему врагу
        }
    }

    canAttack = false;
}
