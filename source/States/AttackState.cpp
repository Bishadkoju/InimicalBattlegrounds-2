#include "States/AttackState.h"
#include "NPC.h"
#include "States/WanderState.h"
#include "States/FleeState.h"
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
	
	
	if (npc->isInRange(npc->detectionRadiusSquared) || npc->isEnemyInSight()) {
		if (!npc->canFight()) {
			npc->changeState(FleeState::Instance());
		}
		if (npc->isEnemyInSight()) {
			npc->fire();
		}		
		if (!npc->isInRange(npc->detectionRadiusSquared / 5)) {
			npc->searchEnemy();
			npc->followPath();
		}
		else {
			npc->resetKeyboardPress();
		}
	}else{
		npc->changeState(WanderState::Instance());
	}
	//std::cout << "AttackState Executing \n";
}

void AttackState::exit(NPC* npc)
{
	npc->clearCurrentPath();
	npc->resetKeyboardPress();
	std::cout << "AttackState Exiting \n";
}
