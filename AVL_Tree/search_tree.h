/*****************************************
* Shahrood User ID:  9814393
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include<iostream>
#include<algorithm>
#include<cassert>

#include "my_stack.h"
#include "exception.h"

using namespace std;

class SearchTree {
private:
    class Node {
    public:
        int nodeValue;
        int treeHeight;

        // The left and right sub-trees
        Node *leftTree;
        Node *rightTree;

        /*
         * Store the lesser node in the previous node
         * and the bigger node in the next node
         */
        Node *previousNode;
        Node *nextNode;

        // Member functions
        Node(int const &);

        /*
         * Is called after inserting or erasing a node
         */
        void updateHeight();

        /*
         * Calculate the balance factor
         */
        int difference() const;

        /*
         * Replace the node with left of it's right node
         */
        Node *rrRotate();

        /*
         * Replace the node with right of it's left node
         */
        Node *llRotate();

        /*
         * Replace the right node with the left of right
         * node and call rrRotate function
         */
        Node *rlRotate();

        /*
         * Replace the left node with the right of left
         * node and call llRotate function
         */
        Node *lrRotate();

        /*
         * Check if balance factor is more than 1 or less than -1
         */
        Node *balance();

        /*
         * Return treeHeight
         */
        int height() const;

        /*
         * Check if the node is leaf
         */
        bool isLeaf() const;

        /*
         * Returns the least node in the subtree
         */
        Node *front();

        /*
         * Returns the most node in the subtree
         */
        Node *back();

        /*
         * If the value is less than the node's value call
         * the left tree find otherwise call the right tree find
         */
        Node *find(int const &);

        /*
         * Recursively clear the tree
         */
        void clear();

        /*
         * If the value is less than the node's value call the left
         * tree insert otherwise call the right tree insert.
         *
         * Recursively calculate the balance factor if it is more
         * than one call balance function
         */
        bool insert(int const &, Node *&toThis);

        /*
         * Check if the value is more or less than the node value
         * If the value is less call the left tree erase
         * else if the value is more call the right tree erase.
         *
         * If the value is equal to the node value delete the node
         * and link the previous node and the next node.
         */
        bool erase(int const &, Node *&toThis);
    };

    Node *rootNode;
    int treeSize;

    // Hint as to how to start your linked list of the nodes in order
    Node *frontSentinel;
    Node *backSentinel;

public:
    class Iterator {
    private:
        SearchTree *containingTree;
        Node *currentNode;
        bool isEnd;

        // The constructor is private so that only the search tree can create an iterator
        Iterator(SearchTree *tree, Node *startingNode);

    public:
        // DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
        int operator*() const;

        /*
         * Assign the value of the next node to the current node
         */
        Iterator &operator++();

        /*
         * Assign the value of the previous node to the current node
         */
        Iterator &operator--();

        bool operator==(Iterator const &rhs) const;

        bool operator!=(Iterator const &rhs) const;

        // Make the search tree a friend so that it can call the constructor
        friend class SearchTree;
    };

    // DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
    SearchTree();

    ~SearchTree();

    bool empty() const;

    int size() const;

    int height() const;

    void printDFSWithHeights(ofstream &) const;

    int front() const;

    int back() const;

    Iterator begin();

    Iterator end();

    Iterator rbegin();

    Iterator rend();

    Iterator find(int const &);

    void clear();

    bool insert(int const &);

    bool erase(int const &);

};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
SearchTree::SearchTree() :
        rootNode(nullptr),
        treeSize(0),
        frontSentinel(new SearchTree::Node(0)),
        backSentinel(new SearchTree::Node(0)) {
    frontSentinel->nextNode = backSentinel;
    backSentinel->previousNode = frontSentinel;
}

SearchTree::~SearchTree() {
    clear();
}

bool SearchTree::empty() const {
    return (rootNode == nullptr);
}

int SearchTree::size() const {
    return treeSize;
}

int SearchTree::height() const {
    return rootNode->height();
}

void SearchTree::printDFSWithHeights(ofstream &out) const {
    out << "START->";

    Stack<Node *> stack;

    if (!empty()) {
        stack.push(rootNode);

        while (!stack.empty()) {
            Node *node = stack.pop();

            out << "[" << node->nodeValue << ", " << node->height() << "]" << "->";

            if (node->rightTree != nullptr) {
                stack.push(node->rightTree);
            }
            if (node->leftTree != nullptr) {
                stack.push(node->leftTree);
            }
        }
    }

    // print each node value and height like this
    // START->[value, height]->[value, height]->END

    out << "END";
    out << endl;
}

int SearchTree::front() const {
    if (empty()) {
        throw Underflow();
    }
    return rootNode->front()->nodeValue;
}

