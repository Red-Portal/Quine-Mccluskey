#include "Term.hpp"

QM::Term::Term(size_t size, unsigned int term)
	:_size(size),
	 _bitArray(static_cast<BitArray>(term)),
	 _numberOfOne(0)
{
	BitArray head = 1;

	for(auto i = 0; i < _size; head = head << 1, ++i)
	{
		if(_bitArray & head)
			++_numberOfOne;
	}
}
