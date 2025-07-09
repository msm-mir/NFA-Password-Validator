#include <iostream>
#include <set>
#include <vector>

using namespace std;

enum TransitionType {
    a_z, A_Z, n0_9, s_char
};

enum StateType {
    q0, q1, q2, q3, q4
};

class State {
public:
    multiset<StateType> name;

    State();
    bool operator<(const State& s) const;
    bool operator==(const State& s) const;
};

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

void buildNFA(NFA&, int&, int&, int&, int&);
void buildStartStates(NFA&, int&, int&, int&, int&);
void buildOtherStates(NFA&, int&, int&, int&, int&);
void finalState(NFA&, int&, int&, int&, int&);
bool isNew(NFA&, State&);
bool notDuplicate(State, StateType, int);
void traverse(NFA&, string&);
string toString1(State&);
string toString2(TransitionType&);
void transferTable(NFA&);

int main() {
    int lowerCase, upperCase, number, specialChar;
    string pass;

    cout << "Lower Case: ";
    cin >> lowerCase;

    cout << "Upper Case: ";
    cin >> upperCase;

    cout << "Number: ";
    cin >> number;

    cout << "Special Character: ";
    cin >> specialChar;

    cout << "Password: ";
    cin.ignore();
    getline(cin, pass);

    NFA machine;
    buildNFA(machine, lowerCase, upperCase, number, specialChar);
    traverse(machine, pass);
    transferTable(machine);

    return 0;
}

void buildNFA(NFA& machine, int& lowerCase, int& upperCase, int& number, int& specialChar) {
    buildStartStates(machine, lowerCase, upperCase, number, specialChar);
    finalState(machine, lowerCase, upperCase, number, specialChar);
    buildOtherStates(machine, lowerCase, upperCase, number, specialChar);
}

void buildStartStates(NFA& machine, int& lowerCase, int& upperCase, int& number, int& specialChar) {
    State s1, s2;
    s1.name.insert(q0);
    machine.firstState = s1;

    if (lowerCase != 0) {
        s2.name.insert(q1);
        machine.states.push_back(s2);
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s2);
        machine.transitions.push_back(a_z);
        s2.name.clear();
    } else {
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s1);
        machine.transitions.push_back(a_z);
    }

    if (upperCase != 0) {
        s2.name.insert(q2);
        machine.states.push_back(s2);
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s2);
        machine.transitions.push_back(A_Z);
        s2.name.clear();
    } else {
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s1);
        machine.transitions.push_back(A_Z);
    }

    if (number != 0) {
        s2.name.insert(q3);
        machine.states.push_back(s2);
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s2);
        machine.transitions.push_back(n0_9);
        s2.name.clear();
    } else {
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s1);
        machine.transitions.push_back(n0_9);
    }

    if (specialChar != 0) {
        s2.name.insert(q4);
        machine.states.push_back(s2);
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s2);
        machine.transitions.push_back(s_char);
    } else {
        machine.currentStates.push_back(s1);
        machine.nextStates.push_back(s1);
        machine.transitions.push_back(s_char);
    }
}

void buildOtherStates(NFA &machine, int &lowerCase, int &upperCase, int &number, int &specialChar) {
    State s;
    for (size_t it = 0; it < machine.states.size(); it++) {
        s = machine.states[it];

        if (lowerCase != 0 && notDuplicate(s, q1, lowerCase)) {
            machine.currentStates.push_back(s);
            s.name.insert(q1);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(a_z);

            if (isNew(machine, s))
                machine.states.push_back(s);

            auto tmp = s.name.find(q1);
            if (tmp != s.name.end())
                s.name.erase(tmp);
        } else {
            machine.currentStates.push_back(s);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(a_z);
        }

        if (upperCase != 0 && notDuplicate(s, q2, upperCase)) {
            machine.currentStates.push_back(s);
            s.name.insert(q2);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(A_Z);

            if (isNew(machine, s))
                machine.states.push_back(s);

            auto tmp = s.name.find(q2);
            if (tmp != s.name.end())
                s.name.erase(tmp);
        } else {
            machine.currentStates.push_back(s);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(A_Z);
        }

        if (number != 0 && notDuplicate(s, q3, number)) {
            machine.currentStates.push_back(s);
            s.name.insert(q3);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(n0_9);

            if (isNew(machine, s))
                machine.states.push_back(s);

            auto tmp = s.name.find(q3);
            if (tmp != s.name.end())
                s.name.erase(tmp);
        } else {
            machine.currentStates.push_back(s);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(n0_9);
        }

        if (specialChar != 0 && notDuplicate(s, q4, specialChar)) {
            machine.currentStates.push_back(s);
            s.name.insert(q4);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(s_char);

            if (isNew(machine, s))
                machine.states.push_back(s);

            auto tmp = s.name.find(q4);
            if (tmp != s.name.end())
                s.name.erase(tmp);
        } else {
            machine.currentStates.push_back(s);
            machine.nextStates.push_back(s);
            machine.transitions.push_back(s_char);
        }
    }
    s.name.clear();
    s.name.insert(q0);
    machine.states.push_back(s);
}

