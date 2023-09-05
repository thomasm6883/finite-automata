#include "TuringMachine.h"

TuringMachine::TuringMachine(string tape, vector<vector<char>> diagram, char start, char accepting) {
    tape_string = tape;
    this->diagram = diagram;
    this->start = start;
    this->accepting = accepting;
}

void TuringMachine::startMachine() {
    TuringNode* currentNode = new TuringNode();
    bool outDiagram = false;

    for (char curr : tape_string) {
        currentNode = currentNode->move_right(curr);
    }
    currentNode = currentNode->move_right('B');
    while (currentNode->previous) {
        currentNode = currentNode->move_left();
    }
    currentNode = currentNode->move_right();
    char currentState = start;
    vector<char> key = { currentState,currentNode->read() };
    int node;

    while (!outDiagram) {
        this->printLayer(currentNode);
        node = -1;
        if (key[0] == accepting) { currentState = accepting; break; }
        /*if (currentNode->character == 'B'
            && currentNode->previous->character == 'B') {
            break;
        }*/
        for (int i = 0; i < diagram.size(); i++) {
            vector<char> x = diagram[i];
            if (x[0] == key[0] && x[1] == key[1]) {
                node = i;
                break;
            }
            if (i == diagram.size()-1) { outDiagram = true; }
        }
        if (!outDiagram) {
            char newChar = diagram[node][2];
            char direction = diagram[node][3];
            char nextState = diagram[node][4];
            if (direction == 'R') {
                currentNode = currentNode->move_right(newChar);
            }
            else {
                currentNode = currentNode->move_left(newChar);
            }
            key = { nextState, currentNode->read() };
            
        }
    }
    if (currentState == accepting) { cout << "accepted"; }
    else { cout << "rejected"; }

   
}

void TuringMachine::printLayer(TuringNode* currentNode) {
    int id = currentNode->id;
    if (currentNode->character == 'B') { currentNode = currentNode->move_left(); }
    while (currentNode->character != 'B') {
        currentNode = currentNode->move_left();
    }
    if (id == currentNode->id) {
        cout << "|" << currentNode->character << "|";
    }
    else { cout << currentNode->character; }
    currentNode = currentNode->move_right();
    while (currentNode->character != 'B') {
        if (id == currentNode->id) {
            cout << "|" << currentNode->character << "|";
        }
        else { cout << currentNode->character; }
        currentNode = currentNode->move_right();
    }
    if (id == currentNode->id) {
        cout << "|" << currentNode->character << "|";
    }
    else { cout << currentNode->character; }
    cout << endl;
    while (currentNode->id != id) {
        currentNode = currentNode->move_left();
    }
    
}
