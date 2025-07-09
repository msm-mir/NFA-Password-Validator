#include "state.h"

State::State() = default;

bool State::operator<(const State& s) const {
    return this->name < s.name;
}

bool State::operator==(const State& s) const {
    return this->name == s.name;
}
