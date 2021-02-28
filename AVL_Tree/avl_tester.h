#ifndef AVL_TESTER_H
#define AVL_TESTER_H

#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "exception.h"
#include "search_tree.h"

using namespace std;

class AvlTester {
public:
    AvlTester();
    ~AvlTester();

    void readInput();

private:
    stack<SearchTree> trees;

    bool readNextLine(ifstream& fin, ofstream& fout);

    void addTree();
    void removeTree();
    bool insert(int);
    bool erase(int);
    bool find(int);
    string front();
    string back();
    int size();
    int height();
    void clear();
    void print(ofstream& fout);
    void printDFS(ofstream& fout);
    bool isEmpty();
};

#endif

AvlTester::AvlTester() : trees() {

}

AvlTester::~AvlTester() {
    trees = stack<SearchTree>();
}

void AvlTester::readInput() {
    ifstream fin;
    fin.open("input.txt");

    ofstream fout;
    fout.open("output.txt");

    while (readNextLine(fin, fout));

    fin.close();
    fout.close();
}

bool AvlTester::readNextLine(ifstream& fin, ofstream& fout) {
    string inputLine;
    if (getline(fin, inputLine)) {
        stringstream ss(inputLine);

        string command = "";
        if (ss.good()) {
            ss >> command;

            if (command == "") return true;
            else if (command == "new") {
                addTree();
            }
            else if (command == "exit") return false;
            else if (command == "end") {
                removeTree();
                if (trees.empty()) return false;
            }
            else if (command == "size") fout << size() << endl;
            else if (command == "height") fout << height() << endl;
            else if (command == "print") print(fout);
            else if (command == "printDFS") printDFS(fout);
            else if (command == "empty") fout << std::boolalpha << isEmpty() << endl;
            else if (command == "clear") clear();
            else if (command == "front") fout << front() << endl;
            else if (command == "back") fout << back() << endl;
            else {
                int param;
                if (ss.good()) ss >> param;
                else throw IllegalArgument();

                if (command == "find") fout << std::boolalpha << find(param) << endl;
                else if (command == "insert") fout << std::boolalpha << insert(param) << endl;
                else if (command == "erase") fout << std::boolalpha << erase(param) << endl;
            }
            return true;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

void AvlTester::addTree() {
    SearchTree newTree = SearchTree();
    trees.push(newTree);
}

void AvlTester::removeTree() {
    trees.pop();
}

bool AvlTester::insert(int val) {
    return trees.top().insert(val);
}

bool AvlTester::erase(int val) {
    return trees.top().erase(val);
}

bool AvlTester::find(int val) {
    SearchTree::Iterator it = trees.top().find(val);
    if (it == trees.top().end()) return false;
    return true;
}

string AvlTester::front() {
    try {
        int val = trees.top().front();
        return to_string(val);
    }
    catch (Underflow ex) {
        return "empty";
    }
    catch (Exception ex) {
        return "error";
    }
    return "none";
}

string AvlTester::back() {
    try {
        int val = trees.top().back();
        return to_string(val);
    }
    catch (Underflow ex) {
        return "empty";
    }
    catch (Exception ex) {
        return "error";
    }
    return "none";
}

int AvlTester::size() {
    return trees.top().size();
}

void AvlTester::clear() {
    trees.top().clear();
}

int AvlTester::height() {
    return trees.top().height();
}

bool AvlTester::isEmpty() {
    return trees.top().empty();
}

void AvlTester::print(ofstream& fout) {
    for (SearchTree::Iterator it = trees.top().begin(); it != trees.top().end(); ++it)
        fout << *it << " ";
    fout << endl;
}

void AvlTester::printDFS(ofstream& fout) {
    trees.top().printDFSWithHeights(fout);
}