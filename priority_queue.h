#pragma once
namespace gsy_study_priority_queue
{
	template<class T>
	struct less
	{
		bool operator()(const T& left, const T& right)
		{
			return left < right;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& left, const T& right)
		{
			return left > right;
		}
	};

	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		
		priority_queue()
			:_con()
		{}

		void push(const T& val)
		{
			_con.push_back(val);
			_AdjustUp(_con.size() - 1);
		}

		void pop()
		{
			if (empty())
				return;
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			_AdjustDown(0);
		}

		const T& top() const
		{
			// 堆顶元素不允许修改，因为：堆顶元素修改可以会破坏堆的特性
			return _con.front();
		}

		bool empty()
		{
			return _con.empty();
		}

		void size()
		{
			return _con.size();
		}
	private:

		void _AdjustUp(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				if (com(_con[parent] , _con[child]))
				{
					swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void _AdjustDown(int parent)
		{
			Compare com;
			int child = parent * 2 + 1;

			while (child < _con.size())
			{
				if (com(child + 1 , _con.size()) && com(_con[child] , _con[child + 1]))
					++child;
				if (com(_con[parent] , _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		Container _con;
	};

	void test()
	{
		priority_queue<int,vector<int>, greater<int>> p;
		p.push(1);
		p.push(2);
		p.push(3);
		p.push(4);
		p.push(5);
		p.push(6);
		while (!p.empty())
		{
			cout << p.top() << ' ';
			p.pop();
		}
		cout << endl;
	}
}