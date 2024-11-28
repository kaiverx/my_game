#include "Game.h"
#include <iostream>

Game::Game() : playerActionPoints(1), enemyActionPoints(1), maxMovesPerTurn(6) {
    window.create(VideoMode(1920, 1080), "RPG Game");
    window.setFramerateLimit(60);
    RectangleShape player;

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

    mageButton.setRadius(70);
    mageButton.setOutlineThickness(5);
    mageButton.setOutlineColor(Color::White);
    mageButton.setFillColor(Color(0, 200, 200)); // Цвет кнопки
    mageButton.setPosition(1700, 500); // Позиция кнопки

    warriorButton.setRadius(70);
    warriorButton.setOutlineThickness(5);
    warriorButton.setOutlineColor(Color::White);
    warriorButton.setFillColor(Color(200, 200, 0)); // Цвет кнопки
    warriorButton.setPosition(1700, 300); // Позиция кнопки

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

    isAttacking = false;  // По умолчанию атака не активна
    canAttack = true;
}

void Game::highlightAttackArea() {
    Vector2f playerPos = player->getPosition();

    // Получаем параметры атаки из объекта игрока
    int attackRadiusX = player->getAttackRangeX();  // Радиус атаки по оси X
    int attackRadiusY = player->getAttackRangeY();  // Радиус атаки по оси Y

    // В зависимости от направления атаки
    if (attackDirectionX == 1 && attackDirectionY == 0) {  // Горизонтальная атака вправо
        for (int i = 1; i <= attackRadiusX; ++i) {  // Создаём клетки по горизонтали
            for (int j = -attackRadiusY/2; j <= attackRadiusY/2; ++j) {  // Создаём клетки по вертикали
                int targetX = playerPos.x + i * TILE_SIZE;  // Смещаем по X
                int targetY = playerPos.y + j * TILE_SIZE;  // Смещаем по Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // Полупрозрачный красный
                    window.draw(highlightRect);
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == 1) {  // Вертикальная атака вниз
        for (int i = -attackRadiusY / 2; i <= attackRadiusY / 2; ++i) {  // Создаём клетки по горизонтали
            for (int j = 1; j <= attackRadiusX; ++j) {  // Создаём клетки по вертикали
                int targetX = playerPos.x + i * TILE_SIZE;  // Смещаем по X
                int targetY = playerPos.y + j * TILE_SIZE;  // Смещаем по Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // Полупрозрачный красный
                    window.draw(highlightRect);
                }
            }
        }
    }
    else if (attackDirectionX == -1 && attackDirectionY == 0) {  // Атака влево
        for (int i = 1; i <= attackRadiusX; ++i) {  // 3 клетки слева от игрока
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // 3 клетки по вертикали
                int targetX = playerPos.x - i * TILE_SIZE;  // Смещаем по X
                int targetY = playerPos.y - j * TILE_SIZE;  // Смещаем по Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // Полупрозрачный красный
                    window.draw(highlightRect);
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == -1) {  // Атака вверх
        for (int i = -attackRadiusY / 2; i <= attackRadiusY / 2; ++i) {  // Создаём клетки по горизонтали
            for (int j = 1; j <= attackRadiusX; ++j) {  // Создаём клетки по вертикали
                int targetX = playerPos.x + i * TILE_SIZE;  // Смещаем по X
                int targetY = playerPos.y - j * TILE_SIZE;  // Смещаем по Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // Полупрозрачный красный
                    window.draw(highlightRect);
                }
            }
        }
    }
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

    auto enemy = make_shared<Enemy>(5, 5, 1);
    enemies.push_back(enemy);
    grid[5][5].hasEnemy = true;
    grid[5][5].isOccupied = true;
}

void Game::chooseCharacter(int choice) {
    if (player != nullptr) {
        delete player;  // Удаляем старого персонажа
        player = nullptr; // Обнуляем указатель
    }

    if (choice == 1) {
        player = new Warrior(); // Создаем воина

    }
    else if (choice == 2) {
        player = new Mage();  // Создаем мага

    }

    // Настройка начальной позиции
    if (player) {
        player->setPosition(100, 100); // Устанавливаем позицию персонажа
    }
    updateHealthText();
}

void Game::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::KeyPressed && playerTurn && playerMovesLeft > 0) {
            Vector2i moveDirection(0, 0);

            // Управление движением игрока
            if (event.key.code == Keyboard::W) moveDirection.y = -1;
            if (event.key.code == Keyboard::S) moveDirection.y = 1;
            if (event.key.code == Keyboard::A) moveDirection.x = -1;
            if (event.key.code == Keyboard::D) moveDirection.x = 1;

            if (playerTurn && playerMovesLeft > 0 && player != nullptr) {
                int newX = (player->getPosition().x / TILE_SIZE) + moveDirection.x;
                int newY = (player->getPosition().y / TILE_SIZE) + moveDirection.y;

                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT && !grid[newY][newX].isOccupied) {
                    int oldX = player->getPosition().x / TILE_SIZE;
                    int oldY = player->getPosition().y / TILE_SIZE;
                    grid[oldY][oldX].isOccupied = false;

                    player->setPosition(newX * TILE_SIZE, newY * TILE_SIZE);
                    playerMovesLeft--;
                    grid[newY][newX].isOccupied = true;
                }
            }
        }

        // Управление направлением атаки с помощью стрелочек
        if (event.type == Event::KeyPressed && isPreparingAttack) {
            if (event.key.code == Keyboard::Up) {
                attackDirectionX = 0;
                attackDirectionY = -1;  // Направление вверх
            }
            else if (event.key.code == Keyboard::Down) {
                attackDirectionX = 0;
                attackDirectionY = 1;   // Направление вниз
            }
            else if (event.key.code == Keyboard::Left) {
                attackDirectionX = -1;
                attackDirectionY = 0;   // Направление влево
            }
            else if (event.key.code == Keyboard::Right) {
                attackDirectionX = 1;
                attackDirectionY = 0;   // Направление вправо
            }
        }

        // Проверка нажатия клавиши для атаки
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && playerTurn) {
            if (!isPreparingAttack) {
                // Первый этап: активируем подготовку к атаке
                isPreparingAttack = true;
                std::cout << "Подготовка к атаке." << std::endl;
            }
            else if (canAttack) {
                // Атакуем врага в выбранном направлении
                playerAttack();

                // Сброс состояния атаки
                isPreparingAttack = false;
                canAttack = false;
            }
        }

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);

                // Выбор персонажа
                if (mageButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    chooseCharacter(2);  // Выбираем мага
                }
                else if (warriorButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    chooseCharacter(1);  // Выбираем воина
                }

                if (endTurnButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    endTurn();
                }
            }
        }
    }
}

