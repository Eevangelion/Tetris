#include "../objects/button/button.h"
#include "screen.h"
#include "../objects/tetromino/tetrominoGenerator.h"
#include <../SFML/Graphics.hpp>
#include <chrono>
#include <string>
#include <iostream>

class GameScreen : public Screen {
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Vector2u resolution;
    Button* pauseButton, *unpauseButton, *backToMainMenuButton;
    sf::Sprite pauseSprite;
    sf::Texture pauseTexture;
    sf::Text pausedTitle;
    sf::Font fontPaused;
    sf::Font pointsFont;
    sf::Text pointsTitle;
    int score;
    bool pauseState;
    TetrominoGenerator* generator;
    Tetromino* currentTetromino;
    std::chrono::high_resolution_clock::time_point lastTime;
    sf::Texture emptyBlockTexture, blockTexture;
    sf::Sprite** gameArea;
    bool** filled;
    int rounds;
    bool gameOver;
    sf::Text gameOverTitle;
    sf::Font fontGameOver;
public:
    GameScreen(sf::Vector2u screenResolution) {
        resolution = screenResolution;
        
        pauseButton = new Button(sf::String("models/button/buttonNormal.png"), 
                                sf::String("models/button/buttonClicked.png"), 
                                sf::String("PAUSE"), 
                                sf::Vector2f(0.85 * resolution.x, 0.88 * resolution.y), 
                                sf::Vector2f(0.15 * resolution.x, 0.12 * resolution.y));
        
        unpauseButton = new Button(sf::String("models/button/buttonNormal.png"), 
                                sf::String("models/button/buttonClicked.png"), 
                                sf::String("RETURN"), 
                                sf::Vector2f(2 * resolution.x / 5., resolution.y / 2.),
                                sf::Vector2f(resolution.x / 5., 1.5 * resolution.y / 16));
        
        backToMainMenuButton = new Button(sf::String("models/button/buttonNormal.png"),
                                sf::String("models/button/buttonClicked.png"),
                                sf::String("MAIN MENU"),
                                sf::Vector2f(2 * resolution.x / 5., 5 * resolution.y / 8.),
                                sf::Vector2f(resolution.x / 5., 1.5 * resolution.y / 16));
        
        backgroundTexture.loadFromFile("models/screens/mainMenuScreen.png");
        backgroundSprite = sf::Sprite(backgroundTexture);
        backgroundSprite.setScale(sf::Vector2f(resolution.x / backgroundSprite.getLocalBounds().width, resolution.y / backgroundSprite.getLocalBounds().height));
        
        pauseTexture.loadFromFile("models/screens/pause.png");
        pauseSprite = sf::Sprite(pauseTexture);
        pauseSprite.setScale(sf::Vector2f(3 / 7. * resolution.x / pauseSprite.getLocalBounds().width, 0.5 * resolution.y / pauseSprite.getLocalBounds().height));
        pauseSprite.setPosition((resolution.x - pauseSprite.getGlobalBounds().width) / 2, (resolution.y - pauseSprite.getGlobalBounds().height) / 2);
        pauseState = false;

        pointsFont.loadFromFile("fonts/arial.ttf");
        pointsTitle.setFont(pointsFont);
        pointsTitle.setCharacterSize(resolution.y / 20.);
        pointsTitle.setFillColor(sf::Color::White);
        pointsTitle.setPosition(7. * resolution.x / 10., resolution.y / 8.);
        score = 0;
        
        gameOver = false;
        fontGameOver.loadFromFile("fonts/UchronyRoman-Regular-FFP.ttf");
        gameOverTitle.setString("GAME OVER");
        gameOverTitle.setFont(fontGameOver);
        gameOverTitle.setCharacterSize(resolution.y / 3);
        gameOverTitle.setFillColor(sf::Color::White);
        gameOverTitle.setPosition((resolution.x - gameOverTitle.getGlobalBounds().width) / 2., resolution.y / 3);

        fontPaused.loadFromFile("fonts/UchronyRoman-Regular-FFP.ttf");
        pausedTitle.setString("Paused");
        pausedTitle.setFont(fontPaused);
        pausedTitle.setCharacterSize(resolution.y / 10.);
        pausedTitle.setFillColor(sf::Color::White);
        pausedTitle.setPosition((resolution.x - pausedTitle.getGlobalBounds().width) / 2., 2.5 * resolution.y / 8.);
        
        double blockSize = std::ceil(3 * resolution.x) / 100.0;

        generator = new TetrominoGenerator(sf::Vector2f(0.5 * resolution.x, (resolution.y - 0.6 * resolution.x) / 2 + 0.03 * resolution.x), 
                                        sf::Vector2f(blockSize, blockSize));
        
        emptyBlockTexture.loadFromFile("models/block/emptyBlock.png");
        blockTexture.loadFromFile("models/block/block.png");
        gameArea = new sf::Sprite*[20];
        filled = new bool*[20];
        for (int i = 0; i < 20; ++i) {
            gameArea[i] = new sf::Sprite[10];
            filled[i] = new bool[10];
        }
        gameArea[0][0].setPosition(sf::Vector2f(0.35 * resolution.x, (resolution.y - 0.6 * resolution.x) / 2.));
        
        for (int i = 0; i < 20; ++i) {
            if (i > 0) gameArea[i][0].setPosition(sf::Vector2f(gameArea[i - 1][0].getPosition().x, gameArea[i - 1][0].getPosition().y + blockSize));
            for (int j = 1; j < 10; ++j) {
                gameArea[i][j].setPosition(sf::Vector2f(gameArea[i][j - 1].getPosition().x + blockSize, gameArea[i][j - 1].getPosition().y));
            }
        }
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 10; ++j) {
                filled[i][j] = false;
                gameArea[i][j].setTexture(emptyBlockTexture);
                gameArea[i][j].setScale(sf::Vector2f(blockSize / gameArea[i][j].getLocalBounds().width, blockSize / gameArea[i][j].getLocalBounds().height));
            }
        }
        currentTetromino = nullptr;
        lastTime = std::chrono::high_resolution_clock::now();
        rounds = 0;
    }
    void refreshScreen(sf::RenderWindow&);
    void checkMouseMove(sf::Vector2f);
    short checkMouseClick(sf::Vector2f);
    bool getStateOfButton(short);
    void moveTetrominoLeft();
    void moveTetrominoRight();
    void rotateTetromino();
    void speedUp();
    void speedDown();
    sf::String checkClickedButtons();
    void changeStateOfPause();
    ~GameScreen() {
        for (int i = 0; i < 20; ++i) {
            if (gameArea[i]) delete[] gameArea[i];
            gameArea[i] = nullptr;
        }
        if (gameArea) delete[] gameArea;
        gameArea = nullptr;

        for (int i = 0; i < 20; ++i) {
            if (filled[i]) delete[] filled[i];
            filled[i] = nullptr;
        }
        if (filled) delete[] filled;
        filled = nullptr;

        delete pauseButton;
        delete unpauseButton;
        delete backToMainMenuButton;
        delete currentTetromino;
        delete generator;
    }
};

