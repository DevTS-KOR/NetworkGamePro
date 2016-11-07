#pragma once
#include "Scene.h"
#include "Building.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Weather.h"
#include "Item.h"


class CInGame : public CScene
{

	Vec3			m_fWorldAngle;
	Vec3			m_fWorldTranslate;
	CWeather		cWeather[200];
	//Vec3			m_fCameraPos;
	//Vec3			m_fCameraRotate;

	Vec3			m_View;
	Vec2			m_MousePos;
	int				m_iMouseSens;

	vector<CBullet> m_vBullet;

	float			m_fSpeed = 1;

	CGameObject*			m_pMonster;
	vector<CGameObject*>	m_vpMonster;
	DWORD					m_dwRegenTime;
	DWORD					m_dwThunderTime;

	GLubyte*		m_pSkyBox[5];

	GLint			m_iBlendcubeAngle;
	CItem			m_cItem;
	//CGameObject*	m_pMonster;
	CGameObject*	m_pBuilding;
	CGameObject*	m_pCharacter;
	Thunder			m_eThunderState;
	float			m_fAmbientLight[4];
	float			m_fDiffuseLight[4];
	float			m_fSpecularLight[4];
	float			m_fLightPos[4];
	int				m_iClear;
public:
	virtual GLvoid Initialize(CBitmapMgr* _pBitmapMgr);
	virtual GLvoid Render(GLvoid);
	virtual GLvoid Keyboard(unsigned char key, int x, int y);
	virtual GLvoid SpecialKeyboard(int key, int x, int y);
	virtual GLvoid Update(int value);
	virtual GLvoid Mouse(int button, int state, int x, int y);
	virtual GLvoid MouseMotionFunc(int x, int y);
	virtual GLvoid Release(GLvoid);
	virtual GLvoid SpecialKeyboardUp(int key, int x, int y);
	virtual GLvoid KeyboardUp(unsigned char key, int x, int y);
public:
	void MultiMatrixAndVec(float* mat4By4, float* vec4Src, float* vec4Result)
	{
		vec4Result[0] = mat4By4[0] * vec4Src[0] + mat4By4[1] * vec4Src[1] + mat4By4[2] * vec4Src[2] + mat4By4[3] * vec4Src[3];
		vec4Result[1] = mat4By4[4] * vec4Src[0] + mat4By4[5] * vec4Src[1] + mat4By4[6] * vec4Src[2] + mat4By4[7] * vec4Src[3];
		vec4Result[2] = mat4By4[8] * vec4Src[0] + mat4By4[9] * vec4Src[1] + mat4By4[10] * vec4Src[2] + mat4By4[11] * vec4Src[3];
		vec4Result[3] = mat4By4[12] * vec4Src[0] + mat4By4[13] * vec4Src[1] + mat4By4[14] * vec4Src[2] + mat4By4[15] * vec4Src[3];
	}
	//void SetClear(int iDead);
	//int GetClear();


public:
	GLvoid	Ground();
	GLvoid	Bunker();
	GLvoid	SkyBox();
	GLvoid	Item();
public:
	GLvoid	Lights();
	GLvoid	Weather(int value);
public:
	CInGame();
	~CInGame();

};



