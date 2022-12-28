#pragma once

class BST
{
public:
	
	explicit BST(int);
	explicit BST(int, BST* parent_, BST* left, BST* right);
	explicit BST(int, int, int, int);
	explicit BST(int, BST* parent);

	bool operator<(BST* orher);

	BST* find(int);
	void insert(int);
	void remove(int);
private:
	int val;
	BST* parent;
	BST* left;
	BST* right;
};