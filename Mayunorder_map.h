#include"HashTable.h"
#include<map>

template<class K, class V>
class Mayunorder_map
{
	struct KOfV
	{
		const K& operator()(const pair<K, V>& p)
		{
			return p.first;
		}
	};
public:
	bool insert(const pair<K, V>& t)
	{
		return _ta.Insert(t);
	}

	typedef typename HashTable<K, pair<K, V>, KOfV>::Iterator iterator;

	iterator begin()
	{
		return _ta.begin();
	}

	iterator end()
	{
		return _ta.end();
	}
private:
	HashTable<K, pair<K, V>, KOfV> _ta;
};