void Game::endTurn() {
    playerTurn = false;
    isPreparingAttack = false;
    enemyAction();
    playerMovesLeft = maxMovesPerTurn;
    canAttack = true;
    playerTurn = true;


    showTurnText = true;
    turnTextTimer.restart();
}

void Game::enemyAction() {
    // Получаем текущую позицию игрока в клетках
    sf::Vector2i playerPos(player->getPosition().x / TILE_SIZE, player->getPosition().y / TILE_SIZE);

    bool allEnemiesDefeated = true;
    std::vector<std::shared_ptr<Enemy>> aliveEnemies;

    // Проходим по всем врагам
    for (auto& enemy : enemies) {
        if (enemy && enemy->isAlive()) {
            allEnemiesDefeated = false;

            // Получаем текущую позицию врага
            sf::Vector2i enemyPos(enemy->getShape().getPosition().x / TILE_SIZE, enemy->getShape().getPosition().y / TILE_SIZE);

            // Находим путь врага к игроку
            std::vector<sf::Vector2i> path = enemy->findPath(grid, enemyPos, playerPos);

            int moves = 0;
            for (const auto& step : path) {
                if (moves >= 4) break;

                // Проверяем, свободна ли клетка для движения
                if (grid[step.y][step.x].isOccupied || grid[step.y][step.x].hasEnemy) {
                    continue;
                }

                // Освобождаем клетку, где был враг
                grid[enemyPos.y][enemyPos.x].hasEnemy = false;
                grid[enemyPos.y][enemyPos.x].isOccupied = false;

                // Перемещаем врага в новую клетку
                enemy->setPosition(step.x, step.y);

                // Отмечаем клетку как занятую
                grid[step.y][step.x].hasEnemy = true;
                grid[step.y][step.x].isOccupied = true;

                // Обновляем позицию врага
                enemyPos = step;
                moves++;
            }

            // Если враг рядом с игроком, атакуем
            if (std::abs(enemyPos.x - playerPos.x) <= 1 && std::abs(enemyPos.y - playerPos.y) <= 1) {
                player->takeDamage(enemy->getAttackPower());
            }

            // Проверяем, жив ли враг
            if (!enemy->isAlive()) {
                // Если враг мертв, освобождаем клетку
                grid[enemyPos.y][enemyPos.x].hasEnemy = false;
                grid[enemyPos.y][enemyPos.x].isOccupied = false;

                // Начисляем опыт игроку за победу над врагом
                onEnemyDefeated(enemy);
            }
            else {
                // Если враг жив, добавляем его в новый список
                aliveEnemies.push_back(enemy);
            }
        }
    }

    // Обновляем основной список врагов на новый
    enemies = aliveEnemies;

    // Если все враги побеждены, повышаем уровень игрока и спавним новых врагов
    if (allEnemiesDefeated) {
        player->levelUp();
        spawnEnemies(4);
    }
}

