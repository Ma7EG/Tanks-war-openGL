#include "Background.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdiplus.h>

using namespace Gdiplus;

static GLuint backgroundTexture = 0;
static int bgWidth = 1280;
static int bgHeight = 720;
static bool bgInitialized = false;

void initBackground() {
    if (bgInitialized) return;
    
    // Initialize GDI+
    static ULONG_PTR gdiplusToken = 0;
    if (gdiplusToken == 0) {
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    }
    
    // Load JPG using GDI+
    Bitmap* bitmap = new Bitmap(L"assets/background.jpg");
    
    if (bitmap->GetLastStatus() == Ok) {
        bgWidth = bitmap->GetWidth();
        bgHeight = bitmap->GetHeight();
        
        // Lock bits to get pixel data
        BitmapData bitmapData;
        Rect rect(0, 0, bgWidth, bgHeight);
        bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
        
        // Convert BGRA to RGBA and flip vertically
        unsigned char* pixels = new unsigned char[bgWidth * bgHeight * 4];
        unsigned char* src = (unsigned char*)bitmapData.Scan0;
        
        for (int y = 0; y < bgHeight; y++) {
            for (int x = 0; x < bgWidth; x++) {
                int srcIdx = (bgHeight - 1 - y) * bitmapData.Stride + x * 4;
                int dstIdx = (y * bgWidth + x) * 4;
                pixels[dstIdx + 0] = src[srcIdx + 2]; // R
                pixels[dstIdx + 1] = src[srcIdx + 1]; // G
                pixels[dstIdx + 2] = src[srcIdx + 0]; // B
                pixels[dstIdx + 3] = src[srcIdx + 3]; // A
            }
        }
        
        bitmap->UnlockBits(&bitmapData);
        
        // Create OpenGL texture
        glGenTextures(1, &backgroundTexture);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgWidth, bgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        
        delete[] pixels;
        delete bitmap;
        bgInitialized = true;
    } else {
        delete bitmap;
    }
}

void drawBackground() {
    if (!bgInitialized || backgroundTexture == 0) {
        initBackground();
    }
    
    if (backgroundTexture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        
        // Draw fullscreen quad
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1280, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1280, 720);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 720);
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
    }
}
