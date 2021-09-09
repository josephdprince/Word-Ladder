#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>
#include <stdexcept>
using namespace std;

#include "WordLadder.h"

WordLadder::WordLadder(const string & filename) {
    ifstream fin;
    string temp;

    try {
        fin.open(filename);
        if (!fin.is_open()) {
            throw runtime_error("File could not be opened");
        }
        // Inputting the dictionary into the list
        while (fin >> temp) {
            // If one word is too large throw an exception
            if (temp.size() != 5) {
                throw range_error("Words in list must have exactly 5 characters");
            }
            // Otherwise put the word in the list
            else {
                dict.push_back(temp);
            }
        }
    }
    catch (range_error &excpt) {
        cout << excpt.what() << endl;
        return;
    }
    catch (runtime_error &excpt) {
        cout << excpt.what() << endl;
        return;
    }
    fin.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    ofstream fout;
    fout.open(outputFile);
    
    try {
        // If the user inputs the same 2 words for the ladder
        if (start == end) {
            throw unexpected_handler();
        }

        int counter = 0;
        // Iterate through the dictionary
        for (list<string>::iterator it = dict.begin(); *it != dict.back(); ++it) {
            // If we find either the start or end word
            if (start == *it || end == *it) {
                ++counter;
            }
            // If counter == 2 then both words exist in the dictionary. Now find word ladder
            if (counter == 2) {
                PlayWordLadder(start, end, outputFile, fout);
                return;
            }
        }
        throw invalid_argument("One or more words not present in dictionary"); //at least one word did not exist in the dictionary
    }
    catch (invalid_argument &excpt) {
        cout << excpt.what() << endl;
    }
    catch (unexpected_handler &excpt) {
        ofstream fout;
        fout.open(outputFile);
        fout << start << endl;
    }
}

void WordLadder::PlayWordLadder(const string &start, const string &end, const string &outputFile, ofstream& fout) {
    stack<string> s;
    queue<stack<string>> q;

    s.push(start);
    q.push(s);

    // Remove starting word from dictionary since we will never need it
    dict.remove(start);

    string tempWord;
    int diffCount = 0;

    // If the queue is emptied, that means that a word ladder was not found
    while (!q.empty()) {
        // Gets top of stack of the first queue. This is what we will compare with
        tempWord = q.front().top();
        for (list<string>::iterator it = dict.begin(); it != dict.end(); ++it) { 
            diffCount = 0;
            unsigned i = 0;
            while (i < it->size()) {
                // If there are 2 or more differences when comparing words, stop comparing
                if (diffCount > 1) {
                    // Manually ends the loop
                    i = it->size() - 1;
                }
                // Counting the differences at each index
                else if (it->at(i) != tempWord.at(i)) {
                    ++diffCount;
                }
                ++i;
            }

            // If the words are similar (off by just one letter)
            if (diffCount == 1) { 
                stack<string> newStack;
                
                // Create a new stack with the same contents of the first stack in queue
                newStack = q.front();
                // Push the similar word we found onto this newstack
                newStack.push(*it);
                
                // If that word we found was the end word then we have our word ladder
                if (newStack.top() == end) {
                    printStack(newStack, fout);
                    fout.close();
                    return;
                }
                else {
                    // Push the new stack with the word we found into the queue
                    q.push(newStack);
                    // Delete that word from the dictionary so we don't come back to it
                    *it = "";
                }
            }
        }
        q.pop();
    }
        fout << "No Word Ladder Found." << endl;
        fout.close();
}

void printStack(stack<string> &ladder, ofstream &fout) {
    stack<string> printStack;

    while(!ladder.empty()) {
        printStack.push(ladder.top()); //putting the stack in reverse order (word ladder was inserted in reverse because of the nature of a stack)
        ladder.pop();
    }
    while(!printStack.empty()) {
        fout << printStack.top() << endl; //put the word ladder to file output
        printStack.pop();
    }
}
