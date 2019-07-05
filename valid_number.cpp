#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <set>

struct DFA {

  enum State {
    // https://leetcode.com/problems/valid-number/discuss/321773/DFA-diagram-for-this-problem
    START = 0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_5,
    STATE_6,
    STATE_7,
    STATE_8,
    ERROR
  };

  std::map<State, std::map<char, State>> graph;
  std::set<State> acceptingStates{
    STATE_2,
    STATE_4,
    STATE_7,
    STATE_8,
  };

  void addTransition(State start, std::string chars, State end) {
    if (graph.count(start) == 0) graph[start] = {};
    for (unsigned int i = 0; i < chars.size(); ++i) {
      graph[start][chars[i]] = end;
    }
  }

  DFA() {

    addTransition(START, " \n\t", START);
    addTransition(START, "-+", STATE_1);
    addTransition(START, "0123456789", STATE_2);
    addTransition(START, ".", STATE_3);

    addTransition(STATE_1, "0123456789", STATE_2);
    addTransition(STATE_1, ".", STATE_3);

    addTransition(STATE_2, "0123456789", STATE_2);
    addTransition(STATE_2, ".", STATE_4);
    addTransition(STATE_2, "e", STATE_5);
    addTransition(STATE_2, " \n\t", STATE_8);

    addTransition(STATE_3, "0123456789", STATE_4);

    addTransition(STATE_4, "0123456789", STATE_4);
    addTransition(STATE_4, "e", STATE_5);
    addTransition(STATE_4, " \n\t", STATE_8);

    addTransition(STATE_5, "-+", STATE_6);
    addTransition(STATE_5, "0123456789", STATE_7);

    addTransition(STATE_6, "0123456789", STATE_7);

    addTransition(STATE_7, "0123456789", STATE_7);
    addTransition(STATE_7, " \n\t", STATE_8);

    addTransition(STATE_8, " \n\t", STATE_8);
  }

  State transition(State curState, char c) {
    if (graph[curState].count(c) == 0) return ERROR;
    return graph[curState][c];
  }

  bool isAcceptingState(State state) {
    return acceptingStates.count(state);
  }

  State getStartState() {
    return START;
  }

};

bool isValid(DFA &dfa, std::string &str) {
  DFA::State state = dfa.getStartState();
  for (auto &c : str) {
    state = dfa.transition(state, c);
    if (state == DFA::ERROR) break;
  }
  return dfa.isAcceptingState(state);
}

int main() {
  std::vector<std::pair<std::string, bool>> input{
    {"0", true},
      {".1.", false},
      {".", false},
      {"3.", true},
      {".3", true},
      {".e1", false},
      {"46.e3", true},
      {"   3.   ", true},
      {"   .   ", false},
      {" 0.1 ", true},
      {"abc", false},
      {"1 a", false},
      {"2e10", true},
      {" -90e3   ", true},
      {" 1e", false},
      {"e3", false},
      {" 6e-1", true},
      {" 99e2.5 ", false},
      {"53.5e93", true},
      {" --6 ", false},
      {"-+3", false},
      {"95a54e53", false},
  };
  DFA dfa;
  for (auto &p : input) {
    if (isValid(dfa, p.first) != p.second) {
      std::cout << p.first
        << ":\n" << "\tExpected: " << p.second
        << "\n\tGot: " << !p.second << '\n';
    }
  }
}
