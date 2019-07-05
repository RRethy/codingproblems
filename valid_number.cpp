#include <map>
#include <string>
#include <iostream>
#include <vector>

struct DFA {
  enum State {
    START = 0,
    PRE_DIGIT_DOT,
    POST_DIGIT_DOT,
    DIGIT,
    E,
    PRE_E_SIGN,
    POST_E_SIGN,
    VALID_WHITESPACE,
    ERROR
  };

  std::map<State, std::map<char, State>> graph;

  bool seenE = false;
  bool seenDot = false;
  bool valid = true;
  bool seenDigit = false;
  State state = START;

  void addTransition(State start, std::string chars, State end) {
    if (graph.count(start) == 0) graph[start] = {};
    for (unsigned int i = 0; i < chars.size(); ++i) {
      graph[start][chars[i]] = end;
    }
  }

  DFA() {
    addTransition(START, " \n\t", START);
    addTransition(START, "0123456789", DIGIT);
    addTransition(DIGIT, ".", POST_DIGIT_DOT);

    addTransition(START, ".", PRE_DIGIT_DOT);
    addTransition(PRE_DIGIT_DOT, "0123456789", DIGIT);

    addTransition(POST_DIGIT_DOT, "0123456789", DIGIT);
    addTransition(POST_DIGIT_DOT, "e", E);
    addTransition(POST_DIGIT_DOT, " \n\t", VALID_WHITESPACE);

    addTransition(START


    addTransition(DOT, " \n\t", VALID_WHITESPACE);
    addTransition(DOT, "e", E);
    addTransition(DIGIT, "0123456789", DIGIT);
    addTransition(DIGIT, "e", E);
    addTransition(DIGIT, ".", DOT);
    addTransition(DIGIT, " \n\t", VALID_WHITESPACE);
    addTransition(VALID_WHITESPACE, " \n\t", VALID_WHITESPACE);
    addTransition(START, "-+", SIGN);
    addTransition(SIGN, "0123456789", DIGIT);
    addTransition(SIGN, ".", DOT);
    addTransition(E, "0123456789", DIGIT);
    addTransition(E, "-+", SIGN);
    addTransition(DOT, "0123456789", DIGIT);
  }

  bool transition(char c) {
    if ((graph[state].count(c) == 0) ||
        (seenE && (c == 'e' || c == '.')) ||
        (seenDot && c == '.')) {
      valid = false;
      return false;
    }

    if (c == 'e') {
      if (state == DOT && !seenDigit) {
        valid = false;
        return false;
      }
      seenE = true;
    } else if (c == '.') seenDot = true;

    state = graph[state][c];
    if (state == DIGIT) seenDigit = true;
    return true;
  }

  void terminate() {
    if (valid) {
      if (!seenDigit) valid = false;
      else valid = state == DIGIT || state == VALID_WHITESPACE || state == DOT;
    }
  }

  bool isValid() {
    return valid;
  }

};

int main() {
  std::vector<std::pair<std::string, bool>> input{
    {"0", true},
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
  for (auto &p : input) {
    DFA dfa{};
    for (auto &c : p.first) {
      if (!dfa.transition(c)) break;
    }
    dfa.terminate();
    if (dfa.isValid() != p.second) {
      std::cout << p.first
        << ":\n" << "\tExpected: " << p.second
        << "\n\tGot: " << !p.second << '\n';
    }
  }
}
