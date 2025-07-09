#ifndef NFA_H
#define NFA_H
#include <TransitionType.h>
#include <state.h>
#include <vector>

class NFA {
public:
    vector<State> states;
    vector<State> currentStates;
    vector<State> nextStates;
    vector<TransitionType> transitions;
    State firstState;
    State finalState;

    NFA();
};

#endif // NFA_H
