#pragma once
#include "State.h"
#include <iostream>

class WanderState :
    public State
{
private:
    WanderState();
    WanderState(const WanderState&);
    WanderState& operator =(const WanderState&);
public:
    static WanderState* Instance();
    virtual void enter(NPC*);
    virtual void execute(NPC*);
    virtual void exit(NPC*);
};

