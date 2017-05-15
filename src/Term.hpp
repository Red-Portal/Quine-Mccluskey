#ifndef TERM_HPP
#define TERM_HPP

#include <vector>
#include <cstdlib>

namespace QM
{
	class Term
	{
		using BitArray = unsigned long;

	private:
		int _numberOfOne;
		size_t const _size;
		BitArray _bitArray;
		BitArray _xMask;

	public:
		Term(size_t size, unsigned int term);
		~Term() = default;

		inline int getNumberOfOnes() const
		{
			return _numberOfOne;
		}
	};
}
#endif
