#include "stdafx.h"
#include "BitmapMgr.h"


GLubyte * CBitmapMgr::LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	fopen_s(&fp, filename, "rb");
	if (fp == NULL){
		printf("File Open Error! Please Check filename");
		return NULL;
	}
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		printf("File Read Error");
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		printf("This is not Bitmap File");
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		printf("Memory Allocation Error");
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		printf("Cannot Read Bitmap Info Header");
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		printf("Memory Allocation Error2");
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		printf("Bitmap Data Save Error");
		return NULL;
	}
	fclose(fp);
	return bits;
}

void CBitmapMgr::TextureInit()
{
	glGenTextures(4, g_ivTextures[DRAW_LOGO]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[DRAW_LOGO][0]);
	m_pBytes[DRAW_LOGO][0] = LoadDIBitmap(m_pszFilename[DRAW_LOGO][0], &m_pInfo[DRAW_LOGO][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[0][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(4, g_ivTextures[DRAW_LOBBY]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[DRAW_LOBBY][0]);
	m_pBytes[DRAW_LOBBY][0] = LoadDIBitmap(m_pszFilename[DRAW_LOBBY][0], &m_pInfo[DRAW_LOBBY][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[DRAW_LOBBY][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glGenTextures(4, g_ivTextures[2]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[2][0]);
	m_pBytes[2][0] = LoadDIBitmap(m_pszFilename[2][0], &m_pInfo[2][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 800, 800, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[2][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glGenTextures(4, g_ivTextures[DRAW_MONSTER]);
	//glBindTexture(GL_TEXTURE_2D, g_ivTextures[DRAW_MONSTER][0]);
	//m_pBytes[DRAW_MONSTER][0] = LoadDIBitmap(m_pszFilename[DRAW_MONSTER][0], &m_pInfo[DRAW_MONSTER][0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[DRAW_MONSTER][0]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	for (size_t j = 0; j < 36; j++)
	{
		m_pPlayerBytes[0][j] = LoadDIBitmap(m_pszPlayerFilename[0][j], &m_pInfo2);
	}

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 36; j++)
		{
			m_pMonsterBytes[i][j] = LoadDIBitmap(m_pszMonsterFilename[i][j], &m_pInfo2);
		}
	}

	m_pBrick[0] = LoadDIBitmap("Texture/etc/_Brick.bmp", &m_pInfo2);
	m_pBrick[1] = LoadDIBitmap("Texture/etc/kpu_brick.bmp", &m_pInfo2);
	m_pBrick[2] = LoadDIBitmap("Texture/etc/clock.bmp", &m_pInfo2);

	m_pContainer[0] = LoadDIBitmap("Texture/Building/Container/side.bmp", &m_pInfo2);
	m_pContainer[1] = LoadDIBitmap("Texture/Building/Container/front.bmp", &m_pInfo2);

	m_pSkyBox[0] = LoadDIBitmap("Texture/etc/_left.bmp", &m_pInfo2);
	m_pSkyBox[1] = LoadDIBitmap("Texture/etc/_right.bmp", &m_pInfo2);
	m_pSkyBox[2] = LoadDIBitmap("Texture/etc/sky2.bmp", &m_pInfo2);
	m_pSkyBox[3] = LoadDIBitmap("Texture/etc/grass.bmp", &m_pInfo2);
	m_pSkyBox[4] = LoadDIBitmap("Texture/etc/_back.bmp", &m_pInfo2);

	//텍스처 파라미터 설정 --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

}


CBitmapMgr::CBitmapMgr()
{

}

CBitmapMgr::~CBitmapMgr()
{

}

void CBitmapMgr::Initialize()
{
	m_pszFilename[DRAW_LOGO][0] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOGO][1] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOGO][2] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOGO][3] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOBBY][0] = "Texture/Lobby.bmp";
	m_pszFilename[DRAW_LOBBY][1] = "Texture/Lobby.bmp";
	m_pszFilename[DRAW_LOBBY][2] = "Texture/Lobby.bmp";
	m_pszFilename[DRAW_LOBBY][3] = "Texture/Lobby.bmp";
	m_pszFilename[2][0] = "Texture/_result.bmp";
	m_pszFilename[2][1] = "Texture/_result.bmp";
	m_pszFilename[2][2] = "Texture/_result.bmp";
	m_pszFilename[2][3] = "Texture/_result.bmp";


	#pragma region MonsterTexture
	m_pszMonsterFilename[MONSTER_SPIDER][0] = "Texture/Monster/Spider/얼굴.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][1] = "Texture/Monster/Spider/얼굴오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][2] = "Texture/Monster/Spider/얼굴뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][3] = "Texture/Monster/Spider/얼굴왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][4] = "Texture/Monster/Spider/얼굴아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][5] = "Texture/Monster/Spider/얼굴위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][6] = "Texture/Monster/Spider/몸통앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][7] = "Texture/Monster/Spider/몸통오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][8] = "Texture/Monster/Spider/몸통뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][9] = "Texture/Monster/Spider/몸통왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][10] = "Texture/Monster/Spider/몸통아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][11] = "Texture/Monster/Spider/몸통위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][12] = "Texture/Monster/Spider/왼팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][13] = "Texture/Monster/Spider/왼팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][14] = "Texture/Monster/Spider/왼팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][15] = "Texture/Monster/Spider/왼팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][16] = "Texture/Monster/Spider/왼팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][17] = "Texture/Monster/Spider/왼팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][18] = "Texture/Monster/Spider/오른팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][19] = "Texture/Monster/Spider/오른팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][20] = "Texture/Monster/Spider/오른팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][21] = "Texture/Monster/Spider/오른팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][22] = "Texture/Monster/Spider/오른팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][23] = "Texture/Monster/Spider/오른팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][24] = "Texture/Monster/Spider/왼발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][25] = "Texture/Monster/Spider/왼발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][26] = "Texture/Monster/Spider/왼발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][27] = "Texture/Monster/Spider/왼발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][28] = "Texture/Monster/Spider/왼발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][29] = "Texture/Monster/Spider/왼발위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][30] = "Texture/Monster/Spider/오른발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][31] = "Texture/Monster/Spider/오른발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][32] = "Texture/Monster/Spider/오른발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][33] = "Texture/Monster/Spider/오른발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][34] = "Texture/Monster/Spider/오른발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][35] = "Texture/Monster/Spider/오른발위쪽.bmp";

	m_pszMonsterFilename[MONSTER_IRON][0] = "Texture/Monster/Iron/아이언맨_얼굴앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][1] = "Texture/Monster/Iron/아이언맨_얼굴오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][2] = "Texture/Monster/Iron/아이언맨_얼굴뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][3] = "Texture/Monster/Iron/아이언맨_얼굴왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][4] = "Texture/Monster/Iron/아이언맨_얼굴아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][5] = "Texture/Monster/Iron/아이언맨_얼굴위쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][6] = "Texture/Monster/Iron/아이언맨_몸통앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][7] = "Texture/Monster/Iron/아이언맨_몸통오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][8] = "Texture/Monster/Iron/아이언맨_몸통뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][9] = "Texture/Monster/Iron/아이언맨_몸통왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][10] = "Texture/Monster/Iron/아이언맨_몸통아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][11] = "Texture/Monster/Iron/아이언맨_몸통위쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][12] = "Texture/Monster/Iron/아이언맨_왼팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][13] = "Texture/Monster/Iron/아이언맨_왼팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][14] = "Texture/Monster/Iron/아이언맨_왼팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][15] = "Texture/Monster/Iron/아이언맨_왼팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][16] = "Texture/Monster/Iron/아이언맨_왼팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][17] = "Texture/Monster/Iron/아이언맨_왼팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][18] = "Texture/Monster/Iron/아이언맨_오른팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][19] = "Texture/Monster/Iron/아이언맨_오른팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][20] = "Texture/Monster/Iron/아이언맨_오른팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][21] = "Texture/Monster/Iron/아이언맨_오른팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][22] = "Texture/Monster/Iron/아이언맨_오른팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][23] = "Texture/Monster/Iron/아이언맨_오른팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][24] = "Texture/Monster/Iron/아이언맨_왼발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][25] = "Texture/Monster/Iron/아이언맨_왼발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][26] = "Texture/Monster/Iron/아이언맨_왼발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][27] = "Texture/Monster/Iron/아이언맨_왼발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][28] = "Texture/Monster/Iron/아이언맨_왼발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][29] = "Texture/Monster/Iron/아이언맨_왼발위쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][30] = "Texture/Monster/Iron/아이언맨_오른발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][31] = "Texture/Monster/Iron/아이언맨_오른발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][32] = "Texture/Monster/Iron/아이언맨_오른발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][33] = "Texture/Monster/Iron/아이언맨_오른발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][34] = "Texture/Monster/Iron/아이언맨_오른발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_IRON][35] = "Texture/Monster/Iron/아이언맨_오른발위쪽.bmp";

	m_pszMonsterFilename[MONSTER_SUPER][0] = "Texture/Monster/Super/슈퍼맨_얼굴앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][1] = "Texture/Monster/Super/슈퍼맨_얼굴오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][2] = "Texture/Monster/Super/슈퍼맨_얼굴뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][3] = "Texture/Monster/Super/슈퍼맨_얼굴왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][4] = "Texture/Monster/Super/슈퍼맨_얼굴아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][5] = "Texture/Monster/Super/슈퍼맨_얼굴위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][6] = "Texture/Monster/Super/슈퍼맨_몸통앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][7] = "Texture/Monster/Super/슈퍼맨_몸통오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][8] = "Texture/Monster/Super/슈퍼맨_몸통뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][9] = "Texture/Monster/Super/슈퍼맨_몸통왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][10] = "Texture/Monster/Super/슈퍼맨_몸통아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][11] = "Texture/Monster/Super/슈퍼맨_몸통위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][12] = "Texture/Monster/Super/슈퍼맨_왼팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][13] = "Texture/Monster/Super/슈퍼맨_왼팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][14] = "Texture/Monster/Super/슈퍼맨_왼팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][15] = "Texture/Monster/Super/슈퍼맨_왼팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][16] = "Texture/Monster/Super/슈퍼맨_왼팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][17] = "Texture/Monster/Super/슈퍼맨_왼팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][18] = "Texture/Monster/Super/슈퍼맨_오른팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][19] = "Texture/Monster/Super/슈퍼맨_오른팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][20] = "Texture/Monster/Super/슈퍼맨_오른팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][21] = "Texture/Monster/Super/슈퍼맨_오른팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][22] = "Texture/Monster/Super/슈퍼맨_오른팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][23] = "Texture/Monster/Super/슈퍼맨_오른팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][24] = "Texture/Monster/Super/슈퍼맨_왼발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][25] = "Texture/Monster/Super/슈퍼맨_왼발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][26] = "Texture/Monster/Super/슈퍼맨_왼발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][27] = "Texture/Monster/Super/슈퍼맨_왼발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][28] = "Texture/Monster/Super/슈퍼맨_왼발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][29] = "Texture/Monster/Super/슈퍼맨_왼발위쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][30] = "Texture/Monster/Super/슈퍼맨_오른발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][31] = "Texture/Monster/Super/슈퍼맨_오른발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][32] = "Texture/Monster/Super/슈퍼맨_오른발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][33] = "Texture/Monster/Super/슈퍼맨_오른발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][34] = "Texture/Monster/Super/슈퍼맨_오른발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][35] = "Texture/Monster/Super/슈퍼맨_오른발위쪽.bmp";

	m_pszMonsterFilename[MONSTER_CAT][0] = "Texture/Monster/Cat/고양이_얼굴앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][1] = "Texture/Monster/Cat/고양이_얼굴오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][2] = "Texture/Monster/Cat/고양이_얼굴뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][3] = "Texture/Monster/Cat/고양이_얼굴왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][4] = "Texture/Monster/Cat/고양이_얼굴아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][5] = "Texture/Monster/Cat/고양이_얼굴위쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][6] = "Texture/Monster/Cat/고양이_몸통앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][7] = "Texture/Monster/Cat/고양이_몸통오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][8] = "Texture/Monster/Cat/고양이_몸통뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][9] = "Texture/Monster/Cat/고양이_몸통왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][10] = "Texture/Monster/Cat/고양이_몸통아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][11] = "Texture/Monster/Cat/고양이_몸통위쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][12] = "Texture/Monster/Cat/고양이_왼팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][13] = "Texture/Monster/Cat/고양이_왼팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][14] = "Texture/Monster/Cat/고양이_왼팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][15] = "Texture/Monster/Cat/고양이_왼팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][16] = "Texture/Monster/Cat/고양이_왼팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][17] = "Texture/Monster/Cat/고양이_왼팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][18] = "Texture/Monster/Cat/고양이_오른팔앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][19] = "Texture/Monster/Cat/고양이_오른팔오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][20] = "Texture/Monster/Cat/고양이_오른팔뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][21] = "Texture/Monster/Cat/고양이_오른팔왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][22] = "Texture/Monster/Cat/고양이_오른팔아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][23] = "Texture/Monster/Cat/고양이_오른팔위쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][24] = "Texture/Monster/Cat/고양이_왼발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][25] = "Texture/Monster/Cat/고양이_왼발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][26] = "Texture/Monster/Cat/고양이_왼발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][27] = "Texture/Monster/Cat/고양이_왼발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][28] = "Texture/Monster/Cat/고양이_왼발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][29] = "Texture/Monster/Cat/고양이_왼발위쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][30] = "Texture/Monster/Cat/고양이_오른발앞쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][31] = "Texture/Monster/Cat/고양이_오른발오른쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][32] = "Texture/Monster/Cat/고양이_오른발뒤쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][33] = "Texture/Monster/Cat/고양이_오른발왼쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][34] = "Texture/Monster/Cat/고양이_오른발아래쪽.bmp";
	m_pszMonsterFilename[MONSTER_CAT][35] = "Texture/Monster/Cat/고양이_오른발위쪽.bmp";
