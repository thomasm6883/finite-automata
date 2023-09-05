#pragma once

#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H
#include <iostream>
#include <vector>
#include <string>
#include "TuringNode.h"

using namespace std;

class TuringMachine {
private:
    string tape_string;
    vector<vector<char>> diagram;
    void printLayer(TuringNode* currentNode);
    char start;
    char accepting;
public:
    TuringMachine(string tape, vector<vector<char>> diagram, char start, char accepting);
    void startMachine();
    
};

#endif