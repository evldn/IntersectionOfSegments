#pragma once
#ifndef INTERSECTION_OF_SEGMENTS_AVL_TREE_H_
#define INTERSECTION_OF_SEGMENTS_AVL_TREE_H_
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node
{
	int key;
	Node* left, * right;
	int height;
	Node(int _key, Node* _left = nullptr, Node* _right = nullptr, int _height = 1) : key(_key), left(_left), right(_right), height(_height) {};
};

class AVLTree
{
	int GetBalance(Node* current);
	int Height(Node* current) { return current ? current->height : 0; }
	void FixHeight(Node* current)
	{
		unsigned char height_left = Height(current->left);
		unsigned char height_right = Height(current->right);
		current->height = (height_right > height_left ? height_right : height_left) + 1;
	}
	void PartInsertRecursive(Node* current, int key);
	Node* root_;
public:
	AVLTree() : root_(nullptr) {};
	Node* RotationRight(Node* current);
	Node* RotationLeft(Node* current);
	Node* BalanceNode(Node* current);
	void Insert(const int key);
	void OrderedPrint(Node* root) {
		if (root != nullptr) {
			OrderedPrint(root->left);
			cout << root->key << " ";
			OrderedPrint(root->right);
		}
	}
	void deleteTree(Node* root)
	{
		if (root != nullptr) {
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}
	}
	void Print()
	{
		OrderedPrint(root_);
	}
	~AVLTree()
	{
		deleteTree(root_);
	}
};

#endif