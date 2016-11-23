#include "stdafx.h"
#include "InGame.h"
#include "Common.h"
#include "BitmapMgr.h"
#include "Monster.h"
#include "Building.h"
#include "Character.h"
#include "SceneMgr.h"
extern	int		g_iWindow_Width;
extern int		g_iWindow_Height;
#define	DYNAMIC(Class,Pointer)	dynamic_cast<Class>(Pointer)
DWORD WINAPI MyThread(LPVOID arg);
DWORD WINAPI RecvCharPosition(LPVOID arg);

CInGame::CInGame()
{
	m_fWorldAngle = {};
	
	m_fWorldTranslate.fX = 0;
	m_View = { 0 };
	m_fWorldTranslate.fY = 0;
	m_fWorldTranslate.fZ = 0;
	m_iMouseSens = 300;
}


CInGame::~CInGame()
{
}

GLvoid CInGame::Initialize(CBitmapMgr* _pBitmapMgr)
{
	m_pBitmapMgr = _pBitmapMgr;
	m_View = { 0, 0, -100 };
	m_iMouseSens = 300;
	m_eThunderState = STATE_START;
	m_dwRegenTime = GetTickCount();
	m_dwThunderTime = GetTickCount();
	for (size_t i = 0; i < 5; i++)
		m_pSkyBox[i] = m_pBitmapMgr->GetTexture(2, i);
	//m_iTextures = m_pBitmapMgr->GetTexture(SCENE_LOBBY)[0];
	m_pMonster = new CMonster(_pBitmapMgr);
	m_pBuilding = new CBuilding(_pBitmapMgr);
	m_pCharacter = new CCharacter(_pBitmapMgr);
	CSceneMgr::GetInst()->SetCharClass(m_pCharacter);

	for (size_t i = 0; i < 200; i++)
		cWeather[i].Initialize();
	for (size_t i = 0; i < 3; i++)
	{
		m_fAmbientLight[i] = 0.9;
		m_fDiffuseLight[i] = 0.9;
		m_fSpecularLight[i]=0.7;
	}
	m_fLightPos[0] = MAP_SIZE / 2;
	m_fLightPos[1] = 800;
	m_fLightPos[2] = MAP_SIZE / 2;
	Lights();

	//for(int i =0; i < 2; i++)
		//m_vpChracter.push_back(new CCharacter(m_pBitmapMgr, CSceneMgr::GetInitInfo()->Player1Pos.fX))
	dynamic_cast<CCharacter*>(m_pCharacter)->SetCharPosition(CSceneMgr::GetInitInfo());
	//glPushMatrix();
	//{
		//glTranslatef(-MAP_SIZE / 2, 0, -MAP_SIZE / 2);
		//CSceneMgr::GetInitInfo()
		//m_vpMonster.push_back(new CMonster(m_pBitmapMgr, CSceneMgr::GetInitInfo()->MonsterPos[5].fX/* + 1000.0f*/, CSceneMgr::GetInitInfo()->MonsterPos[5].fZ/* + 2000.0f*/));
		for (int i = 0; i < 10; i++)
			m_vpMonster.push_back(new CMonster(m_pBitmapMgr, CSceneMgr::GetInitInfo()->MonsterPos[i].fX, CSceneMgr::GetInitInfo()->MonsterPos[i].fZ));
	//}
	//glPopMatrix();
	m_iBlendcubeAngle = 0;
	m_iClear = 0;

	Sleep(500);
	hThread = CreateThread(NULL, 0, MyThread, NULL, 0, NULL);
	//WaitForSingleObject(hThread, INFINITE);
	//hThread = CreateThread(NULL, 0, RecvCharPosition, NULL, 0, NULL);
}

