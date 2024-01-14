#pragma once
#include "IntegerSet.h"

void IntegerSet::deleteTree(Node* node)
{
	if (!node)
		return;

	//if (node->left)
	deleteTree(node->left);
	//if (node->right)
	deleteTree(node->right);

	delete node;
	node = nullptr;
}

void IntegerSet::coptyTree(Node*& newNode, const Node* oldNode)
{
	if (!oldNode)
	{
		newNode = nullptr;
		return;
	}

	newNode = new Node(oldNode->value);
	//if (oldNode->left)
	coptyTree(newNode->left, oldNode->left);
	//if (oldNode->right)
	coptyTree(newNode->right, oldNode->right);
}

void IntegerSet::copyFrom(const IntegerSet& other)
{
	try
	{
		coptyTree(root, other.root);
	}
	catch (...)
	{
		deleteTree(root);
		throw std::bad_alloc();
	}
	numberOfNodes = other.numberOfNodes;
}

//bool IntegerSet::sameTrees(const Node* node1, const Node* node2) const
//{
//	if (!node1 && !node2)
//		return true;
//	if (!node1 || !node2)
//		return false;
//	if (node1->value != node2->value)
//		return false;
//
//	return sameTrees(node1->left, node2->left) && sameTrees(node1->right, node2->right);
//}

bool IntegerSet::hasNode(const Node* node, int num) const
{
	if (!node)
		return false;
	return node->value == num || hasNode(node->left, num) || hasNode(node->right, num);
}

//bool IntegerSet::subTree(const Node* main, const Node* sub) const
//{
//	if (!sub)
//		return true;
//
//	if (!main)
//		return false;
//
//	if (main->value == sub->value)
//		if (subTree(main->left, sub->left) && subTree(main->right, sub->right))
//			return true;
//	
//	return subTree(main->left, sub) || subTree(main->right, sub);
//}

//Node* IntegerSet::createTree(const std::vector<int> arr, int first, int last)
//{
//	if (/*first < 0 || last < 0 ||*/ last < first)
//		return nullptr;
//	unsigned mid = (first + last) / 2;
//	Node* node = new Node(arr[mid]);
//	node->left = createTree(arr, first, mid - 1);
//	node->right = createTree(arr, mid + 1, last);
//	return node;
//}

void IntegerSet::createTree(Node*& node, const std::vector<int> arr, int first, int last) const
{
	if (/*first < 0 || last < 0 ||*/ last < first)
		return;
	unsigned mid = (first + last) / 2;
	node = new Node(arr[mid]);
	createTree(node->left, arr, first, mid - 1);
	createTree(node->right, arr, mid + 1, last);
}

void IntegerSet::printTree(std::ostream& out, const Node* node) const
{
	if (!node)
		return;
	
	printTree(out, node->left);
	out << " " << node->value;
	printTree(out, node->right);
}

//void IntegerSet::treeToVector(std::vector<int>& arr, const Node* node) const
//{
//	if (!node)
//		return;
//
//	treeToVector(arr, node->left);
//	arr.push_back(node->value);
//	treeToVector(arr, node->right);
//}

//void IntegerSet::mergeVectors(std::vector<int>& arr, const std::vector<int> arr1, unsigned size1, const std::vector<int> arr2, unsigned size2) const
//{
//	unsigned index1 = 0;
//	unsigned index2 = 0;
//
//	while (index1 < size1 && index2 < size2)
//	{
//		if (arr1[index1] == arr2[index2])
//		{
//			arr.push_back(arr1[index1]);
//			++index1;
//			++index2;
//		}
//		else if(arr1[index1] < arr2[index2])
//		{
//			arr.push_back(arr1[index1]);
//			++index1;
//		}
//		else
//		{
//			arr.push_back(arr2[index2]);
//			++index2;
//		}
//	}
//	while (index1 < size1)
//	{
//		arr.push_back(arr1[index1]);
//		++index1;
//	}
//	while (index2 < size2)
//	{
//		arr.push_back(arr2[index2]);
//		++index2;
//	}
//}