int SearchTree::back() const {
    if (empty()) {
        throw Underflow();
    }

    return rootNode->back()->nodeValue;
}

SearchTree::Iterator SearchTree::begin() {
    return empty() ? Iterator(this, backSentinel) : Iterator(this, rootNode->front());
}

SearchTree::Iterator SearchTree::end() {
    return Iterator(this, backSentinel);
}

SearchTree::Iterator SearchTree::rbegin() {
    return empty() ? Iterator(this, frontSentinel) : Iterator(this, rootNode->back());
}

SearchTree::Iterator SearchTree::rend() {
    return Iterator(this, frontSentinel);
}

SearchTree::Iterator SearchTree::find(int const &val) {
    if (empty()) {
        return Iterator(this, backSentinel);
    }

    SearchTree::Node *searchResult = rootNode->find(val);

    if (searchResult == nullptr) {
        return Iterator(this, backSentinel);
    } else {
        return Iterator(this, searchResult);
    }
}

void SearchTree::clear() {
    if (!empty()) {
        rootNode->clear();
        rootNode = nullptr;
        treeSize = 0;
    }

    // Reinitialize the sentinels
    frontSentinel->nextNode = backSentinel;
    backSentinel->previousNode = frontSentinel;
}

bool SearchTree::insert(int const &val) {
    if (empty()) {
        rootNode = new SearchTree::Node(val);
        treeSize = 1;

        backSentinel->previousNode = rootNode;
        rootNode->nextNode = backSentinel;
        frontSentinel->nextNode = rootNode;
        rootNode->previousNode = frontSentinel;

        return true;
    } else if (rootNode->insert(val, rootNode)) {
        ++treeSize;

        frontSentinel->nextNode = rootNode->front();
        rootNode->front()->previousNode = frontSentinel;
        backSentinel->previousNode = rootNode->back();
        rootNode->back()->nextNode = backSentinel;

        return true;
    } else {
        return false;
    }
}

