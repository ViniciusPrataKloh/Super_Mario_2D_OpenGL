#include <GL/glut.h>
//#include <math.h>

/* - - - Protótipos das funções - - - */
void display(void);
void Init(void);
void reshape(int w, int h);
void eixosGlobal(void);
void eixosLocal(void);

void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void projection(void);
void timer(int i);

void desenhaCeu(void);
void desenhaChao(void);
void desenhaMario(void);
void autoDesenhaBlocoAmarelo(float xPontoA, float yPontoA);
void autoDesenhaBlocoMarrom(float xPontoA, float yPontoA);
void autoDesenhaCano(float xPontoA, float yPontoA);
void autoDesenhaMontanhaMenor(float xPontoA);
void autoDesenhaMontanhaMaior(float xPontoA);

/* - - - Variáveis Globais - - - */
GLfloat minX = -30.0f, maxX = 30.0f, minY = -30.0f, maxY = 30.0f, minZ = -1.0f, maxZ = 1.0f;
GLfloat dxM = 0.0f, dyM = 0.0f, dzM = 0.0f, passo = 1.0f;
GLboolean eixos = true;

GLint contDireita  = 0;
GLint contEsquerda = 0;
GLint contCima     = 0;
GLint contBaixo    = 0;
GLfloat colisaoDireita[2]  = {19.0f, 59.0f};
GLfloat colisaoEsquerda[2] = {29.0f, 69.0f};

GLboolean pulo = false;
GLfloat pX = 0.0f, pY = 0.0f, pZ = 0.0f;


/* - - - Principal - - - */
int main(int argc, char** argv){
    // Escopo de criação de janelas:
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Projeto Mario");
    
    // Escopo das callbacks:
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(60, timer, 1);
    
    // Escopo dos demais:
    Init();
    glutMainLoop();
    return 0;    
}


/* - - - Funções - - - */

void display(void){
     glClear(GL_COLOR_BUFFER_BIT);
     if (eixos) eixosGlobal();
     
     // Chamada das funções de desenho:
     desenhaChao();
     desenhaCeu();
     
     autoDesenhaMontanhaMenor(-29.5f);
     autoDesenhaMontanhaMenor(-12.0f);
     autoDesenhaMontanhaMaior(1.0f);
     
     autoDesenhaBlocoAmarelo(-20.0f, -9.5f);
     autoDesenhaBlocoAmarelo(-17.0f, -9.5f);
     autoDesenhaBlocoAmarelo(4.0f, -1.0f);
     autoDesenhaBlocoAmarelo(33.0f, -9.5f);   
     autoDesenhaBlocoAmarelo(39.0f, -3.5f);
     autoDesenhaBlocoAmarelo(45.0f, 2.5f);
     autoDesenhaBlocoAmarelo(51.0f, 2.5f);
     autoDesenhaBlocoAmarelo(57.0f, 2.5f);
     
     autoDesenhaBlocoMarrom(-23.0f, -9.5f);
     autoDesenhaBlocoMarrom(-14.0f, -9.5f);
     autoDesenhaBlocoMarrom(4.0f, -9.5f);
     autoDesenhaBlocoMarrom(7.0f, -9.5f);
     autoDesenhaBlocoMarrom(10.0f, -9.5f);
     autoDesenhaBlocoMarrom(30.0f, -9.5f);
     autoDesenhaBlocoMarrom(36.0f, -6.5f);
     autoDesenhaBlocoMarrom(42.0f, -0.5f);
	 autoDesenhaBlocoMarrom(48.0f, 2.5f);
	 autoDesenhaBlocoMarrom(54.0f, 2.5f);
	      
	 autoDesenhaCano(20.0f, -18.5f);
	 autoDesenhaCano(60.0f, -18.5f);
     autoDesenhaCano(66.0f, -18.5f);
                
     glPushMatrix();
          glTranslatef(dxM, dyM, dzM);
          glTranslatef(pX, pY, pZ);
          desenhaMario();
     glPopMatrix();
     
     glutSwapBuffers();
}