void IntegerSet::freeTree(Node* node) const
{
	if (!node)
		return;

	freeTree(node->left);
	freeTree(node->right);

	delete node;
	node = nullptr;
}

//void IntegerSet::mergeTrees(std::vector<int>& arr, const Node* firstNode, const Node* secondNode) const
//{
//	std::vector<int> firstArr;
//	treeToVector(firstArr, firstNode);
//	std::vector<int> secondArr;
//	treeToVector(secondArr, secondNode);
//	mergeVectors(arr, firstArr, firstArr.size(), secondArr, secondArr.size());
//}

//void IntegerSet::intersectTrees(std::vector<int>& arr, const Node* firstNode, const Node* secondNode) const
//{
//	std::vector<int> arr1;
//	treeToVector(arr1, firstNode);
//	std::vector<int> arr2;
//	treeToVector(arr2, secondNode);
//
//	unsigned index1 = 0;
//	unsigned size1 = arr1.size();
//	unsigned index2 = 0;
//	unsigned size2 = arr2.size();
//
//	while (index1 < size1 && index2 < size2)
//	{
//		if (arr1[index1] > arr2[index2])
//		{
//			++index2;
//		}
//		else if (arr1[index1] < arr2[index2])
//		{
//			++index1;
//		}
//		else
//		{
//			arr.push_back(arr1[index1]);
//			++index1;
//			++index2;
//		}
//	}
//}

void IntegerSet::intersectTrees(Node*& node, Node*& curr, const Node* firstNode, const Node* secondNode, unsigned& counter) const
{
	std::stack<const Node*> fisrtStack;
	std::stack<const Node*> secondStack;

	while (firstNode || secondNode || !fisrtStack.empty() && !secondStack.empty())
	{
		while (firstNode)
		{
			fisrtStack.push(firstNode);
			firstNode = firstNode->left;
		}
		while (secondNode)
		{
			secondStack.push(secondNode);
			secondNode = secondNode->left;
		}
		if (!fisrtStack.empty() && !secondStack.empty() && secondStack.top()->value == fisrtStack.top()->value)
		{
			firstNode = fisrtStack.top();
			fisrtStack.pop();
			secondNode = secondStack.top();
			secondStack.pop();
			if (counter == 0)
			{
				node = new Node(firstNode->value);
				node->right = new Node();
				curr = node->right;
			}
			else
			{
				curr->value = firstNode->value;
				curr->right = new Node(0);
				curr = curr->right;
			}
			++counter;
			firstNode = firstNode->right;
			secondNode = secondNode->right;
		}
		else if (!fisrtStack.empty() && !secondStack.empty() && secondStack.top()->value < fisrtStack.top()->value)
		{
			secondNode = secondStack.top();
			secondNode = secondNode->right;
			secondStack.pop();
		}
		else if (!fisrtStack.empty() && !secondStack.empty() && secondStack.top()->value > fisrtStack.top()->value)
		{
			firstNode = fisrtStack.top();
			firstNode = firstNode->right;
			fisrtStack.pop();
		}
	}

	/*if (!firstNode || !secondNode){
		node = nullptr;
		return;
	}
	if (firstNode->left && secondNode->left)
		intersectTrees(node, curr, firstNode->left, secondNode->left, counter);
	else if (firstNode->left)
		intersectTrees(node, curr, firstNode->left, secondNode, counter);
	else if (secondNode->left)
		intersectTrees(node, curr, firstNode, secondNode->left, counter);
	if (firstNode->value == secondNode->value)
	{
		if (counter == 0){
			node = new Node(firstNode->value);
			node->right = new Node();
			curr = node->right;
		}
		else{
			curr->value = firstNode->value;
			curr->right = new Node(0);
			curr = curr->right;
		}
		++counter;
	}
	if (firstNode->right && secondNode->right)
		intersectTrees(node, curr, firstNode->right, secondNode->right, counter);
	else if (firstNode->right)
		intersectTrees(node, curr, firstNode->right, secondNode, counter);
	else if (secondNode->right)
		intersectTrees(node, curr, firstNode, secondNode->right, counter);*/
}