void GameScreen::refreshScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    // Background
    window.draw(backgroundSprite);

    // Button pause game
    window.draw(pauseButton->getSprite());
    window.draw(pauseButton->getText());

    // Game area
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            window.draw(gameArea[i][j]);
        }
    }
    pointsTitle.setString(sf::String("Score: " + std::to_string(score)));
    window.draw(pointsTitle);

    ++rounds;
    if (pauseState == false) {
        double speed = (currentTetromino ? currentTetromino->getSpeed() : 3.5);
        if (!gameOver && abs((speed + rounds / 30000.) * std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - lastTime).count() - 0.5) > 1e-10) {
            sf::Vector2i* coord = currentTetromino->getCoordinates();
            for (int i = 0; i < 4; ++i) {
                if (filled[coord[i].y][coord[i].x]) {
                    gameOver = true;
                    for (int j = 0; j < 4; ++j) 
                        if (coord[j].y >= 0 && !filled[coord[j].y][coord[j].x]) {
                            gameArea[coord[j].y][coord[j].x].setTexture(blockTexture);
                            filled[coord[j].y][coord[j].x] = true;
                        }
                    window.draw(gameOverTitle);
                    break;
                }
            }
            if (!gameOver) {
                currentTetromino->moveDown();
                coord = currentTetromino->getCoordinates();
                bool ok = true;
                for (int i = 0; i < 4; ++i) {
                    if (coord[i].y >= 20 || filled[coord[i].y][coord[i].x]) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) {
                    currentTetromino->moveUp();
                    coord = currentTetromino->getCoordinates();
                    for (int i = 0; i < 4; ++i) {
                        filled[coord[i].y][coord[i].x] = true;
                        gameArea[coord[i].y][coord[i].x].setTexture(blockTexture);
                    }
                    lastTime = std::chrono::high_resolution_clock::now();
                    currentTetromino = nullptr;

                    // check if there is a filled lines
                    int step = 0;
                    int summaryStep = 0;
                    for (int i = 19; i >= 0; --i) {
                        int count = 0;
                        for (int j = 0; j < 10; ++j) {
                            count += filled[i][j];
                        }
                        if (count == 10) ++step;
                        else if (summaryStep + step > 0) {
                            switch (step) {
                            case 1:score += 100;break;
                            case 2:score += 300;break;
                            case 3:score += 700;break;
                            case 4:score += 1500;break;
                            default: score += 0;
                            }
                            summaryStep += step;
                            step = 0;
                            for (int j = 0; j < 10; ++j) {
                                if (filled[i][j]) {
                                    gameArea[i + summaryStep][j].setTexture(blockTexture); 
                                }
                                else {
                                    gameArea[i + summaryStep][j].setTexture(emptyBlockTexture);
                                }
                                gameArea[i][j].setTexture(emptyBlockTexture);
                            }
                            delete[] filled[i + summaryStep];
                            std::swap(filled[i + summaryStep], filled[i]);
                            filled[i] = new bool[10];
                            for (int j = 0; j < 10; ++j) {
                                filled[i][j] = false;
                                gameArea[i][j].setTexture(emptyBlockTexture);
                            }
                        }
                    }
                    return;
                }
            }
            lastTime = std::chrono::high_resolution_clock::now();
        }
    }

    if (!gameOver) {
        if (currentTetromino) {
            sf::Sprite* blocks = currentTetromino->getSpriteBlocks();
            for (int i = 0; i < 4; ++i) window.draw(blocks[i]);
        }
    }
    else {
        window.draw(gameOverTitle);
    }
    // Pause sprite and buttons if paused
    if (pauseState == true) {
        window.draw(pauseSprite);
        window.draw(unpauseButton->getSprite());
        window.draw(unpauseButton->getText());
        window.draw(backToMainMenuButton->getSprite());
        window.draw(backToMainMenuButton->getText());
        window.draw(pausedTitle);
        lastTime = std::chrono::high_resolution_clock::now();
    }
    if (!currentTetromino) 
        currentTetromino = generator->nextTetromino();
}
void GameScreen::checkMouseMove(sf::Vector2f mouseCoord) {
    if (pauseState == false)
        pauseButton->checkMove(mouseCoord);
    else {
        unpauseButton->checkMove(mouseCoord);
        backToMainMenuButton->checkMove(mouseCoord);
    }
}