GLvoid CInGame::Render(GLvoid)
{
	glViewport(0, 0, g_iWindow_Width, g_iWindow_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, ((GLdouble)g_iWindow_Width) / (GLdouble)g_iWindow_Height, 1.0, 6000.0);
	//카메라
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//glFrontFace(GL_CCW);   // 앞면 설정  
	//glEnable(GL_CULL_FACE);  // 내부는 잘라낸다  

	glLoadIdentity();
	//Lights();
	// 저격 모드 토글
	glPushMatrix();
	{

		if (DYNAMIC(CCharacter*, m_pCharacter)->GetSniperMode() == true)
			DYNAMIC(CCharacter*, m_pCharacter)->SetSniper(-1500);
		else
			DYNAMIC(CCharacter*, m_pCharacter)->SetSniper(0);

		gluLookAt(DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fX, DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fY,DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fZ + DYNAMIC(CCharacter*, m_pCharacter)->GetSniper(),
			DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fX + m_View.fX * 2, DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fY + m_View.fY * 2, DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fZ + m_View.fZ + DYNAMIC(CCharacter*, m_pCharacter)->GetSniper(),
			0.0, 1.0, 0.0);


		
		for (auto iter = m_vBullet.begin(); iter != m_vBullet.end(); ++iter)
		{
			glPushMatrix();
			{
				glRotatef(-iter->GetRotate().fX, 1, 0, 0);
				glRotatef(-iter->GetRotate().fY, 0, 1, 0);
				glTranslatef(iter->GetPos().fX, iter->GetPos().fY, iter->GetPos().fZ);

				glColor3f(0.0f, 1.0f, 0.0f);
				glutSolidCube(1);
			}
			glPopMatrix();

		}
	
		glPushMatrix();
		{
			//glTranslatef(-MAP_SIZE / 2, 0, -MAP_SIZE / 2);
			for (size_t i = 0; i < 200; i++)
			{
				glPushMatrix();
				cWeather[i].DrawWeather();
				glPopMatrix();
			}
		//}
		//glPopMatrix();
		//glPushMatrix();
		//{
			//m_pCharacter->Draw();
			m_cItem.Draw();
		//}
		//glPopMatrix();
		//glPushMatrix();
		//{
			//glTranslatef(-MAP_SIZE / 2, 0, -MAP_SIZE / 2);
			Ground();
			//Bunker();
			SkyBox();
		//}
		//glPopMatrix();

		//glPushMatrix();
		//{
			//glTranslatef(-MAP_SIZE / 2, 0, -MAP_SIZE / 2);

			//glPushMatrix();
			//{
				m_pBuilding->Draw();
			//}
			//glPopMatrix();

			/*glPushMatrix();
			{
				glPushMatrix();
				{
					m_pCharacter->Draw();
				}
				glPopMatrix();
			}
			glPopMatrix();*/

			////glPushMatrix();
			////{
			//	for (auto iter = m_vpMonster.begin(); iter != m_vpMonster.end(); ++iter)
			//	{
			//		glPushMatrix();
			//		{
			//		
			//			glTranslatef(dynamic_cast<CMonster*>(*iter)->GetPosition().fX, dynamic_cast<CMonster*>(*iter)->GetPosition().fY, dynamic_cast<CMonster*>(*iter)->GetPosition().fZ);
			//			//if (dynamic_cast<CMonster*>(*iter)->Collision(m_vBullet,5) == false)
			//			glTranslatef(-MAP_SIZE / 2, 0, -MAP_SIZE / 2);
			//			(*iter)->Draw();
			//		}
			//		glPopMatrix();
			//	}
			//
			////}
			////glPopMatrix();
				glPushMatrix();
				{
					m_pCharacter->Draw();
					//m_vpMonster.clear();
					
					/*CSceneMgr::GetInst()->SetMonsterPos();
					auto iter = m_vpMonster.begin();
					
					for (int i = 0; i < 10; i++)
					{
						dynamic_cast<CMonster*>(*iter)->SetPosition(CSceneMgr::GetInst()->GetMonsterPos()->monsters[i].MonsterPos);
						iter++;
						if(i == 9)
							iter = m_vpMonster.begin();
					}*/

						/*m_vpMonster.push_back(new CMonster(m_pBitmapMgr, 
							CSceneMgr::GetInst()->GetMonsterPos()->monsters[i].MonsterPos.fX, 
							CSceneMgr::GetInst()->GetMonsterPos()->monsters[i].MonsterPos.fZ));*/
					
					/*for (auto iter = m_vpMonster.begin(); iter != m_vpMonster.end(); ++iter)
					{
						glPushMatrix();
						{
							glTranslatef(dynamic_cast<CMonster*>(*iter)->GetPosition().fX, dynamic_cast<CMonster*>(*iter)->GetPosition().fY, dynamic_cast<CMonster*>(*iter)->GetPosition().fZ);

							//glTranslatef(dynamic_cast<CMonster*>(*iter)->GetPosition().fX, dynamic_cast<CMonster*>(*iter)->GetPosition().fY, dynamic_cast<CMonster*>(*iter)->GetPosition().fZ);
							//if (dynamic_cast<CMonster*>(*iter)->Collision(m_vBullet,5) == false)\

							//왜 얘만?
							//glTranslatef(MAP_SIZE / 2, 0, MAP_SIZE / 2);
							//cout << "몬스터 : " << dynamic_cast<CMonster*>(*iter)->GetPosition().fX << " " << dynamic_cast<CMonster*>(*iter)->GetPosition().fY << " " << dynamic_cast<CMonster*>(*iter)->GetPosition().fZ << endl;
							(*iter)->Draw();
						}
						glPopMatrix();
					}*/

				}
				glPopMatrix();

		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, 800, 800);
		glOrtho(0.0, 800.0, 0.0, 800.0, -100.0, 2000.0);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix(); //2
		{
			//텍스처 파라미터 설정 --- (4)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// 텍스처 모드 설정
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
			// 텍스처 매핑 활성화
			glEnable(GL_TEXTURE_2D);
			//가운데 중앙 총
			//cout << boolalpha << DYNAMIC(CCharacter*, m_pCharacter)->GetSniperMode() << endl;
			if (DYNAMIC(CCharacter*, m_pCharacter)->GetSniperMode() == false)
			{
				glTranslated(370, 20, 0);
				glRotatef(45.f, 1, 0, 0);
				//Rect2(25, 28, 0, 75, 30, 110, pGun_top, 25, 17);
			}

			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (DYNAMIC(CCharacter*, m_pCharacter)->GetSniperMode() == false)
			{
				glColor3f(0.0f, 1.0f, 0.0f);
				glLineWidth(5);

				glColor3f(0.0f, 0.0f, 0.0f);
				glBegin(GL_LINES);
				glVertex3f(300, 400, 0.0);
				glVertex3f(380, 400, 0.0);
				glEnd();

				glColor3f(0.0f, 0.0f, 0.0f);
				glBegin(GL_LINES);
				glVertex3f(420, 400, 0.0);
				glVertex3f(500, 400, 0.0);
				glEnd();

				glColor3f(0.0f, 0.0f, 0.0f);
				glBegin(GL_LINES);
				glVertex3f(400, 300, 0.0);
				glVertex3f(400, 380, 0.0);
				glEnd();

				glColor3f(0.0f, 0.0f, 0.0f);
				glBegin(GL_LINES);
				glVertex3f(400, 420, 0.0);
				glVertex3f(400, 500, 0.0);
				glEnd();
			}

			else if (DYNAMIC(CCharacter*, m_pCharacter)->GetSniperMode() == true)
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				glTranslatef(400.0f, 400.0f, -1.f);
				glutSolidTorus(100, 475, 50, 50);
				glTranslatef(-400.0f, -400.0f, -1.f);

				glLineWidth(5);
				glBegin(GL_LINES);
				glVertex3f(-800.f, 400.0f, -1.0);
				glVertex3f(800.f, 400.0f, -1.0);
				glEnd();

				glBegin(GL_LINES);
				glVertex3f(400.f, -800.0f, -1.0);
				glVertex3f(400.f, 800.0f, -1.0);
				glEnd();
			}
		}
		glPopMatrix();
		

		
	}
	glPopMatrix();


}