bool IntegerSet::isSubset(const Node* small, const Node* big) const
{
	std::stack<const Node*> fisrtStack;
	std::stack<const Node*> secondStack;

	while (small || big || !fisrtStack.empty() && !secondStack.empty())
	{
		while (small)
		{
			fisrtStack.push(small);
			small = small->left;
		}
		while (big)
		{
			secondStack.push(big);
			big = big->left;
		}
		if (!fisrtStack.empty() && !secondStack.empty() && secondStack.top()->value == fisrtStack.top()->value)
		{
			small = fisrtStack.top();
			fisrtStack.pop();
			big = secondStack.top();
			secondStack.pop();
			
			small = small->right;
			big = big->right;
		}
		else if (!fisrtStack.empty() && !secondStack.empty() && secondStack.top()->value < fisrtStack.top()->value)
		{
			big = secondStack.top();
			big = big->right;
			secondStack.pop();
		}
		else if (!fisrtStack.empty() && !secondStack.empty() && secondStack.top()->value > fisrtStack.top()->value)
		{
			return false;
		}
	}

	if (!fisrtStack.empty())
		return false;

	return true;
}

bool IntegerSet::deleteLastNode(Node* root) const
{
	if (root->right)
	{
		if (deleteLastNode(root->right))
		{
			root->right = nullptr;
		}
	}
	else
	{
		delete root;
		root = nullptr;
		return true;
	}
	return false;
}

void IntegerSet::uniteTrees(Node*& root, Node*& curr, const Node* fisrtNode, const Node* secondNode, unsigned& counter) const
{
	std::stack<const Node*> fisrtStack;
	std::stack<const Node*> secondStack;

	while (fisrtNode || secondNode || !fisrtStack.empty() || !secondStack.empty())
	{
		while (fisrtNode)
		{
			fisrtStack.push(fisrtNode);
			fisrtNode = fisrtNode->left;
		}
		while (secondNode)
		{
			secondStack.push(secondNode);
			secondNode = secondNode->left;
		}
		if (secondStack.empty() || (!fisrtStack.empty() && fisrtStack.top()->value < secondStack.top()->value))
		{
			fisrtNode = fisrtStack.top();
			fisrtStack.pop();
			if (counter == 0)
			{
				root = new Node(fisrtNode->value);
				root->right = new Node();
				curr = root->right;
			}
			else
			{
				curr->value = fisrtNode->value;
				curr->right = new Node(0);
				curr = curr->right;
			}
			++counter;
			fisrtNode = fisrtNode->right;
		}
		else if (fisrtStack.empty() || (!secondStack.empty() && secondStack.top()->value < fisrtStack.top()->value))
		{
			secondNode = secondStack.top();
			secondStack.pop();
			if (counter == 0)
			{
				root = new Node(secondNode->value);
				root->right = new Node();
				curr = root->right;
			}
			else
			{
				curr->value = secondNode->value;
				curr->right = new Node(0);
				curr = curr->right;
			}
			++counter;
			secondNode = secondNode->right;
		}
		else if (!fisrtStack.empty() && !secondStack.empty() && secondStack.top()->value == fisrtStack.top()->value)
		{
			fisrtNode = fisrtStack.top();
			fisrtStack.pop();
			secondNode = secondStack.top();
			secondStack.pop();
			if (counter == 0)
			{
				root = new Node(fisrtNode->value);
				root->right = new Node();
				curr = root->right;
			}
			else
			{
				curr->value = fisrtNode->value;
				curr->right = new Node(0);
				curr = curr->right;
			}
			++counter;
			fisrtNode = fisrtNode->right;
			secondNode = secondNode->right;
		}
	}
}