void Init(void){
     glClearColor(0.49f, 0.83f, 1.0f, 0.0f);
}

void reshape(int w, int h){
     glViewport(0, 0, w, h);
     projection();
}

void projection(){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(minX+dxM, maxX+dxM, minY, maxY, minZ, maxZ);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();    
}

/* - - - Funções de ação - - - */
void keyboard(unsigned char key, int x, int y){
     
}

void timer(int i){
     
     if(pulo){
              pY++; 
              glutPostRedisplay();
              if(pY > 3){
                   pulo = false;
              }       
     }else if(pY > 0){
              pY--;
              glutPostRedisplay(); 
     }
     glutTimerFunc(60, timer, 1);
}

void special(int key, int x, int y){
     switch(key){
          case GLUT_KEY_F1:
               eixos = !eixos;
          break;
          
          case GLUT_KEY_RIGHT:
        	if (contDireita < 3){
				if ((dxM + 2.0f) != colisaoDireita[contDireita]){
        			dxM += passo;
        		} else{
        			dxM += 16.0f;
        			contDireita++;
        		}
        		if (dxM > colisaoEsquerda[contEsquerda]){
        			contDireita = contEsquerda;
        		}
        	}	
          break;        
          
          case GLUT_KEY_LEFT:
            if (contEsquerda < 3){
				if ((dxM + 2.0f) != colisaoEsquerda[contEsquerda]){
        			dxM -= passo;
        		} else{
        			dxM -= 16.0f;
        			contEsquerda++;
        		}
        		if (dxM > colisaoDireita[contDireita]){
        			contEsquerda = contDireita;
        		}
        	}
          break;
          
          case GLUT_KEY_UP:
            if(pY == 0){
            	pulo = true;
            }
          break;
     }

     projection();
     glutPostRedisplay();
}

/* - - - Funções de desenho - - - */
void eixosGlobal(void){
     glBegin(GL_LINES);
          glColor3f(1.0f, 0.0f, 0.0f);
          glVertex2f(minX, 0.0f);
          glVertex2f(maxX, 0.0f);
          
          glColor3f(0.0f, 1.0f, 0.0f);
          glVertex2f(0.0f, minY);
          glVertex2f(0.0f, maxY);
     glEnd();
}

void desenhaCeu(void){
	glBegin(GL_QUADS);
		 glColor3f(0.49f, 0.83f, 1.0f);
		 glVertex2f(-30.0f, 18.0f);
		 glColor3f(0.0f, 0.0f, 1.0f);
		 glVertex2f(-30.0f, 30.0f);
		 glVertex2f(100.0f, 30.0f);
		 glColor3f(0.49f, 0.83f, 1.0f);
		 glVertex2f(100.0f, 18.0f);
	glEnd();
}

void desenhaMario(void){
     glBegin(GL_QUADS);
          glColor3f(1.0f, 0.0f, 0.0f);
          glVertex2f(-2.0f, -18.5f);
          glVertex2f(-2.0f, -14.0f);
          glVertex2f( 2.0f, -14.0f);
          glVertex2f( 2.0f, -18.5f);
     glEnd();
}

void desenhaChao(void){
     glBegin(GL_QUADS);
          glColor3f(0.14f, 0.47f, 0.13f);
          glVertex2f(-30.0f, -20.0f);
          glVertex2f(-30.0f, -18.5f);
          glVertex2f(100.0f, -18.5f);
          glVertex2f(100.0f, -20.0f);  
     glEnd();
     
     glBegin(GL_LINE_LOOP);
          glColor3f(0.0f, 0.0f, 0.0f);
          glVertex2f(-30.0f, -20.0f);
          glVertex2f(-30.0f, -18.5f);
          glVertex2f(100.0f, -18.5f);
          glVertex2f(100.0f, -20.0f);
     glEnd();
     
     glBegin(GL_QUADS);
          glColor3f(0.8f, 0.5f, 0.4f);
          glVertex2f(-30.0f, -30.0f);
          glVertex2f(-30.0f, -20.0f);
          glVertex2f(100.0f, -20.0f);
          glVertex2f(100.0f, -30.0f);
     glEnd();
}

