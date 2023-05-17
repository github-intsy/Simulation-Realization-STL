#pragma once

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;		//balance factor平衡因子
	AVLTreeNode(const pair<K, V>& p(K(),V()))
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
		,_kv(p)
	{}
	pair<K, V> _kv;
};

template<class K, class V>
class AVLTree
{
public:
	typedef AVLTreeNode<K, V> Node;
	AVLTree(Node* root = nullptr)
		:_root(root)
	{}

	bool insert(const pair<K, V>& pa)
	{
		if (_root == nullptr)
		{
			_root = new Node(pa);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first > pa.first)
			{
				parent = cur;
				cur = cur->_left;

			}
			else if (cur->_kv.first < pa.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(pa);
		if (parent->_kv.first > pa.first)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			//1.parent为0, 跳出
			//2.parent-1 or 1, 迭代
			//3.parent-2 or 2, 处理
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//处理
				RotateL(parent);
			}
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* prev = parent->_parent;
		//方便后续判断subR左节点是否为空
		parent->_right = subRL;
		subRL = parent;
		if (subRL)
			subRL->_parent = parent;
		parent->_parent = subR;
		//subR左边给parent的右边
		//parent变成subR的左边
		//1.parent为根, 2.parent不为根
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
		subR->_bf = parent->_bf = 0;
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		//两种情况需要单独处理
		//1.旋转节点为空
		//2.旋转后的subL有可能为根,有可能不为根
		if(subLR)
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
		subL->_bf = parent->_bf = 0;
	}
private:
	Node* _root;
};

void test()
{
	AVLTree<string, int> a;
}