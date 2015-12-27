#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include <GL/freeglut.h>

#define u8 uint8_t

// rgb_sketch needs these.
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s16 int16_t

#include <Adafruit_NeoPixel.h>

#include "rgb_sketch.hpp"

//void display(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    drawLedRing(500, 500, 24, 50);
//}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
}

void tick(void)
{
    // Run the sketch loop.
    loop();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(
        GLUT_DOUBLE // double buffering
        | GLUT_RGB // no alpha channel
    );
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("NeoPixel Emulator");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glColor3f(1.0f, 1.0f, 0.0f);
    //glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(tick);
    // Run the sketch setup.
    setup();
    for (;;) {
        // Run the sketch loop.
        loop();
    }
    return 0;
}
