#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <SOIL/SOIL.h>
#include <GL/glut.h>

float z_pos = -5.0f;
float y_pos = 0.0f;
float x_pos = 0.0f;
float xRot, yRot, zRot;
float rot = 0.0f;
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };
// penyimpanan 1 texture
GLuint tex_2d;
/* penyimpanan 1 texture */
GLuint texture[1];
void init();
void myKeyboard(unsigned char, int, int);
void myDisplay(void);
void myTimeOut(int);
void resize(int, int);
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Membuat Texture Mapping");
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(resize);
    glutTimerFunc(100, myTimeOut, 0);
    init();
    glutMainLoop();
    return 0;
}
GLuint LoadGLTextures() // Load bitmaps dan mengkonversi texture
{
    /* load file image */
    tex_2d = SOIL_load_OGL_texture("gambar/background.jpg",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    /* pengecekan eror */
    if (tex_2d == 0) {
        printf("kesalahan load pada file SOIL : '%s'\n",
            SOIL_last_result());
    }
    // menentukan tipe texture dari image
    glBindTexture(GL_TEXTURE_2D, tex_2d);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex_2d;
}
void init()
{
    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    // glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT0);
}
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case '<':
    case ',':
        z_pos -= 0.1f;
        break;
    case '>':
    case '.':
        z_pos += 0.1f;
        break;
    case 'j':
        y_pos -= 0.1f;
        break;
    case 'k':
        y_pos += 0.1f;
        break;
    case 'h':
        x_pos -= 0.1f;
        break;
    case 'l':
        x_pos += 0.1f;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLoadIdentity();
    glTranslatef(x_pos, y_pos, z_pos);
    // glRotatef(xRot,0.0f,1.0f,0.0f);
    // glRotatef(yRot,0.0f,1.0f,0.0f);
    glRotatef(zRot,0.0f,0.0f,1.0f);
    // glEnable(GL_BLEND); // enable BLENDING
    // glColor3f(1.0, 0.5, 0.0); // Set warna BLENDING
    // glScaled(0.5, 0.5, 0.5);

    glBegin(GL_QUADS);
    // depan
    // glNormal3f(0.0f, 0.0f, 1.0f);
    // glTexCoord2f(0.0f, 0.0f);
    // glVertex3f(-1.0f, -1.0f, 1.0f);
    // glTexCoord2f(1.0f, 0.0f);
    // glVertex3f(1.0f, -1.0f, 1.0f);
    // glTexCoord2f(1.0f, 1.0f);
    // glVertex3f(1.0f, 1.0f, 1.0f);
    // glTexCoord2f(0.0f, 1.0f);
    // glVertex3f(-1.0f, 1.0f, 1.0f);
    // belakang
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    // atas
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    // bawah
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // kanan
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    // kiri
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // glTranslatef(0, 0, 0);
    glRotatef(180, 0, 1, 1);
    glutSolidTeapot(0.2);
    glFlush();
    xRot += 0.1f;
    yRot += 0.1f;
    zRot += 0.1f;
    glutSwapBuffers();
}
void myTimeOut(int id)
{
    rot += 5.0f;
    glutPostRedisplay();
    glutTimerFunc(100, myTimeOut, 0);
}
void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 1.0,
        300.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

