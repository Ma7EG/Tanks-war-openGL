#include "Ground.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

static GLuint groundTexture = 0;
static int groundWidth = 983;
static int groundHeight = 88;
static ULONG_PTR gdiplusToken;

// Initializes the ground texture from an image file
void initGround() {
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    Bitmap* bitmap = new Bitmap(L"assets/ground.png");
    
    if (bitmap->GetLastStatus() == Ok) {
        groundWidth = bitmap->GetWidth();
        groundHeight = bitmap->GetHeight();
        
        BitmapData bitmapData;
        Rect rect(0, 0, groundWidth, groundHeight);
        bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
        
        unsigned char* pixels = new unsigned char[groundWidth * groundHeight * 4];
        unsigned char* src = (unsigned char*)bitmapData.Scan0;
        
        for (int y = 0; y < groundHeight; y++) {
            for (int x = 0; x < groundWidth; x++) {
                int srcIdx = (groundHeight - 1 - y) * bitmapData.Stride + x * 4;
                int dstIdx = (y * groundWidth + x) * 4;
                pixels[dstIdx + 0] = src[srcIdx + 2];
                pixels[dstIdx + 1] = src[srcIdx + 1];
                pixels[dstIdx + 2] = src[srcIdx + 0];
                pixels[dstIdx + 3] = src[srcIdx + 3];
            }
        }
        
        bitmap->UnlockBits(&bitmapData);
        
        glGenTextures(1, &groundTexture);
        glBindTexture(GL_TEXTURE_2D, groundTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, groundWidth, groundHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        
        delete[] pixels;
        delete bitmap;
    } else {
        delete bitmap;
    }
}

// Draws the ground with texture or fallback color (لو حصل مشكلة فالصورة)
void drawGround() {
    if (groundTexture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, groundTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f((float)groundWidth, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f((float)groundWidth, (float)groundHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0, (float)groundHeight);
        glEnd();
        
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    } else {
        glColor3f(0.2f, 0.6f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(983, 0);
        glVertex2f(983, 88);
        glVertex2f(0, 88);
        glEnd();
    }
}
