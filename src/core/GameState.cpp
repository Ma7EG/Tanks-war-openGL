#include "GameState.h"
#include "Audio.h"

GameState::GameState() {
    reset();
    currentScreen = SCREEN_MENU;
}

void GameState::reset() {
    health = 100;
    score = 0;
    gameOver = false;
    won = false;
    currentScreen = SCREEN_MENU;
}

void GameState::startGame() {
    health = 100;
    score = 0;
    gameOver = false;
    won = false;
    currentScreen = SCREEN_PLAYING;
}

void GameState::endGame(bool didWin) {
    gameOver = true;
    won = didWin;
    currentScreen = SCREEN_GAMEOVER;
    Audio::stopBackgroundMusic();
    if (didWin) {
        Audio::playWinGame();
    } else {
        Audio::playGameOver();
    }
}

void GameState::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        endGame(false);
    }
}

void GameState::addScore(int points) {
    score += points;
    if (score >= 1000) {
        endGame(true);
    }
}

int GameState::getHealth() const {
    return health;
}

int GameState::getScore() const {
    return score;
}

bool GameState::isGameOver() const {
    return gameOver;
}

bool GameState::hasWon() const {
    return won;
}

GameScreen GameState::getScreen() const {
    return currentScreen;
}

void GameState::setScreen(GameScreen screen) {
    currentScreen = screen;
}
