#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#include "Transform.h"
#include "Mountain.h"
#include "Building.h"
#include "Cloud.h"
#include "Tree.h"
#include "Ground.h"
#include "Background.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Audio.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int GROUND_HEIGHT = 88;

// Game objects
GameState gameState;
Player player(150, GROUND_HEIGHT + 20);
std::vector<Enemy*> enemies;
std::vector<Bullet*> bullets;
std::vector<Explosion*> explosions;

// Timing
float lastTime = 0;
float enemySpawnTimer = 0;
float enemySpawnInterval = 3.0f;

// Mouse position
int mouseX = 0, mouseY = 0;

// ==================== Background Drawing ====================

void positionGround() {
    Transform ground(1.3f, 1.0f, 0.0f, 0.0f);
    ground.apply();
    drawGround();
    ground.reset();
}

void positionMountains() {
    // Left mountain
    Transform leftMountain(7.0f, 8.0f, 500.0f, GROUND_HEIGHT + 50);
    leftMountain.apply();
    drawMountainLeft();
    leftMountain.reset();

    // Right mountain
    Transform rightMountain(7.0f, 8.0f, 700.0f, GROUND_HEIGHT + 50);
    rightMountain.apply();
    drawMountainRight();
    rightMountain.reset();
}

void positionBuildings() {
    Transform buildings1(0.8f, 0.7f, 0.0f, GROUND_HEIGHT);
    buildings1.apply();
    drawBuilding();
    buildings1.reset();

    Transform buildings2(0.8f, 0.7f, 640.0f, GROUND_HEIGHT);
    buildings2.apply();
    drawBuilding();
    buildings2.reset();
}

void positionClouds() {
    Transform cloud1(120.0f, 80.0f, 80.0f, 580.0f);
    cloud1.apply(); drawCloud(); cloud1.reset();

    Transform cloud2(100.0f, 70.0f, 300.0f, 620.0f);
    cloud2.apply(); drawCloud(); cloud2.reset();

    Transform cloud3(110.0f, 75.0f, 550.0f, 590.0f);
    cloud3.apply(); drawCloud(); cloud3.reset();

    Transform cloud4(130.0f, 85.0f, 750.0f, 630.0f);
    cloud4.apply(); drawCloud(); cloud4.reset();

    Transform cloud5(100.0f, 70.0f, 950.0f, 600.0f);
    cloud5.apply(); drawCloud(); cloud5.reset();

    Transform cloud6(120.0f, 80.0f, 1150.0f, 580.0f);
    cloud6.apply(); drawCloud(); cloud6.reset();
}

void positionTrees() {
    Transform tree1(0.35f, 0.35f, 100.0f, GROUND_HEIGHT);
    tree1.apply(); drawTree(); tree1.reset();

    Transform tree2(0.38f, 0.38f, 450.0f, GROUND_HEIGHT);
    tree2.apply(); drawTree(); tree2.reset();

    Transform tree3(0.4f, 0.4f, 700.0f, GROUND_HEIGHT);
    tree3.apply(); drawTree(); tree3.reset();

    Transform tree4(0.36f, 0.36f, 950.0f, GROUND_HEIGHT);
    tree4.apply(); drawTree(); tree4.reset();
}

