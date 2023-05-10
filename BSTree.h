#pragma once
namespace gsy_study_BSTree
{
	template<class T>
	struct BSTNode
	{
		BSTNode(const T& data = T())
			:_left(nullptr)
			,_right(nullptr)
			,_data(data)
		{}
		BSTNode<T>* _left;
		BSTNode<T>* _right;
		T _data;
	};
	template<class T>
	class BSTree
	{
		typedef BSTNode<T> Node;
	public:
		BSTree()
			:_node(nullptr)
		{}
		bool insert(const T& data)
		{
			if (empty())
			{
				_node = new Node(data);
				return true;
			}
			Node* Pparent = nullptr;
			Node* cur = _node;
			while (cur != nullptr)
			{
				//搜索二叉树,左边比根小,右边比根大
				if (cur->_data < data)
				{
					Pparent = cur;
					cur = cur->_right;
				}
				else if (cur->_data > data)
				{
					Pparent = cur; 
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			if (Pparent->_data > data)
			{
				Pparent->_left = new Node(data);
			}
			else if(Pparent->_data < data)
			{
				Pparent->_right = new Node(data);
			}
			return true;
		}

		bool erase(const T& data)
		{
			if (_node == nullptr)
				return false;
			Node* parent = nullptr;
			Node* cur = _node;
			while (cur)
			{
				//1.找到要删除的数据
				//2.1删除的节点为叶子节点
				//2.2删除的节点左边为空,右边不为空 -> parent指向cur->right
				//2.3删除的节点左边不为空,右边为空 -> parent指向cur->left
				//2.4删除的节点左右都不为空
				if (cur->_data < data)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_data > data)
				{
					parent = cur;
					cur = cur->_left;
				}
				//找到要删除的数据
				else if(cur->_data == data)
				{
					break;
				}
				else
				{
					return false;
				}
			}
			if (cur->_left == nullptr)
			{
				if (parent == nullptr)
				{
					_node = cur->_right;
					delete cur;
					cur = nullptr;
					return true;
				}
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
				delete cur;
				cur = nullptr;
				return true;
			}
			else if (cur->_right == nullptr)
			{
				if (parent == nullptr)
				{
					_node = cur->_left;
					delete cur;
					cur = nullptr;
					return true;
				}
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
				delete cur;
				cur = nullptr;
				return true;
			}
			else
			{
				Node* p = nullptr;
				parent = cur;
				cur = cur->_left;
				while (cur->_right)
				{
					p = cur;
					cur = cur->_right;
				}
				parent->_data = cur->_data;
				if (p->_right == cur)
				{
					p->_right = nullptr;
				}
				else
				{
					p->_left = nullptr;
				}
				delete cur;
				cur = nullptr;
				return true;
			}
			return false;
		}

		void _InOrder(Node* root)
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_data << ' ';
			_InOrder(root->_right);
		}

		void InOrder()
		{
			if (_node == nullptr)
			{
				cout << "nullptr" << endl;
				return;
			}
			_InOrder(_node);
			cout << endl;
		}

		bool empty()
		{
			return _node == nullptr;
		}
	private:
		Node* _node;
	};
	void test()
	{
		BSTree<int> tree;
		int arr[] = { 3,5,1,0,9,7,2,4,6,8,10 };
		for (const auto& e : arr)
		{
			tree.insert(e);
		}
		/*for (const auto& e : arr)
		{
			tree.erase(e);
		}*/
		//tree.erase(2);
		for (int i = 0; i <= 10; ++i)
		{
			tree.erase(i);
		}
		tree.InOrder();
	}
}