#pragma endregion MonsterTexture

	m_pszPlayerFilename[PLAYER_SOLDIER][0] = "Texture/Character/군인_얼굴앞쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][1] = "Texture/Character/군인_얼굴오른쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][2] = "Texture/Character/군인_얼굴뒤쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][3] = "Texture/Character/군인_얼굴왼쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][4] = "Texture/Character/군인_얼굴아래쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][5] = "Texture/Character/군인_얼굴위쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][6] = "Texture/Character/군인_몸통앞쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][7] = "Texture/Character/군인_몸통오른쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][8] = "Texture/Character/군인_몸통뒤쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][9] = "Texture/Character/군인_몸통왼쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][10] = "Texture/Character/군인_몸통아래쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][11] = "Texture/Character/군인_몸통위쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][12] = "Texture/Character/군인_왼팔앞쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][13] = "Texture/Character/군인_왼팔오른쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][14] = "Texture/Character/군인_왼팔뒤쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][15] = "Texture/Character/군인_왼팔왼쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][16] = "Texture/Character/군인_왼팔아래쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][17] = "Texture/Character/군인_왼팔위쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][18] = "Texture/Character/군인_오른팔앞쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][19] = "Texture/Character/군인_오른팔오른쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][20] = "Texture/Character/군인_오른팔뒤쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][21] = "Texture/Character/군인_오른팔왼쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][22] = "Texture/Character/군인_오른팔아래쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][23] = "Texture/Character/군인_오른팔위쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][24] = "Texture/Character/군인_왼발앞쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][25] = "Texture/Character/군인_왼발오른쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][26] = "Texture/Character/군인_왼발뒤쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][27] = "Texture/Character/군인_왼발왼쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][28] = "Texture/Character/군인_왼발아래쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][29] = "Texture/Character/군인_왼발위쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][30] = "Texture/Character/군인_오른발앞쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][31] = "Texture/Character/군인_오른발오른쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][32] = "Texture/Character/군인_오른발뒤쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][33] = "Texture/Character/군인_오른발왼쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][34] = "Texture/Character/군인_오른발아래쪽.bmp";
	m_pszPlayerFilename[PLAYER_SOLDIER][35] = "Texture/Character/군인_오른발위쪽.bmp";



	//MONSTER_IRON
	TextureInit();
}

GLuint* CBitmapMgr::GetTexture(SceneList _eScene)
{
		return g_ivTextures[_eScene];
}

GLubyte** CBitmapMgr::GetTexture(MonsterList _eMonster)
{
	return m_pMonsterBytes[_eMonster];

}

GLubyte** CBitmapMgr::GetTexture(PlayerList _ePlayer)
{
	return m_pPlayerBytes[_ePlayer];

}

GLubyte* CBitmapMgr::GetTexture(int _Type, int _Texture)
{
	switch (_Type)
	{
	case 1:
		return m_pBrick[_Texture];
		break;
	case 2:
		return m_pSkyBox[_Texture];
		break;
	case 3:
		return m_pContainer[_Texture];
		break;
	default:
		break;
	}
	
}
