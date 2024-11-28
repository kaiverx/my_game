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
    endTurnButton.setFillColor(Color(0, 200, 0)); // ���� ������
    endTurnButton.setPosition(1500, 885); // ������� ������

    endTurnButtonText.setFont(font);
    endTurnButtonText.setString("End Turn");
    endTurnButtonText.setCharacterSize(24);
    endTurnButtonText.setStyle(Text::Bold);
    endTurnButtonText.setFillColor(Color::White);
    endTurnButtonText.setPosition(1515, 940); // ������� ������

    attackDamage = 20; // ����, ��������� �������

    mageButton.setRadius(70);
    mageButton.setOutlineThickness(5);
    mageButton.setOutlineColor(Color::White);
    mageButton.setFillColor(Color(0, 200, 200)); // ���� ������
    mageButton.setPosition(1700, 500); // ������� ������

    warriorButton.setRadius(70);
    warriorButton.setOutlineThickness(5);
    warriorButton.setOutlineColor(Color::White);
    warriorButton.setFillColor(Color(200, 200, 0)); // ���� ������
    warriorButton.setPosition(1700, 300); // ������� ������

    createMap();

    mapShape.setSize(Vector2f(230, 230));
    mapShape.setFillColor(Color::White);
    mapShape.setPosition(0, 850);

    playerMovesLeft = maxMovesPerTurn;
    enemyMovesLeft = maxMovesPerTurn;
    playerTurn = true;

    // ��������� ������ "��� ���"
    turnText.setFont(font);
    turnText.setString("YOUR TURN");
    turnText.setCharacterSize(100);
    turnText.setFillColor(Color::White);
    turnText.setStyle(Text::Bold);

    // ������������� ������ �� ������� ����
    FloatRect textRect = turnText.getLocalBounds();
    turnText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    turnText.setPosition(GRID_WIDTH * TILE_SIZE / 2.0f, GRID_HEIGHT * TILE_SIZE / 2.0f);

    isAttacking = false;  // �� ��������� ����� �� �������
    canAttack = true;
}

