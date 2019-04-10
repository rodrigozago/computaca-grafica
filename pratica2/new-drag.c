#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

typedef struct ponto {
    double x, y;
} Ponto;

Ponto criaPonto(double x, double y) {
    Ponto ponto;

    ponto.x = x;
    ponto.y = y;

    return ponto;
}

Ponto quadrado[4];

void desenhaQuadrado(Ponto *quadrado) {
    glColor3f(1, 0, 0);					  //cor vermelha
	glBegin(GL_QUADS);					  //comeca a desenhar quadrilatros
    for(int i=0; i < 4; i++) {
        glVertex2f(quadrado[i].x, quadrado[i].y);
    }
	glEnd();							  //termina o desenho
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaQuadrado(quadrado);
    glFlush();
}

Ponto mouse(int x, int y) {
    printf("Mouse is on (%f, %f)", (float)(x) / WINDOW_WIDTH, 1 - (float)(y) / WINDOW_HEIGHT);
    return criaPonto((float)(x) / WINDOW_WIDTH, 
                     1 - (float)(y) / WINDOW_HEIGHT);
}

void moveQuadrado(Ponto *quadrado, Ponto mousePt) {
    quadrado[0].x = mousePt.x - 0.1;
    quadrado[0].y = mousePt.y - 0.1;
    
    quadrado[1].x = mousePt.x + 0.1;
    quadrado[1].y = mousePt.y - 0.1;

    quadrado[3].x = mousePt.x - 0.1;
    quadrado[3].y = mousePt.y + 0.1;

    quadrado[2].x = mousePt.x + 0.1;
    quadrado[2].y = mousePt.y + 0.1;
}

//drag function
void onMouseMove(int x, int y) {
    Ponto mousePt;
    mousePt = mouse(x, y);

    if (mousePt.x > quadrado[0].x && mousePt.y > quadrado[0].y)
    {       
        if (mousePt.x < quadrado[2].x && mousePt.y < quadrado[2].y)
        {
            printf("debug: Clicou dentro do quadrado");
            moveQuadrado(quadrado, mousePt);
            glutPostRedisplay();
        }
    }
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    //inicializando quadrado
    quadrado[0] = criaPonto(0.2,0.2);
    quadrado[1] = criaPonto(0.4,0.2);
    quadrado[2] = criaPonto(0.4,0.4);
    quadrado[3] = criaPonto(0.2,0.4);
}

int main(int argc, char **argv) {
    //função de inicialização openGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Mouse");

    glutMotionFunc(onMouseMove);

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}