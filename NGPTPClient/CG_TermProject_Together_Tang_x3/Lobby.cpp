#include "stdafx.h"
#include "Lobby.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"

extern	int		g_iWindow_Width;
extern int		g_iWindow_Height;
CLobby::CLobby()
{
}


CLobby::~CLobby()
{
}

GLvoid CLobby::Render(GLvoid)
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

GLvoid CLobby::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		CSceneMgr::GetInst()->SetScene(SCENE_INGAME, m_pBitmapMgr);
		break;
	default:
		break;
	}
}

GLvoid CLobby::SpecialKeyboard(int key, int x, int y)
{

}

GLvoid CLobby::Update(int value)
{
	
}

GLvoid CLobby::Mouse(int button, int state, int x, int y)
{

}

GLvoid CLobby::MouseMotionFunc(int x, int y)
{

}

GLvoid CLobby::Release()
{

}

GLvoid CLobby::Initialize(CBitmapMgr* _pBitmapMgr)
{
	m_pBitmapMgr = _pBitmapMgr;
	m_iTextures = m_pBitmapMgr->GetTexture(SCENE_LOBBY)[0];
//	m_dwTime = GetTickCount();
	//LoadDIBitmap()
}

GLvoid CLobby::SpecialKeyboardUp(int key, int x, int y)
{
}

GLvoid CLobby::KeyboardUp(unsigned char key, int x, int y)
{

}
