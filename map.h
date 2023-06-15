#pragma once
namespace gsy_study_map
{
	template<class K, class V>
	class map
	{
		struct MapKOfV
		{
			const K& operator()(const pair<K,V>& p)
			{
				return p.first;
			}
		};
	public:

		typedef typename RBTree<K,pair<K,V>,MapKOfV>::Iterator iterator;

		iterator begin()
		{
			return _rb.begin();
		}

		iterator end()
		{
			return _rb.end();
		}

		pair<iterator,bool> Insert(const pair<K,V>& t)
		{
			return _rb.insert(t);
		}
		
		V& operator[](const K& k)
		{
			pair<iterator,bool> it = _rb.insert(make_pair(k,V()));
			return it.first->second;
		}

	private:
		RBTree<K, pair<K, V>, MapKOfV> _rb;
	};

	void test_map()
	{
		/*map<int, int> m;
		m.Insert(make_pair(1, 2));
		m.Insert(make_pair(4, 4));
		m.Insert(make_pair(56, 34));
		m.Insert(make_pair(3, 54));
		m.Insert(make_pair(65, 64));
		m.Insert(make_pair(86, 344));
		m.Insert(make_pair(23, 34));
		map<int, int>::iterator it = m.begin();
		while (it != m.end())
		{
			cout << it->first << ':' << it->second << endl;
			++it;
		}*/
		string strs[] = { "西瓜","樱桃","西瓜","苹果","西瓜","西瓜","西瓜","苹果" };
		map<string, int> countMap;
		for (auto& str : strs)   //使用pair对象
		{
			pair<map<string, int>::iterator, bool> ret = countMap.Insert(make_pair(str, 1));
			if (ret.second == false)
			{
				ret.first->second++;
			}
		}
		for (auto& map : countMap)
		{
			cout << map.first << ':' << map.second << endl;
		}
	}
}