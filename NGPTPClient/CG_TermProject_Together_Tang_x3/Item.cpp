#include "stdafx.h"
#include "Item.h"


CItem::CItem()
{
	m_fPosition = { 0, 50, 1800 };
}


CItem::~CItem()
{
}

void CItem::Draw()
{
	glPushMatrix();
	{
		//glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ZERO);
		glColor4f(1.0, 1.0, 1.0, 1);
		glTranslatef(m_fPosition.fX, m_fPosition.fY, m_fPosition.fZ);
		glRotatef(m_iAngle, 0, 1, 0);
		glutSolidCube(25);
		glPushMatrix();
		{
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0, 1.0, 0.0, 0.1);
			glRotatef(m_iAngle*-2, 0, 1, 0);
			glRotatef(-45, 0, 0, 1);
			glRotatef(-45, 1, 0, 0);
			glutSolidCube(50);
		}
		glPopMatrix();
		glDisable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		//glDisable(GL_CULL_FACE);
	}
	glPopMatrix();
}

void CItem::Update()
{
	m_iAngle = (m_iAngle + 3) % 360;
}
