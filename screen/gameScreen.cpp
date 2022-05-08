#include "../objects/button/button.h"
#include "screen.h"
#include "../objects/tetromino/tetrominoGenerator.h"
#include <../SFML/Graphics.hpp>


class GameScreen : public Screen {
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Vector2u resolution;
    Button* pauseButton, *unpauseButton, *backToMainMenuButton;
    sf::Sprite pauseSprite;
    sf::Texture pauseTexture;
    sf::Text pausedTitle;
    sf::Font fontPaused;
    bool pauseState;
    TetrominoGenerator* generator;
    Tetromino* currentTetromino;
    double lastTime;
    sf::Texture emptyBlockTexture, blockTexture;
    sf::Sprite** gameArea;
    bool** filled;
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
        fontPaused.loadFromFile("fonts/UchronyRoman-Regular-FFP.ttf");
        pausedTitle.setString("Paused");
        pausedTitle.setFont(fontPaused);
        pausedTitle.setCharacterSize(resolution.y / 10.);
        pausedTitle.setFillColor(sf::Color::White);
        pausedTitle.setPosition((resolution.x - pausedTitle.getGlobalBounds().width) / 2., 2.5 * resolution.y / 8.);
        generator = new TetrominoGenerator(sf::Vector2f(0.5 * resolution.x, (resolution.y - 0.6 * resolution.x) / 2 + 0.6 * resolution.x / 20), 
                                        sf::Vector2f(0.03 * resolution.x, 0.03 * resolution.x));
        emptyBlockTexture.loadFromFile("models/block/emptyBlock.png");
        blockTexture.loadFromFile("models/block/block.png");
        gameArea = new sf::Sprite*[20];
        filled = new bool*[20];
        for (int i = 0; i < 20; ++i) {
            gameArea[i] = new sf::Sprite[10];
            filled[i] = new bool[10];
        }
        gameArea[0][0].setPosition(sf::Vector2f(0.35 * resolution.x, (resolution.y - 0.6 * resolution.x) / 2));
        for (int i = 0; i < 20; ++i) {
            if (i > 0) gameArea[i][0].setPosition(sf::Vector2f(gameArea[i - 1][0].getPosition().x, gameArea[i - 1][0].getPosition().y + 0.03 * resolution.x));
            for (int j = 1; j < 10; ++j) {
                gameArea[i][j].setPosition(sf::Vector2f(gameArea[i][j - 1].getPosition().x + 0.03 * resolution.x, gameArea[i][j - 1].getPosition().y));
            }
        }
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 10; ++j) {
                filled[i][j] = false;
                gameArea[i][j].setTexture(emptyBlockTexture);
                gameArea[i][j].setScale(sf::Vector2f(0.03 * resolution.x / gameArea[i][j].getLocalBounds().width, 0.03 * resolution.x / gameArea[i][j].getLocalBounds().height));
            }
        }
        currentTetromino = generator->nextTetromino();
        lastTime = time(0);
    }
    void refreshScreen(sf::RenderWindow&);
    void checkMouseMove(sf::Vector2f);
    short checkMouseClick(sf::Vector2f);
    bool getStateOfButton(short);
    void moveTetrominoLeft();
    void moveTetrominoRight();
    void rotateTetromino();
    sf::String checkClickedButtons();
    void changeStateOfPause();
    ~GameScreen() {}
};

void GameScreen::refreshScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    // Background
    window.draw(backgroundSprite);

    // Button pause game
    window.draw(pauseButton->getSprite());
    window.draw(pauseButton->getText());

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            window.draw(gameArea[i][j]);
        }
    }


    double currentTime = time(0);
    if (pauseState == false) {
        if (currentTime - lastTime >= 1.) {
            currentTetromino->moveDown();
            sf::Vector2i* coord = currentTetromino->getCoordinates();
            bool ok = true;
            for (int i = 0; i < 4; ++i) {
                if (coord[i].y >= 20 || filled[coord[i].y][coord[i].x]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                currentTetromino->moveUp();
                for (int i = 0; i < 4; ++i) {
                    filled[coord[i].y][coord[i].x] = true;
                    gameArea[coord[i].y][coord[i].x].setTexture(blockTexture);
                }
                lastTime = currentTime;
                currentTetromino = generator->nextTetromino();
                return;
            }
        }
    }
    lastTime = currentTime;
    sf::Sprite* blocks = currentTetromino->getSpriteBlocks();
    for (int i = 0; i < 4; ++i) window.draw(blocks[i]);
    // Pause sprite and buttons if paused
    if (pauseState == true) {
        window.draw(pauseSprite);
        window.draw(unpauseButton->getSprite());
        window.draw(unpauseButton->getText());
        window.draw(backToMainMenuButton->getSprite());
        window.draw(backToMainMenuButton->getText());
        window.draw(pausedTitle);
    }

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
    currentTetromino->moveLeft();
    sf::Vector2i* coord = currentTetromino->getCoordinates(); 
    bool ok = true;
    for (int i = 0; i < 4; ++i) {
        if (coord[i].x < 0) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        currentTetromino->moveRight();
    }
}

void GameScreen::moveTetrominoRight() {
    currentTetromino->moveRight();
    sf::Vector2i* coord = currentTetromino->getCoordinates(); 
    bool ok = true;
    for (int i = 0; i < 4; ++i) {
        if (coord[i].x >= 10) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        currentTetromino->moveLeft();
    }
}

void GameScreen::rotateTetromino() {
    currentTetromino->rotate();
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

