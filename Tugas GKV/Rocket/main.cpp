#include <GL/glut.h>
#include <cmath>

// Material properties setup
void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
                 GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
                 GLfloat specularR, GLfloat specularG, GLfloat specularB,
                 GLfloat shininess) {
    GLfloat ambient[] = {ambientR, ambientG, ambientB, 1.0f};
    GLfloat diffuse[] = {diffuseR, diffuseG, diffuseB, 1.0f};
    GLfloat specular[] = {specularR, specularG, specularB, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

// Draw a cylinder with caps
void drawCylinder(float baseRadius, float topRadius, float height, int slices) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluCylinder(quadric, baseRadius, topRadius, height, slices, 1);

    // Draw bottom cap
    glPushMatrix();
    gluDisk(quadric, 0, baseRadius, slices, 1);
    glPopMatrix();

    // Draw top cap if needed
    if (topRadius > 0) {
        glPushMatrix();
        glTranslatef(0, 0, height);
        gluDisk(quadric, 0, topRadius, slices, 1);
        glPopMatrix();
    }

    gluDeleteQuadric(quadric);
}

// Draw a cone
void drawCone(float base, float height, int slices) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluCylinder(quadric, base, 0.0, height, slices, 1);
    gluDisk(quadric, 0, base, slices, 1);
    gluDeleteQuadric(quadric);
}

// Draw detailed fins
void drawFin() {
    // Front triangle
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.8f, 0.0f);
    glEnd();

    // 3D thickness
    glBegin(GL_QUADS);
    // Front face
    glNormal3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.05f);
    glVertex3f(0.5f, 0.0f, 0.05f);
    glVertex3f(0.0f, 0.8f, 0.05f);
    glVertex3f(0.0f, 0.0f, 0.05f);

    // Back face
    glNormal3f(0, 0, -1);
    glVertex3f(0.0f, 0.0f, -0.05f);
    glVertex3f(0.5f, 0.0f, -0.05f);
    glVertex3f(0.0f, 0.8f, -0.05f);
    glVertex3f(0.0f, 0.0f, -0.05f);

    // Left side
    glNormal3f(-0.8f, 0.5f, 0);
    glVertex3f(0.0f, 0.0f, 0.05f);
    glVertex3f(0.0f, 0.8f, 0.05f);
    glVertex3f(0.0f, 0.8f, -0.05f);
    glVertex3f(0.0f, 0.0f, -0.05f);

    // Bottom side
    glNormal3f(0, -1, 0);
    glVertex3f(0.0f, 0.0f, 0.05f);
    glVertex3f(0.5f, 0.0f, 0.05f);
    glVertex3f(0.5f, 0.0f, -0.05f);
    glVertex3f(0.0f, 0.0f, -0.05f);

    // Diagonal side
    glNormal3f(0.8f, -0.5f, 0);
    glVertex3f(0.5f, 0.0f, 0.05f);
    glVertex3f(0.0f, 0.8f, 0.05f);
    glVertex3f(0.0f, 0.8f, -0.05f);
    glVertex3f(0.5f, 0.0f, -0.05f);
    glEnd();
}

