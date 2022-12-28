#include "BST.h"


BST::BST(int a)
{
	val = a;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

BST::BST(int a, BST* parent_, BST* left, BST* right)
{
	val = a;
	this->parent = parent_;
	this->left = left;
	this->right = right;
}

BST::BST(int a , int p , int l, int r)
{
	val = a;
	parent = new BST(p);
	left = new BST(l);
	right = new  BST(r);
}

BST::BST(int a, BST* parent)
{
	val = a;
	this->parent = parent;
	left = nullptr;
	right = nullptr;
}

bool BST::operator<(BST* other)
{
	return this->val < other->val;
}

BST* BST::find(int f)
{
	if (val == f)
		return this;
	else if (val > f)
	{
		if (left)
			return left->find(f);
		return nullptr;
	}
	else if (val < f)
	{
		if (right)
			return right->find(f);
		return nullptr;
	}
	return nullptr;
}

void BST::insert(int f)
{
	if (val > f)
	{
		if (left)
			return left->insert(f);
		left = new BST(f, this);
		return;
	}
	else if (val < f)
	{
		if (right)
			return right->insert(f);
		right = new BST(f, this);
		return;
	}
}

void BST::remove(int rem)
{
	auto f = find(rem);
	if (f)
	{
		if (!f->left && !f->right)
			delete f;
		else if (!f->left)
		{
			if (f->parent->left == f)
			{
				f->parent->left = f->right;
				delete f;
			}
			else
			{
				f->parent->right = f->right;
				delete f;
			}
		}
		else if (!f->right)
		{
			if (f->parent->left == f)
			{
				f->parent->left = f->left;
				delete f;
			}
			else
			{
				f->parent->right = f->left;
				delete f;
			}
		}
		else
		{
			if (!f->left->right)
			{
				if (f->parent->left == f)
				{
					f->left->right = f->right;
					f->parent->left = f->left;
					delete f;
				}
				else
				{
					f->left->right = f->right;
					f->parent->right = f->left;
					delete f;
				}
			}
			else // don't understand here!!!!
			{
				auto it = f;
				while (it->right)
				{
					it = it->right;
				}

			}
		}
	}
}
