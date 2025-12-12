#ifndef GAMESTATE_H
#define GAMESTATE_H

enum GameScreen {
    SCREEN_MENU,
    SCREEN_PLAYING,
    SCREEN_GAMEOVER
};

class GameState {
private:
    int health;
    int score;
    bool gameOver;
    bool won;
    GameScreen currentScreen;

public:
    GameState();
    
    void takeDamage(int amount);
    void addScore(int points);
    void reset();
    void startGame();
    void endGame(bool didWin);
    
    int getHealth() const;
    int getScore() const;
    bool isGameOver() const;
    bool hasWon() const;
    GameScreen getScreen() const;
    void setScreen(GameScreen screen);
};

#endif
