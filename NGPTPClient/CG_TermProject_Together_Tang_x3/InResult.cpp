#include "stdafx.h"
#include "InResult.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
extern	int		g_iWindow_Width;
extern int		g_iWindow_Height;

InResult::InResult()
{
}


InResult::~InResult()
{
}

GLvoid InResult::Initialize(CBitmapMgr* _pBitmapMgr)
{
	m_pBitmapMgr = _pBitmapMgr;
	m_iTextures = m_pBitmapMgr->GetTexture(SCENE_INRESULT)[0];
}

GLvoid InResult::Render(GLvoid)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, g_iWindow_Width, g_iWindow_Height);
	glOrtho(0, g_iWindow_Width, 0, g_iWindow_Height, -2, 2);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	{
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, m_iTextures);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(0, g_iWindow_Height, -1);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(0, 0, -1);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(g_iWindow_Width, 0, -1);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(g_iWindow_Width, g_iWindow_Height, -1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

GLvoid InResult::Keyboard(unsigned char key, int x, int y)
{

}

GLvoid InResult::SpecialKeyboard(int key, int x, int y)
{

}

GLvoid InResult::Update(int value)
{

}/*SCENE_INRESULT*/

GLvoid InResult::Mouse(int button, int state, int x, int y)
{

}

GLvoid InResult::MouseMotionFunc(int x, int y)
{

}

GLvoid InResult::Release()
{

}

GLvoid InResult::SpecialKeyboardUp(int key, int x, int y)
{

}

GLvoid InResult::KeyboardUp(unsigned char key, int x, int y)
{

}
