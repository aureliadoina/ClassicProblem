#pragma once
#include "stdafx.h"

class stack
{
	struct node *top;
	int nodesIn;
public:
	stack();
	void push(int);
	int pop();
	int GetNumberOfNodes(){ return nodesIn; }
	bool isEmpty();
	void display();
};