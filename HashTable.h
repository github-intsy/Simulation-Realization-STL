#include<vector>
#include<string>
using namespace std;
#ifdef __HASHVECTOR_H__
//闭散列哈希表
enum State
{
	EMPTY,	//空
	EXITS,	//存在
	DELETE	//删除
};

template<class K, class T, class KOfT>
class HashTable
{
	struct HashDate
	{
		HashDate()
			:_date(T())
			, _state(EMPTY)
		{}
		T _date;
		State _state;
	};
public:

	bool Insert(const T& date)
	{
		KOfT koft;
		if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7)
		{
			//开辟新空间,将原数组中的数据按照规则放入新数组
			int newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			vector<HashDate> newtables;
			newtables.resize(newsize);
			//遍历旧数组, 将数据放到新数组
			for (int i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._state == EXITS)
				{
					size_t index = koft(_tables[i]._date) % newsize;
					while (newtables[index]._state == EXITS)
					{
						++index;
						if (index == newsize)
						{
							index = 0;
						}
					}
					newtables[index] = _tables[i];
				}
			}
			_tables.swap(newtables);
		}
		int index = koft(date) % _tables.size();
		//遍历数组,将数据放到指定位置
		while (_tables[index]._state == EXITS)
		{
			if (koft(_tables[index]._date) == koft(date))
			{
				return false;
			}
			++index;
			if (index > _tables.size() - 1)
				index = 0;
		}
		_tables[index]._date = date;
		_tables[index]._state = EXITS;
		++_num;

		return true;
	}
private:
	vector<HashDate> _tables;
	int _num = 0;
};
#endif
//开散列哈希表



template<class K>
struct _Hash
{
	const K& operator()(const K& key)
	{
		return key;
	}
};

template<>
struct _Hash<string>
{
	size_t operator()(const string& key)
	{
		size_t sum = 0;
		for (auto& e : key)
		{
			sum *= 131;
			sum += e;
		}
		return sum;
	}
};

template<class K, class T>
struct _Node
{
	_Node(const T& t = T())
		:_next(nullptr)
		, _data(t)
	{}

	_Node* _next;
	T _data;
};
template<class K, class T, class KOfT, class Hash>
class HashTable;

template<class K, class T, class KOfT, class Hash = _Hash<K>>
struct HashTable_Iterator
{
	typedef _Node<K, T> Node;
	typedef HashTable_Iterator<K, T, KOfT, Hash> Self;
	typedef HashTable<K, T, KOfT, Hash> Table;
	Node* _node;
	Table* _t;
	HashTable_Iterator(Node* node, Table* t)
		:_node(node)
		,_t(t)
	{}

	T& operator*()
	{
		return _node->_data;
	}

	T* operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self& right)
	{
		return _node != right._node;
	}

	bool operator==(const Self& right)
	{
		return _node == right._node;
	}

	Self& operator++()
	{
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			Hash hash;
			KOfT koft;
			size_t index = hash(koft(_node->_data)) % _t->_table.capacity();
			++index;
			for (; index < _t->_table.capacity(); ++index)
			{
				if (_t->_table[index])
				{
					_node = _t->_table[index];
					return *this;
				}
			}
			_node = nullptr;
			return *this;
		}

	}
};

template<class K, class T, class KOfT, class Hash = _Hash<K>>
class HashTable
{
public:
	typedef _Node<K,T> Node;
	typedef HashTable_Iterator<K, T, KOfT> Iterator;	//在unordered_map封装时的Iterator
	friend struct HashTable_Iterator<K, T, KOfT>;
	KOfT koft;
	Hash hash;
	bool Insert(const T& data)
	{
		if (_table.capacity() == 0 ||  _size * 10 / _table.capacity()  >= 10)
		{
			//先开辟一个空间
			size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
			vector<Node*> newtable;
			newtable.resize(newsize, nullptr);
			for (size_t i = 0; i < _table.size(); ++i)
			{
				//将桶全部挂到新的表->头插
				while (_table[i])
				{
					if (hash(koft(_table[i]->_data)) == hash(koft(data)))
						return false;
					Node* next = _table[i]->_next;
					size_t new_index = hash(koft(_table[i]->_data)) % newsize;
					_table[i]->_next = newtable[new_index];
					newtable[new_index] = _table[i];
					_table[i] = next;
				}
			}
			_table.swap(newtable);
		}
		size_t index = hash(koft(data)) % _table.capacity();
		Node* cur = new Node(data);
		cur->_next = _table[index];
		_table[index] = cur;
		++_size;
		return true;
	}

	Iterator begin()
	{
		for (size_t i = 0; i < _table.capacity(); ++i)
		{
			if (_table[i])
			{
				return Iterator(_table[i], this);
			}
		}
		return end();
	}

	Iterator end()
	{
		return Iterator(nullptr, this);
	}

	void clear()
	{
		for (int i = 0; i < _table.capacity(); ++i)
		{
			Node* cur = _table[i];
			while (cur)
			{
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}
		}
	}

	

	~HashTable()
	{
		clear();
	}
private:
	vector<Node*> _table;
	size_t _size;
};