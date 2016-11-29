#include "stdafx.h"
#include "Character.h"
#include "BitmapMgr.h"

CCharacter::CCharacter(CBitmapMgr* _pBitmapMgr) : m_pBitmapMgr(_pBitmapMgr)
{
	Initialize();
}

CCharacter::CCharacter(CBitmapMgr * _pBitmapMgr, float _fX, float _fZ, float _fX2, float _fZ2)
{
	Initialize();
	m_tPosition.fX = _fX;
	m_tPosition.fY = 50.f;
	m_tPosition.fZ = _fZ;

	m_tPosition2.fX = _fX2;
	m_tPosition2.fY = 50.0f;
	m_tPosition2.fZ = _fZ2;

	m_Rotate = 0.0f;
}


CCharacter::~CCharacter()
{
}

GLvoid CCharacter::Initialize()
{
	//m_tPosition = { 0, 100, MAP_SIZE / 2 };	//카메라의 좌표이다.
	m_fCameraRotate = { 0, -90, 0 };
	m_fSpeed = 5;
	m_fSniper = 0;
	m_iCameradistance = 0;
	m_bIsSniperMode = false;
	m_ePlayerType = (PlayerList)0;

	fZ_left_arm = 0.0f;
	fZ_right_arm = 0.0f;
	fZ_left_leg = 0.0f;
	fZ_right_leg = 0.0f;
	fArm_move = 10.0f;
	fLeg_move = 5.0f;

	for(int j = 0; j < 36; j++)
		m_pPlayer[0][j] = m_pBitmapMgr->GetTexture((PlayerList)0)[j];

	for (size_t i = 0; i < 4; i++)
		m_bKeyUpState[i] = false;
	/*cout << "X " << m_tPosition.fX << "Y " << m_tPosition.fY << "Z " << m_tPosition.fZ << endl;*/
}

