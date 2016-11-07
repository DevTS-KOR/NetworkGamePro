#include "stdafx.h"
#include "Weather.h"


CWeather::CWeather()
{
}


CWeather::~CWeather()
{
}
void CWeather::Initialize()
{
	m_tPosition = { (float)(rand() % MAP_SIZE), (float)(rand() % 1000), (float)(rand() % MAP_SIZE) };
}

void CWeather::Update()
{
	if (m_tPosition.fY < 0)
		Initialize();
	m_tPosition.fY -= m_fSpeed;

}

void CWeather::DrawWeather()
{
	glDisable(GL_TEXTURE_2D);
	glTranslatef(m_tPosition.fX, m_tPosition.fY, m_tPosition.fZ);
		//m_fSpeed = (rand() % 11)*0.1 + 2;
		m_fSpeed = (rand() % 11)*0.1 + 2;
		glPushMatrix();
		glColor3ub(200, 255, 255);
		glScalef(0.2, 10, 0.2);
		glutSolidCube(5);
		glPopMatrix();


	glEnable(GL_TEXTURE_2D);
}

