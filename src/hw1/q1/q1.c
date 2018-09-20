#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

static int rotateAngle = 0;

void initOpenGL();

void reshape(int, int);

void display();

void drawTriangle(GLfloat vtx1[], GLfloat vtx2[], GLfloat vtx3[]);

void drawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

void drawCircle(GLfloat x, GLfloat y, double radius);

void drawAllPolygon();

void mouseClick(int button, int state, int x, int y);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hw1_q1");
    initOpenGL();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    // Call when windows is created or changed
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}

void display(void) {
    // Use the glClearColor color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotated(rotateAngle, 0.0, 1.0, 0.0);
    drawAllPolygon();
    glutSwapBuffers();
}

void drawTriangle(GLfloat vtx1[], GLfloat vtx2[], GLfloat vtx3[])
{
    // First triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(vtx1[0], vtx1[1]);
    glVertex2f(vtx2[0], vtx2[1]);
    glVertex2f(vtx3[0], vtx3[1]);
    glEnd();
}

void drawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(x, y);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();
}

void drawCircle(GLfloat x, GLfloat y, double radius)
{
    //Draw Circle
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    //Notice the correlation between the value and the number of sides
    //The number of sides is always twice the value given this range
    for (int i = 0; i <= 300; i++)
    {
        double angle = 2 * PI * i / 60;
        glVertex2f((GLfloat) (cos(angle) * radius) + x, (GLfloat) (sin(angle) * radius + y));
    }
    glEnd();
    //Draw Circle
}

void drawAllPolygon(){
    GLfloat tVtx1[2] = {(GLfloat) -1.0, 0.0};
    GLfloat tVtx2[2] = {0.0, 0.0};
    GLfloat tVtx3[2] = {(GLfloat) -0.5, 1};
    drawTriangle(tVtx1, tVtx2, tVtx3);
    drawSquare(0, 0, 1, 1);
    drawCircle(0, (GLfloat)-0.5, 0.5);
}

void mouseClick(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            switch (state) {
                case GLUT_DOWN:
                    rotateAngle = rotateAngle + 15;
                    break;
                case GLUT_UP:
                    break;
                default:
                    break;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            switch (state) {
                case GLUT_DOWN:
                    rotateAngle = 0;
                    break;
                case GLUT_UP:
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}


void reshape(int w, int h) {
    // Where to draw when window is reshaped
    glViewport(0, 0, w, h);
}

void initOpenGL() {
    // Set the color yet use it
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}
