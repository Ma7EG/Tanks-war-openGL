#include "Explosion.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <gdiplus.h>

using namespace Gdiplus;

unsigned int Explosion::textureId = 0;
bool Explosion::textureLoaded = false;
int Explosion::texWidth = 0;
int Explosion::texHeight = 0;

Explosion::Explosion() : x(0), y(0), timer(0), duration(0.5f), active(false) {}

Explosion::Explosion(float posX, float posY) : x(posX), y(posY), timer(0), duration(0.5f), active(true) {
    if (!textureLoaded) {
        initTexture();
    }
}

// Loads the explosion texture from file
void Explosion::initTexture() {
    if (textureLoaded) return;
    
    static ULONG_PTR gdiplusToken = 0;
    if (gdiplusToken == 0) {
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    }
    
    Bitmap* bitmap = new Bitmap(L"assets/fire.png");
    
    if (bitmap->GetLastStatus() == Ok) {
        texWidth = bitmap->GetWidth();
        texHeight = bitmap->GetHeight();
        
        BitmapData bitmapData;
        Rect rect(0, 0, texWidth, texHeight);
        bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
        
        unsigned char* pixels = new unsigned char[texWidth * texHeight * 4];
        unsigned char* src = (unsigned char*)bitmapData.Scan0;
        
        for (int y = 0; y < texHeight; y++) {
            for (int x = 0; x < texWidth; x++) {
                int srcIdx = (texHeight - 1 - y) * bitmapData.Stride + x * 4;
                int dstIdx = (y * texWidth + x) * 4;
                pixels[dstIdx + 0] = src[srcIdx + 2];
                pixels[dstIdx + 1] = src[srcIdx + 1];
                pixels[dstIdx + 2] = src[srcIdx + 0];
                pixels[dstIdx + 3] = src[srcIdx + 3];
            }
        }
        
        bitmap->UnlockBits(&bitmapData);
        
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        
        delete[] pixels;
        textureLoaded = true;
    }
    
    delete bitmap;
}

// Updates explosion timer and deactivates when expired
void Explosion::update(float dt) {
    if (!active) return;
    
    timer += dt;
    if (timer >= duration) {
        active = false;
    }
}

// Draws the explosion with fading alpha
void Explosion::draw() {
    if (!active || !textureLoaded || textureId == 0) return;
    
    float size = 100.0f;
    float alpha = 1.0f - (timer / duration);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x - size/2, y - size/2);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + size/2, y - size/2);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + size/2, y + size/2);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x - size/2, y + size/2);
    glEnd();
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

bool Explosion::isActive() const {
    return active;
}