bool SearchTree::erase(int const &val) {
    if (!empty() && rootNode->erase(val, rootNode)) {
        --treeSize;

        if (!empty()) {
            frontSentinel->nextNode = rootNode->front();
            rootNode->front()->previousNode = frontSentinel;
            backSentinel->previousNode = rootNode->back();
            rootNode->back()->nextNode = backSentinel;
        } else {
            frontSentinel->nextNode = backSentinel;
            backSentinel->previousNode = frontSentinel;
        }

        return true;
    } else {
        return false;
    }
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

SearchTree::Node::Node(int const &val) :
        nodeValue(val),
        leftTree(nullptr),
        rightTree(nullptr),
        nextNode(nullptr),
        previousNode(nullptr),
        treeHeight(0) {
    // does nothing
}

void SearchTree::Node::updateHeight() {
    treeHeight = max(leftTree->height(), rightTree->height()) + 1;
}

int SearchTree::Node::height() const {
    return (this == nullptr) ? -1 : treeHeight;
}

// Return true if the current node is a leaf node, false otherwise
bool SearchTree::Node::isLeaf() const {
    return ((leftTree == nullptr) && (rightTree == nullptr));
}

// Return a pointer to the front node
SearchTree::Node *SearchTree::Node::front() {
    return (leftTree == nullptr) ? this : leftTree->front();
}

// Return a pointer to the back node
SearchTree::Node *SearchTree::Node::back() {
    return (rightTree == nullptr) ? this : rightTree->back();
}

SearchTree::Node *SearchTree::Node::find(int const &val) {
    if (val == nodeValue) {
        return this;
    } else if (val < nodeValue) {
        return (leftTree == nullptr) ? nullptr : leftTree->find(val);
    } else {
        return (rightTree == nullptr) ? nullptr : rightTree->find(val);
    }
}

// Recursively clear the tree
void SearchTree::Node::clear() {
    if (leftTree != nullptr) {
        leftTree->clear();
    }

    if (rightTree != nullptr) {
        rightTree->clear();
    }

    delete this;
}

bool SearchTree::Node::insert(int const &val, SearchTree::Node *&toThis) {

    if (val < nodeValue) {
        if (leftTree == nullptr) {

            leftTree = new SearchTree::Node(val);

            leftTree->nextNode = toThis;
            leftTree->previousNode = toThis->previousNode;
            toThis->previousNode->nextNode = leftTree;
            toThis->previousNode = leftTree;

            toThis = balance();

            updateHeight();

            return true;
        } else {
            if (leftTree->insert(val, leftTree)) {
                toThis = balance();

                updateHeight();

                return true;
            } else {
                return false;
            }
        }
    } else if (val > nodeValue) {
        if (rightTree == nullptr) {
            rightTree = new SearchTree::Node(val);

            rightTree->previousNode = toThis;
            rightTree->nextNode = toThis->nextNode;
            toThis->nextNode->previousNode = rightTree;
            toThis->nextNode = rightTree;

            toThis = balance();

            updateHeight();

            return true;
        } else {
            if (rightTree->insert(val, rightTree)) {
                toThis = balance();

                updateHeight();

                return true;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
}

bool SearchTree::Node::erase(int const &val, SearchTree::Node *&toThis) {
    if (val < nodeValue) {
        if (leftTree == nullptr) {
            return false;
        } else {
            if (leftTree->erase(val, leftTree)) {

                toThis = balance();

                updateHeight();

                return true;
            }

            return false;
        }
    } else if (val > nodeValue) {
        if (rightTree == nullptr) {
            return false;
        } else {
            if (rightTree->erase(val, rightTree)) {

                toThis = balance();

                updateHeight();

                return true;
            }

            return false;
        }
    } else {
        assert(val == nodeValue);

        if (isLeaf()) {

            toThis->previousNode->nextNode = toThis->nextNode;
            toThis->nextNode->previousNode = toThis->previousNode;

            toThis = nullptr;
            delete this;
        } else if (leftTree == nullptr) {

            toThis->previousNode->nextNode = toThis->nextNode;
            toThis->nextNode->previousNode = toThis->previousNode;

            toThis = rightTree;
            delete this;
        } else if (rightTree == nullptr) {

            toThis->previousNode->nextNode = toThis->nextNode;
            toThis->nextNode->previousNode = toThis->previousNode;

            toThis = leftTree;
            delete this;
        } else {
            nodeValue = rightTree->front()->nodeValue;
            rightTree->erase(nodeValue, rightTree);
            toThis = balance();

            updateHeight();

        }

        return true;
    }
}

int SearchTree::Node::difference() const {

    return leftTree->height() - rightTree->height();
}

SearchTree::Node *SearchTree::Node::rrRotate() {

    Node *tempNode = rightTree;
    rightTree = tempNode->leftTree;
    tempNode->leftTree = this;

    tempNode->rightTree->updateHeight();
    updateHeight();
    tempNode->updateHeight();

    return tempNode;

}

SearchTree::Node *SearchTree::Node::llRotate() {

    Node *tempNode = leftTree;
    leftTree = tempNode->rightTree;
    tempNode->rightTree = this;

    tempNode->leftTree->updateHeight();
    updateHeight();
    tempNode->updateHeight();

    return tempNode;
}

SearchTree::Node *SearchTree::Node::lrRotate() {

    Node *tempNode = leftTree;
    leftTree = tempNode->rightTree;
    tempNode->rightTree = leftTree->leftTree;
    leftTree->leftTree = tempNode;

    return llRotate();
}

SearchTree::Node *SearchTree::Node::rlRotate() {

    Node *tempNode = rightTree;
    rightTree = tempNode->leftTree;
    tempNode->leftTree = rightTree->rightTree;
    rightTree->rightTree = tempNode;


    return rrRotate();
}

SearchTree::Node *SearchTree::Node::balance() {

    int diff = difference();

    Node *tempNode = this;

    if (diff > 1) {

        leftTree->difference() > 0 ? tempNode = llRotate() : tempNode = lrRotate();

    } else if (diff < -1) {

        rightTree->difference() > 0 ? tempNode = rlRotate() : tempNode = rrRotate();

    }

    return tempNode;

}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

SearchTree::Iterator::Iterator(SearchTree *tree, SearchTree::Node *startingNode) :
        containingTree(tree),
        currentNode(startingNode) {
    // This is done for you...
    // Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

int SearchTree::Iterator::operator*() const {
    // This is done for you...
    return currentNode->nodeValue;
}

SearchTree::Iterator &SearchTree::Iterator::operator++() {

    if (currentNode->nextNode == nullptr) {
        isEnd = true;
    }

    if (!isEnd) {
        currentNode = currentNode->nextNode;
    }

    return *this;
}

SearchTree::Iterator &SearchTree::Iterator::operator--() {

    if (currentNode->previousNode == nullptr) {
        isEnd = true;
    }

    if (!isEnd) {
        currentNode = currentNode->previousNode;
    }

    return *this;
}

bool SearchTree::Iterator::operator==(SearchTree::Iterator const &rhs) const {
    // This is done for you...
    return (currentNode == rhs.currentNode);
}

bool SearchTree::Iterator::operator!=(SearchTree::Iterator const &rhs) const {
    // This is done for you...
    return (currentNode != rhs.currentNode);
}

#endif