void Game::spawnEnemies(int count) {
    enemies.clear();  // Очищаем старых врагов

    for (int i = 0; i < count; ++i) {
        // Спавним врага в случайной позиции
        int x = rand() % GRID_WIDTH;
        int y = rand() % GRID_HEIGHT;

        // Убедимся, что клетка не занята
        while (grid[y][x].isOccupied || grid[y][x].hasEnemy) {
            x = rand() % GRID_WIDTH;
            y = rand() % GRID_HEIGHT;
        }

        // Создаем нового врага и добавляем в список
        auto enemy = make_shared<Enemy>(x, y, 1);  // Пример создания врага
        enemies.push_back(enemy);
        grid[y][x].hasEnemy = true;
        grid[y][x].isOccupied = true;
    }
}

void Game::onEnemyDefeated(std::shared_ptr<Enemy>& enemy) {
    int experienceGained = enemy->getLevel() * 10;  // Чем выше уровень врага, тем больше опыта
    player->gainExperience(experienceGained);
    std::cout << "Player gained " << experienceGained << " experience!" << std::endl;
}

void Game::update() {
    updateHealthText();

    if (showTurnText && turnTextTimer.getElapsedTime().asSeconds() > 1.0f) {
        showTurnText = false;
    }
}

void Game::updateHealthText() {
    if (player != nullptr) {
        playerHealthText.setString(" " + std::to_string(player->getHealth()) + "/" + std::to_string(player->getMaxHealth()));
    }
}

void Game::render() {
    window.clear();
    window.draw(mapShape);

    // Отрисовка тайлов через getShape
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            window.draw(grid[y][x].getShape());
        }
    }

    // Отрисовка игрока
    if (player != nullptr) {
        window.draw(*player);
    }

    // Отрисовка врагов
    for (const auto& enemy : enemies) {
        window.draw(enemy->getShape());
        window.draw(enemy->getHealthBar());
    }

    // Отрисовка области атаки
    if (player != nullptr & isPreparingAttack) {
        highlightAttackArea();  // Подсветка области атаки
    }

    // Отрисовка элементов интерфейса
    window.draw(endTurnButton);
    window.draw(endTurnButtonText);
    window.draw(playerHealthCircle);
    window.draw(playerHealthText);

    window.draw(mageButton);
    window.draw(warriorButton);

    if (showTurnText) {
        window.draw(turnText);
    }

    window.display();
}