GLvoid CInGame::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_UP,true);
		break;
	case 'a':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_LEFT, true);
		break;
	case 's':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_DOWN, true);
		break;
	case 'd':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_RIGHT, true);
		break;
	case 27:
		exit(0);
		break;
	case '1':
		static_cast<CCharacter*>(m_pCharacter)->SetSniperMode(false);
		//DYNAMIC(CCharacter*, m_pCharacter)->SetSniperMode(false);
		break;
	case '2':
		static_cast<CCharacter*>(m_pCharacter)->SetSniperMode(true);
	///	DYNAMIC(CCharacter*, m_pCharacter)->SetSniperMode(true);
		break;
	/*case 'a':
		m_fWorldAngle.fY += 1;
		break;
	case 'd':
		m_fWorldAngle.fY -= 1;
		break;
	case 'w':
		m_fWorldAngle.fX += 1;
		break;
	case 's':
		m_fWorldAngle.fX -= 1;
		break;*/
	default:
		break;
	}

	CSceneMgr::GetInst()->SetKey(key);
	CSceneMgr::GetInst()->SendKey(dynamic_cast<CCharacter*>(m_pCharacter)->GetPosition());
	//dynamic_cast<CCharacter*>(m_pCharacter)->SetCharRecvPosition(CSceneMgr::GetInitInfo(), CSceneMgr::GetPlayerPos());

	glutPostRedisplay();
}

