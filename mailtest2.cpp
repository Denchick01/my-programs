#include <cmath>
#include <GL/glut.h>
#include <iostream>

#define WRONG_SIZE 1
#define WROG_COORDINATES 2
#define WRONG_RADIUS 3

#define WINDOW_HEIGH 1024
#define WINDOW_WIDTH 1280



void init_parameters();
void getPoint (int, int);
void draw_shape ();
void size_handler(int , int );
int error_handler(int );

//xr, yr: радиусы эллипса
//width, height: размер холста
//x0, y0: Начало координат 
struct {
	int xr, yr;
	int width, height;
	int x0, y0;
} ellipse_axis;

int main (int argc, char** argv)
{	
	init_parameters();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(ellipse_axis.width,ellipse_axis.height);	
	glutCreateWindow("Ellipse");	
	glutReshapeFunc(size_handler);
	glutDisplayFunc(draw_shape);
	glutMainLoop();
	
	return 0;
}

//Функция вывода изображения
void draw_shape()
{
	glTranslatef(ellipse_axis.x0, ellipse_axis.y0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);	
	for (int i = 0; i <= 360; i++) {
		double alpha = (M_PI/180) * i;  
       		getPoint( (ellipse_axis.xr) * cos(alpha), (ellipse_axis.yr) * sin(alpha)); 
	} 
	glEnd();
        glutSwapBuffers();
}

//Функция вывода точки на монитор
void getPoint (int x, int y)
{
       	glColor3f(1.0, 1.0, 1.0);
      	glVertex2i( x, y);
}

//Функция корректирующая размер изображения относительно размеров окна
void size_handler(int width, int height)
{
	if( width == 0 || height == 0)              
	{
		height = 1;
		width == 1; 
	}

	glViewport(0, 0, width, height);
       
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, height);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

void init_parameters()
{
	ellipse_axis = {-1, -1, -1, -1, -1, -1};
	int error_flag = 0;	

	do {	
		error_flag = 0;
		std::cout << "Введите размер окна: width height\n";
		std::cin >> ellipse_axis.width >> ellipse_axis.height;
		if (ellipse_axis.width <= -1 || ellipse_axis.height <= -1 || 
		  ellipse_axis.height > WINDOW_HEIGH || ellipse_axis.width > WINDOW_WIDTH)
			error_flag = error_handler(WRONG_SIZE);
	} while(error_flag);	

	do {
		error_flag = 0;
		std::cout << "Введите радиусы эллипса: xr yr\n";
		std::cin >> ellipse_axis.xr >> ellipse_axis.yr;
		if (ellipse_axis.xr <= -1 || ellipse_axis.yr <= -1)
			error_flag = error_handler(WRONG_RADIUS);
			
	} while(error_flag);	

	do {	
		error_flag = 0;
		std::cout << "Введите начало координат: x0 y0"<< std::endl;
		std::cin >> ellipse_axis.x0 >> ellipse_axis.y0;
		if (ellipse_axis.x0 <= -1 || ellipse_axis.y0 <= -1) 
			error_flag = error_handler(WROG_COORDINATES);
	} while(error_flag);	


}
//функция проверки на то что вводимое значение не строка
//и в пределах допустимых параметров
int error_handler(int flag)
{
	switch (flag) {
		case WRONG_SIZE:
		std::cerr << "Неверно введен размер окна\n"; 
		break;
		case WRONG_RADIUS:
		std::cerr << "Неверно введен радиус\n"; 
		break;
		case  WROG_COORDINATES:
		std::cerr << "Неверно введены координаты\n"; 
		break;
	}

	std::cin.clear();
	while(std::cin.get() != '\n');
	return 1;
}

