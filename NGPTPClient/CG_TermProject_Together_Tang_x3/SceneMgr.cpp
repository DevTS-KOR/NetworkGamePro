#include "stdafx.h"
#include "SceneMgr.h"
#include "Lobby.h"
#include "Logo.h"
#include "Scene.h"
#include "BitmapMgr.h"
#include "InGame.h"
#include "InResult.h"
CSceneMgr* CSceneMgr::m_pInst = NULL;
CSceneMgr::CSceneMgr() :m_pScene(NULL)
{
}


CSceneMgr::~CSceneMgr()
{
	
}

void CSceneMgr::SetScene(SceneList _eID, CBitmapMgr* _pBitmapMgr)
{
	if (m_pScene != NULL)
		::Safe_Delete(m_pScene);
	
	switch (_eID)
	{
	case SCENE_LOGO:
		m_pScene = new CLogo;
		break;
	case SCENE_LOBBY:
		m_pScene = new CLobby;
		break;
	case SCENE_INGAME:
		m_pScene = new CInGame;
		break;
	case SCENE_INRESULT:
		m_pScene = new InResult;
	case SCENE_NONE:
		break;
	default:
		break;
	}
	m_pScene->Initialize(_pBitmapMgr);
}

GLvoid CSceneMgr::Render(GLvoid)
{
	m_pScene->Render();
}

GLvoid CSceneMgr::Keyboard(unsigned char key, int x, int y)
{
	m_pScene->Keyboard(key, x, y);
}

GLvoid	CSceneMgr::KeyboardUp(unsigned char key, int x, int y)
{
	m_pScene->KeyboardUp(key, x, y);
}

GLvoid CSceneMgr::SpecialKeyboard(int key, int x, int y)
{
	m_pScene->SpecialKeyboard(key, x, y);
}

GLvoid CSceneMgr::SpecialKeyboardUp(int key, int x, int y)
{
	m_pScene->SpecialKeyboardUp(key, x, y);
}

GLvoid CSceneMgr::Update(int value)
{
	m_pScene->Update(value);
}

GLvoid CSceneMgr::Mouse(int button, int state, int x, int y)
{
	m_pScene->Mouse(button, state, x, y);
}

GLvoid CSceneMgr::MouseMotionFunc(int x, int y)
{
	m_pScene->MouseMotionFunc( x, y);
}

GLvoid CSceneMgr::Release()
{
	::Safe_Delete(m_pScene);
}

CSceneMgr* CSceneMgr::GetInst(void)
{
	if (m_pInst == NULL)
		m_pInst = new CSceneMgr;

	return m_pInst;
}

void CSceneMgr::DestroyInst(void)
{
	delete m_pInst;
	m_pInst = NULL;
}