GLvoid CInGame::SpecialKeyboard(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_UP:
		m_fWorldTranslate.fZ += 25;
		break;;
	case GLUT_KEY_DOWN:
		m_fWorldTranslate.fZ -= 25;
		break;
	case GLUT_KEY_LEFT:
		m_fWorldTranslate.fX += 25;
		break;
	case GLUT_KEY_RIGHT:
		m_fWorldTranslate.fX -= 25;
		break;
	case GLUT_KEY_HOME:
		m_fWorldTranslate.fY -= 25;
		break;
	case GLUT_KEY_END:
		m_fWorldTranslate.fY += 25;
		break;

	}
	glutPostRedisplay();
}

GLvoid CInGame::Update(int value)
{
	//printf("몬스터값 %f", CSceneMgr::GetInitInfo()->MonsterPos[0].fY);

	/*if (m_dwRegenTime + 5000 < GetTickCount())
	{
		m_vpMonster.push_back(new CMonster(m_pBitmapMgr, 500+rand()%500, 1200+rand()%1000));
		m_dwRegenTime = GetTickCount();
	}*/
	//m_vpMonster.push_back(new CMonster(m_pBitmapMgr));
	//UpdatePosition();


	for (auto iter = m_vpMonster.begin(); iter != m_vpMonster.end(); ++iter)
	{
	
		(*iter)->Update();
		if (static_cast<CMonster*>(*iter)->Collision(m_vBullet, 5))
		{
			m_iClear++;
			m_vpMonster.erase(iter);
			iter = m_vpMonster.begin();
		}
		if (m_vpMonster.empty()) break;


		//dynamic_cast<CMonster*>(*iter)->Chase(dynamic_cast<CCharacter*>(m_pCharacter));
	}
	for (auto iter = m_vBullet.begin(); iter != m_vBullet.end(); ++iter)
	{
		iter->Update();
	}
	for (size_t i = 0; i < 200; i++)
		cWeather[i].Update();
	m_pCharacter->Update();

	//m_iBlendcubeAngle = (m_iBlendcubeAngle + 3) % 360;
	m_cItem.Update();
	Weather(0);

	if (m_iClear >= 10)
		CSceneMgr::GetInst()->SetScene(SCENE_INRESULT, m_pBitmapMgr);

	//m_pMonster->Update();
}

DWORD WINAPI MyThread(LPVOID arg)
{
	
	CSceneMgr::GetInst()->RecvServer();
	
	return 0;
}

DWORD WINAPI RecvCharPosition(LPVOID arg)
{
	while (true)
	{
		CSceneMgr::GetInst()->RecvKey();
	}
	return 0;
}

GLvoid CInGame::Mouse(int button, int state, int x, int y)
{
	//cout << "움직임1" << endl;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		PlaySound(TEXT("Sound\\총격.wav"), NULL, SND_ASYNC);
		float sz = -10 * sin((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY* PI / 180) *cos((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX)* PI / 180));
		float sx = 10 * cos((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY)* PI / 180) * sin((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX)* PI / 180);
		float sy = -10 * cos((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY)* PI / 180);
		//cout << Charx << "// " << Chary << "// " << Charz << endl;
		//cout << Charx + Viewx * 2 <<  " // " << Chary + Viewy * 2 << " // " << Charz + Viewz << endl;
		m_vBullet.push_back(CBullet(
			DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fX + m_View.fX,
			DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fY + m_View.fY,
			DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fZ + m_View.fZ / 2,
			DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fX + m_View.fX * 2,
			DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fY + m_View.fY * 2,
			DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fZ + m_View.fZ)
			);

		//
		cout << "끼욬 : " << sx << ", " << sy << ", " << sz << endl;
		cout << "뷰뷰 : " << m_View.fX << ", " << m_View.fY << ", " << m_View.fZ << endl;
		//플레이어 위치가 나온다...
		cout << "위치? : " << DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fX << ", "
			<< DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fY << ", "
			<< DYNAMIC(CCharacter*, m_pCharacter)->GetPosition().fZ << endl;
	}
	glutPostRedisplay();
}

