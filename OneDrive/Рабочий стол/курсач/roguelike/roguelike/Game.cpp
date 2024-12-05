#include "Game.h"
#include <iostream>
#include <random>  // ���������� ���������� ��� ������ �� ���������� �������


Game::Game() : playerActionPoints(1), enemyActionPoints(1){
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

    // ������������� ����� �������
    playerLVL.setFont(font);
    playerLVL.setString("PLAYER LVL: 1");
    playerLVL.setCharacterSize(16);
    playerLVL.setStyle(Text::Bold);
    playerLVL.setFillColor(Color::White);
    playerLVL.setPosition(700, 900); // ������� ������

    playerDMG.setFont(font);
    playerDMG.setString("DMG: 10");
    playerDMG.setCharacterSize(16);
    playerDMG.setStyle(Text::Bold);
    playerDMG.setFillColor(Color::White);
    playerDMG.setPosition(700, 980); // ������� ������

    playerHP.setFont(font);
    playerHP.setString("HP: 100");
    playerHP.setCharacterSize(16);
    playerHP.setStyle(Text::Bold);
    playerHP.setFillColor(Color::White);
    playerHP.setPosition(700, 940); // ������� ������

    enemyLVL.setFont(font);
    enemyLVL.setString("ENEMY LVL: 1");
    enemyLVL.setCharacterSize(16);
    enemyLVL.setStyle(sf::Text::Bold);
    enemyLVL.setFillColor(sf::Color::White);
    enemyLVL.setPosition(1725, 200);

    bossLvl.setFont(font);
    bossLvl.setString("BOSS LVL: 0");
    bossLvl.setCharacterSize(16);
    bossLvl.setStyle(sf::Text::Bold);
    bossLvl.setFillColor(sf::Color::White);
    bossLvl.setPosition(1725, 250);

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
    enemyLvlCount = 1;
    bossLvlCount = 0;
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


void Game::run(){

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
                if (endTurnButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    endTurn();
                }
            }
        }
    }
}

void Game::choosePerson(int choose) {
    if (choose == 1) {
        chooseCharacter(1);  // �������� �����
    }
    if (choose == 2) {
        chooseCharacter(2);  // �������� ����
    }
}

void Game::endTurn() {
    playerTurn = false;
    isPreparingAttack = false;
    enemyAction();
    // ������������� ���������� ���� ������ ������� ������������� ���������� �����
    if (player) { // ���������, ��� ��������� �� ����� nullptr
        playerMovesLeft = player->getMovesPerTurn();
    }
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
    // ������� ��������� ��������������� �����
    std::random_device rd;                  // �������� ����������� (seed)
    std::mt19937 gen(rd());                 // ��������� ��������������� �����
    std::uniform_int_distribution<> disX(0, GRID_WIDTH - 1);  // �������� ��� X
    std::uniform_int_distribution<> disY(0, GRID_HEIGHT - 1); // �������� ��� Y

    enemies.clear();  // ������� ������ ������
    enemyLvlCount += 1;

    if (enemyLvlCount % 5 == 0) {
        bossLvlCount += 1;

        // ���������� ��������� ���������� ��� �����
        int x = disX(gen);
        int y = disY(gen);

        // ��������, ��� ������ �� ������
        while (grid[y][x].isOccupied || grid[y][x].hasEnemy) {
            x = disX(gen);
            y = disY(gen);
        }

        // ������� ����� � ��������� � ������
        auto enemy = std::make_shared<Enemy>(5, 5, bossLvlCount, true);  // ������� �����
        enemy->levelUp();  // �������� ������� �����
        enemies.push_back(enemy);
        grid[y][x].hasEnemy = true;
        grid[y][x].isOccupied = true;
    }

    for (int i = 0; i < count; ++i) {
        // ���������� ��������� ���������� ��� �������� �����
        int x = disX(gen);
        int y = disY(gen);

        // ��������, ��� ������ �� ������
        while (grid[y][x].isOccupied || grid[y][x].hasEnemy) {
            x = disX(gen);
            y = disY(gen);
        }

        // ������� �������� ����� � ��������� � ������
        auto enemy = std::make_shared<Enemy>(x, y, enemyLvlCount);  // ������� �����
        enemies.push_back(enemy);
        grid[y][x].hasEnemy = true;
        grid[y][x].isOccupied = true;
    }

    updateEnemyLvlText();  // ��������� ����� ������ ������
}

