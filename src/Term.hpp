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
		bool _checked;
		size_t const _size;
		BitArray _bitArray;
		BitArray _xMask;

	public:
		Term() = default;
		Term(size_t size, unsigned long term);
		Term(size_t size, unsigned long term, BitArray mask);
		~Term() = default;

		std::pair<Term, bool> compareIfImplicant(Term& other);

		inline void operator=(Term const& other)
		{
		    _numberOfOne = other._numberOfOne;
			_checked = other._checked;
			_bitArray = other._bitArray;
			_xMask = other._xMask;
		}

		inline void operator=(Term&& other)
		{
		    _numberOfOne = other._numberOfOne;
			_checked = other._checked;
			_bitArray = other._bitArray;
			_xMask = other._xMask;
		}

		inline int getNumberOfOnes() const
		{
			return _numberOfOne;
		}

		inline bool isChecked() const
		{
			return _checked;
		}
	};
}
#endif
