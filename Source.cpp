#include "TuringMachine.h"
#include <thread>

int main() {
    vector<vector<char>> diagram = {
        {'1','a','X','R','2'},
        {'2','a','a','R','2'},
        {'2','Y','Y','R','2'},
        {'2','b','Y','L','3'},
        {'3','Y','Y','L','3'},
        {'3','a','a','L','3'},
        {'3','X','X','R','1'},
        {'1','B','B','R','5'},
        {'1','Y','Y','R','4'},
        {'4','Y','Y','R','4'},
        {'4','B','B','L','5'}
    };

    int n = 30;
    string toTest = "";
    for (int i = 0; i < n; i++) {
        toTest.push_back('a');
    }
    for (int i = 0; i < n; i++) {
        toTest.push_back('b');
    }

    TuringMachine* TMnotHM = new TuringMachine(toTest, diagram, '1', '5');
    TMnotHM->startMachine();
    delete TMnotHM;
}