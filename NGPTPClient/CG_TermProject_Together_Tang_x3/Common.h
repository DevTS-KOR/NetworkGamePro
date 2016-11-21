#pragma once
//#include "stdafx.h"

// Pie��
#define PI	3.141592

// �������� �ʺ�, ����
#define WINDOW_WIDTH	800
#define	WINDOW_HEIGHT	800

// �ؽ��ĸ� �޾ƿö� Scene�����ؼ�
// �迭�� �ε����� ����ֱ�����
// ex) GetTexture(DRAW_LOGO)
#define DRAW_LOGO		0
#define DRAW_LOBBY		1
#define DRAW_MONSTER	2


#define MAP_SIZE	4000

// �����Ҵ�� ������ �����ϱ� ���� ���ø�
template<typename T>
static void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

// X, Y, Z��ǥ�� �����ϴ� ����ü
// ���� float���� ��������� ������ ����
struct Vec3
{
	float fX;
	float fY;
	float fZ;
};

// X, Y��ǥ�� �����ϴ� ����ü
// ���� float���� ��������� ������ ����
struct Vec2
{
	float fX;
	float fY;
};

// �� �� �� 3���� ������� ����ü ���İ��� ����
struct Color
{
	int iRed;
	int iGreen;
	int iBlue;
};

// �� �� �� 3���� ������� ����ü ���İ� ����
struct ColorAlpha
{
	int iRed;
	int iGreen;
	int iBlue;
	int	iAlpha;
};

// Scene��ȯ�� ���� enum����
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

struct InitInfo						//������ �ʱⰪ�� ����ϴ� ����ü
{
	int playerIndex;
	Vec3 Player1Pos;				//ù��° �÷��̾��� ��ġ�� ���
	Vec3 Player2Pos;				//�ι�° �÷��̾��� ��ġ�� ���
	Vec3 MonsterPos[10] = { 0 };			//���͵��� ��ġ������ ���
	//Vec3 containerPos[4];			// �ʿ��Ѱ�?
};

enum DataType						//������ Ÿ���� ���� ������ ���� ������
{
	PLAYER,							//����Ÿ�� -> �÷��̾�����
	BULLET,							//����Ÿ�� -> �Ѿ�����
	MONSTER,						//����Ÿ�� -> ��������
	SCENE							//����Ÿ�� -> ������
};

// Ÿ�� ������ �ʿ��� ����	
struct SceneInfo					//���� ������ ����ϴ� ����ü
{
	int type;						//������ Ÿ���� ������ ���
	int SceneState;					//���� ���� ���¸� ����
};

struct PlayerInfo					//�÷��̾��� ������ ����ϴ� ����ü
{
	int type;						//������ Ÿ���� ������ ���
	int PlayerIndex;
	Vec3 PlayerPos;					//�÷��̾��� ��ġ�� ���
	Vec3 CameraDir;					//�÷��̾��� ������ ���
	bool AniandKeyState;			//Ű�� ���� ���� ���
	unsigned char charKey;			//�Ű?
};

struct BulletInfo					//�Ѿ��� ������ ����ϴ� ����ü
{
	int type;						//������ Ÿ���� ������ ���
	Vec3 BulletPos;					//�Ѿ��� ��ġ�� ���
	bool newBullet;					//�Ѿ��� ���� ������� �Ѿ����� �ƴ���
									//True�� �������� �Ѿ˰��� ���Ϳ� �߰�.
	int bulletOwner;				//���� �߻��� �Ѿ����� ����
	int bulletIndex;				//�Ѿ˵��� �����ϱ� ���ؼ�
};

struct MonsterInfo					//������ ������ ����ϴ� ����ü
{
	int type;						//������ Ÿ���� ������ ���
	Vec3 MonsterPos;				//������ ��ġ�� ���
	int hp;							//���Ϳ� ü���� ���, 
									//�⺻������ 3�� ü���� ������ �Ѿ˿� �ѹ� ������, ü���� 1�� ���δ�.
};

struct ContainerInfo				//�����̳� ��ġ�� ����ü
{
	Vec3 position;					//�����̳��� �߽� ��ġ��.
};

struct ResultInfo					// ��� ������ ������ ���� ����ü
{
	int killCount;					// �÷��̾ �� ������ ���͸� ��Ҵ��� 
	int SceneState;					// ���� Ŭ���̾�Ʈ�� ���ȭ���� ���� ���� ������ ����
};

struct MonsterPosForRecv
{
	MonsterInfo monsters[10];
};