void finalState(NFA &machine, int &lowerCase, int &upperCase, int &number, int &specialChar) {
    State s;
    for (int j = 0; j < lowerCase; j++) {
        s.name.insert(q1);
    }
    for (int j = 0; j < upperCase; j++) {
        s.name.insert(q2);
    }
    for (int j = 0; j < number; j++) {
        s.name.insert(q3);
    }
    for (int j = 0; j < specialChar; j++) {
        s.name.insert(q4);
    }
    if (s.name.empty()) s.name.insert(q0);

    machine.finalState = s;
}

bool isNew(NFA& machine, State& m) {
    bool b = false;
    for (size_t i = 0; i < machine.states.size(); i++) {
        State s = machine.states[i];
        if (s.name.size() != m.name.size()) {
            b = true;
            continue;
        }

        auto i1 = s.name.begin();
        auto i2 = m.name.begin();
        while (i1 != s.name.end() && i2 != m.name.end()) {
            if (*i1 != *i2) {
                b = true;
                break;
            }
            i1++;
            i2++;
        }

        if (i1 == s.name.end() && i2 == m.name.end()) return false;
    }
    return b;
}

bool notDuplicate(State s, StateType t, int cnt) {
    int tmp = 0;
    s.name.insert(t);
    for (auto i = s.name.begin(); i != s.name.end(); i++) {
        if (*i == t) tmp++;
    }
    return tmp <= cnt;
}

void traverse(NFA& machine, string& pass) {
    State s = machine.firstState;
    string output = toString1(s);
    output += " -> ";

    for (char c : pass) {
        if (c >= 'a' && c <= 'z') {
            for (size_t i = 0; i < machine.currentStates.size(); i++) {
                if (machine.transitions[i] == a_z && machine.currentStates[i] == s) {
                    s = machine.nextStates[i];
                    break;
                }
            }
        } else if (c >= 'A' && c <= 'Z') {
            for (size_t i = 0; i < machine.currentStates.size(); i++) {
                if (machine.transitions[i] == A_Z && machine.currentStates[i] == s) {
                    s = machine.nextStates[i];
                    break;
                }
            }
        } else if (c >= '0' && c <= '9') {
            for (size_t i = 0; i < machine.currentStates.size(); i++) {
                if (machine.transitions[i] == n0_9 && machine.currentStates[i] == s) {
                    s = machine.nextStates[i];
                    break;
                }
            }
        } else {
            for (size_t i = 0; i < machine.currentStates.size(); i++) {
                if (machine.transitions[i] == s_char && machine.currentStates[i] == s) {
                    s = machine.nextStates[i];
                    break;
                }
            }
        }
        output += toString1(s);
        output += " -> ";
    }

    for (int i = 0; i < 4; i++) output.pop_back();
    cout << endl << output << endl;
    if (s == machine.finalState) {
        cout << "GOOD" << endl;
    } else {
        cout << "BAD" << endl;
    }
    cout << endl;
}

string toString1(State &s) {
    string out;
    for (StateType t : s.name) {
        if (t == q0) out += "q0";
        else if (t == q1) out += "q1";
        else if (t == q2) out += "q2";
        else if (t == q3) out += "q3";
        else if (t == q4) out += "q4";
    }
    return out;
}

string toString2(TransitionType &t) {
    string out;
    if (t == a_z) out = "a-z";
    else if (t == A_Z) out = "A-Z";
    else if (t == n0_9) out = "0-9";
    else if (t == s_char) out = "#!@";
    return out;
}

void transferTable(NFA &machine) {
    printf("%5s", " ");
    printf("%12s", "current state");
    printf("  |  ");
    printf("%-12s", "next state");
    printf("  |  ");
    printf("%-12s\n", "input");

    for (int i = 0; i < 70; ++i) {
        printf("%s", "-");
    }
    printf("\n");
    printf("%5s", " ");

    for (int i = 0; i < (int)machine.currentStates.size(); ++i) {
        printf("%-18s", toString1(machine.currentStates[i]).c_str());
        printf("%-17s", toString1(machine.nextStates[i]).c_str());
        printf("%-17s\n", toString2(machine.transitions[i]).c_str());
        printf("%5s", " ");
    }
    printf("\n\n\n\n");
}

State::State() = default;

NFA::NFA() {
    this->states.clear();
    this->currentStates.clear();
    this->nextStates.clear();
    this->transitions.clear();
    this->firstState = State();
    this->finalState = State();
}

bool State::operator<(const State& s) const {
    return this->name < s.name;
}

bool State::operator==(const State& s) const {
    return this->name == s.name;
}
