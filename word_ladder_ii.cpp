#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>

// Given two words (beginWord and endWord), and a dictionary's word list, find
// all shortest transformation sequence(s) from beginWord to endWord, such
// that:

// Only one letter can be changed at a time
// Each transformed word must exist in the word list. Note that beginWord is
// not a transformed word.
// Note:

// Return an empty list if there is no such transformation sequence.
// All words have the same length.
// All words contain only lowercase alphabetic characters.
// You may assume no duplicates in the word list.
// You may assume beginWord and endWord are non-empty and are not the same.

class Solution {

  std::map<std::string, std::vector<std::string>> graph;
  std::set<std::string> seen;
  std::string begin;

  void findOneEditWords(std::string &start, std::vector<std::string> &wordList, std::vector<std::string> &oneEditWords) {
    for (auto &word : wordList) {
      int edits = 0;
      for (unsigned int i = 0; i < word.size(); ++i) {
        if (word[i] != start[i]) ++edits;
        if (edits > 1) break;
      }
      if (edits == 1) oneEditWords.emplace_back(word);
    }
  }

  void initGraph(std::string &beginWord, std::vector<std::string> &wordList) {
    for (auto &word : wordList) {
      std::vector<std::string> oneEditWords;
      findOneEditWords(word, wordList, oneEditWords);
      graph[word] = oneEditWords;
    }
    std::vector<std::string> beginChildren;
    findOneEditWords(beginWord, wordList, beginChildren);
    graph[beginWord] = beginChildren;
  }

  std::vector<std::vector<std::string>> dfsStep(std::vector<std::vector<std::string>> sequences) {
    std::vector<std::vector<std::string>> newSeqs;
    for (auto &s : sequences) {
      seen.insert(s.back());
      auto &words = graph[s.back()];
      for (auto &word : words) {
        if (seen.count(word) > 0) continue;
        s.emplace_back(word);
        newSeqs.push_back(s);
        s.pop_back();
      }
    }
    return newSeqs;
  }

  public:

  std::vector<std::vector<std::string>> findLadders(std::string beginWord, std::string endWord, std::vector<std::string> &wordList) {
    graph = {};
    seen = {};
    initGraph(beginWord, wordList);
    std::vector<std::vector<std::string>> sequences{{beginWord}};

    for (int i = 0; i < wordList.size(); ++i) {
      sequences = dfsStep(sequences);
      bool validSeq = false;
      for (auto &s : sequences) {
        if (s.back() == endWord) {
          validSeq = true;
          break;
        }
      }
      if (validSeq) break;
    }

    for (auto it = sequences.begin(); it != sequences.end();) {
      if (it->back() != endWord) sequences.erase(it);
      else ++it;
    }

    return sequences;
  }
};

int main() {
  Solution soln;
  std::vector<std::string> wordList = {"hot","dot","dog","lot","log","cog"};
  auto seqs = soln.findLadders("hit", "cog", wordList);
  for (auto &sequence : seqs) {
    for (auto &word : sequence) {
      std::cout << word << ' ';
    }
    std::cout << '\n';
  }
}
