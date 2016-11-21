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
	SCENE_INGAME,
	SCENE_INRESULT,
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

struct InitInfo						//게임의 초기값을 담당하는 구조체
{
	int playerIndex;
	Vec3 Player1Pos;				//첫번째 플레이어의 위치를 담당
	Vec3 Player2Pos;				//두번째 플레이어의 위치를 담당
	Vec3 MonsterPos[10] = { 0 };			//몬스터들의 위치정보를 담당
	//Vec3 containerPos[4];			// 필요한가?
};

enum DataType						//데이터 타입의 구분 변수를 가진 열거형
{
	PLAYER,							//구분타입 -> 플레이어정보
	BULLET,							//구분타입 -> 총알정보
	MONSTER,						//구분타입 -> 몬스터정보
	SCENE							//구분타입 -> 씬정보
};

// 타입 구분이 필요한 정보	
struct SceneInfo					//씬의 구분을 담당하는 구조체
{
	int type;						//데이터 타입의 구분을 담당
	int SceneState;					//현재 씬의 상태를 구분
};

struct PlayerInfo					//플레이어의 정보를 담당하는 구조체
{
	int type;						//데이터 타입의 구분을 담당
	int PlayerIndex;
	Vec3 PlayerPos;					//플레이어의 위치를 담당
	Vec3 CameraDir;					//플레이어의 방향을 담당
	bool AniandKeyState;			//키의 눌림 여부 담당
	unsigned char charKey;			//어떤키?
};

struct BulletInfo					//총알의 정보를 담당하는 구조체
{
	int type;						//데이터 타입의 구분을 담당
	Vec3 BulletPos;					//총알의 위치를 담당
	bool newBullet;					//총알이 새로 만들어진 총알인지 아닌지
									//True면 서버내에 총알관리 벡터에 추가.
	int bulletOwner;				//누가 발사한 총알인지 구분
	int bulletIndex;				//총알들을 구분하기 위해서
};

struct MonsterInfo					//몬스터의 정보를 담당하는 구조체
{
	int type;						//데이터 타입의 구분을 담당
	Vec3 MonsterPos;				//몬스터의 위치를 담당
	int hp;							//몬스터에 체력을 담당, 
									//기본적으로 3에 체력을 가지며 총알에 한발 맞으면, 체력이 1이 깎인다.
};

struct ContainerInfo				//컨테이너 위치값 구조체
{
	Vec3 position;					//컨테이너의 중심 위치값.
};

struct ResultInfo					// 결과 조건을 보내기 위한 구조체
{
	int killCount;					// 플레이어가 몇 마리의 몬스터를 잡았는지 
	int SceneState;					// 양쪽 클라이언트에 결과화면을 띄우기 위해 보내는 변수
};

struct MonsterPosForRecv
{
	MonsterInfo monsters[10];
};