#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_

#include <iostream>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

struct Node
{
	Node *parent;
	Node *child;
	Node *sibling;
	int key;
	int degree;
	string data;

	Node(int, string s = "");
	string toString();
	void showTreeContent(int);
};

struct BinomialHeap
{
	Node *head;

	BinomialHeap();
	void showContent();

	friend BinomialHeap *makeBinomialHeap();

	friend BinomialHeap *binomialHeapUnion(BinomialHeap *, BinomialHeap *);
	friend void binomialLink(Node *, Node *);
	friend Node *nodeListMerge(Node *, Node *);
	friend Node *binomialHeapMerge(BinomialHeap *, BinomialHeap *);

	friend BinomialHeap *insert(BinomialHeap *, Node *);

	friend Node *findMinRoot(Node *);

	friend Node *binomialHeapExtractMin(BinomialHeap *);
	friend Node *reverseList(Node *);

	friend Node *findNode(Node *, int);
	friend void decreaseKey(Node *, int, int);
};

// Node ----------------------------------
/**
 * Constructor
 */
Node::Node(int k, string s)
	: parent(0), child(0), sibling(0), key(k), degree(0), data(s) {}

/**
 * Display node 'key : data'
 */
string Node::toString()
{
	stringstream ss;
	if (data != "")
	{
		ss << key << " : " << data;
		return ss.str();
	}
	return "";
}

/**
 * Display tree with this node as root
 */
void Node::showTreeContent(int indent)
{
	if (sibling)
		sibling->showTreeContent(indent);
	for (int i = 1; i <= indent; i++)
		cout << ' ';
	cout << toString() << endl;
	if (child)
		child->showTreeContent(indent + 1);
}
// Node ----------------------------------

// BinomialHeap --------------------------
/**
 * Builder. An empty binomial heap is created,
 * the head pointer points to Nil.
 */
BinomialHeap::BinomialHeap()
{
	head = 0;
}

/**
 * Displaying the trees in the pile
 */
void BinomialHeap::showContent()
{
	if (head)
	{
		cout << "The content of the binomial heap is: " << endl;
		head->showTreeContent(0);
	}
	else
		cout << "The binomial heap is empty." << endl;
}

/*
 * Friendly function that creates a binomial stack
 * and returns the pointer to it
 */
BinomialHeap *makeBinomialHeap()
{
	return new BinomialHeap();
}

/**
 * Auxiliary function that connects root y to root z
 */
void binomialLink(Node *y, Node *z)
{
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree++;
}

/*
 * Auxiliary function that combines l1 and l2 (destructively),
 * in the non-decreasing order of their degrees.
 *
 * l1 and l2 are lists of nodes sorted in ascending order of degrees
 */
Node *nodeListMerge(Node *l1, Node *l2)
{
	if (l1 == 0) // l1 doesn't have elements
		return l2;
	else if (l2 == 0) // l2 doesn't have elements
		return l1;
	else if (l1->degree <= l2->degree)
	{
		l1->sibling = nodeListMerge(l1->sibling, l2);
		return l1;
	}
	else
	{
		l2->sibling = nodeListMerge(l1, l2->sibling);
		return l2;
	}
}

/**
 * Auxiliary function that combines the root lists of piles H1 and H2
 */
Node *binomialHeapMerge(BinomialHeap *H1, BinomialHeap *H2)
{
	return nodeListMerge(H1->head, H2->head);
}

/**
 * Friendly function that returns a pointer to a newly formed heap
 * from the meeting of piles H1 and H2. Heaps H1 and H2 can be destroyed.
 */
BinomialHeap *binomialHeapUnion(BinomialHeap *H1, BinomialHeap *H2)
{
	BinomialHeap *H = makeBinomialHeap();
	H->head = binomialHeapMerge(H1, H2);
	if (H->head == 0)
		return H;
	Node *prev_x = 0;
	Node *x = H->head;
	Node *next_x = x->sibling;

	while (next_x)
	{
		if (x->degree != next_x->degree ||
			(next_x->sibling && next_x->sibling->degree == x->degree))
		{
			prev_x = x; // Case 1 and 2
			x = next_x; // Case 1 and 2
		}
		else if (x->key <= next_x->key)
		{
			x->sibling = next_x->sibling; // Case 3
			binomialLink(next_x, x);	  // Case 3
		}
		else
		{
			if (prev_x == 0)	  // Case 4
				H->head = next_x; // Case 4
			else
				prev_x->sibling = next_x; // Case 4
			binomialLink(x, next_x);	  // Case 4
			x = next_x;					  // Case 4
		}
		next_x = x->sibling;
	}
	return H;
}

/*
 * Friendly function that inserts the node x into the binomial heap H.
 */
BinomialHeap *insert(BinomialHeap *H, Node *x)
{
	BinomialHeap *H1 = makeBinomialHeap();
	x->parent = x->child = x->sibling = NULL;
	x->degree = 0;
	H1->head = x;
	return binomialHeapUnion(H, H1);
}

/**
 * Friendly function that returns the node with the smallest key in
 * the list of nodes indicated by n
 */
Node *findMinRoot(Node *n)
{
	Node *minNode = n;
	Node *current = n;
	while (current)
	{
		if (current->key < minNode->key)
		{
			minNode = current;
		}
		current = current->sibling;
	}
	return minNode;
}

/*
 * Auxiliary function that reverses the list of nodes
 * linked by the 'sibling' pointer
 */
Node *reverseList(Node *l)
{
	Node *prev = NULL, *curr = l, *next;
	while (curr)
	{
		next = curr->sibling;
		curr->sibling = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

/**
 * Friendly function that extracts the node with the smallest key
 * from the list of roots of the binomial heap H
 */
Node *binomialHeapExtractMin(BinomialHeap *H)
{
	Node *x = findMinRoot(H->head);
	if (x == NULL)
	{
		cout << "This heap is empty" << endl;
		return 0;
	}
	else
	{
		Node *n = H->head;
		if (n == x)
			H->head = n->sibling;
		else
		{
			while (n->sibling != x)
				n = n->sibling;
			n->sibling = n->sibling->sibling;
		}
	}
	BinomialHeap *H1 = makeBinomialHeap();
	H1->head = reverseList(x->child);
	H->head = binomialHeapUnion(H, H1)->head;
	x->child = x->sibling = x->parent = 0;
	return x;
}

/**
 * Auxiliary function that returns the node, from the tree rooted in n,
 * whose key is equal to k
 */
Node *findNode(Node *n, int k)
{
	if (n == 0)
		return NULL;

	if (n->key == k)
		return n;

	Node *rez = findNode(n->child, k);
	if (rez != NULL)
		return rez;

	return findNode(n->sibling, k);
}

/**
 * Friendly function that decrements the key of a node to the new value
 */
void decreaseKey(Node *H, int o, int n)
{
	Node *node = findNode(H, o);
	if (node == NULL)
		return;
	if (n > node->key)
	{
		cout << "New key is greater than current key" << endl;
		return;
	}
	node->key = n;
	Node *y = node;
	Node *z = y->parent;
	while (z != NULL && y->key < z->key)
	{
		swap(y->key, z->key); // swap the keys
		y = z;
		z = y->parent;
	}
}

// BinomialHeap --------------------------

#endif /* BINOMIALHEAP_H_ */
