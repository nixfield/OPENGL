#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

float z_pos = -5.0f;
float y_pos = 0.0f;
float x_pos = 0.0f;
float xRot, yRot, zRot;
float rot = 0.0f;

// GLfloat LightPosition[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat MatSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat MatShininess[] = { 50.0f };

/* penyimpanan 1 texture */
GLuint texture[0];

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

GLuint LoadGLTextures(const char* tex_name) // Load bitmaps dan mengkonversi texture
{

	GLuint texture = SOIL_load_OGL_texture
	(
		tex_name,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
  if (tex_name == 0) {
        printf("kesalahan load pada file SOIL : '%s'\n",
            SOIL_last_result());
  }
	return texture;
}

void init()
{
    texture[1] = LoadGLTextures("gambar/taplak.jpg");
    texture[2] = LoadGLTextures("gambar/tea_bg.jpg");
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // light & shading
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void draw_leg(float xt, float yt, float zt)
{
  glPushMatrix();
  glTranslatef(xt, yt, zt); 
  glScalef(0.1, 1, 0.1); 
  glutSolidCube(1.0); 
  glPopMatrix(); 
}


void draw_table() 
{
  // glColor4f(1.0,0, 0,1); 
  // glRotated(-90, 1, 0, 0);
  glPushMatrix(); 
    glPushMatrix(); 

    // alas meja
    glTranslatef(0.0f, 0.945f, 0.0f);
    glScalef(2, 0.1, 2); // scale y buat ketebalan 
    glutSolidCube(1.0); 
    glPopMatrix(); 

    // kaki meja
    draw_leg(0.75,0.4,-0.75); 
    draw_leg(0.75,0.4,0.75); 
    draw_leg(-0.75,0.4,-0.75); 
    draw_leg(-0.75,0.4,0.75); 

    // taplak meja
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
    glEnd();
  glPopMatrix(); 

}


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLoadIdentity();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_SPECULAR);

    glTranslatef(x_pos, y_pos, z_pos);
    glRotatef(30,1.0f,0.0f,0.0f);
    // glRotatef(xRot,0.0f,1.0f,0.0f);
    glRotatef(zRot,0.0f,1.0f,0.0f);
    draw_table();

    // membuat teapot
    glPushMatrix(); 
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTranslatef(-0.8f, 1.15f, -0.5f);
    glutSolidTeapot(0.2);
    glPopMatrix(); 

    glDisable(GL_COLOR_MATERIAL);
    glFlush();
    xRot += 0.1f;
    yRot += 0.1f;
    zRot += 0.1f;
    glutSwapBuffers();
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
    case 'h':
        x_pos += 0.1f;
        break;
    case 'k':
        y_pos -= 0.1f;
        break;
    case 'j':
        y_pos += 0.1f;
        break;
    case 'l':
        x_pos -= 0.1f;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
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
    gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 1.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

