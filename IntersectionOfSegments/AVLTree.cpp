#include "AVLTree.h"

int AVLTree::GetBalance(Node* current)
{
	return Height(current->right) - Height(current->left);
}

Node* AVLTree::RotationRight(Node* current, Node* parent)
{
	Node* left = current->left;
	Node* A = left->left;
	Node* B = left->right;
	Node* C = current->right;
	left->left = A;
	left->right = current;
	current->left = B;
	current->right = C;
	if (A != nullptr)
	{
		A->parent = left;
	}
	current->parent = left;
	if(B != nullptr)
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

Node* AVLTree::RotationLeft(Node* current, Node* parent)
{
	Node* right = current->right;
	Node* A = right->right;
	Node* B = right->left;
	Node* C = current->left;
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

Node* AVLTree::BalanceNode(Node* current) {
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

void AVLTree::PartInsertRecursive(Node* current, int key) {
	if (key < current->key) {
		if (current->left)
			PartInsertRecursive(current->left, key);
		else
			current->left = new Node(key, current);
		current->left = BalanceNode(current->left);
	}
	else {
		if (current->right)
			PartInsertRecursive(current->right, key);
		else
			current->right = new Node(key, current);
		current->right = BalanceNode(current->right);
	}
}

void AVLTree::Insert(const int key) {
	if (root_ == nullptr) {
		root_ = new Node(key);
		return;
	}
	PartInsertRecursive(root_, key);
	root_ = BalanceNode(root_);
}

Node* AVLTree::UnderNode(Node* node)
{
	if (node->right != nullptr)
	{
		return Min(node->right);
	}
	Node* tmp = node->parent;
	while (tmp != nullptr && node == tmp->right)
	{
		node = tmp;
		tmp = tmp->parent;
	}
	return tmp;
}

Node* AVLTree::OverNode(Node* node)
{
	if (node->left != nullptr)
	{
		return Max(node->left);
	}
	Node* tmp = node->parent;
	while (tmp != nullptr && node == tmp->left)
	{
		node = tmp;
		tmp = tmp->parent;
	}
	return tmp;
}