// Draw the complete rocket
void drawRocket() {
    // Rocket body - lower part (red)
    setMaterial(0.8f, 0.0f, 0.0f, 1.0f, 0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 20.0f);
    glPushMatrix();
    drawCylinder(0.5, 0.5, 2.0, 32);
    glPopMatrix();

    // Rocket body - upper part (white)
    setMaterial(0.9f, 0.9f, 0.9f, 1.0f, 1.0f, 1.0f, 0.8f, 0.8f, 0.8f, 50.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    drawCylinder(0.5, 0.5, 1.5, 32);
    glPopMatrix();

    // Red stripes
    setMaterial(0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 10.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glutSolidTorus(0.05, 0.5, 10, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.3f);
    glutSolidTorus(0.05, 0.5, 10, 32);
    glPopMatrix();

    // Nose cone (white)
    setMaterial(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.9f, 0.9f, 0.9f, 64.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.5f);
    drawCone(0.5, 1.0, 32);

    // Nose tip (black)
    setMaterial(0.1f, 0.1f, 0.1f, 0.2f, 0.2f, 0.2f, 0.1f, 0.1f, 0.1f, 5.0f);
    glutSolidSphere(0.1, 16, 16);
    glPopMatrix();

    // Fins (dark gray - now more visible)
    setMaterial(0.4f, 0.4f, 0.4f, 0.6f, 0.6f, 0.6f, 0.5f, 0.5f, 0.5f, 30.0f);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glRotatef(90 * i, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.5f, 0.0f, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        drawFin();
        glPopMatrix();
    }

    // Engine nozzle (dark gray)
    setMaterial(0.3f, 0.3f, 0.3f, 0.5f, 0.5f, 0.5f, 0.4f, 0.4f, 0.4f, 30.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.3f);
    drawCylinder(0.3, 0.4, 0.3, 32);
    glPopMatrix();

    // Windows - now clearly visible
     setMaterial(0.1f, 0.3f, 0.6f, 0.2f, 0.4f, 0.8f, 0.8f, 0.8f, 0.8f, 60.0f); // Warna biru
    // Jendela utama di depan
   glPushMatrix();
glTranslatef(0.0f, 0.5f, 2.6f); // y positif
glutSolidSphere(0.12, 32, 32);
glPopMatrix();
    
    // Second window (symmetrical)
    glPushMatrix();
glTranslatef(0.0f, -0.5f, 2.6f); // y negatif, z sama
glutSolidSphere(0.12, 32, 32);
glPopMatrix();

    // Panel body - thin rectangles around the rocket
    setMaterial(0.7f, 0.7f, 0.7f, 0.8f, 0.8f, 0.8f, 0.4f, 0.4f, 0.4f, 20.0f);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glRotatef(i * 90, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.45f, 0.0f, 2.0f);
        glScalef(0.05f, 0.25f, 0.01f);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // Bolts around the rocket body
    setMaterial(0.2f, 0.2f, 0.2f, 0.3f, 0.3f, 0.3f, 0.1f, 0.1f, 0.1f, 10.0f);
    for (float angle = 0; angle < 360; angle += 45) {
        float rad = angle * M_PI / 180.0;
        float x = 0.5 * cos(rad);
        float y = 0.5 * sin(rad);

        // Lower ring of bolts
        glPushMatrix();
        glTranslatef(x, y, 1.0f);
        glutSolidSphere(0.03, 10, 10);
        glPopMatrix();
        
        // Upper ring of bolts
        glPushMatrix();
        glTranslatef(x, y, 1.5f);
        glutSolidSphere(0.03, 10, 10);
        glPopMatrix();
    }
}
enum ProjectionMode {
    PERSPECTIVE,
    ORTHO_TOP,
    ORTHO_FRONT,
    ORTHO_SIDE,
    ISOMETRIC,
    DIMETRIC,
    TRIMETRIC,
    PERSPECTIVE_1_POINT,
    PERSPECTIVE_2_POINT,
    PERSPECTIVE_3_POINT
};

ProjectionMode currentProjection = PERSPECTIVE;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Pusat objek sekitar (0,0,1.75) karena tinggi roket ~3.5 unit
    GLfloat centerX = 0.0f;
    GLfloat centerY = 0.0f; 
    GLfloat centerZ = 1.75f;

    switch (currentProjection) {
        case PERSPECTIVE:
            gluLookAt(8.0, 8.0, 8.0, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
            
        // Orthogonal Views
        case ORTHO_TOP:  // Plan View
            gluLookAt(centerX, centerY, 10.0, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
            break;
        case ORTHO_FRONT:  // Front View
            gluLookAt(centerX, -10.0, centerZ, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
        case ORTHO_SIDE:  // Side View
            gluLookAt(10.0, centerY, centerZ, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
            
        // Axonometric Projections
        case ISOMETRIC:
            gluLookAt(5.0, 5.0, 5.0, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
        case DIMETRIC:
            gluLookAt(5.0, 5.0, 3.0, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
        case TRIMETRIC:
            gluLookAt(4.0, 3.0, 2.0, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
            
        // Perspective Projections
        case PERSPECTIVE_1_POINT:
            gluLookAt(centerX, -8.0, centerZ, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
        case PERSPECTIVE_2_POINT:
            gluLookAt(5.0, -8.0, centerZ, centerX, centerY, centerZ, 0.0, 0.0, 1.0);
            break;
        case PERSPECTIVE_3_POINT:
            gluLookAt(5.0, -8.0, 5.0, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
            break;
    }

    drawRocket();
    glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1': currentProjection = ORTHO_TOP; break;
        case '2': currentProjection = ORTHO_FRONT; break;
        case '3': currentProjection = ORTHO_SIDE; break;
        case '4': currentProjection = ISOMETRIC; break;
        case '5': currentProjection = DIMETRIC; break;
        case '6': currentProjection = TRIMETRIC; break;
        case '7': currentProjection = PERSPECTIVE_1_POINT; break;
        case '8': currentProjection = PERSPECTIVE_2_POINT; break;
        case '9': currentProjection = PERSPECTIVE_3_POINT; break;
        case '0': currentProjection = PERSPECTIVE; break;
        case 27: exit(0); break; // Esc untuk keluar
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Di bagian reshape() - Perbaikan proyeksi orthogonal
// Di bagian reshape() - Perbaikan proyeksi orthogonal
if (currentProjection == ORTHO_TOP || currentProjection == ORTHO_FRONT || 
    currentProjection == ORTHO_SIDE || currentProjection == ISOMETRIC ||
    currentProjection == DIMETRIC || currentProjection == TRIMETRIC) {
    
    // Skala ortho yang lebih besar untuk menampung seluruh roket
    if (w <= h)
        glOrtho(-8.0, 8.0, -8.0/aspect, 8.0/aspect, -20.0, 20.0);
    else
        glOrtho(-8.0*aspect, 8.0*aspect, -8.0, 8.0, -20.0, 20.0);
} else {
    // Perspective projections
    gluPerspective(45.0, aspect, 0.1, 100.0);
}
    glMatrixMode(GL_MODELVIEW);
}


void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    GLfloat lightPos[] = {5.0f, 5.0f, 10.0f, 1.0f};
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Rocket with Multiple Projections");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
