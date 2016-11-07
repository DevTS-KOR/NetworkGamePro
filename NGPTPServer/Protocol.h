#pragma once
struct Vec3							//X, Y, Z. 
{
	float x, y, z;
};

struct InitInfo						//������ �ʱⰪ�� ����ϴ� ����ü
{
	Vec3 Player1Pos;				//ù��° �÷��̾��� ��ġ�� ���
	Vec3 Player2Pos;				//�ι�° �÷��̾��� ��ġ�� ���
	Vec3 MonsterPos[10];			//���͵��� ��ġ������ ���
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
struct ResultInfo					// ��� ������ ������ ���� ����ü
{
	int killCount;					// �÷��̾ �� ������ ���͸� ��Ҵ��� 
	int SceneState;					// ���� Ŭ���̾�Ʈ�� ���ȭ���� ���� ���� ������ ����
};