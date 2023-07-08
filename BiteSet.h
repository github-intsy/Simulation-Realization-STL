#pragma once
#include <vector>
namespace gsy_study_biteset
{
	
	class bit_set
	{
	public:
		bit_set(size_t N)
		{
			_table.resize(N / 32 + 1, 0);
			_size = 0;
		}

		void set(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;

			_table[index] |= (1 << pos);
			++_size;
		}

		void reset(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;

			_table[index] &= ~(1 << pos);
			--_size;
		}
	private:
		std::vector<int> _table;
		size_t _size;
	};
}