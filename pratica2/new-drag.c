#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

//definindo tipo da estrutura que representa um ponto
typedef struct ponto {
    double x, y;
} Ponto;

//função para criar um ponto
Ponto criaPonto(double x, double y) {
    Ponto ponto;

    ponto.x = x;
    ponto.y = y;

    return ponto;
}

//definição de um quadrado: 4 pontos
Ponto quadrado[4];

//função que desenha um quadrado
void desenhaQuadrado(Ponto *quadrado) {
    glColor3f(1, 0, 0);					  //cor vermelha
	glBegin(GL_QUADS);					  //comeca a desenhar quadrilatros
    for(int i=0; i < 4; i++) {            //desenha cada ponto do quadrado
        glVertex2f(quadrado[i].x, quadrado[i].y);
    }
	glEnd();							  //termina o desenho
}

//função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //desenha o quadrado na tela
    desenhaQuadrado(quadrado);
    glFlush();
}

//função para retornar um ponto referente ao ponteiro do mouse
Ponto mouse(int x, int y) {
    printf("debug: Mouse is on (%f, %f)\n", (float)(x) / WINDOW_WIDTH, 1 - (float)(y) / WINDOW_HEIGHT);
    return criaPonto((float)(x) / WINDOW_WIDTH, 
                     1 - (float)(y) / WINDOW_HEIGHT);
}

//função para transladar o quadrado para o ponto do ponteiro do mouse
void moveQuadrado(Ponto *quadrado, Ponto mousePt) {
    //move primeiro ponto
    quadrado[0].x = mousePt.x - 0.1;
    quadrado[0].y = mousePt.y - 0.1;
    
    //move segundo ponto
    quadrado[1].x = mousePt.x + 0.1;
    quadrado[1].y = mousePt.y - 0.1;

    //move terceiro ponto
    quadrado[3].x = mousePt.x - 0.1;
    quadrado[3].y = mousePt.y + 0.1;

    //move quarto ponto
    quadrado[2].x = mousePt.x + 0.1;
    quadrado[2].y = mousePt.y + 0.1;
}

//função chamada ao clickar e mover o mouse
void onMouseClickMove(int x, int y) {
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

//função de inicialização
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
    //utiliza RGB para cores e janela com apenas um buffer
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //define o tamanho da janela
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //define posição incial da tela
    glutInitWindowPosition(200, 200);
    //cria janel "Mouse"
    glutCreateWindow("Mouse");

    //função de movimento, passa como parâmetro o procedimento
    //a ser executado ao clicar e mover o mouse
    glutMotionFunc(onMouseClickMove);

    //chama procedimento de inicialização
    init();
    
    //passa a função de exibição por parâmetro
    glutDisplayFunc(display);
    
    //inicia o loop do glut 
    glutMainLoop();

    return 0;
}