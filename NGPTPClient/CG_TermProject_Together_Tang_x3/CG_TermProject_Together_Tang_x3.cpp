// CG_TermProject_Together_Tang_x3.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"
CMainGame	MainGame;
int		g_iWindow_Width = 0;
int		g_iWindow_Height = 0;
//extern	int g_iWindow_Width;
//extern	int g_iWindow_Height;

GLvoid	Initialize();
GLvoid MenuInit();
GLvoid	LightInit();
GLvoid	drawScene(GLvoid);
GLvoid	Reshape(int w, int h);
GLvoid	Keyboard(unsigned char key, int x, int y);
GLvoid	KeyboardUp(unsigned char key, int x, int y);
GLvoid	SpecialKeyboardUp(int key, int x, int y);
GLvoid	SpecialKeyboard(int key, int x, int y);
GLvoid	TimerFunc(int value);
GLvoid	Mouse(int button, int state, int x, int y);
GLvoid	MotionFunc(int x, int y);
GLvoid		MenuFunc(int button);
int _tmain(int argc, _TCHAR* argv[])
{
	srand(unsigned int(time(NULL)));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정 
	glutCreateWindow("다함께 탕탕탕"); // 윈도우 생성 (윈도우 이름) 
	Initialize();
	glutDisplayFunc(drawScene);// 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutSpecialFunc(SpecialKeyboard);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(MotionFunc);
	glutPassiveMotionFunc(MotionFunc);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();
	MainGame.~CMainGame();
}

GLvoid Initialize()
{
	MainGame.Initialize();
	MenuInit();
}

GLvoid LightInit()
{

}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MainGame.Render();
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	g_iWindow_Width = w;
	g_iWindow_Height = h;

	glLoadIdentity();
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	MainGame.Keyboard(key, x, y);
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	MainGame.SpecialKeyboard(key, x, y);
	glutPostRedisplay();
}
GLvoid SpecialKeyboardUp(int key, int x, int y)
{

	MainGame.SpecialKeyboardUp(key, x, y);
	glutPostRedisplay();
}

GLvoid TimerFunc(int value)
{
	MainGame.Update(value);
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunc, 1);

}

GLvoid Mouse(int button, int state, int x, int y)
{
	MainGame.Mouse(button, state, x, y);
	glutPostRedisplay();
}

GLvoid MotionFunc(int x, int y)
{
	MainGame.MouseMotionFunc(x, y);
	glutPostRedisplay();
}

GLvoid MenuFunc(int button)
{
	switch (button)
	{
	case 11:

		exit(0);
		break;
	}
}

GLvoid MenuInit()
{

	/*int mainMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("종료", 11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);*/
}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	MainGame.KeyboardUp(key, x, y);
	glutPostRedisplay();
}
