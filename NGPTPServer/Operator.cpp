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
void COperator::Update()		//recv¹ÞÀº°Å ¾î¶»°Ô ³Ñ±æÁö °í¹ÎÇØ¾ßÇÒµí.
{
	std::vector<PlayerInfo>::iterator iter;
	iter = playerVecForCalcul->begin();

	std::cout <<"player1"<< iter->PlayerPos.x << std::endl;
	++iter;
	std::cout << "player2" << iter->PlayerPos.x << std::endl;
}
void COperator::PlayerPosUpdate(PlayerInfo param)
{
	PlayerInfo a=param;
	std::cout << "PlayerPosUpdateÈ£Ãâ" << std::endl;
	std::cout << a.playerIndex << std::endl;
	if (a.playerIndex == 1)
	{
		if (a.charKey == 'w')
		{
			std::cout << "p1 wÅ°¿È" << std::endl;
			playerVecForCalcul->at(0).PlayerPos.z -= 1;
			std::cout << playerVecForCalcul->at(0).PlayerPos.z << std::endl;
		}
		if (a.charKey == 's')
		{
			std::cout << "p1 sÅ°¿È" << std::endl;
			playerVecForCalcul->at(0).PlayerPos.z += 1;
			std::cout << playerVecForCalcul->at(0).PlayerPos.z << std::endl;
		}
		if (a.charKey == 'a')
		{
			std::cout << "p1 aÅ°¿È" << std::endl;
			playerVecForCalcul->at(0).PlayerPos.x -= 1;
			std::cout << playerVecForCalcul->at(0).PlayerPos.z << std::endl;
		}
		if (a.charKey == 'd')
		{
			std::cout << "p1 dÅ°¿È" << std::endl;
			playerVecForCalcul->at(0).PlayerPos.x += 1;
			std::cout << playerVecForCalcul->at(0).PlayerPos.z << std::endl;
		}
	}
	else if(a.playerIndex==2)
	{
		std::cout << a.playerIndex << std::endl;
		if (a.charKey == 'w')
		{
			std::cout << "p2 wÅ°¿È" << std::endl;
			playerVecForCalcul->at(1).PlayerPos.z -= 1;
			std::cout << playerVecForCalcul->at(1).PlayerPos.z << std::endl;
		}
		if (a.charKey == 's')
		{
			std::cout << "p2 sÅ°¿È" << std::endl;
			playerVecForCalcul->at(1).PlayerPos.z += 1;
			std::cout << playerVecForCalcul->at(1).PlayerPos.z << std::endl;
		}
		if (a.charKey == 'a')
		{
			std::cout << "p2 aÅ°¿È" << std::endl;
			playerVecForCalcul->at(1).PlayerPos.x -= 1;
			std::cout << playerVecForCalcul->at(1).PlayerPos.z << std::endl;
		}
		if (a.charKey == 'd')
		{
			std::cout << "p2 dÅ°¿È" << std::endl;
			playerVecForCalcul->at(1).PlayerPos.x += 1;
			std::cout << playerVecForCalcul->at(1).PlayerPos.z << std::endl;
		}
	}
}

bool COperator::CollisionBulletWithMonster(BulletInfo & bullet, MonsterInfo& monster)
{
	return(
		bullet.BulletPos.x+1 > monster.MonsterPos.x-30 &&
		bullet.BulletPos.x-1 < monster.MonsterPos.x+30 &&
		bullet.BulletPos.y+1 > monster.MonsterPos.y-55 &&
		bullet.BulletPos.y-1 < monster.MonsterPos.y+55 &&
		bullet.BulletPos.z+1 > monster.MonsterPos.z-15 &&
		bullet.BulletPos.z-1 < monster.MonsterPos.z+15
		);
}
bool COperator::CollisionBulletWithObstacle(BulletInfo&bullet, ContainerInfo& container )
{
	return(
		bullet.BulletPos.x + 1 > container.position.x - 128 &&
		bullet.BulletPos.x - 1 < container.position.x + 128 &&
		bullet.BulletPos.y + 1 > container.position.y - 128 &&
		bullet.BulletPos.y - 1 < container.position.y + 128 &&
		bullet.BulletPos.z + 1 > container.position.z - 256 &&
		bullet.BulletPos.z - 1 < container.position.z + 256
		);
}
bool COperator::CollisionBulletWithMap(BulletInfo& bullet)
{
	if (bullet.BulletPos.x + 1 > 2000)
		return true;
	if (bullet.BulletPos.x - 1 < -2000)
		return true;
	if (bullet.BulletPos.y + 1 > 2000)
		return true;
	if (bullet.BulletPos.y - 1 < -2000)
		return true;

	return false;
}
bool COperator::CollisionObstacleWithPlayer(PlayerInfo&player, ContainerInfo& container)
{
	return(
		player.PlayerPos.x + 1 > container.position.x - 128 &&
		player.PlayerPos.x - 1 < container.position.x + 128 &&
		player.PlayerPos.z + 1 > container.position.z - 256 &&
		player.PlayerPos.z - 1 < container.position.z + 256
		);
}
COperator::~COperator()
{

}
