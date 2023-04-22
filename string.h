#pragma once
namespace gsy
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		string(const char* str = "")
			:_str(new char[strlen(str) + 1])
		{
			strcpy(_str, str);
			_capacity = _size = strlen(str);
		}
		/*
		string(const string& s)
			:_str(new char[strlen(s._str) + 1])
		{
			strcpy(_str, s._str);
		}
		*/
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str);
			swap(tmp);
		}

		void swap(string& tmp)
		{
			::swap(_str, tmp._str);
			::swap(_capacity, tmp._capacity);
			::swap(_size, tmp._size);
		}

		void push_back(const char& c)
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size++] = c;
			_str[_size] = '\0';
		}

		void reserve(size_t n)
		{//开辟指定大小的空间
			if (n > _capacity)
			{
				char* newstr = new char[n + 1];
				for (int i = 0; i <= _size; ++i)
				{
					newstr[i] = _str[i];
				}
				delete[] _str;
				_str = newstr;
				_capacity = n;
			}
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			strcpy(_str + _size, str);
			_size += len;
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_capacity = _size = 0;
		}

		char& operator[](size_t i)
		{
			return _str[i];
		}

		const char* c_str() const
		{
			return _str;
		}

		void insert(size_t pos, const char& ch)
		{
			assert(pos <= _size);
			if (_capacity == _size)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			//end如果等于pos,并且把前一个元素给了_str[end] ,也会在后面被覆盖掉
			_str[pos] = ch;
			++_size;
		}

		void erase(size_t pos, size_t len)//删除指定位置的元素
		{
			assert(_size);
			//在pos位置删除长度为len的字符串
			//从前往后,依次向前挪动len个字符
			// pos    pos+len
			size_t end = pos + len;
			size_t begin = pos;
			while (end < _size)
			{
				_str[begin++] = _str[end++];
			}
			_size -= len;
		}

		void insert(size_t pos, const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(len + _size);
			}
			size_t end = _size + len;
			while (end >= len + pos)
			{
				_str[end] = _str[end - len];
				--end;
			}
			size_t i = pos;
			size_t j = 0;
			while (j < len)
			{
				_str[i++] = str[j++];
			}
			_size += len;
		}

		size_t size()
		{
			return _size;
		}

		bool operator<(const string& s)
		{
			if (strcmp(_str, s._str) < 0)
				return true;
			else
				return false;
		}

		bool operator==(const string& s)
		{
			if (strcmp(_str, s._str) == 0)
				return true;
			else
				return false;
		}

		bool operator<=(const string& s)
		{
			return operator<(s) || operator==(s);
		}

		bool operator>(const string& s)
		{
			return !operator<=(s);
		}

		bool operator>=(const string& s)
		{
			return !operator<(s);
		}

		bool operator!=(const string& s)
		{
			return !operator==(s);
		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};

	void Test02()
	{
		string s1("hello");
		string s2(s1);
		string::iterator i = s2.begin();
		while (i != s2.end())
		{
			cout << *i << ' ';
			++i;
		}
		cout << endl;
		cout << "hello world" << endl;
		//operator[]是可以访问到字符串的'\0'的
	}
}