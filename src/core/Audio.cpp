#include "Audio.h"

void Audio::playShot() {
    mciSendStringA("close shot", NULL, 0, NULL);
    mciSendStringA("open \"assets/shot.mp3\" type mpegvideo alias shot", NULL, 0, NULL);
    mciSendStringA("play shot", NULL, 0, NULL);
}

void Audio::playDamageHelicopter() {
    mciSendStringA("close damage", NULL, 0, NULL);
    mciSendStringA("open \"assets/damage_H.mp3\" type mpegvideo alias damage", NULL, 0, NULL);
    mciSendStringA("play damage", NULL, 0, NULL);
}

void Audio::playExplosion() {
    mciSendStringA("close explosion", NULL, 0, NULL);
    mciSendStringA("open \"assets/shot.mp3\" type mpegvideo alias explosion", NULL, 0, NULL);
    mciSendStringA("play explosion", NULL, 0, NULL);
}

void Audio::playGameOver() {
    mciSendStringA("close gameover", NULL, 0, NULL);
    mciSendStringA("open \"assets/game_over.mp3\" type mpegvideo alias gameover", NULL, 0, NULL);
    mciSendStringA("play gameover", NULL, 0, NULL);
}

void Audio::playWinGame() {
    mciSendStringA("close wingame", NULL, 0, NULL);
    mciSendStringA("open \"assets/win_game.mp3\" type mpegvideo alias wingame", NULL, 0, NULL);
    mciSendStringA("play wingame", NULL, 0, NULL);
}

void Audio::playStartGame() {
    mciSendStringA("close startgame", NULL, 0, NULL);
    mciSendStringA("open \"assets/Start_game1.mp3\" type mpegvideo alias startgame", NULL, 0, NULL);
    mciSendStringA("play startgame", NULL, 0, NULL);
}

void Audio::playBackgroundMusic() {
    mciSendStringA("close bgmusic", NULL, 0, NULL);
    mciSendStringA("open \"assets/music.mp3\" type mpegvideo alias bgmusic", NULL, 0, NULL);
    mciSendStringA("play bgmusic repeat", NULL, 0, NULL);
}

void Audio::stopBackgroundMusic() {
    mciSendStringA("stop bgmusic", NULL, 0, NULL);
    mciSendStringA("close bgmusic", NULL, 0, NULL);
}
