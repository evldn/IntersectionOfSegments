#pragma once
namespace TwoThirdTree {
#include <algorithm>
#include <iostream>
#include <vector>
template <class T>
struct Node 
{
	//-------------------------[FIELDS]-------------------------
	int size;
	T keys[3];
	Node* children[4];
	Node* parent;
	//-------------------------[CONSTRUCTOR]-------------------------
	Node(T key, Node* _first = nullptr, Node* _second = nullptr, Node* _third = nullptr, Node* _fourth = nullptr, Node* _parent = nullptr) :
		size(1), parent(_parent) 
	{
		keys[0] = key;
		children[0] = _first;
		children[1] = _second; 
		children[2] = _third; 
		children[3] = _fourth;
	}
	//-------------------------[SERVICE METHODS]-------------------------
	int GetChildIndex()
	{
		int child_index = 0;
		for (; child_index <= parent->size; ++child_index) 
		{

			if (this == parent->children[child_index])
				break;
		}
		return child_index;
	}
	Node<T>* GetRightMostChild() 
	{ 
		return children[size]; 
	}
	void Swap(T& x, T& y) 
	{
		T r = x;
		x = y;
		y = r;
	}
	bool Find(T key)
	{
		for (int i = 0; i < size; ++i)
		{
			if (keys[i] == key)
			{
				return true;
			}
		}
		return false;
	}
	//-------------------------[SORTS]-------------------------
	void Sort2(T& x, T& y)
	{
		if (x > y) Swap(x, y);
	}
	void Sort3(T& x, T& y, T& z)
	{
		if (x > y) Swap(x, y);
		if (x > z) Swap(x, z);
		if (y > z) Swap(y, z);
	}
	void Sort()
	{
		if (size == 1) return;
		if (size == 2) Sort2(keys[0], keys[1]);
		if (size == 3) Sort3(keys[0], keys[1], keys[2]);
	}
	//-------------------------[CHANGES]-------------------------
	void InsertToNode(T key)
	{
		keys[size] = key;
		size++;
		Sort();
	}
	void RemoveFromNode(T key)
	{
		if (size >= 1 && keys[0] == key)
		{
			keys[0] = keys[1];
			keys[1] = keys[2];
			size--;
		}
		else if (size == 2 && keys[1] == key)
		{
			keys[1] = keys[2];
			size--;
		}
	}
	//-------------------------[CHECKS]-------------------------
	void BecomeNode2(T key, Node* _first, Node* _second)
	{
		keys[0] = key;
		children[0] = _first;
		children[1] = _second;
		children[2] = nullptr;
		children[3] = nullptr;
		parent = nullptr;
		size = 1;
	}
	bool IsLeaf()
	{
		return (!children[0]) && (!children[1]);
	}
	bool IsTwoNode()
	{
		return (children[0] != nullptr) && (children[1] != nullptr) && (children[2] == nullptr);
	}
	bool IsThreeNode()
	{
		return (size == 2);
	}
	//-------------------------[OUTPUT]-------------------------
	void Traverse() 
	{
		int i;
		for (i = 0; i < size; ++i) {
			if (!IsLeaf()) {
				children[i]->Traverse();
			}
			std::cout << " " << keys[i];
		}

		if (!IsLeaf()) {
			children[i]->Traverse();
		}
	}
};

template <class T>
class TwoThreeTree
{
	//-------------------------[BALANCING]-------------------------
	Node<T>* Split(Node<T>* current)
	{
		if (current->size < 3) return current;

		Node<T>* x = new Node<T>(current->keys[0], current->children[0], current->children[1], nullptr, nullptr, current->parent);
		Node<T>* y = new Node<T>(current->keys[2], current->children[2], current->children[3], nullptr, nullptr, current->parent);
		if (x->children[0])  x->children[0]->parent = x;
		if (x->children[1]) x->children[1]->parent = x;
		if (y->children[0])  y->children[0]->parent = y;
		if (y->children[1]) y->children[1]->parent = y;

		if (current->parent) 
		{
			current->parent->InsertToNode(current->keys[1]);

			if (current->parent->children[0] == current) current->parent->children[0] = nullptr;
			else if (current->parent->children[1] == current) current->parent->children[1] = nullptr;
			else if (current->parent->children[2] == current) current->parent->children[2] = nullptr;

			if (current->parent->children[0] == nullptr) 
			{
				current->parent->children[3] = current->parent->children[2];
				current->parent->children[2] = current->parent->children[1];
				current->parent->children[1] = y;
				current->parent->children[0] = x;
			}
			else if (current->parent->children[1] == nullptr) 
			{
				current->parent->children[3] = current->parent->children[2];
				current->parent->children[2] = y;
				current->parent->children[1] = x;
			}
			else 
			{
				current->parent->children[3] = y;
				current->parent->children[2] = x;
			}

			Node<T>* tmp = current->parent;
			delete current;
			return tmp;
		}
		else 
		{
			x->parent = current;
			y->parent = current;
			current->BecomeNode2(current->keys[1], x, y);
			return current;
		}
	}
	Node<T>* Merge(Node<T>* leaf)
	{
		Node<T>* parent = leaf->parent;

		if (parent->children[0] == leaf)
		{
			parent->children[1]->InsertToNode(parent->keys[0]);
			parent->children[1]->children[2] = parent->children[1]->children[1];
			parent->children[1]->children[1] = parent->children[1]->children[0];

			if (leaf->children[0] != nullptr) parent->children[1]->children[0] = leaf->children[0];
			else if (leaf->children[1] != nullptr) parent->children[1]->children[0] = leaf->children[1];

			if (parent->children[1]->children[0] != nullptr) parent->children[1]->children[0]->parent = parent->children[1];

			parent->RemoveFromNode(parent->keys[0]);
			delete parent->children[0];
			parent->children[0] = nullptr;
		}
		else if (parent->children[1] == leaf)
		{
			parent->children[0]->InsertToNode(parent->keys[0]);

			if (leaf->children[0] != nullptr) parent->children[0]->children[2] = leaf->children[0];
			else if (leaf->children[1] != nullptr) parent->children[0]->children[2] = leaf->children[1];

			if (parent->children[0]->children[2] != nullptr) parent->children[0]->children[2]->parent = parent->children[0];

			parent->RemoveFromNode(parent->keys[0]);
			delete parent->children[1];
			parent->children[1] = nullptr;
		}

		if (parent->parent == nullptr)
		{
			Node<T>* tmp = nullptr;
			if (parent->children[0] != nullptr) tmp = parent->children[0];
			else tmp = parent->children[1];
			tmp->parent = nullptr;
			delete parent;
			return tmp;
		}
		return parent;
	}
	Node<T>* Redistribute(Node<T>* leaf)
	{
		Node<T>* parent = leaf->parent;
		Node<T>* first = parent->children[0];
		Node<T>* second = parent->children[1];
		Node<T>* third = parent->children[2];

		if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) 
		{
			if (first == leaf) 
			{
				parent->children[0] = parent->children[1];
				parent->children[1] = parent->children[2];
				parent->children[2] = nullptr;
				parent->children[0]->InsertToNode(parent->keys[0]);
				parent->children[0]->children[2] = parent->children[0]->children[1];
				parent->children[0]->children[1] = parent->children[0]->children[0];

				if (leaf->children[0] != nullptr) parent->children[0]->children[0] = leaf->children[0];
				else if (leaf->children[1] != nullptr) parent->children[0]->children[0] = leaf->children[1];

				if (parent->children[0]->children[0] != nullptr) parent->children[0]->children[0]->parent = parent->children[0];

				parent->RemoveFromNode(parent->keys[0]);
				delete first;
			}
			else if (second == leaf) 
			{
				first->InsertToNode(parent->keys[0]);
				parent->RemoveFromNode(parent->keys[0]);
				if (leaf->children[0] != nullptr) first->children[2] = leaf->children[0];
				else if (leaf->children[1] != nullptr) first->children[2] = leaf->children[1];

				if (first->children[2] != nullptr) first->children[2]->parent = first;

				parent->children[1] = parent->children[2];
				parent->children[2] = nullptr;

				delete second;
			}
			else if (third == leaf) 
			{
				second->InsertToNode(parent->keys[1]);
				parent->children[2] = nullptr;
				parent->RemoveFromNode(parent->keys[1]);
				if (leaf->children[0] != nullptr) second->children[2] = leaf->children[0];
				else if (leaf->children[1] != nullptr) second->children[2] = leaf->children[1];

				if (second->children[2] != nullptr)  second->children[2]->parent = second;

				delete third;
			}
		}
		else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) 
		{
			if (third == leaf) 
			{
				if (leaf->children[0] != nullptr) 
				{
					leaf->children[1] = leaf->children[0];
					leaf->children[0] = nullptr;
				}
				leaf->InsertToNode(parent->keys[1]);
				if (second->size == 2) 
				{
					parent->keys[1] = second->keys[1];
					second->RemoveFromNode(second->keys[1]);
					leaf->children[0] = second->children[2];
					second->children[2] = nullptr;
					if (leaf->children[0] != nullptr) leaf->children[0]->parent = leaf;
				}
				else if (first->size == 2) 
				{
					parent->keys[1] = second->keys[0];
					leaf->children[0] = second->children[1];
					second->children[1] = second->children[0];
					if (leaf->children[0] != nullptr) leaf->children[0]->parent = leaf;
					second->keys[0] = parent->keys[0];
					parent->keys[0] = first->keys[1];
					first->RemoveFromNode(first->keys[1]);
					second->children[0] = first->children[2];
					if (second->children[0] != nullptr) second->children[0]->parent = second;
					first->children[2] = nullptr;
				}
			}
			else if (second == leaf) 
			{
				if (third->size == 2) 
				{
					if (leaf->children[0] == nullptr) 
					{
						leaf->children[0] = leaf->children[1];
						leaf->children[1] = nullptr;
					}
					second->InsertToNode(parent->keys[1]);
					parent->keys[1] = third->keys[0];
					third->RemoveFromNode(third->keys[0]);
					second->children[1] = third->children[0];
					if (second->children[1] != nullptr) second->children[1]->parent = second;
					third->children[0] = third->children[1];
					third->children[1] = third->children[2];
					third->children[2] = nullptr;
				}
				else if (first->size == 2) 
				{
					if (leaf->children[1] == nullptr) 
					{
						leaf->children[1] = leaf->children[0];
						leaf->children[0] = nullptr;
					}
					second->InsertToNode(parent->keys[0]);
					parent->keys[0] = first->keys[1];
					first->RemoveFromNode(first->keys[1]);
					second->children[0] = first->children[2];
					if (second->children[0] != nullptr) second->children[0]->parent = second;
					first->children[2] = nullptr;
				}
			}
			else if (first == leaf)
			{
				if (leaf->children[0] == nullptr) 
				{
					leaf->children[0] = leaf->children[1];
					leaf->children[1] = nullptr;
				}
				first->InsertToNode(parent->keys[0]);
				if (second->size == 2) 
				{
					parent->keys[0] = second->keys[0];
					second->RemoveFromNode(second->keys[0]);
					first->children[1] = second->children[0];
					if (first->children[1] != nullptr) first->children[1]->parent = first;
					second->children[0] = second->children[1];
					second->children[1] = second->children[2];
					second->children[2] = nullptr;
				}
				else if (third->size == 2) 
				{
					parent->keys[0] = second->keys[0];
					second->keys[0] = parent->keys[1];
					parent->keys[1] = third->keys[0];
					third->RemoveFromNode(third->keys[0]);
					first->children[1] = second->children[0];
					if (first->children[1] != nullptr) first->children[1]->parent = first;
					second->children[0] = second->children[1];
					second->children[1] = third->children[0];
					if (second->children[1] != nullptr) second->children[1]->parent = second;
					third->children[0] = third->children[1];
					third->children[1] = third->children[2];
					third->children[2] = nullptr;
				}
			}
		}
		else if (parent->size == 1) 
		{
			leaf->InsertToNode(parent->keys[0]);

			if (first == leaf && second->size == 2) 
			{
				parent->keys[0] = second->keys[0];
				second->RemoveFromNode(second->keys[0]);

				if (leaf->children[0] == nullptr) leaf->children[0] = leaf->children[1];

				leaf->children[1] = second->children[0];
				second->children[0] = second->children[1];
				second->children[1] = second->children[2];
				second->children[2] = nullptr;
				if (leaf->children[1] != nullptr) leaf->children[1]->parent = leaf;
			}
			else if (second == leaf && first->size == 2) 
			{
				parent->keys[0] = first->keys[1];
				first->RemoveFromNode(first->keys[1]);

				if (leaf->children[1] == nullptr) leaf->children[1] = leaf->children[0];

				leaf->children[0] = first->children[2];
				first->children[2] = nullptr;
				if (leaf->children[0] != nullptr) leaf->children[0]->parent = leaf;
			}
		}
		return parent;
	}
	Node<T>* Fix(Node<T>* leaf)
	{
		if (leaf->size == 0 && leaf->parent == nullptr)
		{
			delete leaf;
			return nullptr;
		}
		if (leaf->size != 0)
		{
			if (leaf->parent) return Fix(leaf->parent);
			else return leaf;
		}
		Node<T>* parent = leaf->parent;
		if (parent->children[0]->size == 2 || parent->children[1]->size == 2 || parent->size == 2) leaf = Redistribute(leaf);
		else if (parent->size == 2 && parent->children[2]->size == 2) leaf = Redistribute(leaf);
		else leaf = Merge(leaf);
		return Fix(leaf);
	}
	//-------------------------[SERVICE METHODS]-------------------------
	Node<T>* PartInsert(Node<T>* root, T key)
	{
		if (!root) return new Node<T>(key);
		if (root->IsLeaf()) root->InsertToNode(key);
		else if (key <= root->keys[0]) PartInsert(root->children[0], key);
		else if ((root->size == 1) || ((root->size == 2) && key <= root->keys[1])) PartInsert(root->children[1], key);
		else PartInsert(root->children[2], key);
		return Split(root);
	}
	Node<T>* RemoveNode(Node<T>* root, T& key)
	{
		Node<T>* current = Search(root, key);
		if (!current) return root;
		Node<T>* min = nullptr;
		if (current->keys[0] == key) min = SearchMin(current->children[1]);
		else min = SearchMin(current->children[2]);
		if (min) 
		{
			T& z = (key == current->keys[0] ? current->keys[0] : current->keys[1]);
			current->Swap(z, min->keys[0]);
			current = min;
		}
		current->RemoveFromNode(key);
		return Fix(current);
	}
	Node<T>* Search(Node<T>* current, T& key)
	{
		if (!current)
		{
			return nullptr;
		}
		if (current->Find(key))
		{
			return current;
		}
		else if (key < current->keys[0])
		{
			return Search(current->children[0], key);
		}
		else if ((current->size == 2) && (key < current->keys[1]) || (current->size == 1))
		{
			return Search(current->children[1], key);
		}
		else if (current->size == 2)
		{
			return Search(current->children[2], key);
		}
		else
		{
			return nullptr;
		}
	}
	Node<T>* SearchMin(Node<T>* current)
	{
		if (!current) return current;
		if (!(current->children[0])) return current;
		else return SearchMin(current->children[0]);
	}
	void DeleteTree(Node<T>* root)
	{
		if (root != nullptr) 
		{
			DeleteTree(root->children[0]);
			DeleteTree(root->children[1]);
			DeleteTree(root->children[2]);
			DeleteTree(root->children[3]);
			delete root;
		}
	}
	T GetPredecessor(Node<T>* current, T key)
	{
		if (current->IsLeaf())
		{
			if (current == root_)
			{
				if (root_->IsThreeNode() && root_->keys[1] == key)
				{
					return current->keys[0];
				}
				return nothing_1;
			}
			else
			{
				return GetLeafNodePredecessor(current, key);
			}

		}
		else
		{
			return GetInternalNodePredecessor(current, key);
		}
	}
	T GetInternalNodePredecessor(Node<T>* pnode, T key)
	{
		Node<T>* tmp = Search(root_, key);
		Node<T>* leftChild = pnode->children[((tmp->size == 2 && tmp->keys[1] == key) ? 1 : 0)];
		for (Node<T>* current = leftChild; current; current = current->children[current->size])
		{
			pnode = current;
		}
		return pnode->keys[pnode->size - 1];
	}
	T GetLeafNodePredecessor(Node<T>* pnode, T key)
	{
		if (pnode->IsThreeNode() && pnode->keys[1] == key)
		{
			return pnode->keys[0];
		}
		if (int child_index = pnode->GetChildIndex(); child_index != 0)
		{
			return pnode->parent->keys[child_index - 1];
		}
		else
		{
			Node<T>* parent = pnode->parent;
			for (; pnode == parent->children[0]; parent = parent->parent)
			{
				if (parent == root_) 
				{

					return nothing_1;
				}
				pnode = parent;
			}
			int index_of_child = pnode == parent->children[1] ? 1 : 2;
			return parent->keys[index_of_child - 1];
		}
	}
	T GetSuccessor(Node<T>* current, T key)
	{
		if (current->IsLeaf())
		{
			if (current == root_)
			{
				if (root_->IsThreeNode() && key == root_->keys[0])
				{
					return current->keys[1];
				}
				return nothing_2;
			}
			else
			{
				return GetLeafNodeSuccessor(current, key);
			}

		}
		else
		{
			return GetInternalNodeSuccessor(current, key);
		}
	}
	T GetInternalNodeSuccessor(Node<T>* pnode, T key)
	{
		Node<T>* tmp = Search(root_, key);
		Node<T>* rightChild = pnode->children[((tmp->size == 2 && tmp->keys[1] == key) ? 1 : 0) + 1];
		for (Node<T>* current = rightChild; current; current = current->children[0])
		{
			pnode = current;
		}
		return pnode->keys[0];
	}
	T GetLeafNodeSuccessor(Node<T>* pnode, T key)
	{
		if (pnode->IsThreeNode() && key == pnode->keys[0])
		{
			return pnode->keys[1];
		}
		int suc_key_index;
		switch (int child_index = pnode->GetChildIndex(); child_index)
		{
		case 0: 
		{ 
			return pnode->parent->keys[0]; 
		}
		case 1:
		{
			if (pnode->parent->IsThreeNode())
			{
				return pnode->parent->keys[1];
			}
		}
		case 2:
		{
			Node<T>* parent = pnode->parent;
			for (;pnode == parent->GetRightMostChild(); parent = parent->parent)
			{
				if (parent == root_)
				{
					return nothing_2;
				}
				pnode = parent;
			}
			if (parent->IsThreeNode())
			{
				suc_key_index = (pnode == parent->children[0]) ? 0 : 1;
			}
			else
			{
				suc_key_index = 0;
			}

			return parent->keys[suc_key_index];
		}
		break;
		default:
			break;
		}
		return nothing_2;
	}
	//-------------------------[FIELDS]-------------------------
	Node<T>* root_;
	Segment nothing_1;
	Segment nothing_2;
public:
	//-------------------------[CONSTRUCTORS AND DESTRUCTOR]-------------------------
	TwoThreeTree(Node<T>* root = nullptr) : root_(root), nothing_1(-22, -16, -20, -15, -1), nothing_2(-18, -16, -16, -16, -2) {};
	~TwoThreeTree() { DeleteTree(root_); }
	//-------------------------[CHANGES]-------------------------
	void Insert(T key)
	{
		root_ = PartInsert(root_, key);
	}
	void Remove(T& key)
	{
		root_ = RemoveNode(root_, key);
	}
	//-------------------------[SEARCHES]-------------------------
	T Under(T key)
	{
		Node<T>* current = Search(root_, key);
		if(current != nullptr)
			return GetPredecessor(current, key);
		return nothing_1;
	}
	T Over(T key)
	{
		Node<T>* current = Search(root_, key);
		if (current != nullptr)
			return GetSuccessor(current, key);
		return nothing_2;
	}
	//-------------------------[OUTPUT]-------------------------
	void Traverse()
	{
		root_->Traverse();
	}
};
}