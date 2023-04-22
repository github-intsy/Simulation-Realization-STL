#pragma once
namespace gsy_study_vector
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}

		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}

		vector(int n, const T& val = T())
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{
			reserve(n);
			while (n--)
			{
				push_back(val);
			}
		}
		//v2(v1)
		vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{
			reserve(v.capacity());
			iterator i = begin();
			const_iterator vi = v.cbegin();
			while (vi != v.cend())
			{
				*i = *vi;
				++i;
				++vi;
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		
		T& operator[](const size_t& i)
		{
			return _start[i];
		}
		
		const T& operator[](const size_t& pos) const
		{
			return _start[pos];
		}

		void reserve(const size_t& n)
		{
			if (n > capacity())
			{
				size_t OldSize = size();
				T* tmp = new T[n];
				if (_start)
				{
					for (size_t i = 0; i < OldSize; ++i)	
						tmp[i] = _start[i];
					delete[] _start;
				}
				_start = tmp;
				_finish = tmp + OldSize;
				_end_of_storage = _start + n;
			}
		}

		iterator erase(iterator pos)
		{
			iterator i = pos;
			while (i != end())
			{
				*i = *(i + 1);
				++i;
			}
			--_finish;
			return pos;
		}

		iterator insert(iterator pos, const T& x)
		{
			//指定位置插入一个数据
			if (size() == capacity())
			{
				size_t OldSize = size();
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
				_finish = _start + OldSize;
				_end_of_storage = _start + newcapacity;
			}
			iterator i = end();
			while (i != pos)
			{
				*i = *(i - 1);
				--i;
			}
			*i = x;
			++_finish;
			return i;
		}

		vector<T>& operator=(vector<T> v)
		{
			::swap(_start, v._start);
			::swap(_finish, v._finish);
			::swap(_end_of_storage, v._end_of_storage);
			return *this;
		}

		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish = x;
			++_finish;

		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		bool empty() const
		{
			return _start == _finish;
		}

	private:
		iterator _start;			//有效数据的第一位
		iterator _finish;			//有效数据的最后一位
		iterator _end_of_storage;	//最大内存
	};

	void test02()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		vector<int>::iterator i = v.begin();
		while (i != v.end())
		{
			if ((*i & 1) != 0)
				i = v.erase(i);
			else
				++i;
		}
		for (auto e : v)
		{
			cout << e << ' ';
		}

	}
}