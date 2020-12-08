#pragma once
class NPC;
class State
{
public:

	virtual ~State() {}

	virtual void enter(NPC*) = 0;

	virtual void execute(NPC*) = 0;

	virtual void exit(NPC*) = 0;

};
