#include "TuringNode.h"

TuringNode::TuringNode(char character) {
	this->character = character;
	this->next = nullptr;
	this->previous = nullptr;
	this->id = 0;
}
TuringNode::TuringNode() {
	this->character = 'B';
	this->next = nullptr;
	this->previous = nullptr;
	this->id = 0;
}
TuringNode::TuringNode(TuringNode* A) {
	this->character = A->character;
	this->next = A->next;
	this->previous = A->previous;
	this->id = (A->id);
}

char TuringNode::read() {
	return character;
}

TuringNode* TuringNode::move_right(char character) {
	if (character != (char) 0 && next != nullptr) {
		this->character = character;
	}
	if (next == nullptr) {
		next = new TuringNode(character);
		next->previous = this;
		next->id = (this->id)+1;
	}
	return next;
}

TuringNode* TuringNode::move_left(char character) {
	if (character != (char) 0) {
		this->character = character;
	}
	if (previous == nullptr) {
		previous = new TuringNode(character);
		previous->next = this;
		next->id = (this->id) - 1;
	}
	return previous;
}