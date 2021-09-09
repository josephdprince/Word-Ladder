#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <iostream>
#include <list>
#include <stack>
using namespace std;

class WordLadder {
 private:
   list<string> dict;
   int comparisons = 0;
   bool optimization = false;
 public:
   WordLadder(const string &);
   void outputLadder(const string &, const string &, const string &);
   void setOptimization(bool);
   int getComparisons() const { return this->comparisons; }
 private:
   void PlayWordLadder(const string &, const string &, const string &, ofstream &);
};

void printStack(stack<string> &, ofstream &);

#endif
