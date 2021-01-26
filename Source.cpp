#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int data;
	Node* pLeft;
	Node* pRight;

	Node(int data) : data(data), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->data <= pRoot->data)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->data = q->data;
	q = p;
	p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->data < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->data > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->data << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->data < pRoot->data)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}

pair<int, vector<Node*>* > findLargestBranch(Node*& pRoot)
{
	//Checking whether or not a node exists.
	if (pRoot == nullptr)
		return { 0, nullptr };

	//Algorithm runs recursively for both left and right side of the current node. Using const auto& reduces the memory allocated because the program doesn't make new copies.
	const auto& leftPair	= findLargestBranch(pRoot->pLeft);
	const auto& rightPair	= findLargestBranch(pRoot->pRight);

	//Declaration of the pair to be returned.
	pair<int, vector<Node*>*> largestBranchPair;

	//Is current node a "leaf"? If it's left and right child nodes are nullptr, then the node is a "leaf". If the node is a "leaf", then construct a new vector. So we will have as much vectors as "leafs", in heap.
	if (leftPair.second == nullptr && rightPair.second == nullptr)
		largestBranchPair.second = new vector<Node*>;
	//If not, compare right and left sides and pick the larger one.
	else
	{
		if (leftPair.first < rightPair.first)
			largestBranchPair = rightPair;
		else
			largestBranchPair = leftPair;
	}

	//Adding node's data to largest sum and pointer to branch vector.
	largestBranchPair.first += pRoot->data;
	largestBranchPair.second->push_back(pRoot);
	
	return largestBranchPair;
}

void main()
{
	// Constructing the tree.
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}

	//Constructing the tree in the example.
	//auto pRoot = new Node(5);
	//auto Node2 = new Node(4);
	//auto Node3 = new Node(8);
	//auto Node4 = new Node(11);
	//auto Node5 = new Node(13);
	//auto Node6 = new Node(4);
	//auto Node7 = new Node(7);
	//auto Node8 = new Node(2);
	//auto Node9 = new Node(1);

	//pRoot->pLeft = Node2;
	//pRoot->pRight = Node3;
	//Node2->pLeft = Node4;
	//Node4->pLeft = Node7;
	//Node4->pRight = Node8;
	//Node3->pRight = Node6;
	//Node3->pLeft = Node5;
	//Node6->pRight = Node9;

	auto result = findLargestBranch(pRoot);

	cout << "Branch with the largest sum is:";

	for (int i = result.second->size() - 1; i >= 0; i--)
		cout << " " << result.second->at(i)->data;

	cout << " -> SUM = " << result.first << endl;

	//PrintTree(pRoot, 1);
}