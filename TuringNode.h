#pragma once

#ifndef TURINGNODE_H
#define TURINGNODE_H

class TuringNode {
public:
	char character;
	int id;
	TuringNode* next;
	TuringNode* previous;
	TuringNode(char character);
	TuringNode();
	TuringNode(TuringNode* A);

	char read();

	TuringNode* move_right(char character = (char) 0);

	TuringNode* move_left(char character = (char) 0);
};

#endif