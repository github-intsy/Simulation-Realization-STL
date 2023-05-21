#pragma once

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;		//balance factor平衡因子
	AVLTreeNode(const pair<K, V>& p)
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
		else if(parent->_kv.first < pa.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			return false;
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
				//parent所在的子树出现不平衡了,需要旋转处理
				//1. 旋转前提是保持它依旧是搜索二叉树
				//2. 旋转成平衡数
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (cur->_bf == -1)
					{
						//1. parent为右,cur为左,则旋转为右左旋转
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (cur->_bf == 1)
					{
						//2. parent为左,cur为右,则旋转为左右双旋
						RotateLR(parent);
					}
				}
				break;
			}
		}
		return true;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//方便后续判断subR左节点是否为空
		/*
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		//subR左边给parent的右边
		//parent变成subR的左边
		//1.parent为根, 2.parent不为根
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
		subR->_bf = parent->_bf = 0;
		*/
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
	/*
	* 1. 双旋转LR按顺序调用左旋和右旋
	* 2. 直接旋转,根据图像分析旋转后的平衡因子
	*/
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(subL);
		RotateR(parent);
		if (bf == 1)
		{
			subLR->_bf = 0;
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			subLR->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 0)
		{
			subL->_bf = 0;
			subLR->_bf = 0;
			parent->_bf = 0;
		}
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(subR);
		RotateL(parent);
		if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 0)
		{
			subR->_bf = 0;
			subRL->_bf = 0;
			parent->_bf = 0;
		}
	}
	
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ' ' << root->_kv.second << endl;
		_InOrder(root->_right);
	}

	void InOrder()
	{
		if (_root == nullptr)
		{
			cout << "nullptr" << endl;
			return;
		}
		_InOrder(_root);
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int left = Height(root->_left);
		int right = Height(root->_right);
		return left > right ? left + 1 : right + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;
		int left = Height(root->_left);
		int right = Height(root->_right);
		return abs(left - right) < 2 &&
			_IsBalance(root->_left) &&
			_IsBalance(root->_right);
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}

private:
	Node* _root;
};

void test()
{
	AVLTree<int, int> t;
	/*t.insert(make_pair(1, 1));
	t.insert(make_pair(2, 1));
	t.insert(make_pair(3, 1));
	t.insert(make_pair(4, 1));
	t.insert(make_pair(5, 1));*/
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		t.insert(make_pair(e, e));
	}
	t.InOrder();
	cout << t.IsBalance();
}