GLvoid CInGame::MouseMotionFunc(int x, int y)
{
	//cout << "움직임2" << endl;
	Vec2	MousePos;
	MousePos.fX = 400 - x;
	MousePos.fY = 400 - y;

	//마우스 휠을 느리게 하는수 밖에...
	//아니면 핸들값을 얻기위해 Client Init을 갈아엎어야 한다.
	/*if (MousePos.fX >= 200.f || MousePos.fX <= -200.0f)
		SetCursorPos(500.0f, 500.0f);

	if (MousePos.fY >= 200.f || MousePos.fY <= -200.0f)
		SetCursorPos(500.0f, 500.0f);*/

	m_MousePos.fX = (MousePos.fX);
	m_MousePos.fY = (MousePos.fY);

	if ((abs(m_MousePos.fX) < 100 && abs(m_MousePos.fY) < 100))
	{
		m_MousePos.fX = 0, m_MousePos.fY = 0;
	}

	DYNAMIC(CCharacter*, m_pCharacter)->SetCameraRotate(
		DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX + (m_MousePos.fX * 5.0f/**0.5*/ / m_iMouseSens)
		, 1);
	DYNAMIC(CCharacter*, m_pCharacter)->SetCameraRotate(
		DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY + (m_MousePos.fY * 5.0f/**0.5*/ / m_iMouseSens)
		, 2);


	//좌표가 반대로 되어있더라
	//if (abs(m_MousePos.fX) >= 400.f)
	//	m_MousePos.fX = 0.0f;
	//if(m_MousePos.fY <= )

	m_View.fZ = 50 * sin((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY)* PI / 180) * cos((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX)* PI / 180);
	m_View.fX = 50 * sin((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY)* PI / 180) * sin((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX)* PI / 180);
	m_View.fY = 50 * cos((DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY)* PI / 180);

	if (DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX <= -360 || DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX >= 360)
		DYNAMIC(CCharacter*, m_pCharacter)->SetCameraRotate(0, 1);

	if (DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY < -179)
		DYNAMIC(CCharacter*, m_pCharacter)->SetCameraRotate(-179, 2);

	else if (DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY > -1)
		DYNAMIC(CCharacter*, m_pCharacter)->SetCameraRotate(-1, 2);

	/*cout << "X " << m_View.fX <<
		"Y " << m_View.fY <<
		"Z " << m_View.fZ << endl;*/

	//cout << DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fX << ", " << DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fY << ", " << DYNAMIC(CCharacter*, m_pCharacter)->GetCameraRotate().fZ << endl;

	glutPostRedisplay();
}

GLvoid CInGame::Release(GLvoid)
{
	for (auto iter = m_vpMonster.begin(); iter != m_vpMonster.end(); ++iter)
	{
		if (*iter == nullptr)
			continue;
		else
			delete *iter;
	}
}

GLvoid CInGame::Ground()
{
	glPushMatrix();
	{
		//glColor4f(0.2f, 0.8f, 0.2f, 1.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pSkyBox[3]);
		glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 1.0f);	
		//glTexCoord2f(0.0f, 0.0f);	
		//glTexCoord2f(1.0f, 0.0f);	
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-2000, 0, -2000); glTexCoord2f(0.0f, 5.0f);
		glVertex3f(2000, 0, -2000); glTexCoord2f(5.0f, 5.0f);
		glVertex3f(2000, 0, 2000); glTexCoord2f(5.0f, 0.0f);
		glVertex3f(-2000, 0, 2000); glTexCoord2f(0.0f, 0.0f);
		glEnd();
		//glEnable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

		glPushMatrix();
		{
			glTranslatef(250, 250, 125);


		}
		glPopMatrix();
	}
	glPopMatrix();
}

