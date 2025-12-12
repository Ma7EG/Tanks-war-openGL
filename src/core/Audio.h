#ifndef AUDIO_H
#define AUDIO_H

#include <windows.h>
#include <mmsystem.h>

class Audio {
public:
    static void playShot();
    static void playDamageHelicopter();
    static void playExplosion();
    static void playGameOver();
    static void playWinGame();
    static void playStartGame();
    static void playBackgroundMusic();
    static void stopBackgroundMusic();
};

#endif
