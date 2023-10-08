#pragma once
#ifndef INTERSECTION_OF_SEGMENTS_AVL_TREE_H_
#define INTERSECTION_OF_SEGMENTS_AVL_TREE_H_
#include <algorithm>
#include <iostream>
#include "Segments.h"
#include <vector>

template <class T>
struct Node
{
	T key;
	Node* left, * right;
	Node* parent;
	int height;
	Node(T _key, Node* _parent = nullptr, Node* _left = nullptr, Node* _right = nullptr, int _height = 1) :
		key(_key), left(_left), right(_right), parent(_parent), height(_height) {};
};

template <class T>
class AVLTree
{
	int GetBalance(Node<T>* current)
	{
		return Height(current->right) - Height(current->left);
	}
	int Height(Node<T>* current) { return current ? current->height : 0; }
	void FixHeight(Node<T>* current)
	{
		unsigned char height_left = Height(current->left);
		unsigned char height_right = Height(current->right);
		current->height = (height_right > height_left ? height_right : height_left) + 1;
	}
	void PartInsertRecursive(Node<T>* current, T key)
	{
		if (key < current->key) {
			if (current->left)
				PartInsertRecursive(current->left, key);
			else
				current->left = new Node<T>(key, current);
			current->left = BalanceNode(current->left);
		}
		else {
			if (current->right)
				PartInsertRecursive(current->right, key);
			else
				current->right = new Node<T>(key, current);
			current->right = BalanceNode(current->right);
		}
	}
	void PartInsertNodeRecursive(Node<T>* current, Node<T>* keyNode)
	{
		if (keyNode->key < current->key) {
			if (current->left)
				PartInsertNodeRecursive(current->left, keyNode);
			else
			{
				current->left = keyNode;
				keyNode->parent = current;
			}
			current->left = BalanceNode(current->left);
		}
		else {
			if (current->right)
				PartInsertNodeRecursive(current->right, keyNode);
			else
			{
				current->right = keyNode;
				keyNode->parent = current;
			}
			current->right = BalanceNode(current->right);
		}
	}
	Node<T>* Min(Node<T>* node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}
	Node<T>* Max(Node<T>* node)
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node;
	}
	Node<T>* root_;
public:
	AVLTree(Node<T>* root = nullptr) : root_(root) {};

	Node<T>* RotationRight(Node<T>* current, Node<T>* parent)
	{
		Node<T>* left = current->left;
		Node<T>* A = left->left;
		Node<T>* B = left->right;
		Node<T>* C = current->right;
		left->left = A;
		left->right = current;
		current->left = B;
		current->right = C;
		if (A != nullptr)
		{
			A->parent = left;
		}
		current->parent = left;
		if (B != nullptr)
		{
			B->parent = current;
		}
		if (C != nullptr)
		{
			C->parent = current;
		}
		left->parent = parent;
		int th = 0;
		if (B != nullptr)
			th = B->height;
		if (C != nullptr)
			th = std::max(th, C->height);
		th++;
		current->height = th;
		if (A != nullptr)
			th = std::max(th, A->height);
		th++;
		left->height = th;
		return left;
	}
	Node<T>* RotationLeft(Node<T>* current, Node<T>* parent)
	{
		Node<T>* right = current->right;
		Node<T>* A = right->right;
		Node<T>* B = right->left;
		Node<T>* C = current->left;
		right->right = A;
		right->left = current;
		current->right = B;
		current->left = C;
		if (A != nullptr)
		{
			A->parent = right;
		}
		current->parent = right;
		if (B != nullptr)
		{
			B->parent = current;
		}
		if (C != nullptr)
		{
			C->parent = current;
		}
		right->parent = parent;
		int th = 0;
		if (B != nullptr)
			th = B->height;
		if (C != nullptr)
			th = std::max(th, C->height);
		th++;
		current->height = th;
		if (A != nullptr)
			th = std::max(th, A->height);
		th++;
		right->height = th;
		return right;
	}
	Node<T>* BalanceNode(Node<T>* current)
	{
		FixHeight(current);
		int b = GetBalance(current);
		if (b == 2) {
			if (GetBalance(current->right) < 0)
				current->right = RotationRight(current->right, current);
			return RotationLeft(current, current->parent);
		}
		else if (b == -2) {
			if (GetBalance(current->left) > 0)
				current->left = RotationLeft(current->left, current);
			return RotationRight(current, current->parent);
		}
		return current;
	}

	Node<T>* Maximum() { return Max(root_); }
	Node<T>* Minimum() { return Min(root_); }

	void Insert(const T key)
	{
		if (root_ == nullptr) {
			root_ = new Node<T>(key);
			return;
		}
		PartInsertRecursive(root_, key);
		root_ = BalanceNode(root_);
	}
	void InsertNode(Node<T>* keyNode)
	{
		if (root_ == nullptr) {
			root_ = keyNode;
			return;
		}
		PartInsertNodeRecursive(root_, keyNode);
		root_ = BalanceNode(root_);
	}

	void RemoveMin(Node<T>* node) // удаление узла с минимальным ключом из дерева p
	{
		if (node->left == 0)
			return node->right;
		node->left = RemoveMin(node->left);
		BalanceNode(node);
	}

	void deleteTree(Node<T>* root)
	{
		if (root != nullptr) {
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}
	}

	Node<T>* UnderNode(Node<T>* node)
	{
		if (node->right != nullptr)
		{
			return Min(node->right);
		}
		Node<T>* tmp = node->parent;
		while (tmp != nullptr && node == tmp->right)
		{
			node = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}
	Node<T>* OverNode(Node<T>* node)
	{
		if (node->left != nullptr)
		{
			return Max(node->left);
		}
		Node<T>* tmp = node->parent;
		while (tmp != nullptr && node == tmp->left)
		{
			node = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}
	Node<T>& getNode(const T key) {
		Node<T>* current = root_;
		while (current != nullptr) {
			if (key == current->key)
				return &current;
			else if (key < current->key)
				current = current->left;
			else if (key > current->key)
				current = current->right;
		}
	}

	void OrderedContent(Node<T>* root, T mass[], int& i)//std::vector<T>& mass)
	{
		if (root != nullptr) {
			OrderedContent(root->left, mass, i);
			mass[i] = root->key;
			i++;
			OrderedContent(root->right, mass, i);
		}
	}

	void OrderedPrint(Node<T>* root) {
		if (root != nullptr) {
			OrderedPrint(root->left);
			std::cout << root->key << " ";
			OrderedPrint(root->right);
		}
	}
	void Print() { OrderedPrint(root_); }
	void Content(T mass[], int& i) { OrderedContent(root_, mass, i); }
	~AVLTree() { deleteTree(root_); }
};
#endif