GLvoid CInGame::Bunker()
{
	glPushMatrix();
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 1.0f);	
		//glTexCoord2f(0.0f, 0.0f);	
		//glTexCoord2f(1.0f, 0.0f);	
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, MAP_SIZE);
		glVertex3f(MAP_SIZE, 0, MAP_SIZE);
		glVertex3f(MAP_SIZE, 0, 0);
		glEnd();
		glPushMatrix();
		{
			glTranslatef(500, 0, 300);
			glColor4f(1.0f, 0.3f, 0.3f, 1.0f);
			glBegin(GL_QUADS);
			glVertex3f(0, 100, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 800);
			glVertex3f(0, 100, 800);

			glVertex3f(100, 100, 0);
			glVertex3f(0, 100, 0);
			glVertex3f(0, 100, 800);
			glVertex3f(100, 100, 800);
			//////////////////////////////////////////////////////////////////////////
			glVertex3f(0, 100, 800);
			glVertex3f(0, 0, 800);
			glVertex3f(800, 0, 800);
			glVertex3f(800, 100, 800);

			glVertex3f(0, 100, 700);
			glVertex3f(0, 100, 800);
			glVertex3f(800, 100, 800);
			glVertex3f(800, 100, 700);
			//////////////////////////////////////////////////////////////////////////
			glVertex3f(800, 100, 0);
			glVertex3f(800, 0, 0);
			glVertex3f(800, 0, 800);
			glVertex3f(800, 100, 800);

			glVertex3f(700, 100, 0);
			glVertex3f(800, 100, 0);
			glVertex3f(800, 100, 800);
			glVertex3f(700, 100, 800);
			//////////////////////////////////////////////////////////////////////////
			glVertex3f(800, 100, 0);
			glVertex3f(800, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 100, 0);

			glVertex3f(0, 100, 0);
			glVertex3f(0, 100, 100);
			glVertex3f(800, 100, 100);
			glVertex3f(800, 100, 0);
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			glVertex3f(100, 200, 100);
			glVertex3f(100, 100, 100);
			glVertex3f(100, 100, 700);
			glVertex3f(100, 200, 700);

			glVertex3f(200, 200, 100);
			glVertex3f(100, 200, 100);
			glVertex3f(100, 200, 700);
			glVertex3f(200, 200, 700);
			//////////////////////////////////////////////////////////////////////////
			glVertex3f(100, 200, 700);
			glVertex3f(100, 100, 700);
			glVertex3f(700, 100, 700);
			glVertex3f(700, 200, 700);

			glVertex3f(100, 200, 600);
			glVertex3f(100, 200, 700);
			glVertex3f(700, 200, 700);
			glVertex3f(700, 200, 600);
			//////////////////////////////////////////////////////////////////////////
			glVertex3f(700, 200, 100);
			glVertex3f(700, 100, 100);
			glVertex3f(700, 100, 700);
			glVertex3f(700, 200, 700);

			glVertex3f(600, 200, 100);
			glVertex3f(700, 200, 100);
			glVertex3f(700, 200, 700);
			glVertex3f(600, 200, 700);
			//////////////////////////////////////////////////////////////////////////
			glVertex3f(700, 200, 100);
			glVertex3f(700, 100, 100);
			glVertex3f(100, 100, 100);
			glVertex3f(100, 200, 100);

			glVertex3f(100, 200, 100);
			glVertex3f(100, 200, 200);
			glVertex3f(700, 200, 200);
			glVertex3f(700, 200, 100);

			glEnd();
		}
		glPopMatrix();


	}
	glPopMatrix();
}

GLvoid CInGame::SpecialKeyboardUp(int key, int x, int y)
{

}

GLvoid CInGame::KeyboardUp(unsigned char key, int x, int y)
{
	//cout << "Keyboard Up함수 호출" << endl;
	switch (key)
	{
	case 'w':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_UP, false);
		break;
	case 'a':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_LEFT, false);
		break;
	case 's':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_DOWN, false);
		break;
	case 'd':
		DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_RIGHT, false);
		break;
	}

	//CSceneMgr::GetInst()->SetKey(key);


	//if (key == 'w')
	//	DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_NONE);

	//if (key == 's')
	//	DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_NONE);

	//if (key == 'a')
	//	DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_NONE);

	//if (key == 'd')
	//	DYNAMIC(CCharacter*, m_pCharacter)->SetKeyUpstate(KEYUP_NONE);

	glutPostRedisplay();
}

