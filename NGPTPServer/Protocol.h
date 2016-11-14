#pragma once

struct Vec3							//X, Y, Z. 
{
	Vec3(){}
	Vec3(float x1, float y1,float z1 ):x(x1),y(y1),z(z1)
	{}
	float x, y, z;
};

struct InitInfo						//게임의 초기값을 담당하는 구조체
{
	int playerIndex;
	Vec3 Player1Pos;				//첫번째 플레이어의 위치를 담당
	Vec3 Player2Pos;				//두번째 플레이어의 위치를 담당
	Vec3 MonsterPos[10]	;			//몬스터들의 위치정보를 담당
	//Vec3 containerPos[4];			// 필요한가?
};

enum DataType						//데이터 타입의 구분 변수를 가진 열거형
{
	PLAYER,							//구분타입 -> 플레이어정보
	BULLET,							//구분타입 -> 총알정보
	MONSTER,						//구분타입 -> 몬스터정보
	SCENE							//구분타입 -> 씬정보
};

enum SceneList						//씬 구분 변수를 가진 열거험
{
	LOBBY,							//구분타입 -> 로비 씬
	INGAME,							//구분타입 -> 게임진행 씬
	RESULT							//구분타입 -> 게임결과 씬
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
	Vec3 PlayerPos;					//플레이어의 위치를 담당
	Vec3 CameraDir;					//플레이어의 방향을 담당
	bool AniandKeyState;			//키의 눌림 여부 담당
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
	int hp = 3;						//몬스터에 체력을 담당, 
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
struct MapSizeInfo
{
	
};

//-------내가 필요해서 만든부분-------
struct ThreadParam
{
	SOCKET clientsock;
	int clientInex;		
};