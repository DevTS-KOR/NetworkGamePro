#include "stdafx.h"
#include "Building.h"
#include "Common.h"


CBuilding::CBuilding()
{
}

CBuilding::CBuilding(CBitmapMgr* _pBitmapMgr) :m_pBitmapMgr(_pBitmapMgr)
{
	Initialize();
}


CBuilding::~CBuilding()
{
}

GLvoid CBuilding::Initialize()
{
	for (size_t i = 0; i < 3; i++)
		m_pBuilding[i] = m_pBitmapMgr->GetTexture(1,i);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 36; j++)
		{

			m_pMonster[i][j] = m_pBitmapMgr->GetTexture((MonsterList)i)[j];
		}
	}
	m_pContainer[0] = m_pBitmapMgr->GetTexture(3, 0);
	m_pContainer[1] = m_pBitmapMgr->GetTexture(3, 1);
}

GLvoid CBuilding::Draw()
{
	glPushMatrix();
	{
		
		glEnable(GL_TEXTURE_2D);
		//DrawCube(0, 30, 0, 30, 30, 30, m_pMonster[MONSTER_CAT], 64, 64);
		
	
		//glTranslatef(MAP_SIZE / 2 + 120, 790, 170);
		glPushMatrix();
		{

			glColor3ub(255, 255, 255);
			glPushMatrix();
			{
				glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBuilding[1]);
				//glColor3f(1.0f, 1.f, 1.f);
				glTranslatef(0, 0, 1);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(MAP_SIZE/2 - (400 / 2), 700 - (400 / 2), 100 + (200 / 2));
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(MAP_SIZE/2 + (400 / 2), 700 - (400 / 2), 100 + (200 / 2));
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(MAP_SIZE/2 + (400 / 2), 700 + (400 / 2), 100 + (200 / 2));
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(MAP_SIZE/2 - (400 / 2), 700 + (400 / 2), 100 + (200 / 2));
				glEnd();
			}
			glPopMatrix();
			//glTranslatef(0, 700, 500);
			
			DrawCube(MAP_SIZE / 2 + 130, 800, 200, 150, 150, 150, m_pBuilding[2], 512, 512,1);
		}
		glPopMatrix();

		DrawCube((MAP_SIZE / 2 - 200) / 2 +( MAP_SIZE / 2 + 200), 350, 100, MAP_SIZE / 2 - 200, 700, 200, m_pBuilding[0], 64, 64,0);
		DrawCube(0, 300, MAP_SIZE / 2, 100 , 300, 100, m_pBuilding[0], 64, 64, 0);
		DrawCube((MAP_SIZE / 2 - 200) / 2, 350, 100, MAP_SIZE / 2 - 200, 700, 200, m_pBuilding[0], 64, 64, 0);
		DrawCube(MAP_SIZE / 2, 700, 100, 400, 400, 200, m_pBuilding[0], 64, 64, 0);

		glPushMatrix();
		{
			glRotatef(90, 1, 0, 0);
			//DrawCube(0, 300, MAP_SIZE / 2, 100, 300, 100, m_pBuilding[0], 64, 64, 0);
		}
		glPopMatrix();


		DrawContainer((MAP_SIZE / 2) + 300, 100, MAP_SIZE / 2, 200, 200, 500, m_pContainer, 512, 256, 3);
		
		glPushMatrix();
		{
			/*float fX = (MAP_SIZE / 2)+300;
			float fY = 100;
			float fZ = MAP_SIZE / 2;
			float fWidth = 200;
			float fHigh = 200;
			float fDepth = 500;
			float fXsize = 256;
			float fYsize = 256;
			glEnable(GL_TEXTURE_2D);
			fXsize = 512;
			fYsize = 256;
			//坷弗率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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


			//哭率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//关搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//拉搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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
			glDisable(GL_TEXTURE_2D);*/
		}
		glPopMatrix();

		DrawContainer((MAP_SIZE / 4) + 500, 100, (MAP_SIZE / 2) + 800, 200, 200, 500, m_pContainer, 512, 256, 3);

		glPushMatrix();
		{
			/*float fX = (MAP_SIZE / 4) + 500;
			float fY = 100;
			float fZ = (MAP_SIZE / 2) + 800;
			float fWidth = 200;
			float fHigh = 200;
			float fDepth = 500;
			float fXsize = 256;
			float fYsize = 256;
			glEnable(GL_TEXTURE_2D);
			fXsize = 512;
			fYsize = 256;
			//坷弗率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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


			//哭率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//关搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//拉搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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
			glDisable(GL_TEXTURE_2D);*/
		}
		glPopMatrix();

		DrawContainer((MAP_SIZE / 2) + 100, 100, MAP_SIZE / 2, 200, 200, 500, m_pContainer, 512, 256, 3);

		glPushMatrix();
		{
			/*float fX = (MAP_SIZE / 2) + 100;
			float fY = 100;
			float fZ = MAP_SIZE / 2;
			float fWidth = 200;
			float fHigh = 200;
			float fDepth = 500;
			float fXsize = 256;
			float fYsize = 256;
			glEnable(GL_TEXTURE_2D);
			fXsize = 512;
			fYsize = 256;
			//坷弗率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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


			//哭率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//关搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//拉搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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
			glDisable(GL_TEXTURE_2D);*/

		}
		glPopMatrix();

		DrawContainer((MAP_SIZE / 2) + 800, 100, (MAP_SIZE / 2) + 600, 200, 200, 500, m_pContainer, 512, 256, 3);

		glPushMatrix();
		{
			/*float fX = (MAP_SIZE / 2) + 800;
			float fY = 100;
			float fZ = (MAP_SIZE / 2) + 600;
			float fWidth = 200;
			float fHigh = 200;
			float fDepth = 500;
			float fXsize = 256;
			float fYsize = 256;
			glEnable(GL_TEXTURE_2D);
			fXsize = 512;
			fYsize = 256;
			//坷弗率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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


			//哭率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//关搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//拉搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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
			glDisable(GL_TEXTURE_2D);*/

		}
		glPopMatrix();

		DrawContainer((MAP_SIZE / 2) + 700, 100, (MAP_SIZE / 2) - 300, 200, 200, 500, m_pContainer, 512, 256, 3);

		glPushMatrix();
		{
			/*float fX = (MAP_SIZE / 2) + 700;
			float fY = 100;
			float fZ = (MAP_SIZE / 2) - 300;
			float fWidth = 200;
			float fHigh = 200;
			float fDepth = 500;
			float fXsize = 256;
			float fYsize = 256;
			glEnable(GL_TEXTURE_2D);
			fXsize = 512;
			fYsize = 256;
			//坷弗率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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


			//哭率 糠搁
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//关搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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

			//拉搁积己
			glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
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
			glDisable(GL_TEXTURE_2D);*/

		}
		glPopMatrix();

		//DrawCube(0, 300, MAP_SIZE / 2, 100, 300, 100, m_pBuilding[0], 64, 64, 0);


		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}



