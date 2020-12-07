#include "States/WanderState.h"
#include "NPC.h"
#include "States/AttackState.h"

WanderState::WanderState()
{
}

WanderState* WanderState::Instance()
{
	static WanderState instance;
	return &instance;
}

void WanderState::enter(NPC* npc)
{
	std::cout << "WanderState Entered \n";
}

void WanderState::execute(NPC* npc)
{
	//std::cout << "WanderState Executing \n";
	if (npc->isInRange(npc->detectionRadiusSquared)) {
		npc->changeState(AttackState::Instance());
	}
}

void WanderState::exit(NPC* npc)
{
	std::cout << "WanderState Exiting \n";
	
}