// ==================== UI Drawing ====================

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawTextLarge(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void drawButton(float x, float y, float w, float h, const char* text, bool highlighted) {
    // Button background
    if (highlighted) {
        glColor3f(0.2f, 0.6f, 0.3f);
    } else {
        glColor3f(0.15f, 0.45f, 0.2f);
    }
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
    
    // Button border
    glColor3f(0.3f, 0.8f, 0.4f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
    
    // Button text - centered based on text length
    glColor3f(1.0f, 1.0f, 1.0f);
    int textLen = 0;
    for (const char* c = text; *c != '\0'; c++) textLen++;
    float textWidth = (float)(textLen * 9);
    float textX = x + w/2 - textWidth/2 - 30;  
    float textY = y + h/2 - 8;
    drawTextLarge(textX, textY, text);
}

void drawMenuScreen() {
    // Draw background image
    drawBackground();
    
    // Semi-transparent overlay for better text readability
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(WINDOW_WIDTH, 0);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(0, WINDOW_HEIGHT);
    glEnd();
    glDisable(GL_BLEND);
    
    float centerX = WINDOW_WIDTH / 2.0f;
    
    // Title - centered
    glColor3f(0.2f, 0.8f, 0.3f);
    drawTextLarge(centerX - 55, WINDOW_HEIGHT - 100, "TANK WAR");
    
    // Subtitle - centered
    glColor3f(0.8f, 0.8f, 0.3f);
    drawText(centerX - 65, WINDOW_HEIGHT - 140, "Defend Your City!");
    
    // Instructions box - centered
    float boxW = 360;
    float boxH = 260;
    float boxX = centerX - boxW/2;
    float boxY = 180;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(boxX, boxY);
    glVertex2f(boxX + boxW, boxY);
    glVertex2f(boxX + boxW, boxY + boxH);
    glVertex2f(boxX, boxY + boxH);
    glEnd();
    glDisable(GL_BLEND);
    
    // Instructions title - centered
    glColor3f(1.0f, 1.0f, 0.0f);
    drawTextLarge(centerX - 70, boxY + boxH - 30, "HOW TO PLAY");
    
    // Instructions - left aligned within box
    glColor3f(1.0f, 1.0f, 1.0f);
    float textX = boxX + 25;
    float lineY = boxY + boxH - 65;
    float lineSpacing = 28;
    
    drawText(textX, lineY, "Move mouse to aim cannon");
    lineY -= lineSpacing;
    drawText(textX, lineY, "Left click to shoot");
    lineY -= lineSpacing;
    drawText(textX, lineY, "Destroy tanks and helicopters");
    lineY -= lineSpacing;
    drawText(textX, lineY, "Tanks: 50 pts (3 hits)");
    lineY -= lineSpacing;
    drawText(textX, lineY, "Helicopters: 100 pts (5 hits)");
    lineY -= lineSpacing;
    glColor3f(0.3f, 1.0f, 0.3f);
    drawText(textX, lineY, "Reach 1000 points to WIN!");
    lineY -= lineSpacing;
    glColor3f(1.0f, 0.3f, 0.3f);
    drawText(textX, lineY, "Don't let health reach 0!");
    
    // Start button - centered
    float btnW = 180;
    float btnH = 50;
    drawButton(centerX - btnW/2, 100, btnW, btnH, "START GAME", true);
    
    // Hint - centered
    glColor3f(0.7f, 0.7f, 0.7f);
    drawText(centerX - 100, 65, "Click button or press SPACE");
}

void drawUI() {
    // Health bar background
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(20, WINDOW_HEIGHT - 40);
    glVertex2f(220, WINDOW_HEIGHT - 40);
    glVertex2f(220, WINDOW_HEIGHT - 20);
    glVertex2f(20, WINDOW_HEIGHT - 20);
    glEnd();
    
    // Health bar
    float healthPercent = gameState.getHealth() / 100.0f;
    glColor3f(1.0f - healthPercent, healthPercent, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(20, WINDOW_HEIGHT - 40);
    glVertex2f(20 + 200 * healthPercent, WINDOW_HEIGHT - 40);
    glVertex2f(20 + 200 * healthPercent, WINDOW_HEIGHT - 20);
    glVertex2f(20, WINDOW_HEIGHT - 20);
    glEnd();
    
    // Health text
    glColor3f(1.0f, 1.0f, 1.0f);
    char healthText[32];
    sprintf(healthText, "Health: %d", gameState.getHealth());
    drawText(25, WINDOW_HEIGHT - 35, healthText);
    
    // Score
    glColor3f(1.0f, 1.0f, 0.0f);
    char scoreText[32];
    sprintf(scoreText, "Score: %d / 1000", gameState.getScore());
    drawText(WINDOW_WIDTH - 180, WINDOW_HEIGHT - 35, scoreText);
}

void drawGameOverScreen() {
    // Semi-transparent overlay
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(WINDOW_WIDTH, 0);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(0, WINDOW_HEIGHT);
    glEnd();
    glDisable(GL_BLEND);
    
    // Result
    if (gameState.hasWon()) {
        glColor3f(0.2f, 1.0f, 0.3f);
        drawTextLarge(WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT/2 + 80, "VICTORY!");
        glColor3f(1.0f, 1.0f, 0.0f);
        drawText(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 40, "You defended the city!");
    } else {
        glColor3f(1.0f, 0.2f, 0.2f);
        drawTextLarge(WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 + 80, "GAME OVER");
        glColor3f(1.0f, 0.5f, 0.5f);
        drawText(WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 + 40, "The city has fallen...");
    }
    
    // Final score
    glColor3f(1.0f, 1.0f, 1.0f);
    char finalScore[64];
    sprintf(finalScore, "Final Score: %d", gameState.getScore());
    drawTextLarge(WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 - 10, finalScore);
    
    // Restart button
    drawButton(WINDOW_WIDTH/2 - 90, WINDOW_HEIGHT/2 - 100, 180, 50, "PLAY AGAIN", true);
    
    // Hint
    glColor3f(0.7f, 0.7f, 0.7f);
    drawText(WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 - 130, "Click button or press R");
}

// ==================== Game Logic ====================

void spawnEnemy() {
    int type = rand() % 3; // 0-1 = tank, 2 = helicopter
    
    if (type < 2) {
        // Spawn tank from right side
        float startX = WINDOW_WIDTH + 50;
        // Stop at random position between 500-900
        float stopX = 500.0f + (float)(rand() % 400);
        enemies.push_back(new Enemy(ENEMY_TANK, startX, GROUND_HEIGHT + 20, stopX));
    } else {
        // Spawn helicopter from right
        float y = 350.0f + (float)(rand() % 200);
        enemies.push_back(new Enemy(ENEMY_HELICOPTER, WINDOW_WIDTH + 100, y, 0));
    }
}

void updateGame(float dt) {
    if (gameState.isGameOver()) return;
    
    // Update player cannon angle based on mouse
    player.setCannonAngle((float)mouseX, (float)(WINDOW_HEIGHT - mouseY));
    
    // Spawn enemies
    enemySpawnTimer += dt;
    if (enemySpawnTimer >= enemySpawnInterval) {
        enemySpawnTimer = 0;
        spawnEnemy();
        // Make game harder over time
        if (enemySpawnInterval > 1.0f) {
            enemySpawnInterval -= 0.1f;
        }
    }
    
    // Update enemies
    for (auto& enemy : enemies) {
        if (enemy->isActive()) {
            enemy->update(dt, GROUND_HEIGHT);
            
            // Enemy shoots at player
            Bullet* b = enemy->shoot(player.getX(), player.getY());
            if (b) bullets.push_back(b);
            
            // Remove off-screen helicopters
            if (enemy->isOffScreen(WINDOW_WIDTH)) {
                enemy->deactivate();
            }
        }
    }
    
    // Update bullets
    for (auto& bullet : bullets) {
        if (bullet->isActive()) {
            bullet->update(dt);
            
            // Check off-screen
            if (bullet->isOffScreen(WINDOW_WIDTH, WINDOW_HEIGHT)) {
                bullet->deactivate();
            }
            
            // Player bullet hits enemy
            if (bullet->isPlayerBullet()) {
                for (auto& enemy : enemies) {
                    if (enemy->isActive() && !enemy->isDying()) {
                        float dx = bullet->getX() - enemy->getX();
                        float dy = bullet->getY() - enemy->getY();
                        float dist = sqrtf(dx*dx + dy*dy);
                        
                        float hitRadius = (enemy->getType() == ENEMY_TANK) ? 40.0f : 50.0f;
                        if (dist < hitRadius) {
                            bullet->deactivate();
                            enemy->takeDamage(1);
                            if (!enemy->isAlive()) {
                                gameState.addScore(enemy->getScoreValue());
                                if (enemy->getType() == ENEMY_TANK) {
                                    explosions.push_back(new Explosion(enemy->getX(), enemy->getY() + 20));
                                }
                            }
                            break;
                        }
                    }
                }
            } else {
                // Enemy bullet hits player
                float dx = bullet->getX() - player.getX();
                float dy = bullet->getY() - player.getY();
                float dist = sqrtf(dx*dx + dy*dy);
                
                if (dist < 50.0f) {
                    bullet->deactivate();
                    gameState.takeDamage(10);
                }
            }
        }
    }
    
    // Clean up inactive objects
    for (int i = enemies.size() - 1; i >= 0; i--) {
        if (!enemies[i]->isActive()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
    }
    
    for (int i = bullets.size() - 1; i >= 0; i--) {
        if (!bullets[i]->isActive()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
    
    // Update and clean explosions
    for (auto& exp : explosions) {
        exp->update(dt);
    }
    for (int i = explosions.size() - 1; i >= 0; i--) {
        if (!explosions[i]->isActive()) {
            delete explosions[i];
            explosions.erase(explosions.begin() + i);
        }
    }
}

void resetGame() {
    gameState.reset();
    
    for (auto& e : enemies) delete e;
    enemies.clear();
    
    for (auto& b : bullets) delete b;
    bullets.clear();
    
    enemySpawnTimer = 0;
    enemySpawnInterval = 3.0f;
}

// ==================== GLUT Callbacks ====================

void display() {
    glClearColor(0.45f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw based on current screen
    if (gameState.getScreen() == SCREEN_MENU) {
        // Just draw menu screen
        drawMenuScreen();
    } 
    else if (gameState.getScreen() == SCREEN_PLAYING) {
        // Draw background
        positionMountains();
        positionBuildings();
        positionGround();
        positionClouds();
        positionTrees();

        // Draw game objects
        player.draw();
        
        for (size_t i = 0; i < enemies.size(); i++) {
            enemies[i]->draw();
        }
        
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i]->draw();
        }
        
        for (size_t i = 0; i < explosions.size(); i++) {
            explosions[i]->draw();
        }
        
        // Draw UI
        drawUI();
    }
    else if (gameState.getScreen() == SCREEN_GAMEOVER) {
        // Draw background
        positionMountains();
        positionBuildings();
        positionGround();
        positionClouds();
        positionTrees();
        
        // Draw game objects (frozen)
        player.draw();
        for (size_t i = 0; i < enemies.size(); i++) {
            enemies[i]->draw();
        }
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i]->draw();
        }
        
        // Draw UI and game over screen
        drawUI();
        drawGameOverScreen();
    }

    glFlush();
    glutSwapBuffers();
}

void update(int value) {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = currentTime - lastTime;
    lastTime = currentTime;
    
    // Only update game logic when playing
    if (gameState.getScreen() == SCREEN_PLAYING) {
        updateGame(dt);
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void mouseMove(int x, int y) {
    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int clickY = WINDOW_HEIGHT - y; // Convert to OpenGL coords
        
        if (gameState.getScreen() == SCREEN_MENU) {
            // Check if clicked on Start button
            float btnX = WINDOW_WIDTH/2 - 90;
            float btnY = 100;
            float btnW = 180;
            float btnH = 50;
            
            if (x >= btnX && x <= btnX + btnW && clickY >= btnY && clickY <= btnY + btnH) {
                Audio::playStartGame();
                Audio::playBackgroundMusic();
                gameState.startGame();
            }
        }
        else if (gameState.getScreen() == SCREEN_PLAYING) {
            Audio::playShot();
            Bullet* b = player.shoot();
            bullets.push_back(b);
        }
        else if (gameState.getScreen() == SCREEN_GAMEOVER) {
            // Check if clicked on Play Again button
            float btnX = WINDOW_WIDTH/2 - 90;
            float btnY = WINDOW_HEIGHT/2 - 100;
            float btnW = 180;
            float btnH = 50;
            
            if (x >= btnX && x <= btnX + btnW && clickY >= btnY && clickY <= btnY + btnH) {
                resetGame();
                Audio::playStartGame();
                Audio::playBackgroundMusic();
                gameState.startGame();
            }
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (gameState.getScreen() == SCREEN_MENU) {
        if (key == ' ') { // SPACE to start
            gameState.startGame();
        }
    }
    else if (gameState.getScreen() == SCREEN_GAMEOVER) {
        if (key == 'r' || key == 'R') {
            resetGame();
            gameState.startGame();
        }
    }
    
    if (key == 27) { // ESC
        exit(0);
    }
}

// ==================== Main ====================

int main(int argc, char** argv) {
    srand((unsigned int)time(NULL));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("TankWar - Defend Your City!");

    initGround();

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);
    
    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    glutMainLoop();
    return 0;
}
