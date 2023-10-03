#include "AVLTree.h"

int main()
{
	AVLTree avl;
	avl.Insert(2);
	avl.Insert(8);
	avl.Insert(4);
	avl.Insert(12);
	avl.Insert(16);
	avl.Insert(17);
	avl.Insert(14);
	avl.Insert(10);
	avl.Insert(6);
	avl.Print();
	cout << "\n";
	avl.Print();
	return 0;
}