void Game::highlightAttackArea() {
    Vector2f playerPos = player->getPosition();

    // �������� ��������� ����� �� ������� ������
    int attackRadiusX = player->getAttackRangeX();  // ������ ����� �� ��� X
    int attackRadiusY = player->getAttackRangeY();  // ������ ����� �� ��� Y

    // � ����������� �� ����������� �����
    if (attackDirectionX == 1 && attackDirectionY == 0) {  // �������������� ����� ������
        for (int i = 1; i <= attackRadiusX; ++i) {  // ������ ������ �� �����������
            for (int j = -attackRadiusY/2; j <= attackRadiusY/2; ++j) {  // ������ ������ �� ���������
                int targetX = playerPos.x + i * TILE_SIZE;  // ������� �� X
                int targetY = playerPos.y + j * TILE_SIZE;  // ������� �� Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // �������������� �������
                    window.draw(highlightRect);
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == 1) {  // ������������ ����� ����
        for (int i = -attackRadiusY / 2; i <= attackRadiusY / 2; ++i) {  // ������ ������ �� �����������
            for (int j = 1; j <= attackRadiusX; ++j) {  // ������ ������ �� ���������
                int targetX = playerPos.x + i * TILE_SIZE;  // ������� �� X
                int targetY = playerPos.y + j * TILE_SIZE;  // ������� �� Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // �������������� �������
                    window.draw(highlightRect);
                }
            }
        }
    }
    else if (attackDirectionX == -1 && attackDirectionY == 0) {  // ����� �����
        for (int i = 1; i <= attackRadiusX; ++i) {  // 3 ������ ����� �� ������
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // 3 ������ �� ���������
                int targetX = playerPos.x - i * TILE_SIZE;  // ������� �� X
                int targetY = playerPos.y - j * TILE_SIZE;  // ������� �� Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // �������������� �������
                    window.draw(highlightRect);
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == -1) {  // ����� �����
        for (int i = -attackRadiusY / 2; i <= attackRadiusY / 2; ++i) {  // ������ ������ �� �����������
            for (int j = 1; j <= attackRadiusX; ++j) {  // ������ ������ �� ���������
                int targetX = playerPos.x + i * TILE_SIZE;  // ������� �� X
                int targetY = playerPos.y - j * TILE_SIZE;  // ������� �� Y
                if (targetX >= 0 && targetX < grid[0].size() * TILE_SIZE &&
                    targetY >= 0 && targetY < grid.size() * TILE_SIZE) {
                    RectangleShape highlightRect(Vector2f(TILE_SIZE, TILE_SIZE));
                    highlightRect.setPosition(targetX, targetY);
                    highlightRect.setFillColor(Color(255, 0, 0, 128));  // �������������� �������
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
        delete player;  // ������� ������� ���������
        player = nullptr; // �������� ���������
    }

    if (choice == 1) {
        player = new Warrior(); // ������� �����

    }
    else if (choice == 2) {
        player = new Mage();  // ������� ����

    }

    // ��������� ��������� �������
    if (player) {
        player->setPosition(100, 100); // ������������� ������� ���������
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

            // ���������� ��������� ������
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

        // ���������� ������������ ����� � ������� ���������
        if (event.type == Event::KeyPressed && isPreparingAttack) {
            if (event.key.code == Keyboard::Up) {
                attackDirectionX = 0;
                attackDirectionY = -1;  // ����������� �����
            }
            else if (event.key.code == Keyboard::Down) {
                attackDirectionX = 0;
                attackDirectionY = 1;   // ����������� ����
            }
            else if (event.key.code == Keyboard::Left) {
                attackDirectionX = -1;
                attackDirectionY = 0;   // ����������� �����
            }
            else if (event.key.code == Keyboard::Right) {
                attackDirectionX = 1;
                attackDirectionY = 0;   // ����������� ������
            }
        }

        // �������� ������� ������� ��� �����
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && playerTurn) {
            if (!isPreparingAttack) {
                // ������ ����: ���������� ���������� � �����
                isPreparingAttack = true;
                std::cout << "���������� � �����." << std::endl;
            }
            else if (canAttack) {
                // ������� ����� � ��������� �����������
                playerAttack();

                // ����� ��������� �����
                isPreparingAttack = false;
                canAttack = false;
            }
        }

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);

                // ����� ���������
                if (mageButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    chooseCharacter(2);  // �������� ����
                }
                else if (warriorButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    chooseCharacter(1);  // �������� �����
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
    // �������� ������� ������� ������ � �������
    sf::Vector2i playerPos(player->getPosition().x / TILE_SIZE, player->getPosition().y / TILE_SIZE);

    bool allEnemiesDefeated = true;
    std::vector<std::shared_ptr<Enemy>> aliveEnemies;

    // �������� �� ���� ������
    for (auto& enemy : enemies) {
        if (enemy && enemy->isAlive()) {
            allEnemiesDefeated = false;

            // �������� ������� ������� �����
            sf::Vector2i enemyPos(enemy->getShape().getPosition().x / TILE_SIZE, enemy->getShape().getPosition().y / TILE_SIZE);

            // ������� ���� ����� � ������
            std::vector<sf::Vector2i> path = enemy->findPath(grid, enemyPos, playerPos);

            int moves = 0;
            for (const auto& step : path) {
                if (moves >= 4) break;

                // ���������, �������� �� ������ ��� ��������
                if (grid[step.y][step.x].isOccupied || grid[step.y][step.x].hasEnemy) {
                    continue;
                }

                // ����������� ������, ��� ��� ����
                grid[enemyPos.y][enemyPos.x].hasEnemy = false;
                grid[enemyPos.y][enemyPos.x].isOccupied = false;

                // ���������� ����� � ����� ������
                enemy->setPosition(step.x, step.y);

                // �������� ������ ��� �������
                grid[step.y][step.x].hasEnemy = true;
                grid[step.y][step.x].isOccupied = true;

                // ��������� ������� �����
                enemyPos = step;
                moves++;
            }

            // ���� ���� ����� � �������, �������
            if (std::abs(enemyPos.x - playerPos.x) <= 1 && std::abs(enemyPos.y - playerPos.y) <= 1) {
                player->takeDamage(enemy->getAttackPower());
            }

            // ���������, ��� �� ����
            if (!enemy->isAlive()) {
                // ���� ���� �����, ����������� ������
                grid[enemyPos.y][enemyPos.x].hasEnemy = false;
                grid[enemyPos.y][enemyPos.x].isOccupied = false;

                // ��������� ���� ������ �� ������ ��� ������
                onEnemyDefeated(enemy);
            }
            else {
                // ���� ���� ���, ��������� ��� � ����� ������
                aliveEnemies.push_back(enemy);
            }
        }
    }

    // ��������� �������� ������ ������ �� �����
    enemies = aliveEnemies;

    // ���� ��� ����� ���������, �������� ������� ������ � ������� ����� ������
    if (allEnemiesDefeated) {
        player->levelUp();
        spawnEnemies(4);
    }
}

void Game::spawnEnemies(int count) {
    enemies.clear();  // ������� ������ ������

    for (int i = 0; i < count; ++i) {
        // ������� ����� � ��������� �������
        int x = rand() % GRID_WIDTH;
        int y = rand() % GRID_HEIGHT;

        // ��������, ��� ������ �� ������
        while (grid[y][x].isOccupied || grid[y][x].hasEnemy) {
            x = rand() % GRID_WIDTH;
            y = rand() % GRID_HEIGHT;
        }

        // ������� ������ ����� � ��������� � ������
        auto enemy = make_shared<Enemy>(x, y, 1);  // ������ �������� �����
        enemies.push_back(enemy);
        grid[y][x].hasEnemy = true;
        grid[y][x].isOccupied = true;
    }
}

void Game::onEnemyDefeated(std::shared_ptr<Enemy>& enemy) {
    int experienceGained = enemy->getLevel() * 10;  // ��� ���� ������� �����, ��� ������ �����
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

    // ��������� ������ ����� getShape
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            window.draw(grid[y][x].getShape());
        }
    }

    // ��������� ������
    if (player != nullptr) {
        window.draw(*player);
    }

    // ��������� ������
    for (const auto& enemy : enemies) {
        window.draw(enemy->getShape());
        window.draw(enemy->getHealthBar());
    }

    // ��������� ������� �����
    if (player != nullptr & isPreparingAttack) {
        highlightAttackArea();  // ��������� ������� �����
    }

    // ��������� ��������� ����������
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

    // �������� ��������� ��� �����
    int attackRadiusX = player->getAttackRangeX();  // ������ ����� �� ��� X
    int attackRadiusY = player->getAttackRangeY();  // ������ ����� �� ��� Y

    // � ����������� �� ����������� �����
    if (attackDirectionX == 1 && attackDirectionY == 0) {  // �������������� ����� ������
        for (int i = 1; i <= attackRadiusX; ++i) {  // ������ ������ �� �����������
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // ������ ������ �� ���������
                int targetX = (playerPos.x / TILE_SIZE) + i;  // ������� �� X
                int targetY = (playerPos.y / TILE_SIZE) + j;  // ������� �� Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // ����� �� �����
                        for (auto it = enemies.begin(); it != enemies.end(); /* �� ����������� �������� � ���� ����� */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // �������� �����, ���� �� �����
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // ����������� ������
                                    grid[targetY][targetX].isOccupied = false;  // ���� ���� ���� ���������
                                    it = enemies.erase(it);  // ������� ����� �� ������ � �������� ����� ��������
                                }
                                else {
                                    ++it;  // ���� ���� ���, ���������� ����� ������
                                }
                            }
                            else {
                                ++it;  // ���� �� ���������, ���������� �����
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == 1) {  // ������������ ����� ����
        for (int i = -attackRadiusX / 2; i <= attackRadiusX / 2; ++i) {  // ������ ������ �� �����������
            for (int j = 1; j <= attackRadiusY; ++j) {  // ������ ������ �� ���������
                int targetX = (playerPos.x / TILE_SIZE) + i;  // ������� �� X
                int targetY = (playerPos.y / TILE_SIZE) + j;  // ������� �� Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // ����� �� �����
                        for (auto it = enemies.begin(); it != enemies.end(); /* �� ����������� �������� � ���� ����� */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // �������� �����, ���� �� �����
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // ����������� ������
                                    grid[targetY][targetX].isOccupied = false;  // ���� ���� ���� ���������
                                    it = enemies.erase(it);  // ������� ����� �� ������ � �������� ����� ��������
                                }
                                else {
                                    ++it;  // ���� ���� ���, ���������� ����� ������
                                }
                            }
                            else {
                                ++it;  // ���� �� ���������, ���������� �����
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == -1 && attackDirectionY == 0) {  // ����� �����
        for (int i = 1; i <= attackRadiusX; ++i) {  // ������ ������ �� �����������
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // ������ ������ �� ���������
                int targetX = (playerPos.x / TILE_SIZE) - i;  // ������� �� X
                int targetY = (playerPos.y / TILE_SIZE) + j;  // ������� �� Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // ����� �� �����
                        for (auto it = enemies.begin(); it != enemies.end(); /* �� ����������� �������� � ���� ����� */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // �������� �����, ���� �� �����
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // ����������� ������
                                    grid[targetY][targetX].isOccupied = false;  // ���� ���� ���� ���������
                                    it = enemies.erase(it);  // ������� ����� �� ������ � �������� ����� ��������
                                }
                                else {
                                    ++it;  // ���� ���� ���, ���������� ����� ������
                                }
                            }
                            else {
                                ++it;  // ���� �� ���������, ���������� �����
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == -1) {  // ����� �����
        for (int i = -attackRadiusX / 2; i <= attackRadiusX / 2; ++i) {  // ������ ������ �� �����������
            for (int j = 1; j <= attackRadiusY; ++j) {  // ������ ������ �� ���������
                int targetX = (playerPos.x / TILE_SIZE) + i;  // ������� �� X
                int targetY = (playerPos.y / TILE_SIZE) - j;  // ������� �� Y
                if (targetX >= 0 && targetX < GRID_WIDTH && targetY >= 0 && targetY < GRID_HEIGHT) {
                    if (grid[targetY][targetX].hasEnemy) {
                        // ����� �� �����
                        for (auto it = enemies.begin(); it != enemies.end(); /* �� ����������� �������� � ���� ����� */) {
                            auto& enemy = *it;
                            if (enemy->getShape().getPosition().x / TILE_SIZE == targetX &&
                                enemy->getShape().getPosition().y / TILE_SIZE == targetY) {
                                enemy->takeDamage(attackDamage);
                                // �������� �����, ���� �� �����
                                if (!enemy->isAlive()) {
                                    grid[targetY][targetX].hasEnemy = false;  // ����������� ������
                                    grid[targetY][targetX].isOccupied = false;  // ���� ���� ���� ���������
                                    it = enemies.erase(it);  // ������� ����� �� ������ � �������� ����� ��������
                                }
                                else {
                                    ++it;  // ���� ���� ���, ���������� ����� ������
                                }
                            }
                            else {
                                ++it;  // ���� �� ���������, ���������� �����
                            }
                        }
                    }
                }
            }
        }
    }
}




