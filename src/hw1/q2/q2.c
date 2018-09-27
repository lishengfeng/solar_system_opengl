#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/gl.h>

#endif

#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

static GLdouble sunRadius = 300;
static GLdouble earthRadius = 100;
static GLdouble earthMoonRadius = 14;
static GLdouble marsRadius = 50;
static GLdouble marsMoon1Radius = 11;
static GLdouble marsMoon2Radius = 20;

static int earthOrbitRadius = 600;
static int earthMoonOrbitRadius = 150;
static int marsOrbitRadius = 900;
static int marsMoonOrbit1Radius = 100;
static int marsMoonOrbit2Radius = 105;

static float earthAngle = 0.0f;

static float earth = 360.0 / 365.26;
static float mars = 360.0 / 686.98;

static float marsAngle = 0.0f;


GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
GLfloat mat_specular[] = {0.0, 0.0, 0.0, 0.0};
GLfloat mat_shininess[] = {50.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
GLfloat model_ambient[] = {1.0, 1.0, 1.0, 1.0};


float eyeX = 0.0f;
float eyeY = 800.0f;
float eyeZ = 1700.0f;

float angle = 0.0f;

void initOpenGL();

void setupMaterials();

void changeColour(GLfloat r, GLfloat g, GLfloat b, GLfloat A);

void reshape(int, int);

void display();

void mouseClick(int button, int state, int x, int y);

void draw3DCircle(double radius);

void initOpenGL() {
    // Set the color yet use it
    glClearColor(0.0, 0.0, 0.0, 1.0);
    setupMaterials();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    // Remove back face rendering
    glEnable(GL_CULL_FACE);
    // Enable blend
    glEnable(GL_BLEND);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hw1_q2");
    initOpenGL();
    glutDisplayFunc(display);
    // Call when windows is created or changed
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutMainLoop();
    return 0;
}

void display(void) {
    // Use the glClearColor color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//    changeColour(1.0, 1.0, 1.0, 1.0);

    draw3DCircle(earthOrbitRadius);
    draw3DCircle(marsOrbitRadius);

    // The Sun
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    changeColour(1.0, 1.0, 0.0, 0.5);
    GLUquadric *sun;
    sun = gluNewQuadric();
    gluSphere(sun,sunRadius,100,100);
    //glutWireSphere(200, 30, 30);
    glPopMatrix();

    // Earth
    glPushMatrix();
    glRotatef(earthAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(earthOrbitRadius,0.0, 0.0);
    changeColour(0.0, 0.007, 0.686, 0.5);
    GLUquadric *Earth;
    Earth = gluNewQuadric();
    gluSphere(Earth,earthRadius,100,100);
    //glPopMatrix();

    //Earth Moon
    glRotatef(5*earthAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(earthMoonOrbitRadius,0.0, 0.0);
    changeColour(0.7, 0.7, 0.7, 0.0);
    GLUquadric *EarthMoon;
    EarthMoon = gluNewQuadric();
    gluSphere(EarthMoon,earthMoonRadius,100,100);
    glPopMatrix();

//    glPushMatrix();
//    glRotatef(earthAngle, 0.0f, 1.0f, 0.0f);
//    glTranslatef(earthOrbitRadius,0.0, 0.0);
//    changeColour(1.0, 1.0, 1.0, 1.0);
//    draw3DCircle(earthMoonOrbitRadius);
//    glPopMatrix();

    // Mars
    glPushMatrix();
    glRotatef(marsAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(marsOrbitRadius,0.0, 0.0);
    changeColour(170/255.0, 60/255.0, 5/255.0, 0.5);
    GLUquadric *Mars;
    Mars = gluNewQuadric();
    gluSphere(Mars,marsRadius,100,100);

    glPushMatrix();
    //Mars Moon1
    glRotatef(5*marsAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(marsMoonOrbit1Radius,0.0, 0.0);
    changeColour(0.7, 0.7, 0.7, 0.0);
    GLUquadric *MarsMoon1;
    MarsMoon1 = gluNewQuadric();
    gluSphere(MarsMoon1,marsMoon1Radius,100,100);
    glPopMatrix();

    glPushMatrix();
    //Mars Moon2
    glRotatef(11 * marsAngle, 0.0f, 1.0f, 1.0f);
    glTranslatef(marsMoonOrbit2Radius,0.0, 0.0);
    changeColour(0.7, 0.7, 0.7, 0.0);
    GLUquadric *MarsMoon2;
    MarsMoon2 = gluNewQuadric();
    gluSphere(MarsMoon2,marsMoon2Radius,100,100);
    glRotated(45.0f, 1.0, 0.0, 1.0);

    glPopMatrix();

    glPopMatrix();

//    glPushMatrix();
//    glRotatef(marsAngle, 0.0f, 1.0f, 0.0f);
//    glTranslatef(marsOrbitRadius,0.0, 0.0);
//    changeColour(1.0, 1.0, 1.0, 1.0);
//    draw3DCircle(marsMoonOrbit1Radius);
//    glPopMatrix();


//    glPushMatrix();
//    glRotatef(marsAngle, 0.0f, 1.0f, 0.0f);
//    glTranslatef(marsOrbitRadius,0.0, 0.0);
//    glRotatef(marsAngle, 0.0f, 0.0f, 1.0f);
//    changeColour(1.0, 1.0, 1.0, 1.0);
//    draw3DCircle(marsMoonOrbit2Radius);
//    glPopMatrix();

    angle += 0.2f;
    earthAngle += earth / 10;
    marsAngle += mars / 10;

    //if(angle == 360) angle = 0;
    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(display);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
        break;
    }
}


void reshape(int w, int h) {
    if(h == 0) h = 1;
    float ratio = (float) (1.0 * w / h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 5000);

    glMatrixMode(GL_MODELVIEW);
}

void draw3DCircle(double radius) {
    int num_segments = 1000;
    glBegin(GL_POINTS);
    for (int i = 0; i <= num_segments; i++) {
        double angle = 2.0f * PI * ((float)i) / (float) num_segments;
        glVertex3f((GLfloat) (cos(angle) * radius), 1.0, (GLfloat) (sin(angle) * radius));
    }
    glEnd();
}

void setupMaterials()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
}

void changeColour(GLfloat r, GLfloat g, GLfloat b, GLfloat A)
{
    model_ambient[0] = r;
    model_ambient[1] = g;
    model_ambient[2] = b;
    model_ambient[3] = A;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
}
