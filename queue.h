#pragma once
namespace gsy_study_queue
{
	template<class T, class Container = list<int>>
	class queue
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_front();
		}
		bool empty()
		{
			return _con.empty();
		}
		T& back()
		{
			return _con.back();
		}
		T& front()
		{
			return _con.front();
		}
		const T& back()	const
		{
			return _con.back();
		}
		const T& front()	const
		{
			return _con.front();
		}
	private:
		Container _con;
	};
	void test_queue()
	{
		queue<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		q.push(4);
		q.push(5);
		while (!q.empty())
		{
			cout << q.front() << ' ';
			q.pop();
		}
		cout << endl;
	}
}