#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <stack>

class IntegerSet {
private:
  //TODO Add implementation details here

	class Node 
	{
	public:
		int value;
		Node* left;
		Node* right;
		
		Node() : value(0), left(nullptr), right(nullptr) {}
		Node(int value) : value(value), left(nullptr), right(nullptr) {}
		Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
	};

	Node* root;
	unsigned numberOfNodes;

private:
	void deleteTree(Node*);
	void coptyTree(Node*&, const Node*);
	void copyFrom(const IntegerSet&);

	//bool sameTrees(const Node*, const Node*) const;
	bool hasNode(const Node*, int) const;
	//bool subTree(const Node* main, const Node* sub) const;
	//Node* createTree(const std::vector<int>, int, int);
	void createTree(Node*&, const std::vector<int>, int, int) const;
	void printTree(std::ostream&, const Node*) const;
	//void treeToVector(std::vector<int>&, const Node*) const;
	//void mergeVectors(std::vector<int>&, const std::vector<int>, unsigned, const std::vector<int>, unsigned) const;
	void freeTree(Node*) const;
	//void mergeTrees(std::vector<int>&, const Node*, const Node*) const;
	//void intersectTrees(std::vector<int>&, const Node*, const Node*) const;
	void intersectTrees(Node*&, Node*&, const Node*, const Node*, unsigned&) const;
	bool isSubset(const Node*, const Node*) const;
	bool deleteLastNode(Node*) const;
	void uniteTrees(Node*&, Node*&, const Node*, const Node*, unsigned&) const;

public:
  IntegerSet();
  IntegerSet(const IntegerSet&);
  IntegerSet& operator=(const IntegerSet&);
  ~IntegerSet();

public:
  // Връща броя на елементите в множеството
  size_t size() const;

  /// Проверява дали две множества се състоят от едни и същи елементи
  bool equals(const IntegerSet&) const;

  /// Проверява дали елемент се съдържа в множеството
  bool contains(int) const;

  /// Проверява дали текущия обект е подмножество на друг
  bool subsetOf(const IntegerSet&) const;

  /// Връща обединението на две множества
  IntegerSet getUnion(const IntegerSet&) const;

  /// Връща сечението на две множества
  IntegerSet getIntersection(const IntegerSet&) const;

  /// Десериализира съдържанието на едно множество.
  /// Новата информация напълно заменя старата.
  void deserialize(std::istream&);

  /// Сериализира съдържанието на едно множество
  void serialize(std::ostream&) const;
};

inline std::istream& operator>>(std::istream& in, IntegerSet& set)
{
  set.deserialize(in);
  return in;
}

inline std::ostream& operator<<(std::ostream& out, const IntegerSet& set)
{
  set.serialize(out);
  return out;
}
