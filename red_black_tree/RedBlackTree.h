#pragma once
class RedBlackTree
{
private:
	enum Color
	{
		BLACK = 0,
		RED
	};
	struct Node
	{
		Node* _parent;
		Node* _left;
		Node* _right;
		Color _color;
		int _data;
	};
public:

	RedBlackTree() { _root = &_nil; }
	~RedBlackTree() { clear(); }

	int getHeight();
	int getSize() { return _size; }
	
	bool insertData(int data);
	bool deleteData(int data);
	bool isExistData(int data);
	void clear();
	
private:

	void RotateRight(Node* node);
	void RotateLeft(Node* node);
	int  getHeight(Node* node, int height);
	void postOrderForClear(Node* node);

	Node* getUncle(Node* node);
	Node* getGrandParent(Node* node);
	Node* getSibling(Node* node);
	Node* isExistData(Node* node, int data);
	void connectNilNode(Node* node);
private:
	Node* _root;
	Node _nil{ nullptr, nullptr, nullptr, BLACK };
	size_t _size = 0;
};


