#pragma once
#include "State.h"
#include <iostream>

class AttackState :
    public State
{
private:
    AttackState();
    AttackState(const AttackState&);
    AttackState& operator =(const AttackState&);
public:
    static AttackState* Instance();
    virtual void enter(NPC*);
    virtual void execute(NPC*);
    virtual void exit(NPC*);
};