IntegerSet::IntegerSet()
{
	root = nullptr;
	numberOfNodes = 0;
}

IntegerSet::IntegerSet(const IntegerSet& other)
{
	copyFrom(other);
}

IntegerSet& IntegerSet::operator=(const IntegerSet& other)
{
	if (this == &other)
		return *this;

	Node* temp = nullptr;
	try
	{
		coptyTree(temp, other.root);
	}
	catch (...)
	{
		delete(temp);
		temp = nullptr;
		throw std::bad_alloc();
	}
	deleteTree(root); //delete the original tree after copying the other, in order not to lose the original if there is not enough memory to copy the other
	root = temp;
	numberOfNodes = other.numberOfNodes;

	return *this;
}

IntegerSet::~IntegerSet()
{
	deleteTree(root);
}

size_t IntegerSet::size() const
{
	return numberOfNodes;
}

bool IntegerSet::equals(const IntegerSet& other) const
{
	if (this->numberOfNodes != other.numberOfNodes)
		return false;
	return isSubset(this->root, other.root);
	//return sameTrees(this->root, other.root);
}

bool IntegerSet::contains(int elem) const
{
	return hasNode(this->root, elem);
}

bool IntegerSet::subsetOf(const IntegerSet& other) const
{
	if (this->numberOfNodes > other.numberOfNodes)
		return false;

	return isSubset(this->root, other.root);
	//return subTree(other.root, this->root);
}

IntegerSet IntegerSet::getUnion(const IntegerSet& other) const
{
	if (!this->root && !other.root)
	{
		return IntegerSet();
	}

	Node* root = nullptr;
	Node* temp = nullptr;
	unsigned counter = 0;
	try
	{
		uniteTrees(root, temp, this->root, other.root, counter);
		deleteLastNode(root);
	}
	catch (...)
	{
		freeTree(root);
		throw std::bad_alloc();
	}
	IntegerSet result;
	result.root = root;
	result.numberOfNodes = counter;
	return result;

	/*std::vector<int> arr;
	mergeTrees(arr, this->root, other.root);
	Node* temp = nullptr;
	try
	{
		createTree(temp, arr, 0, arr.size()-1);
	}
	catch (...)
	{
		freeTree(temp);
		throw std::bad_alloc();
	}
	IntegerSet result;
	result.root = temp;
	result.numberOfNodes = arr.size();
	return result;*/
}

IntegerSet IntegerSet::getIntersection(const IntegerSet& other) const
{
	if (!this->root || !other.root)
	{
		return IntegerSet();
	}

	Node* root = nullptr;
	Node* temp = nullptr;
	unsigned counter = 0;
	try
	{
		intersectTrees(root, temp, this->root, other.root, counter);
		deleteLastNode(root);
	}
	catch (...)
	{
		freeTree(root);
		throw std::bad_alloc();
	}
	IntegerSet result;
	result.root = root;
	result.numberOfNodes = counter;
	return result;
}

void IntegerSet::deserialize(std::istream& in)
{
	int number, value;
	in >> number;
	std::vector<int> arr;
	for (size_t i = 0; i < number; i++)
	{
		in >> value;
		if (i > 0 && value <= arr[i - 1])
			throw std::runtime_error("elements not ascending strictly");
		arr.push_back(value);
	}
	Node* temp = nullptr;
	try
	{
		createTree(temp, arr, 0, number - 1);
		this->root = temp;
	}
	catch (...)
	{
		deleteTree(temp);
		throw std::bad_alloc();
	}
	numberOfNodes = number;
}

void IntegerSet::serialize(std::ostream& out) const
{
	out << numberOfNodes;
	printTree(out, this->root);
}

//throw  std::runtime_error("Not implementet");