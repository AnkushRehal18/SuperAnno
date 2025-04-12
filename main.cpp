#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables for angles to control simple animation
float head_angle_y = 0.0f;
float arm_angle_r = -45.0f;
float arm_angle_l = 45.0f;

void drawCircle(float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawEllipse(float radiusX, float radiusY, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(segments);
        float x = radiusX * cosf(theta);
        float y = radiusY * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}

void drawQuad() {
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
}

void drawLine() {
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glEnd();
}

void drawLineStrip() {
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glEnd();
}

void drawLineLoop() {
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glEnd();
}

void drawPoints() {
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    glPointSize(1.0f); // Reset point size
}

void drawHead() {
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f);
    glRotatef(head_angle_y, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.8f, 0.6f); // Skin color
    drawCircle(0.2f, 30); // Face
    glColor3f(0.0f, 0.0f, 0.0f); // Eyes
    glPushMatrix();
    glTranslatef(-0.08f, 0.05f, 0.0f);
    drawCircle(0.02f, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.08f, 0.05f, 0.0f);
    drawCircle(0.02f, 10);
    glPopMatrix();
    // Mouth (using line strip)
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -0.05f, 0.0f);
    glScalef(0.1f, 0.05f, 1.0f);
    drawLineStrip();
    glPopMatrix();
    glPopMatrix();
}

void drawTorso() {
    glColor3f(0.8f, 0.2f, 0.2f); // Red shirt
    glPushMatrix();
    glScalef(0.3f, 0.5f, 1.0f);
    drawQuad();
    glPopMatrix();
}

void drawArm(float sign) {
    glPushMatrix();
    glTranslatef(sign * 0.35f, 0.4f, 0.0f);
    glRotatef((sign > 0) ? arm_angle_r : arm_angle_l, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.8f, 0.6f); // Skin color
    glPushMatrix();
    glScalef(0.1f, 0.4f, 1.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    drawQuad(); // Upper arm
    glPopMatrix();

    glTranslatef(0.0f, -0.4f, 0.0f);
    glRotatef(((sign > 0) ? arm_angle_r : arm_angle_l) * 0.5f, 1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(0.1f, 0.4f, 1.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    drawQuad(); // Lower arm
    glPopMatrix();

    glTranslatef(0.0f, -0.4f, 0.0f);
    drawCircle(0.05f, 15); // Hand (using circle as a polygon)
    glPopMatrix();
}

void drawLeg(float sign) {
    glColor3f(0.2f, 0.2f, 0.8f); // Blue pants
    glPushMatrix();
    glTranslatef(sign * 0.15f, -0.25f, 0.0f);
    glPushMatrix();
    glScalef(0.15f, 0.5f, 1.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    drawQuad(); // Upper leg
    glPopMatrix();

    glTranslatef(0.0f, -0.5f, 0.0f);
    glPushMatrix();
    glScalef(0.15f, 0.5f, 1.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    drawQuad(); // Lower leg
    glPopMatrix();

    glTranslatef(0.0f, -0.5f, 0.0f);
    glColor3f(0.4f, 0.2f, 0.0f); // Brown shoes
    glPushMatrix();
    glScalef(0.2f, 0.1f, 1.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    drawQuad(); // Foot
    glPopMatrix();

    glPopMatrix();
}

void drawHumanFigure() {
    // Torso (using GL_QUADS)
    drawTorso();

    // Head (using GL_POLYGON for circle and GL_LINE_STRIP for mouth)
    drawHead();

    // Arms (using GL_QUADS for limbs and GL_POLYGON for hands)
    drawArm(1.0f); // Right arm
    drawArm(-1.0f); // Left arm

    // Legs (using GL_QUADS for limbs and feet)
    drawLeg(1.0f); // Right leg
    drawLeg(-1.0f); // Left leg

    // Example of using other primitives (can be placed anywhere or as details)
    glColor3f(0.0f, 0.5f, 0.0f); // Green
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glScalef(0.1f, 0.05f, 1.0f);
    drawTriangle(); // A simple patch on the shirt using GL_TRIANGLES
    glPopMatrix();

    glColor3f(0.5f, 0.5f, 0.5f); // Gray
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    drawLine(); // Ground line using GL_LINES
    glPopMatrix();

    glColor3f(0.2f, 0.8f, 0.2f); // Light Green
    glPushMatrix();
    glTranslatef(-0.5f, -0.8f, 0.0f);
    glScalef(0.2f, 0.1f, 1.0f);
    drawLineStrip(); // A small detail using GL_LINE_STRIP
    glPopMatrix();

    glColor3f(0.8f, 0.8f, 0.2f); // Yellow
    glPushMatrix();
    glTranslatef(0.5f, -0.8f, 0.0f);
    glScalef(0.2f, 0.1f, 1.0f);
    drawLineLoop(); // Another small detail using GL_LINE_LOOP
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    drawPoints(); // Some points using GL_POINTS
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Center the human figure
    glTranslatef(0.0f, 0.0f, -3.0f);
    glScalef(0.7f, 0.7f, 0.7f);

    drawHumanFigure();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            head_angle_y += 5.0f;
            break;
        case 'd':
            head_angle_y -= 5.0f;
            break;
        case 'w':
            arm_angle_r += 5.0f;
            arm_angle_l -= 5.0f;
            break;
        case 's':
            arm_angle_r -= 5.0f;
            arm_angle_l += 5.0f;
            break;
        case 27: // Escape key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 800);
    glutCreateWindow("OpenGL Human Figure (All Primitives)");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
