#pragma once
enum Color
{
	BLACK,
	RED
};

template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& t)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(t)
		, _col(RED)
	{}
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;
	Color _col;
	
};
/*map<int, int> m;
	m.insert(make_pair(1, 4));
	m.insert(make_pair(5, 4));
	m.insert(make_pair(19, 4));
	map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ' ' << it->second << endl;
		++it;
	}*/
template<class T, class Ref, class Ptr>
struct __iterator
{
	typedef RBTreeNode<T> Node;
	typedef __iterator<T, Ref, Ptr> self;
	Node* _node;
	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	__iterator(Node* node)
		:_node(node)
	{}

	self& operator++()
	{
		//1. 右节点不为空, 获得右节点最左边的那个节点
		//2. 右节点为空, 判断到它为父节点左子树的那个父节点,然后再迭代到最左边的那个节点
		if (_node->_right)
		{
			_node = _node->_right;
			while (_node && _node->_left)
			{
				_node = _node->_left;
			}
		}
		else
		{
			Node* parent = _node->_parent;
			Node* cur = _node;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	bool operator!=(const self& node)
	{
		return _node != node._node;
	}

	bool operator==(const self& node)
	{
		return _node == node._node;
	}
};

template<class K, class T, class KofT>
class RBTree
{
	typedef RBTreeNode<T> Node;
	
public:

	typedef __iterator<T, T&, T*> Iterator;
	typedef __iterator<T, const T&, const T*> const_Iterator;

	RBTree(Node* n = nullptr)
		:_root(n)
	{}

	Iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return Iterator(cur);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	pair<Iterator,bool> insert(const T& t)
	{
		if (_root == nullptr)
		{
			_root = new Node(t);
			_root->_col = BLACK;
			return make_pair(Iterator(_root), true);
		}

		Node* cur = _root;
		Node* parent = nullptr;
		KofT koft;
		//查找合适的位置
		while (cur)
		{
			if (koft(cur->_data) > koft(t))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (koft(cur->_data) < koft(t))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(Iterator(cur), false);
			}
		}
		//将新节点连接起来,默认是红色
		cur = new Node(t);
		Node* newNode = cur;
		if (koft(parent->_data) < koft(t))
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
			
			Node* grandfather = parent->_parent;
			if (!grandfather)
			{
				return make_pair(Iterator(cur), true);
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
					//情况3: 双旋 -> 变为单旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}

					//情况2: 有可能是情况3转变过来的
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					
					break;
				}
			}
			else if(parent == grandfather->_right)
			{
				Node* uncle = grandfather->_left;
				//情况1: uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					
					cur = grandfather;
					parent = cur->_parent;
				}
				//2. uncle不存在,或者为黑
				//情况2和情况3
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}

					RotateL(grandfather);
					if (uncle)
					{
						uncle->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return make_pair(Iterator(newNode), true);
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
	Node* _root;
	
};