void Game::playerAttack() {
    Vector2f playerPos = player->getPosition();

    // Получаем диапазоны для атаки
    int attackRadiusX = player->getAttackRangeX();  // Радиус атаки по оси X
    int attackRadiusY = player->getAttackRangeY();  // Радиус атаки по оси Y

    // В зависимости от направления атаки
    if (attackDirectionX == 1 && attackDirectionY == 0) {  // Горизонтальная атака вправо
        for (int i = 1; i <= attackRadiusX; ++i) {  // Создаём клетки по горизонтали
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // Создаём клетки по вертикали
                int targetX = (playerPos.x / TILE_SIZE) + i;  // Смещаем по X
                int targetY = (playerPos.y / TILE_SIZE) + j;  // Смещаем по Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // Атака по врагу
                        for (auto it = enemies.begin(); it != enemies.end(); /* не увеличиваем итератор в теле цикла */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // Удаление врага, если он мертв
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // Освобождаем клетку
                                    grid[targetY][targetX].isOccupied = false;  // Если есть флаг занятости
                                    it = enemies.erase(it);  // Удаляем врага из списка и получаем новый итератор
                                }
                                else {
                                    ++it;  // Если враг жив, продолжаем обход списка
                                }
                            }
                            else {
                                ++it;  // Враг не нацелился, продолжаем обход
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == 1) {  // Вертикальная атака вниз
        for (int i = -attackRadiusX / 2; i <= attackRadiusX / 2; ++i) {  // Создаём клетки по горизонтали
            for (int j = 1; j <= attackRadiusY; ++j) {  // Создаём клетки по вертикали
                int targetX = (playerPos.x / TILE_SIZE) + i;  // Смещаем по X
                int targetY = (playerPos.y / TILE_SIZE) + j;  // Смещаем по Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // Атака по врагу
                        for (auto it = enemies.begin(); it != enemies.end(); /* не увеличиваем итератор в теле цикла */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // Удаление врага, если он мертв
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // Освобождаем клетку
                                    grid[targetY][targetX].isOccupied = false;  // Если есть флаг занятости
                                    it = enemies.erase(it);  // Удаляем врага из списка и получаем новый итератор
                                }
                                else {
                                    ++it;  // Если враг жив, продолжаем обход списка
                                }
                            }
                            else {
                                ++it;  // Враг не нацелился, продолжаем обход
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == -1 && attackDirectionY == 0) {  // Атака влево
        for (int i = 1; i <= attackRadiusX; ++i) {  // Создаём клетки по горизонтали
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // Создаём клетки по вертикали
                int targetX = (playerPos.x / TILE_SIZE) - i;  // Смещаем по X
                int targetY = (playerPos.y / TILE_SIZE) + j;  // Смещаем по Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // Атака по врагу
                        for (auto it = enemies.begin(); it != enemies.end(); /* не увеличиваем итератор в теле цикла */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // Удаление врага, если он мертв
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // Освобождаем клетку
                                    grid[targetY][targetX].isOccupied = false;  // Если есть флаг занятости
                                    it = enemies.erase(it);  // Удаляем врага из списка и получаем новый итератор
                                }
                                else {
                                    ++it;  // Если враг жив, продолжаем обход списка
                                }
                            }
                            else {
                                ++it;  // Враг не нацелился, продолжаем обход
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == -1) {  // Атака вверх
        for (int i = -attackRadiusX / 2; i <= attackRadiusX / 2; ++i) {  // Создаём клетки по горизонтали
            for (int j = 1; j <= attackRadiusY; ++j) {  // Создаём клетки по вертикали
                int targetX = (playerPos.x / TILE_SIZE) + i;  // Смещаем по X
                int targetY = (playerPos.y / TILE_SIZE) - j;  // Смещаем по Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // Атака по врагу
                        for (auto it = enemies.begin(); it != enemies.end(); /* не увеличиваем итератор в теле цикла */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // Удаление врага, если он мертв
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // Освобождаем клетку
                                    grid[targetY][targetX].isOccupied = false;  // Если есть флаг занятости
                                    it = enemies.erase(it);  // Удаляем врага из списка и получаем новый итератор
                                }
                                else {
                                    ++it;  // Если враг жив, продолжаем обход списка
                                }
                            }
                            else {
                                ++it;  // Враг не нацелился, продолжаем обход
                            }
                        }
                    }
                }
            }
        }
    }
}




