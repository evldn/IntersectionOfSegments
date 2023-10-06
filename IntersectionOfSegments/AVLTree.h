#pragma once
#ifndef INTERSECTION_OF_SEGMENTS_AVL_TREE_H_
#define INTERSECTION_OF_SEGMENTS_AVL_TREE_H_
#include <algorithm>
#include <iostream>

struct Node
{
	int key;
	Node* left, * right;
	Node* parent;
	int height;
	Node(int _key, Node* _parent = nullptr, Node* _left = nullptr, Node* _right = nullptr, int _height = 1) :
		key(_key), left(_left), right(_right), parent(_parent), height(_height) {};
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
	Node* Min(Node* node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}
	Node* Max(Node* node)
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node;
	}
	Node* root_;
public:
	AVLTree(Node* root = nullptr) : root_(root) {};

	Node* RotationRight(Node* current, Node* parent);
	Node* RotationLeft(Node* current, Node* parent);
	Node* BalanceNode(Node* current);

	Node* Maximum() { return Max(root_); }
	Node* Minimum() { return Min(root_); }

	void Insert(const int key);
	void deleteTree(Node* root)
	{
		if (root != nullptr) {
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}
	}

	Node* UnderNode(Node* node);
	Node* OverNode(Node* node);

	void OrderedPrint(Node* root) {
		if (root != nullptr) {
			OrderedPrint(root->left);
			std::cout << root->key << " ";
			OrderedPrint(root->right);
		}
	}
	void Print() { OrderedPrint(root_); }
	~AVLTree() { deleteTree(root_); }
};
#endif