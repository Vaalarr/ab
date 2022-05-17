#include <GL/freeglut.h>
#include <GL/gl.h>


void displayPoint(int x,int y){
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();	
}


void ddaline(float x1,float y1,float x2,float y2){
	float dx = x2-x1;
	float dy = y2-y1;
	float step;
	if(dx<0){
		dx = -dx;
	}
	if(dy<0){
		dy = -dy;
	}
	
	if(dx>dy){
		step = dx;
	}
	else{
		step = dy;
	}
	float xin = dx/step;
	float yin = dy/step;
	int x = x1;
	int y = y1;
	for(int i = 0;i<=step;i++){
		displayPoint(x,y);
		x = x + xin;
		y = y + yin;
	}
	glFlush();
	
}

void drawSteps(int x, int y){
	ddaline(x,y,x+150,y);
	ddaline(x+150,y,x+150,y+150);
	int l = x;
	int m = y;
	for(int i = 0;i<6;i++){
		ddaline(l,m,l,m+25);
		ddaline(l,m+25,l+25,m+25);
		l = l+25;
		m = m+25;
	}
}

void renderFunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0,500,0,500);
    drawSteps(50,50);
    glEnd();
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(renderFunction);
    glutMainLoop();    
    return 0;
}
