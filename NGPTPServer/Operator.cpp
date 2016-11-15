#include "Operator.h"
#pragma comment(lib, "ws2_32")

std::vector<PlayerInfo> * COperator::playerVecForCalcul;
std::vector<MonsterInfo>* COperator::monsterVecForCalcul;
std::vector<BulletInfo> * COperator::bulletVecForCalcul;
std::vector<ContainerInfo> * COperator::conVecForCalcul;
COperator::COperator(){}
COperator::COperator(
	std::vector<PlayerInfo>*  player, 
	std::vector<MonsterInfo> * monsters, 
	std::vector<BulletInfo> * bullets)
{
	playerVecForCalcul = player;
	monsterVecForCalcul = monsters;
	bulletVecForCalcul = bullets;

	playerIter = playerVecForCalcul->begin();
	monsterIter = monsterVecForCalcul->begin();
	//bulletIter = bulletVecForCalcul->begin();

}
void COperator::Update()		//recv������ ��� �ѱ��� ����ؾ��ҵ�.
{
	std::vector<PlayerInfo>::iterator iter;
	iter = playerVecForCalcul->begin();

	std::cout <<"player1"<< iter->PlayerPos.x << std::endl;
	++iter;
	std::cout << "player2" << iter->PlayerPos.x << std::endl;
}
void COperator::PlayerPosUpdate()
{
	PlayerInfo a;

	if (a.playerIndex == 1)
	{
		playerIter->PlayerPos.x = 1;// 1��� recv������
	}
	else//a.playerIndex==2
	{
		++playerIter;
		playerIter->PlayerPos.x;
		--playerIter;
	}
}
COperator::~COperator()
{
}