GLvoid CInGame::SkyBox()
{
	glPushMatrix();
	{
		// 좌측
		glEnable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 1);
		//glTranslatef(-MAP_SIZE / 2, 0, -MAP_SIZE / 2);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 1600, 900, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pSkyBox[0]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(-2000, 1000, 2000);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(-2000, 0, 2000);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(-2000, 0, -2000);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(-2000, 1000, -2000);
		glEnd();

		//우측
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 1600, 900, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pSkyBox[1]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(2000, 1000, -2000);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(2000, 0, -2000);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(2000, 0, 2000);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(2000, 1000, 2000);
		glEnd();

		// 하늘
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pSkyBox[2]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(-2000, 1000, 2000);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(-2000, 1000, -2000);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(2000, 1000, -2000);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(2000, 1000, 2000);
		glEnd();

		// 뒤
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pSkyBox[4]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(-2000, 1000, -2000);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(-2000, 0, -2000);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(2000, 0, -2000);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(2000, 1000, -2000);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		/*glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(m_tPosition[0].fX, m_tPosition[0].fY, m_tPosition[0].fZ);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(m_tPosition[1].fX, m_tPosition[1].fY, m_tPosition[1].fZ);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(m_tPosition[2].fX, m_tPosition[2].fY, m_tPosition[2].fZ);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(m_tPosition[3].fX, m_tPosition[3].fY, m_tPosition[3].fZ);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(m_tPosition[0].fX, m_tPosition[0].fY, m_tPosition[0].fZ);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(m_tPosition[1].fX, m_tPosition[1].fY, m_tPosition[1].fZ);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(m_tPosition[2].fX, m_tPosition[2].fY, m_tPosition[2].fZ);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(m_tPosition[3].fX, m_tPosition[3].fY, m_tPosition[3].fZ);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(m_tPosition[0].fX, m_tPosition[0].fY, m_tPosition[0].fZ);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(m_tPosition[1].fX, m_tPosition[1].fY, m_tPosition[1].fZ);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(m_tPosition[2].fX, m_tPosition[2].fY, m_tPosition[2].fZ);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(m_tPosition[3].fX, m_tPosition[3].fY, m_tPosition[3].fZ);
		glEnd();*/
	}
	glPopMatrix();
}

GLvoid CInGame::Lights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_fAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_fDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_fSpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, m_fLightPos);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glEnable(GL_LIGHT0);
}

GLvoid CInGame::Item()
{
	
}



GLvoid CInGame::Weather(int value)
{

	switch (m_eThunderState)
	{
	case STATE_START:
		for (size_t i = 0; i < 4; i++)
		{
			m_fAmbientLight[i] = 1.0;
			m_fDiffuseLight[i] = 1.0;
		}
		m_eThunderState = STATE_PROGRESS;
		break;
	case STATE_PROGRESS:

		if (m_fDiffuseLight[0] > 0.01)
		{
			for (size_t i = 0; i < 4; i++)
			{
				m_fAmbientLight[i] -= 0.009;
				m_fDiffuseLight[i] -= 0.009;
			}
		}
		else if (m_dwThunderTime+5000< GetTickCount())
		{

			m_dwThunderTime = GetTickCount();
			m_eThunderState = STATE_END;
		}
		//g_iTimer += 1;
		//eThunderState = STATE_END;
		break;
	case STATE_END:
		for (size_t i = 0; i < 4; i++)
		{
			m_fAmbientLight[i] = 0.01f;
			m_fDiffuseLight[i] = 0.1f;
		}
		m_eThunderState = STATE_START;
		//for (size_t i = 0; i < 2; i++)
		//{
		//cLights[1].SetAmbientLight(0.01f, 0.01f, 0.01f);
		//cLights[1].SetDiffuseLight(0.1f, 0.1f, 0.1f);
		//cLights[1].SetSpecularLight(0.7f, 0.7f, 0.7f);
		////}
		////glDisable(GL_LIGHT2);
		//eThunderState = STATE_START;
		break;
	case STATE_NONE:
	
		break;
	}

}
