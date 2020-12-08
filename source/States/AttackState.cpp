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
	
	if (npc->isInRange(npc->detectionRadiusSquared)) {
		if (!npc->isInRange(npc->detectionRadiusSquared / 5)) {
			npc->chaseEnemy();
		}
		else {
			npc->resetButtonPress();
		}
	}else{
		npc->changeState(WanderState::Instance());
	}
	//std::cout << "AttackState Executing \n";
}

void AttackState::exit(NPC* npc)
{
	npc->clearCurrentPath();
	npc->resetButtonPress();
	std::cout << "AttackState Exiting \n";
}