void Game::onEnemyDefeated(std::shared_ptr<Enemy>& enemy) {
    int experienceGained = enemy->getLevel() * 10;  // ��� ���� ������� �����, ��� ������ �����
    player->gainExperience(experienceGained);
    std::cout << "Player gained " << experienceGained << " experience!" << std::endl;
}

void Game::update() {
    updateHealthText();
   if (player != nullptr) {
        playerLVL.setString("PLAYER LVL: " + std::to_string(player->getLevel()));
        playerDMG.setString("DMG: " + std::to_string(player->getAttackPower()));
        playerHP.setString("HP: " + std::to_string(player->getHealth()));
    }
    if (showTurnText && turnTextTimer.getElapsedTime().asSeconds() > 1.0f) {
        showTurnText = false;
    }
    // �������� �����, ���� ����� ������ 5 �������
    if (player != nullptr && player->getLevel() % 5 == 0 && !boss) {
        boss = std::make_shared<Enemy>(5, 5, 1, true);  // ������� ����� � ������� 1
        boss->levelUp();  // ����������� ������� �����, ���� �����
    }

    // ���� ���� ����������, ��������� ��� �������
    if (boss != nullptr) {
        boss->levelUp();
    }
}

void Game::updateHealthText() {
    if (player != nullptr) {
        playerHealthText.setString(" " + std::to_string(player->getHealth()) + "/" + std::to_string(player->getMaxHealth()));
    }
}

void Game::updateEnemyLvlText() {
    enemyLVL.setString("ENEMY LVL: " + std::to_string(enemyLvlCount));
    if (enemyLvlCount >= 5) {
        bossLvl.setString("BOSS LVL: " + std::to_string(bossLvlCount));
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
    // ������������ ����� ��������� �������
    window.draw(playerLVL); // ������� ������
    window.draw(playerDMG); // ���� ������
    window.draw(playerHP);  // ������� �������� ������
    window.draw(enemyLVL);
    window.draw(bossLvl);

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

    int attackDamage = player->getAttackDamage();

    // � ����������� �� ����������� �����
    if (attackDirectionX == 1 && attackDirectionY == 0) {  // �������������� ����� ������
        for (int i = 1; i <= attackRadiusX; ++i) {  // ������� �� ��� X
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // �� ��� Y
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
                                    grid[targetY][targetX].hasEnemy = false;
                                    grid[targetY][targetX].isOccupied = false;
                                    it = enemies.erase(it);  // ������� ����� �� ������
                                }
                                else {
                                    ++it;
                                }
                            }
                            else {
                                ++it;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == 1) {  // ������������ ����� ����
        for (int i = -attackRadiusY / 2; i <= attackRadiusY / 2; ++i) {  // �� ��� X
            for (int j = 1; j <= attackRadiusX; ++j) {  // �� ��� Y
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
                                    grid[targetY][targetX].hasEnemy = false;
                                    grid[targetY][targetX].isOccupied = false;
                                    it = enemies.erase(it);  // ������� ����� �� ������
                                }
                                else {
                                    ++it;
                                }
                            }
                            else {
                                ++it;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == -1 && attackDirectionY == 0) {  // ����� �����
        for (int i = 1; i <= attackRadiusX; ++i) {  // ������� �� ��� X
            for (int j = -attackRadiusY / 2; j <= attackRadiusY / 2; ++j) {  // �� ��� Y
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
                                    grid[targetY][targetX].hasEnemy = false;
                                    grid[targetY][targetX].isOccupied = false;
                                    it = enemies.erase(it);  // ������� ����� �� ������
                                }
                                else {
                                    ++it;
                                }
                            }
                            else {
                                ++it;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (attackDirectionX == 0 && attackDirectionY == -1) {  // ����� �����
        for (int i = -attackRadiusY / 2; i <= attackRadiusY / 2; ++i) {  // �� ��� X
            for (int j = 1; j <= attackRadiusX; ++j) {  // �� ��� Y
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
                                    grid[targetY][targetX].hasEnemy = false;
                                    grid[targetY][targetX].isOccupied = false;
                                    it = enemies.erase(it);  // ������� ����� �� ������
                                }
                                else {
                                    ++it;
                                }
                            }
                            else {
                                ++it;
                            }
                        }
                    }
                }
            }
        }
    }
} 
