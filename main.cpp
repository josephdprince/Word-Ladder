//collaborated with Skyler Saltos and Charles Alares for a classroom project

#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::string;
using std::endl;

#include "WordLadder.h"

int main() {
   string dictFile, wordBegin, wordEnd, outFile;

   dictFile = "words.txt"; 
   outFile = "ladder.txt"; 
   
   cout << "Enter the first word: ";
   cin >> wordBegin;
   cout << endl;

   while (wordBegin.size() != 5) {
      cout << "Word must have exactly 5 characters." << endl << "Please reenter the first word: ";
      cin >> wordBegin;
      cout << endl;
   }

   cout << "Enter the last word: ";
   cin >> wordEnd;
   cout << endl;

   while (wordEnd.size() != 5) {
      cout << "Word must have exactly 5 characters." << endl << "Please reenter the last word: ";
      cin >> wordEnd;
      cout << endl;
   }

   try {
	   WordLadder wl(dictFile);
      wl.setOptimization(true);
	   wl.outputLadder(wordBegin, wordEnd, outFile);
   }
   catch (invalid_argument& excpt) {
      cout << excpt.what() << endl;
   }
   catch (range_error& excpt) {
      cout << excpt.what() << endl;
   }
   catch (runtime_error& excpt) {
      cout << excpt.what() << endl;
   }
   
   return 0;
}
