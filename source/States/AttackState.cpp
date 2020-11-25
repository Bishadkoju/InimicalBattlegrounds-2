#include "States/AttackState.h"
#include "NPC.h"
#include "States/WanderState.h"
AttackState::AttackState()
{
}

AttackState* AttackState::Instance()
{
	static AttackState instance;
	return &instance;
}

void AttackState::enter(NPC* npc)
{
	std::cout << "AttackState Entered \n";
}

void AttackState::execute(NPC* npc)
{
	npc->adjustPlayerDirection();
	npc->searchEnemy();
	if (!npc->isInRange()) {
		npc->changeState(WanderState::Instance());
	}
	//std::cout << "AttackState Executing \n";
}

void AttackState::exit(NPC* npc)
{
	npc->clearCurrentPath();
	std::cout << "AttackState Exiting \n";
}
