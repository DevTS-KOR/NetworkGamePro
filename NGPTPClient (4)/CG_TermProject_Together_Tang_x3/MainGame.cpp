#include "stdafx.h"
#include "MainGame.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
CMainGame::CMainGame()
{
	m_pBitmapMgr = nullptr;
}


CMainGame::~CMainGame()
{
	Release();
}

GLvoid CMainGame::Render(GLvoid)
{
	CSceneMgr::GetInst()->Render();
}

GLvoid CMainGame::Keyboard(unsigned char key, int x, int y)
{
	CSceneMgr::GetInst()->Keyboard(key, x, y);
}

GLvoid CMainGame::SpecialKeyboard(int key, int x, int y)
{
	CSceneMgr::GetInst()->SpecialKeyboard(key, x, y);
}

GLvoid CMainGame::SpecialKeyboardUp(int key, int x, int y)
{
	CSceneMgr::GetInst()->SpecialKeyboardUp(key, x, y);
}
GLvoid CMainGame::Update(int value)
{
	CSceneMgr::GetInst()->Update(value);
}

GLvoid CMainGame::Mouse(int button, int state, int x, int y)
{
	CSceneMgr::GetInst()->Mouse(button, state, x, y);
}

GLvoid CMainGame::MouseMotionFunc(int x, int y)
{
	CSceneMgr::GetInst()->MouseMotionFunc( x, y);
}

GLvoid  CMainGame::KeyboardUp(unsigned char key, int x, int y)
{
	CSceneMgr::GetInst()->KeyboardUp(key, x, y);
	glutPostRedisplay();
}


GLvoid CMainGame::Release()
{
	::Safe_Delete(m_pBitmapMgr);
	CSceneMgr::GetInst()->Release();
	CSceneMgr::GetInst()->DestroyInst();
	
}

GLvoid CMainGame::Initialize()
{
	m_pBitmapMgr = new CBitmapMgr;
	m_pBitmapMgr->Initialize();
	CSceneMgr::GetInst()->SetScene(SCENE_LOGO,m_pBitmapMgr);

	SetCursor(NULL);
	ShowCursor(FALSE);
}