GLvoid CBuilding::Update()
{

}

bool CBuilding::Collision()
{
	return false;
}

GLvoid CBuilding::SetType(BuildType _eType)
{
	glEnable(GL_TEXTURE_CUBE_MAP);
}
					
GLvoid CBuilding::DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)
{
	//菊搁积己
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

	//坷弗率 糠搁
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

	//缔搁
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

	//哭率 糠搁
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

	//关搁积己
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

	//拉搁积己
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

GLvoid CBuilding::DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pByte, float fXsize, float fYsize,int _type)
{
	if (_type == 0)
	{
		//菊搁积己
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
		glColor3f(1.0f, 1.f, 1.f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(5.0, 0.0f);
		glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(5.0, 5.0);
		glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(0.0f, 5.0);
		glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glEnd();

		//坷弗率 糠搁
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
		glColor3f(1.0f, 1.f, 1.f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
		glTexCoord2f(5.0f, 5.0f);
		glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glEnd();

		//缔搁
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
		//glColor3f(1.0f, 1.f, 1.f);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
		//glTexCoord2f(5.0f, 0.0f);
		//glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
		//glTexCoord2f(5.0f, 5.0f);
		//glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
		//glTexCoord2f(0.0f, 5.0f);
		//glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
		//glEnd();

		//哭率 糠搁
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
		glColor3f(1.0f, 1.f, 1.f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(5.0f, 5.0f);
		glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
		glEnd();

		//关搁积己
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
		//glColor3f(1.0f, 1.f, 1.f);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		//glTexCoord2f(5.0f, 0.0f);
		//glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		//glTexCoord2f(5.0f, 5.0f);
		//glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
		//glTexCoord2f(0.0f, 5.0f);
		//glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
		//glEnd();

		//拉搁积己
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
		glColor3f(1.0f, 1.f, 1.f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(5.0f, 0.0f);
		glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(5.0f, 5.0f);
		glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
		glTexCoord2f(0.0f, 5.0f);
		glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
		glEnd();
	}
	else
	{
		//菊搁积己
		glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
		glColor3f(1.0f, 1.f, 1.f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(1.0, 0.0f);
		glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glTexCoord2f(0.0f, 1.0);
		glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
		glEnd();

		glDisable(GL_TEXTURE_2D);
		//坷弗率 糠搁
	//	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
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

		//哭率 糠搁
	//	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
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


		//拉搁积己
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte);
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
		glEnable(GL_TEXTURE_2D);
	}
	
}

GLvoid CBuilding::DrawContainer(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte ** pByte, float fXsize, float fYsize, int _type)
{
	//菊搁积己
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte[1]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0, 0.5);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(0.0f, 0.5);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glEnd();

	//缔搁
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte[1]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

	//坷弗率 糠搁
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pContainer[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte[0]);
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


	//哭率 糠搁
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte[0]);
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

	//关搁积己
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte[0]);
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

	//拉搁积己
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pByte[0]);
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
	//glDisable(GL_TEXTURE_2D);
}

void CBuilding::drawBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
		{ -1.0, 0.0, 0.0 }, // 谅
		{ 0.0, 1.0, 0.0 }, // 惑
		{ 1.0, 0.0, 0.0 }, // 快
		{ 0.0, -1.0, 0.0 }, // 窍
		{ 0.0, 0.0, 1.0 }, // 菊
		{ 0.0, 0.0, -1.0 } // 第
	};
	static GLint faces[6][4] =
	{
		{ 0, 1, 2, 3 },
		{ 3, 2, 6, 7 },
		{ 7, 6, 5, 4 },
		{ 4, 5, 1, 0 },
		{ 5, 6, 2, 1 },
		{ 7, 4, 0, 3 }
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}