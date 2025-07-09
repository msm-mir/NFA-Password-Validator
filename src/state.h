#ifndef STATE_H
#define STATE_H
#include <StateType.h>
#include <set>

using namespace std;

class State
{
public:
    multiset<StateType> name;

    State();
    bool operator<(const State&) const;
    bool operator==(const State&) const;
};

#endif // STATE_H
