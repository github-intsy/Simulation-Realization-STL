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

template<class K, class T, class KofT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	RBTree(Node* n = nullptr)
		:_root(n)
	{}

	bool insert(const T& t)
	{
		if (_root == nullptr)
		{
			_root = new Node(t);
			_root->_col = BLACK;
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		KofT koft;
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
				return false;
			}
		}
		//将新节点连接起来,默认是红色
		cur = new Node(t);
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
	
	void _show(Node* root)
	{
		if (root == nullptr)
			return;
		static KofT koft;
		_show(root->_left);
		cout << koft(root->_data) << ' ';
		_show(root->_right);
	}

	void show()
	{
		_show(_root);
	}


private:
	Node* _root;
	
};