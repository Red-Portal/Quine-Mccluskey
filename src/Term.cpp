#include "Term.hpp"

QM::Term::Term(size_t size, unsigned long term)
	:_size(size),
	 _bitArray(static_cast<BitArray>(term)),
	 _numberOfOne(0),
	 _checked(false),
	 _xMask(0)
{
	BitArray head = 1;

	for(auto i = 0; i < _size; head <<= 1, ++i)
	{
		if(_bitArray & head)
			++_numberOfOne;
	}

	_xMask = ~_xMask; // flipping the bits in order to form a mask
}

QM::Term::Term(size_t size, unsigned long term, BitArray mask)
	:_size(size),
	 _bitArray(static_cast<BitArray>(term)),
	 _numberOfOne(0),
	 _checked(false),
	 _xMask(mask)
{
	BitArray head = 1;

	for(auto i = 0; i < _size; head <<= 1, ++i)
	{
		if(_bitArray & head)
			++_numberOfOne;
	}

	_xMask = ~_xMask; // flipping the bits in order to form a mask
}

std::pair<QM::Term, bool> QM::Term::compareIfImplicant(Term &other)
{
	auto result = _bitArray ^ other._bitArray; //XOR operation
	// if the result has only one '1' then it's an implicant

	if(result > 0 && result % 2 == 0)
	{
		
 	}
}
