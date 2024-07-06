#include "RedBlackTree.h"

void RedBlackTree::RotateRight(Node* node)
{
	Node* root = node->_left;
	Node* parent = node->_parent;

	if (root->_right != &_nil)
		root->_right->_parent = node;

	node->_left = root->_right;
	node->_parent = root;

	root->_right = node;
	root->_parent = parent;

	if (root->_parent)
	{
		if (parent->_right == node)
			parent->_right = root;
		else
			parent->_left = root;
	}
	else
	{
		_root = root;
	}

}
void RedBlackTree::RotateLeft(Node* node)
{
	Node* root = node->_right;
	Node* parent = node->_parent;

	if (root->_left != &_nil)
		root->_left->_parent = node;

	node->_right = root->_left;
	node->_parent = root;

	root->_left = node;
	root->_parent = parent;

	if (root->_parent)
	{
		if (parent->_right == node)
			parent->_right = root;
		else
			parent->_left = root;
	}
	else
	{
		_root = root;
	}

}
RedBlackTree::Node* RedBlackTree::getGrandParent(Node* node)
{
	return node->_parent->_parent;
}
RedBlackTree::Node* RedBlackTree::getUncle(Node* node)
{
	Node* gf = getGrandParent(node);
	if (gf->_left == node->_parent)
		return gf->_right;
	else
		return gf->_left;
}
RedBlackTree::Node* RedBlackTree::getSibling(Node* node)
{
	if (node->_parent->_left == node)
		return node->_parent->_right;
	else
		return node->_parent->_left;
}
bool RedBlackTree::insertData(int data)
{

	if (_root == &_nil)
	{
		_root = new Node{ nullptr, &_nil, &_nil, BLACK, data };
		_size++;
		return true;
	}

	Node* parentNode = _root;

	while (1)
	{
		if (parentNode->_data > data)
		{
			if (parentNode->_left == &_nil)
				break;
			else
				parentNode = parentNode->_left;
		}
		else if (data > parentNode->_data)
		{
			if (parentNode->_right == &_nil)
				break;
			else
				parentNode = parentNode->_right;
		}
		else
			return false;

	}
	_size++;
	Node* node = new Node{ parentNode, &_nil, &_nil, RED, data };

	if (parentNode->_data > data)
		parentNode->_left = node;
	else
		parentNode->_right = node;

	if (parentNode->_color == RED)
	{
		Node* uncle = getUncle(node);

		while (1)
		{
			//CASE 1
			if (uncle->_color == RED)
			{
				uncle->_color = BLACK;
				node->_parent->_color = BLACK;

				if (uncle->_parent == _root)
				{
					uncle->_parent->_color = BLACK;
					break;
				}
				else
					uncle->_parent->_color = RED;

				node = uncle->_parent;

				if (node->_parent->_color == RED)
					uncle = getUncle(node);
				else
					break;
			}
			else
			{
				//CASE 2, 3
				Node* gf = getGrandParent(node);
				Node* parent = node->_parent;

				if (gf->_left == parent)
				{
					if (parent->_right == node)
					{
						RotateLeft(parent);

						parent = node;
						node = node->_left;
					}

					gf->_color = RED;
					parent->_color = BLACK;
					RotateRight(gf);

				}
				else if (gf->_right == parent)
				{
					if (parent->_left == node)
					{
						RotateRight(parent);

						parent = node;
						node = node->_right;
					}

					gf->_color = RED;
					parent->_color = BLACK;
					RotateLeft(gf);
				}

				if (gf == _root)
					_root = parent;

				break;
			}
		}
	}

	return true;
}
void RedBlackTree::connectNilNode(Node* node)
{
	if (node->_parent->_left == node)
		node->_parent->_left = &_nil;
	else if (node->_parent->_right == node)
		node->_parent->_right = &_nil;
}
bool RedBlackTree::deleteData(int data)
{

	if (_root == &_nil)
		return false;


	Node* target = _root;
	while (target != &_nil)
	{
		if (target->_data > data)
		{
			target = target->_left;
		}
		else if (data > target->_data)
		{
			target = target->_right;
		}
		else
		{
			--_size;
			// 磊侥 滴疙 贸府
			if (target->_left != &_nil && target->_right != &_nil)
			{
				Node* changeNode = target->_left;
				while (changeNode->_right != &_nil)
					changeNode = changeNode->_right;

				target->_data = changeNode->_data;
				target = changeNode;
			}


			// 窜鉴 RED 贸府
			if (target->_color == RED)
			{
				if (target->_left != &_nil)
				{
					target->_parent->_right = target->_left;
					target->_left->_parent = target->_parent;
				}
				else if (target->_right != &_nil)
				{
					target->_parent->_left = target->_right;
					target->_right->_parent = target->_parent;
				}
				else
				{
					if (target->_parent->_left == target)
						target->_parent->_left = &_nil;
					else
						target->_parent->_right = &_nil;
				}

				delete target;
				return true;
			}

			// ROOT 贸府
			if (target == _root)
			{
				if (target->_left == &_nil)
				{
					target->_right->_color = BLACK;
					target->_right->_parent = target->_parent;

					_root = target->_right;
					delete target;
					return true;
				}
				else if (target->_right == &_nil)
				{
					target->_left->_color = BLACK;
					target->_left->_parent = target->_parent;

					_root = target->_left;
					delete target;
					return true;
				}
			}

			Node* delNode = target;
			Node* sibling;

			// CASE 1 target->black, child->red
			if (target->_left->_color == RED)
			{
				target->_left->_color = BLACK;
				target->_left->_parent = target->_parent;

				if (target->_parent->_left == target)
					target->_parent->_left = target->_left;
				else
					target->_parent->_right = target->_left;

				delete delNode;
				return true;
			}
			else if (target->_right->_color == RED)
			{

				target->_right->_color = BLACK;
				target->_right->_parent = target->_parent;

				if (target->_parent->_left == target)
					target->_parent->_left = target->_right;
				else
					target->_parent->_right = target->_right;

				delete delNode;
				return true;
			}

			while (1)
			{
				sibling = getSibling(target);
				if (sibling->_left->_color == BLACK &&
					sibling->_right->_color == BLACK)
				{
					// CASE 2
					if (sibling->_color == RED)
					{
						target->_parent->_color = RED;
						sibling->_color = BLACK;

						if (target->_parent->_left == sibling)
							RotateRight(target->_parent);
						else
							RotateLeft(target->_parent);

						sibling = getSibling(target);
					}
					// CASE 3
					else if (sibling->_parent->_color == BLACK)
					{
						sibling->_color = RED;
						target = target->_parent;

						if (target == _root)
						{
							connectNilNode(delNode);
							delete delNode;

							return true;
						}
						continue;
					}
				}

				//CASE 4
				if (sibling->_parent->_color == RED &&
					sibling->_left->_color == BLACK &&
					sibling->_right->_color == BLACK)
				{
					sibling->_parent->_color = BLACK;
					sibling->_color = RED;

					connectNilNode(delNode);
					delete delNode;
					return true;
				}

				if (target->_parent->_right == sibling)
				{
					//CASE 5
					if (sibling->_left->_color == RED &&
						sibling->_right->_color == BLACK)
					{
						sibling->_color = RED;
						sibling->_left->_color = BLACK;

						RotateRight(sibling);
						sibling = getSibling(target);
					}

					//CASE 6

					sibling->_color = target->_parent->_color;
					target->_parent->_color = BLACK;
					sibling->_right->_color = BLACK;
					RotateLeft(target->_parent);
				}
				else
				{
					//CASE 5
					if (sibling->_left->_color == BLACK &&
						sibling->_right->_color == RED)
					{
						sibling->_color = RED;
						sibling->_left->_color = BLACK;

						RotateLeft(sibling);
						sibling = getSibling(target);
					}

					//CASE 6
					sibling->_color = target->_parent->_color;
					target->_parent->_color = BLACK;
					sibling->_left->_color = BLACK;
					RotateRight(target->_parent);
				}

				connectNilNode(delNode);
				delete delNode;
				return true;
			}

		}
	}

	return false;
}
bool RedBlackTree::isExistData(int data)
{
	Node* node = isExistData(_root, data);

	if (node == &_nil)
		return false;

	return true;
}
RedBlackTree::Node* RedBlackTree::isExistData(RedBlackTree::Node* node, int data)
{
	if (node == &_nil)
		return node;

	if (node->_data > data)
		return isExistData(node->_left, data);
	else if (data > node->_data)
		return isExistData(node->_right, data);
	else
		return node;
}
int RedBlackTree::getHeight()
{
	return getHeight(_root, 0);
}
int RedBlackTree::getHeight(RedBlackTree::Node* node, int height)
{
	if (node == &_nil)
		return height - 1;

	int left = getHeight(node->_left, height + 1);
	int right = getHeight(node->_right, height + 1);

	if (left > right)
		return left;
	else
		return right;

}
void RedBlackTree::clear()
{
	if (_root == &_nil)
		return;

	_size = 0;
	postOrderForClear(_root);
	_root = &_nil;
}
void RedBlackTree::postOrderForClear(Node* node)
{
	if (node != &_nil)
		return;

	postOrderForClear(node->_left);
	postOrderForClear(node->_right);

	delete node;

}

