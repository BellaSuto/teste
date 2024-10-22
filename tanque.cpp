#include <gl/glut.h>
#include <gl/glu.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <cmath>

float anguloTanque = 0.0;
float posicaoTanqueX = 0.0, posicaoTanqueZ = 0.0;
GLuint texturaCorpo, texturaTorre, texturaCano, texturaRoda, texturaChao;

// Função para carregar uma textura
GLuint carregarTextura(const char *caminho)
{
    GLuint texturaID;
    int largura, altura, canais;
    unsigned char *imagem = SOIL_load_image(caminho, &largura, &altura, &canais, SOIL_LOAD_AUTO);

    if (!imagem)
    {
        printf("Erro ao carregar a imagem: %s\n", SOIL_last_result());
        return 0;
    }

    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum formato = (canais == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, formato, largura, altura, 0, formato, GL_UNSIGNED_BYTE, imagem);

    SOIL_free_image_data(imagem);
    return texturaID;
}

void desenharCilindro(GLfloat raio, GLfloat altura)
{
    GLUquadric *quadrica = gluNewQuadric();
    gluCylinder(quadrica, raio, raio, altura, 32, 32);
    gluDeleteQuadric(quadrica);
}

void desenharTanque()
{
    // Corpo do tanque
    glBindTexture(GL_TEXTURE_2D, texturaCorpo); // Vincula a textura
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(1.0f, 0.5f, 1.2f); // Escala o corpo do tanque

    glBegin(GL_QUADS);

    // Face frontal
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.6);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, 0.6);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, 0.6);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, 0.6);

    // Face traseira
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.6);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, -0.6);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, -0.6);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, -0.6);

    // Lateral esquerda
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.6);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.6);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-0.5, 0.5, 0.6);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, -0.6);

    // Lateral direita
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.6);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, 0.6);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, 0.6);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.5, 0.5, -0.6);

    // Face superior
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, 0.5, -0.6);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, 0.5, -0.6);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, 0.6);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, 0.6);

    // Face inferior
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.6);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, -0.6);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.6);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, -0.5, 0.6);
    glEnd();

    glPopMatrix();

    // Torre do tanque
    glBindTexture(GL_TEXTURE_2D, texturaTorre);
    glPushMatrix();
    glTranslatef(0.0, -0.1, 0.0); // Posicionada levemente acima do corpo
    glColor3f(1.0f, 0.8f, 0.9f);
    glScalef(0.5f, 0.3f, 0.5f); // Proporção da torre
    glutSolidCube(1.0f);
    glPopMatrix();

    // Canhão do tanque
    glBindTexture(GL_TEXTURE_2D, texturaCano);
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.7); // Posicionado mais próximo ao centro da torre
    glColor3f(1.0f, 0.5f, 0.7f);
    glScalef(0.1f, 0.1f, 1.5f); // Proporção mais fina e comprida do canhão
    glutSolidCube(1.0f);
    glPopMatrix();

    // Esteiras do tanque - Esquerda
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(-0.6f, -0.5f, 0.0f); 
    glScalef(0.2f, 0.2f, 1.5f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // Esteiras do tanque - Direita
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.6f, -0.5f, 0.0f); 
    glScalef(0.2f, 0.2f, 1.5f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // Rodas do tanque - Esquerda
    for (int i = -1; i <= 2; i++) {
        glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glTranslatef(-0.7f, -0.45f, -0.14 + i * 0.4f); 
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        desenharCilindro(0.25f, 0.15f); 
        glPopMatrix();
    }

    // Rodas do tanque - Direita
    for (int i = -1; i <= 2; i++) {
        glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glTranslatef(0.55f, -0.45f, -0.14 + i * 0.4f); 
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        desenharCilindro(0.25f, 0.15f); 
        glPopMatrix();
    }
}

void exibir()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 5.0, 5.0,  // Aproxima a câmera do tanque
              0.0, 0.0, 0.0,  // Ponto de foco permanece no centro do tanque
              0.0, 1.0, 0.0); // Vetor "up"

    glPushMatrix();
    glTranslatef(posicaoTanqueX, 0.0, posicaoTanqueZ);
    glRotatef(anguloTanque, 0.0, 1.0, 0.0);
    desenharTanque();
    glPopMatrix();

    glutSwapBuffers();
}

void inicializar()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.6, 0.48, 0.55, 1.0);// Fundo

    texturaCorpo = carregarTextura("camouflage.jpg");
    //texturaRoda = carregarTextura("pneu.png");
    // texturaTorreta = carregarTextura("pink-military.jpg");
    // texturaCano = carregarTextura("camouflage.jpg");
}
void moverTanque(float direcao) {
    float velocidade = 0.5 * direcao;
    float radiano = anguloTanque * M_PI / 180.0;
    float dx = velocidade * sin(radiano);
    float dz = velocidade * cos(radiano);

    posicaoTanqueX += dx;
    posicaoTanqueZ += dz;
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 's') { // mover para trás
        moverTanque(-1.0);
    } else if (tecla == 'w') { // mover para frente
        moverTanque(1.0);
    } else if (tecla == 'a') { // girar para esquerda
        anguloTanque += 5.0;
    } else if (tecla == 'd') { // girar para direita
        anguloTanque -= 5.0;
    }
    
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tanque 3D");
    inicializar();
    glutDisplayFunc(exibir);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}