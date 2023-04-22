#pragma once
namespace gsy_study_list
{
	template<class T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;

		__list_node(const T& x = T())
			:_data(x)
			, _prev(nullptr)
			, _next(nullptr)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;
		
		Node* _node;
		__list_iterator(Node* node = nullptr)
			:_node(node)
		{}
		
		Ref operator*()
		{
			return _node->_data;
		}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		self operator--(int)
		{
			self tmp = *this;
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const self& it)
		{
			return _node != it._node;
		}
		//i->_year
		Ptr operator->()
		{
			return &_node->_data;
		}

	};

	template<class T>
	class list
	{
	public:
		typedef __list_node<T> Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		list()
		{
			_head = new Node;
			_head->_prev = _head;
			_head->_next = _head;
		}

		void push_back(const T& x)
		{
			Node* tail = _head->_prev;
			Node* newnode = new Node;
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
			newnode->_data = x;
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		iterator erase(iterator& it)
		{
			Node* pos = it._node;
			Node* prev = pos->_prev;
			Node* next = pos->_next;
			delete pos;
			//	pre nex
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}

		const_iterator cbegin()
		{
			return const_iterator(_head->_next);
		}

		const_iterator cend()
		{
			return const_iterator(_head);
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
	private:
		Node* _head;
	};
	
	struct Date
	{
		size_t _year = 1;
		size_t _month = 1;
		size_t _day = 1;
	};

	void Test()
	{
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		list<int>::const_iterator i = l.cbegin();
		while (i != l.cend())
		{
			cout << *i << endl;
			++i;
		}

	}
}


