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

		bool Insert(const pair<K,V>& t)
		{
			return _rb.insert(t);
		}
		
		void show()
		{
			_rb.show();
		}

	private:
		RBTree<K, pair<K, V>, MapKOfV> _rb;
	};

	void test_map()
	{
		map<int, int> m;
		m.Insert(make_pair(1, 2));
		m.Insert(make_pair(4, 4));
		m.Insert(make_pair(56, 34));
		m.Insert(make_pair(3, 54));
		m.Insert(make_pair(65, 64));
		m.Insert(make_pair(86, 344));
		m.Insert(make_pair(23, 34));
		m.show();
	}
}