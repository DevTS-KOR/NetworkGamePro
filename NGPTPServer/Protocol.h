#pragma once

struct Vec3							//X, Y, Z. 
{
	Vec3(){}
	Vec3(float x1, float y1,float z1 ):x(x1),y(y1),z(z1)
	{}
	float x, y, z;
};

struct InitInfo						//������ �ʱⰪ�� ����ϴ� ����ü
{
	int playerIndex;
	Vec3 Player1Pos;				//ù��° �÷��̾��� ��ġ�� ���
	Vec3 Player2Pos;				//�ι�° �÷��̾��� ��ġ�� ���
	Vec3 MonsterPos[10]	;			//���͵��� ��ġ������ ���
	//Vec3 containerPos[4];			// �ʿ��Ѱ�?
};

enum DataType						//������ Ÿ���� ���� ������ ���� ������
{
	PLAYER,							//����Ÿ�� -> �÷��̾�����
	BULLET,							//����Ÿ�� -> �Ѿ�����
	MONSTER,						//����Ÿ�� -> ��������
	SCENE							//����Ÿ�� -> ������
};

enum SceneList						//�� ���� ������ ���� ������
{
	LOBBY,							//����Ÿ�� -> �κ� ��
	INGAME,							//����Ÿ�� -> �������� ��
	RESULT							//����Ÿ�� -> ���Ӱ�� ��
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
	Vec3 PlayerPos;					//�÷��̾��� ��ġ�� ���
	Vec3 CameraDir;					//�÷��̾��� ������ ���
	bool AniandKeyState;			//Ű�� ���� ���� ���
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
	int hp = 3;						//���Ϳ� ü���� ���, 
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
struct MapSizeInfo
{
	
};

//-------���� �ʿ��ؼ� ����κ�-------
struct ThreadParam
{
	SOCKET clientsock;
	int clientInex;		
};