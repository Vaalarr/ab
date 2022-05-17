#include <GL/freeglut.h>
#include <GL/gl.h>

void renderfunction(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,500,0,500);
	glEnd();
	glFlush();	
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("BSA Steps");
	glutDisplayFunc(renderfunction);
	glutMainLoop();
	return 0;
}
