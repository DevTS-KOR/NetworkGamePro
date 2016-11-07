#pragma once
//#include "stdafx.h"

// Pie값
#define PI	3.141592

// 윈도우의 너비, 높이
#define WINDOW_WIDTH	800
#define	WINDOW_HEIGHT	800

// 텍스쳐를 받아올때 Scene구분해서
// 배열에 인덱스로 집어넣기위함
// ex) GetTexture(DRAW_LOGO)
#define DRAW_LOGO		0
#define DRAW_LOBBY		1
#define DRAW_MONSTER	2


#define MAP_SIZE	4000

// 동적할당된 변수를 제거하기 위한 템플릿
template<typename T>
static void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

// X, Y, Z좌표를 저장하는 구조체
// 각기 float형의 멤버변수를 가지고 있음
struct Vec3
{
	float fX;
	float fY;
	float fZ;
};

// X, Y좌표를 저장하는 구조체
// 각기 float형의 멤버변수를 가지고 있음
struct Vec2
{
	float fX;
	float fY;
};

// 빨 초 파 3원색 담기위한 구조체 알파값은 없음
struct Color
{
	int iRed;
	int iGreen;
	int iBlue;
};

// 빨 초 파 3원색 담기위한 구조체 알파값 존재
struct ColorAlpha
{
	int iRed;
	int iGreen;
	int iBlue;
	int	iAlpha;
};

// Scene전환을 위한 enum선언
enum SceneList
{
	SCENE_LOGO,
	SCENE_LOBBY,
	SCENE_INRESULT,
	SCENE_INGAME,
	SCENE_NONE
};

enum BuildType
{
	BUILD_BUNKER,
	BUILD_BOX,
	BUILD_NONE
};

enum PlayerList
{
	PLAYER_SOLDIER,
	PLAYER_NONE
};

enum MonsterList
{
	MONSTER_SPIDER,
	MONSTER_IRON,
	MONSTER_SUPER,
	MONSTER_CAT,
	//MONSTER_SOLDIER,
	MONSTER_NONE
};

enum KeyUpState
{
	KEYUP_UP,
	KEYUP_DOWN,
	KEYUP_LEFT,
	KEYUP_RIGHT,
	KEYUP_NONE
};
enum Thunder{
	STATE_START,
	STATE_PROGRESS,
	STATE_END,
	STATE_NONE
};