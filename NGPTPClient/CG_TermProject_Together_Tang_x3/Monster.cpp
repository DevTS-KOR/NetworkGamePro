#include "stdafx.h"
#include "Monster.h"
#include "Common.h"
#include "Character.h"
CMonster::CMonster()
{
	Initialize();
}

CMonster::CMonster(CBitmapMgr* _pBitmapMgr) :m_pBitmapMgr(_pBitmapMgr)
{
	Initialize();
}

CMonster::CMonster(CBitmapMgr* _pBitmapMgr, float _fX, float _fZ) : m_pBitmapMgr(_pBitmapMgr)
{
	Initialize();
	Monster_Vec.fX = _fX;
	Monster_Vec.fY = 50.0f;
	Monster_Vec.fZ = _fZ;
}


CMonster::~CMonster()
{
}

GLvoid CMonster::Initialize()
{
	//Monster_Vec.fX = 0.0f;
//	Monster_Vec.fY = 0.0f;
//	Monster_Vec.fZ = 0.0f;
	fZ_left_arm = 0.0f;
	fZ_right_arm = 0.0f;
	fZ_left_leg = 0.0f;
	fZ_right_leg = 0.0f;
	fArm_move = 10.0f;
	fLeg_move = 5.0f;
	m_fSpeed = 9;
	m_eMonterType = (MonsterList)(rand() % 4);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 36; j++)
		{

			m_pMonster[i][j] = m_pBitmapMgr->GetTexture((MonsterList)i)[j];
		}
	}
	//for (size_t i = 0; i < 36; i++)
	//{
	//	m_pMonster[MONSTER_SPIDER][i] = m_pBitmapMgr->GetTexture(MONSTER_SPIDER)[i];

	//}
}

GLvoid CMonster::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	//3차원 사각형을 만드는 함수(x, y, z, 너비, 높이, 깊이, 그림배열, 그림x값, 그림y값)
	glPushMatrix();
	//머리
	DrawCube(0, 30, 0, 30, 30, 30, m_pMonster[m_eMonterType], 64, 64);
	glPopMatrix();

	glPushMatrix();
	//몸통
	DrawCube(0, 0, 0, 30, 40, 15, m_pMonster[m_eMonterType] + 6, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//왼팔
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(-22.5, 0, 0, 15, 40, 15, m_pMonster[m_eMonterType] + 12, 21, 64);

	glPopMatrix();

	glPushMatrix();
	//오른팔
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_right_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(22.5, 0, 0, 15, 40, 15, m_pMonster[m_eMonterType] + 18, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//왼다리
	//glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_leg, 1, 0, 0);
	//glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(-7.5, -30, 0, 15, 40, 15, m_pMonster[m_eMonterType] + 24, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//오른다리
	//glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_right_leg, 1, 0, 0);
	//glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(7.5, -30, 0, 15, 40, 15, m_pMonster[m_eMonterType] + 30, 21, 64);
	glPopMatrix();


	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

GLvoid CMonster::Draw(MonsterList _eMonster)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	//3차원 사각형을 만드는 함수(x, y, z, 너비, 높이, 깊이, 그림배열, 그림x값, 그림y값)
	glPushMatrix();
	//머리
	DrawCube(0, 30, 0, 30, 30, 30, m_pMonster[_eMonster], 64, 64);
	glPopMatrix();

	glPushMatrix();
	//몸통
	DrawCube(0, 0, 0, 30, 40, 15, m_pMonster[_eMonster] + 6, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//왼팔
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(-22.5, 0, 0, 15, 40, 15, m_pMonster[_eMonster] + 12, 21, 64);

	glPopMatrix();

	glPushMatrix();
	//오른팔
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_right_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(22.5, 0, 0, 15, 40, 15, m_pMonster[_eMonster] + 18, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//왼다리
	//glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_leg, 1, 0, 0);
	//glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(-7.5, -30, 0, 15, 40, 15, m_pMonster[_eMonster] + 24, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//오른다리
	//glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_right_leg, 1, 0, 0);
	//glTranslatef(0.f, -20.f, 0.0f);
	DrawCube(7.5, -30, 0, 15, 40, 15, m_pMonster[_eMonster] + 30, 21, 64);
	glPopMatrix();


	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

GLvoid CMonster::Update()
{
	if (fZ_left_arm >= 70.f)
	{
		fArm_move *= -1;
		fLeg_move *= -1;
	}

	else if (fZ_left_arm <= -70.f)
	{
		fArm_move *= -1;
		fLeg_move *= -1;
	}

	fZ_left_arm += fArm_move;
	fZ_right_arm -= fArm_move;
	fZ_left_leg -= fLeg_move;
	fZ_right_leg += fLeg_move;

	//if (m_CCharacter->GetClear() >= 2)
		//exit(1);

}

bool CMonster::Collision()
{
	return false;
}

bool CMonster::Collision(double _targetX, double _targetY, double _targetZ, double _targetRad)
{
	return pow((Monster_Vec.fX - _targetX), 2) + pow((Monster_Vec.fY - _targetY), 2) + pow((Monster_Vec.fZ - _targetZ), 2) < pow((40 + 1), 2);
}

bool CMonster::Collision(vector<CBullet>&_vpBullet, double _targetRad)
{
	//int a = 0;
	for (auto iter = _vpBullet.begin(); iter != _vpBullet.end(); ++iter)
	{
		if (pow((Monster_Vec.fX - ((*iter).GetPos().fX + (MAP_SIZE / 2))), 2) + pow((Monster_Vec.fY - (*iter).GetPos().fY), 2) + pow((Monster_Vec.fZ - ((*iter).GetPos().fZ + (MAP_SIZE / 2))), 2) <= pow((100 + 5 / 2), 2) == true)
		{
			PlaySound(TEXT("Sound\\맞춤.wav"), NULL, SND_ASYNC);
			if (_vpBullet.empty()) break;
			_vpBullet.erase(iter);
			iter = _vpBullet.begin();
			
			return true;
		}
	}

	return false;

}

GLvoid CMonster::DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)
{
	//앞면생성
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, *pBytes);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glEnd();

	//오른쪽 옆면
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, *(pBytes + 1));
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glEnd();

	//뒷면
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, *(pBytes + 2));
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

	//왼쪽 옆면
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, *(pBytes + 3));
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

	//밑면생성
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, *(pBytes + 4));
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

	/*윗면생성*/
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, *(pBytes + 5));
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

}

Vec3 CMonster::GetPosition()
{
	return Monster_Vec;
}

void CMonster::Chase(CCharacter*_pCharacter)
{
	float	fWidth = (_pCharacter->GetPosition().fX )- Monster_Vec.fX;
	float	fHeight = (_pCharacter->GetPosition().fZ) - Monster_Vec.fZ;

	float   fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);
	
	m_fAngle = acosf(fWidth / fDistance);

	if (Monster_Vec.fZ > _pCharacter->GetPosition().fZ)
	{
		m_fAngle = 2 * PI - m_fAngle;
	}

	Monster_Vec.fX += cosf(m_fAngle) * m_fSpeed;
	Monster_Vec.fZ -= sinf(m_fAngle) * m_fSpeed;
}