GLvoid CCharacter::Draw()
{
	glEnable(GL_TEXTURE_2D);
	//if (m_InitInfo->playerIndex == 1)
	//{

	
		glPushMatrix();
		
		SetCameraRecv();
		//glRotatef(180.0f, 0, 1, 0);
		//3차원 사각형을 만드는 함수(x, y, z, 너비, 높이, 깊이, 그림배열, 그림x값, 그림y값)
		glPushMatrix();
		//머리
		DrawCube(m_tPosition2.fX, m_tPosition2.fY + 30, m_tPosition2.fZ + 20, 30, 30, 30, m_pPlayer[m_ePlayerType], 64, 64);
		glPopMatrix();

		glPushMatrix();
		//몸통
		//cout << "그려지고 있어요" << endl;
		DrawCube(m_tPosition2.fX, m_tPosition2.fY, m_tPosition2.fZ + 20, 30, 40, 15, m_pPlayer[m_ePlayerType] + 6, 64, 64);
		glPopMatrix();

		glPushMatrix();
		//왼팔
		glPushMatrix();
		glTranslatef(0.f, 20.f, 0.0f);
		glRotatef(fZ_left_arm, 1, 0, 0);
		glTranslatef(0.f, -20.f, 0.0f);
		glPopMatrix();
		DrawCube(m_tPosition2.fX - 22.5, m_tPosition2.fY, m_tPosition2.fZ + 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 12, 21, 64);

		glPopMatrix();

		glPushMatrix();
		//오른팔
		glPushMatrix();
		glTranslatef(0.f, 20.f, 0.0f);
		glRotatef(fZ_right_arm, 1, 0, 0);
		glTranslatef(0.f, -20.f, 0.0f);
		glPopMatrix();
		DrawCube(m_tPosition2.fX + 22.5, m_tPosition2.fY, m_tPosition2.fZ + 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 18, 21, 64);
		glPopMatrix();

		glPushMatrix();
		//왼다리
		//glTranslatef(0.f, 20.f, 0.0f);
		glPushMatrix();
		glRotatef(fZ_left_leg, 1, 0, 0);
		glPopMatrix();
		//glTranslatef(0.f, -20.f, 0.0f);
		DrawCube(m_tPosition2.fX - 7.5, m_tPosition2.fY - 30, m_tPosition2.fZ + 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 24, 21, 64);
		glPopMatrix();

		glPushMatrix();
		//오른다리
		glPushMatrix();
		//glTranslatef(0.f, 20.f, 0.0f);
		glRotatef(fZ_right_leg, 1, 0, 0);
		glPopMatrix();
		//glTranslatef(0.f, -20.f, 0.0f);
		DrawCube(m_tPosition2.fX + 7.5, m_tPosition2.fY - 30, m_tPosition2.fZ + 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 30, 21, 64);
		glPopMatrix();

		//glRotatef(-180.0f, 0, 1, 0);
		glPopMatrix();
	//}

	/*if (m_InitInfo->playerIndex == 2)
	{
		glPushMatrix();
		//3차원 사각형을 만드는 함수(x, y, z, 너비, 높이, 깊이, 그림배열, 그림x값, 그림y값)
		glPushMatrix();
		//머리
		DrawCube(m_tPosition.fX, m_tPosition.fY + 30, m_tPosition.fZ + 20, 30, 30, 30, m_pPlayer[m_ePlayerType], 64, 64);
		glPopMatrix();

		glPushMatrix();
		//몸통
		//cout << "그려지고 있어요" << endl;
		DrawCube(m_tPosition.fX, m_tPosition.fY, m_tPosition.fZ + 20, 30, 40, 15, m_pPlayer[m_ePlayerType] + 6, 64, 64);
		glPopMatrix();

		glPushMatrix();
		//왼팔
		glTranslatef(0.f, 20.f, 0.0f);
		glRotatef(fZ_left_arm, 1, 0, 0);
		glTranslatef(0.f, -20.f, 0.0f);
		DrawCube(m_tPosition.fX - 22.5, m_tPosition.fY, m_tPosition.fZ + 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 12, 21, 64);

		glPopMatrix();

		glPushMatrix();
		//오른팔
		glTranslatef(0.f, 20.f, 0.0f);
		glRotatef(fZ_right_arm, 1, 0, 0);
		glTranslatef(0.f, -20.f, 0.0f);
		DrawCube(m_tPosition.fX + 22.5, m_tPosition.fY, m_tPosition.fZ + 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 18, 21, 64);
		glPopMatrix();

		glPushMatrix();
		//왼다리
		//glTranslatef(0.f, 20.f, 0.0f);
		glRotatef(fZ_left_leg, 1, 0, 0);
		//glTranslatef(0.f, -20.f, 0.0f);
		DrawCube(m_tPosition.fX - 7.5, m_tPosition.fY - 30, m_tPosition.fZ + 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 24, 21, 64);
		glPopMatrix();

		glPushMatrix();
		//오른다리
		//glTranslatef(0.f, 20.f, 0.0f);
		glRotatef(fZ_right_leg, 1, 0, 0);
		//glTranslatef(0.f, -20.f, 0.0f);
		DrawCube(m_tPosition.fX + 7.5, m_tPosition.fY - 30, m_tPosition.fZ - 20, 15, 40, 15, m_pPlayer[m_ePlayerType] + 30, 21, 64);
		glPopMatrix();


		glPopMatrix();
	}*/

	glDisable(GL_TEXTURE_2D);
}

GLvoid CCharacter::Update()
{
	if (m_bKeyUpState[KEYUP_UP])		//w
	{
		m_tPosition.fX += m_fSpeed * cos((-m_fCameraRotate.fX - 90) * PI / 180);
		m_tPosition.fZ += m_fSpeed * sin((-m_fCameraRotate.fX - 90) * PI / 180);
	}
	if (m_bKeyUpState[KEYUP_DOWN])		//s
	{
		m_tPosition.fX -= m_fSpeed * cos((-m_fCameraRotate.fX - 90) * PI / 180);
		m_tPosition.fZ -= m_fSpeed * sin((-m_fCameraRotate.fX - 90) * PI / 180);
	}
	if (m_bKeyUpState[KEYUP_LEFT])
	{
		m_tPosition.fX -= m_fSpeed * cos((-m_fCameraRotate.fX) * PI / 180);
		m_tPosition.fZ -= m_fSpeed * sin((-m_fCameraRotate.fX) * PI / 180);
	}
	if (m_bKeyUpState[KEYUP_RIGHT])
	{
		m_tPosition.fX += m_fSpeed * cos((-m_fCameraRotate.fX) * PI / 180);
		m_tPosition.fZ += m_fSpeed * sin((-m_fCameraRotate.fX) * PI / 180);
	}

	//cout <<"캐릭터 : " << m_tPosition.fX << " " << m_tPosition.fY << " " << m_tPosition.fZ << endl;

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

	//cout << fZ_left_arm << endl;
	fZ_left_arm += fArm_move;
	fZ_right_arm -= fArm_move;
	fZ_left_leg -= fLeg_move;
	fZ_right_leg += fLeg_move;

}