short GameScreen::checkMouseClick(sf::Vector2f mouseCoord) {
    if (pauseState == false) {
        if (pauseButton->checkMove(mouseCoord)) 
            return 0;
    }
    else {
        if (unpauseButton->checkMove(mouseCoord)) 
            return 1;
        if (backToMainMenuButton->checkMove(mouseCoord)) 
            return 2;
    }
    return 5;
}

bool GameScreen::getStateOfButton(short type) {
    switch (type) {
    case 0: 
        return !pauseState && pauseButton->getState();
        break;
    case 1:
        return pauseState && unpauseButton->getState();
    case 2:
        return pauseState && backToMainMenuButton->getState();
    default:
        return false;
        break;
    }
}


void GameScreen::moveTetrominoLeft() {
    if (!currentTetromino) return;
    currentTetromino->moveLeft();
    sf::Vector2i* coord = currentTetromino->getCoordinates(); 
    bool ok = true;
    for (int i = 0; i < 4; ++i) {
        if (coord[i].x < 0 || filled[coord[i].y][coord[i].x]) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        currentTetromino->moveRight();
    }
}

void GameScreen::moveTetrominoRight() {
    if (!currentTetromino) return;
    currentTetromino->moveRight();
    sf::Vector2i* coord = currentTetromino->getCoordinates(); 
    bool ok = true;
    for (int i = 0; i < 4; ++i) {
        if (coord[i].x >= 10 || filled[coord[i].y][coord[i].x]) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        currentTetromino->moveLeft();
    }
}

void GameScreen::rotateTetromino() {
    if (!currentTetromino) return;
    currentTetromino->rotate();
    sf::Vector2i* coord = currentTetromino->getCoordinates(); 
    bool ok = true;
    for (int i = 0; i < 4; ++i) {
        if (coord[i].x < 0 || coord[i].x >= 10 || coord[i].y < 0 || coord[i].y >= 20 || filled[coord[i].y][coord[i].x]) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        for (int i = 0; i < 3; ++i)
            currentTetromino->rotate();
    }
}
void GameScreen::speedUp() {
    if (currentTetromino)
        currentTetromino->speedUp();
}
void GameScreen::speedDown() {
    if (currentTetromino)
        currentTetromino->normalSpeed();
}

sf::String GameScreen::checkClickedButtons() {
    if (!pauseState && pauseButton->getState())
    {
        return "Pause";
    }
    if (pauseState && unpauseButton->getState()) 
    {
        return "Unpause";
    }
    if (pauseState && backToMainMenuButton->getState()) {
        return "Back to main menu";
    }
    return "Do nothing";
}

void GameScreen::changeStateOfPause() {
    pauseState = !pauseState;
    pauseButton->setState(false);
    unpauseButton->setState(false);
}

