#include "States/FleeState.h"
#include "States/WanderState.h"
#include "States/AttackState.h"
#include "NPC.h"
FleeState::FleeState() {

}

FleeState* FleeState::Instance()
{
	static FleeState instance;
	return &instance;
}

void FleeState::enter(NPC*)
{
	std::cout << "FleeState Entered \n";
}

void FleeState::execute(NPC* npc)
{
	npc->flee();
	if (npc->isInRange(npc->detectionRadiusSquared) || npc->isEnemyInSight()) {
		if (npc->canFight()) {
			npc->changeState(AttackState::Instance());
		}
	}
	else {
		npc->changeState(WanderState::Instance());
	}
}

void FleeState::exit(NPC*)
{
	std::cout << "FleeState Exited \n";
}
