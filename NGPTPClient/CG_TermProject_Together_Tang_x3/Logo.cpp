#include "stdafx.h"
#include "Logo.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
extern	int		g_iWindow_Width;
extern int		g_iWindow_Height;
CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

GLvoid CLogo::Render(GLvoid)
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

GLvoid CLogo::Keyboard(unsigned char key, int x, int y)
{

}

GLvoid CLogo::SpecialKeyboard(int key, int x, int y)
{

}

GLvoid CLogo::Update(int value)
{
	if (m_dwTime + 2000 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		CSceneMgr::GetInst()->SetScene(SCENE_LOBBY,m_pBitmapMgr);
		return;
	}
}

GLvoid CLogo::Mouse(int button, int state, int x, int y)
{

}

GLvoid CLogo::MouseMotionFunc(int x, int y)
{

}

GLvoid CLogo::Release()
{

}



GLvoid CLogo::Initialize(CBitmapMgr* _pBitmapMgr)
{
	m_pBitmapMgr = _pBitmapMgr;
	m_iTextures = m_pBitmapMgr->GetTexture(SCENE_LOGO)[0];
	m_dwTime = GetTickCount();
	//LoadDIBitmap()
}

GLvoid CLogo::SpecialKeyboardUp(int key, int x, int y)
{

}

GLvoid CLogo::KeyboardUp(unsigned char key, int x, int y)
{

}