void autoDesenhaMontanhaMenor(float xPontoA){
	 glBegin(GL_TRIANGLES);
          glColor3f(0.20f, 0.55f, 0.20f);
          glVertex2f(xPontoA, -18.5f);
          glVertex2f((xPontoA + 6.0f), -6.0f);
          glVertex2f((xPontoA + 12.0f), -18.5f);
	 glEnd();
}

void autoDesenhaMontanhaMaior(float xPontoA){
	 glBegin(GL_TRIANGLES);
          glColor3f(0.4f, 0.2f, 0.2f);
          glVertex2f(xPontoA, -18.5f);
          glVertex2f((xPontoA + 12.0f), 5.0f);
          glVertex2f((xPontoA + 24.0f), -18.5f);
	 glEnd();
}

void autoDesenhaBlocoAmarelo(float xPontoA, float yPontoA){
     glBegin(GL_QUADS);
          glColor3f(1.0f, 1.0f, 0.0f);
          glVertex2f(xPontoA, yPontoA);
          glVertex2f(xPontoA, (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), yPontoA);
     glEnd();
     
     glBegin(GL_LINE_LOOP);
          glColor3f(0.0f, 0.0f, 0.0f);
          glVertex2f(xPontoA, yPontoA);
          glVertex2f(xPontoA, (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), yPontoA);
     glEnd();
}

void autoDesenhaBlocoMarrom(float xPontoA, float yPontoA){
     glBegin(GL_QUADS);
          glColor3f(0.9f, 0.5f, 0.4f);
          glVertex2f(xPontoA, yPontoA);
          glVertex2f(xPontoA, (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), yPontoA);
     glEnd();
     
     glBegin(GL_LINE_LOOP);
          glColor3f(0.0f, 0.0f, 0.0f);
          glVertex2f(xPontoA, yPontoA);
          glVertex2f(xPontoA, (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), (yPontoA + 3.0f));
          glVertex2f((xPontoA + 3.0f), yPontoA);
     glEnd();
}

void autoDesenhaCano(float xPontoA, float yPontoA){			// altura: 3.5f     largura: 3.5f
	// Meio
	glBegin(GL_QUADS);
	     glColor3f(0.1f, 1.0f, 0.2f);
	     glVertex2f(xPontoA, yPontoA);
	     glVertex2f(xPontoA, (yPontoA + 3.5f));
	     glVertex2f((xPontoA + 3.5f), (yPontoA + 3.5f));
	     glVertex2f((xPontoA + 3.5f), yPontoA);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	     glColor3f(0.0f, 0.0f, 0.0f);
	     glVertex2f(xPontoA, yPontoA);
	     glVertex2f(xPontoA, (yPontoA + 3.5f));
	     glVertex2f((xPontoA + 3.5f), (yPontoA + 3.5f));
	     glVertex2f((xPontoA + 3.5f), yPontoA);
	glEnd();
	
	// Topo:
	glBegin(GL_QUADS);
		 glColor3f(0.1f, 1.0f, 0.2f);
	     glVertex2f((xPontoA - 0.8f), (yPontoA + 3.5f));
	     glVertex2f((xPontoA - 0.8f), ((yPontoA + 3.5f) + 1.5f));
	     glVertex2f((xPontoA + 4.3f), ((yPontoA + 3.5f) + 1.5f));
	     glVertex2f((xPontoA + 4.3f), ((yPontoA + 3.5f)));
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		 glColor3f(0.0f, 0.0f, 0.0f);
	     glVertex2f((xPontoA - 0.8f), (yPontoA + 3.5f));
	     glVertex2f((xPontoA - 0.8f), ((yPontoA + 3.5f) + 1.5f));
	     glVertex2f((xPontoA + 4.3f), ((yPontoA + 3.5f) + 1.5f));
	     glVertex2f((xPontoA + 4.3f), ((yPontoA + 3.5f)));
	glEnd();
}