bool CCharacter::Collision()
{
	return 0;
}

GLvoid CCharacter::DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)
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

GLfloat CCharacter::GetSpeed()
{
	return m_fSpeed;
}

Vec3 CCharacter::GetPosition()
{
	return m_tPosition;
}

Vec3 CCharacter::GetPosition2()
{
	return m_tPosition2;
}


bool CCharacter::GetSniperMode()
{
	return m_bIsSniperMode;
}

float CCharacter::GetSniper()
{
	return m_fSniper;
}

void CCharacter::SetSniper(float _fSniper)
{
	m_fSniper = _fSniper;
}

void CCharacter::SetSniperMode(bool _bMode)
{
	m_bIsSniperMode = _bMode;
}

bool CCharacter::GetKeyUpState(KeyUpState _eState)
{
	return m_bKeyUpState[_eState];
}

void CCharacter::SetKeyUpstate(KeyUpState _eState,bool _bState)
{

	m_bKeyUpState[_eState] = _bState;

}

Vec3 CCharacter::GetCameraRotate()
{
	return m_fCameraRotate;
}

Vec3 CCharacter::GetCameraPos()
{
	return m_fCameraPos;
}

void CCharacter::SetCameraPos(float _fPos,int _Type)
{
	if(_Type == 1)
		m_fCameraPos.fX = _fPos;
	else if(_Type == 2)
		m_fCameraPos.fY = _fPos;
	else if(_Type == 3)
		m_fCameraPos.fZ = _fPos;

	/*switch (_Type)
	{
	case 1:
		m_fCameraPos.fX = _fPos;
		break;
	case 2:
		m_fCameraPos.fY = _fPos;
		break;
	case 3:
		m_fCameraPos.fZ = _fPos;
		break;
	default:
		break;
	}*/
}

void CCharacter::SetCameraRotate(float _fPos, int _Type)
{
	if (_Type == 1)
		m_fCameraRotate.fX = _fPos;
	else if (_Type == 2)
		m_fCameraRotate.fY = _fPos;
	else if (_Type == 3)
		m_fCameraRotate.fZ = _fPos;

	/*switch (_Type)
	{
	case 1:
		m_fCameraRotate.fX = _fPos;
		break;
	case 2:
		m_fCameraRotate.fY = _fPos;
		break;
	case 3:
		m_fCameraRotate.fZ = _fPos;
		break;
	default:
		break;
	}*/
}

int CCharacter::GetCameraDistance()
{
	return m_iCameradistance;
}

void CCharacter::SetCameraDistance(int _iDistance)
{
	m_iCameradistance = _iDistance;
}

void CCharacter::SetCharPosition(InitInfo* _InitInfo)
{
	m_InitInfo = _InitInfo;
	//cout << "인덱스 번호 : " << m_InitInfo->playerIndex << endl;
	if (_InitInfo->playerIndex == 1)
	{
		m_tPosition = _InitInfo->Player1Pos;
		m_tPosition2 = _InitInfo->Player2Pos;
	}
	else if (_InitInfo->playerIndex == 2)
	{
		m_tPosition = _InitInfo->Player2Pos;
		m_tPosition2 = _InitInfo->Player1Pos;
	}
}

void CCharacter::SetCharRecvPosition(InitInfo* _InitInfo, PlayerInfo _PlayerInfo)
{

		//cout << "들어온값 : " << _PlayerInfo.PlayerPos.fX << ", " << _PlayerInfo.PlayerPos.fY << ", " << _PlayerInfo.PlayerPos.fZ << endl;
	m_tPosition2 = _PlayerInfo.PlayerPos;
	m_Rotate = _PlayerInfo.CameraDir.fX;

	/*if (_InitInfo->playerIndex == _PlayerInfo->playerIndex)
	{
		m_tPosition = _PlayerInfo->PlayerPos;
	}*/

}

void CCharacter::SetCameraRecv()
{
	glTranslatef(m_tPosition2.fX, m_tPosition2.fY, m_tPosition2.fZ);
	glRotatef(m_Rotate, 0, 1, 0);
	glTranslatef(-m_tPosition2.fX, -m_tPosition2.fY, -m_tPosition2.fZ);
}
