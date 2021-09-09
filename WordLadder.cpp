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
        fin.open(filename); //opening file and making sure that it opens correctly
        if (!fin.is_open()) {
            throw runtime_error("File could not be opened");
        }
        while (fin >> temp) {  //inputting the dictionary into the list
            if (temp.size() != 5) { //if one word is too large throw an exception
                throw range_error("Words in list must have exactly 5 characters");
            }
            else { //otherwise put the word in the list
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
    fout.open(outputFile); //opens an output file stream but doesnt check if it exists because it'll make one
    
    try {
        if (start == end) { //if the user inputs the same 2 words for the ladder
            throw unexpected_handler();
        }

        int counter = 0;
        for (list<string>::iterator it = dict.begin(); *it != dict.back(); ++it) { //iterating through the dictionary
            if (start == *it || end == *it) { //use a counter to see if the word exists in the dictionary
                ++counter;
            }
            if (counter == 2) { //if both words exist, find the word ladder
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

    s.push(start); //starts the first stack with just the word inputted by the user
    q.push(s); //pushes that stack onto the queue

    dict.remove(start); //removes the starting word from the dictionary so we don't use that as a similar word. 

    string tempWord;
    int diffCount = 0;

    while (!q.empty()) {  //if the queue is emptied, that means that a word ladder was not found
        tempWord = q.front().top(); //gets the word at the top of the first stack in the queue
        for (list<string>::iterator it = dict.begin(); it != dict.end(); ++it) { 
            diffCount = 0;
            unsigned i = 0;
            while (i < it->size()) {
                if (optimization == true) { //Extra credit: if the user wants to turn on optimization
                    if (diffCount > 1) { //If there are 2 or more differences when comparing words, stop comparing
                        i = it->size() - 1; //this will end the loop (there is a ++i at the end so we say size - 1)
                    }
                    else if (it->at(i) != tempWord.at(i)) { //if there is a difference count it and count the comparison
                        ++diffCount;
                        ++comparisons;
                    }
                }
                else { //if the user does not want to optimize the algorithm.
                    if (it->at(i) != tempWord.at(i)) { //same comparison as before
                        ++diffCount;
                        ++comparisons;
                    }
                }
                ++i;
            }

            if (diffCount == 1) { //if the words are similar (off by just one letter)
                stack<string> newStack;
                newStack = q.front(); //create a new stack with the same contents of the first stack in queue
                newStack.push(*it); //push the similar word we found onto this newstack
                if (newStack.top() == end) { //if that word we found was the end word then we have our word ladder
                    printStack(newStack, fout); //prints the stack via file output
                    fout.close();
                    return;
                }
                else {
                    q.push(newStack); //if not the end of the ladder then just push the new stack onto the queue
                    *it = ""; //deletes the word without causing us to lose out iterator position
                }
            }
        }
        q.pop(); //pop the next stack in the queue
    }
        fout << "No Word Ladder Found." << endl;
        fout.close();
}

void WordLadder::setOptimization(bool b) {
    optimization = b; //sets the optimization value
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
