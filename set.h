#pragma once
namespace gsy_study_set
{
	template<class K>
	class set
	{
		struct SetkOfT
		{
			const K& operator()(const K& k)
			{
				return k;
			}
		};

	public:
		typedef typename RBTree<K, K, SetkOfT>::Iterator iterator;

		pair<iterator,bool> Insert(const K& k)
		{
			return _rb.insert(k);
		}

	private:
		RBTree<K, K, SetkOfT> _rb;
	};

	void test_set()
	{
		set<int> s;
		s.Insert(1);
		s.Insert(5);
		s.Insert(3);
		s.Insert(29);
		s.Insert(23);
		s.Insert(43);
	}
}