#pragma once
namespace gsy_study_stack
{
	template<class T, class Container = list<T>>
	class stack
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_back();
		}
		T& top()
		{
			return _con.back();
		}
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
	void test_stack()
	{
		stack<int> st;
		st.push(1);
		st.push(2);
		st.push(3);
		st.push(4);
		while (!st.empty())
		{
			cout << st.top() << ' ';
			st.pop();
		}
		cout << endl;

	}
}