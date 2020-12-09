#include "States/WanderState.h"
#include "NPC.h"
#include "States/AttackState.h"
#include "States/FleeState.h"

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
	npc->target = sf::Vector2f(800, 800);
	std::cout << "WanderState Entered \n";
}

void WanderState::execute(NPC* npc)
{
	//std::cout << "WanderState Executing \n";
	npc->wander();
	if (npc->isInRange(npc->detectionRadiusSquared) || npc->isEnemyInSight()) {
		if (npc->canFight()) {
			npc->changeState(AttackState::Instance());
		}
		else {
			npc->changeState(FleeState::Instance());
		}
		
	}
}

void WanderState::exit(NPC* npc)
{
	std::cout << "WanderState Exiting \n";
	
}
