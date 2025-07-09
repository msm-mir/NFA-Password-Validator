#include "nfa.h"

NFA::NFA() {
    this->states.clear();
    this->currentStates.clear();
    this->nextStates.clear();
    this->transitions.clear();
    this->firstState = State();
    this->finalState = State();
}
