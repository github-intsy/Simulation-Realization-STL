#pragma once
enum Color
{
	BLACK,
	RED
};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Color _col;
	
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		//将新节点连接起来,默认是红色
		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		
		//判断parent是grandfather的左节点还是右节点
		while (parent->_col == RED)
		{
			//未解决->如果树的深度为2->如何解决
			Node* grandfather = parent->_parent;
			if (!grandfather)
			{
				return true;
			}
			//如果是左节点
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;

				//三种情况
				//1. u存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//uncle不存在 or uncle存在且为黑
				else
				{
					//情况3: 双旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}

					//情况2: 有可能是情况3转变过来的
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* prev = parent->_parent;

		parent->_right = subRL;
		subRL = parent;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			subR->_parent = nullptr;
			_root = subR;
		}
		else
		{
			if (prev->_left == parent)
			{
				prev->_left = subR;
			}
			else
			{
				prev->_right = subR;
			}
			subR->_parent = prev;
		}
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		//两种情况需要单独处理
		//1.旋转节点为空
		//2.旋转后的subL有可能为根,有可能不为根
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* prev = parent->_parent;
		parent->_parent = subL;
		if (parent == _root)
		{
			subL->_parent = prev;
			_root = subL;
		}
		else
		{
			if (prev->_left == parent)
			{
				prev->_left = subL;
			}
			else
			{
				prev->_right = subL;
			}
			subL->_parent = prev;
		}
	}
private:
	Node _root;
};