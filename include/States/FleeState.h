#pragma once
#include "State.h"
#include <iostream>

class FleeState :
    public State
{
private:
    FleeState();
    FleeState(const FleeState&);
    FleeState& operator =(const FleeState&);
public:
    static FleeState* Instance();
    virtual void enter(NPC*);
    virtual void execute(NPC*);
    virtual void exit(NPC*);
};

