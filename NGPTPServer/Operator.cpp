#include "Operator.h"
#pragma comment(lib, "ws2_32")

std::vector<PlayerInfo> * COperator::playerVecForCalcul;

COperator::COperator()
{
}
COperator::COperator(std::vector<PlayerInfo>*  player)
{
	playerVecForCalcul = player;
}
void COperator::Update()
{
	

}


COperator::~COperator()
{
}
