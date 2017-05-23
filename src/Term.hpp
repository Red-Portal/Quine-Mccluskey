#ifndef TERM_HPP
#define TERM_HPP

#include <vector>
#include <memory>
#include <cstdlib>

#include <iostream>

namespace QM
{
	template<typename BitArray>
	class Term
	{
	private:
		int _numberOfOne;
		bool _checked;
		size_t _size;
		BitArray _bitArray;
		BitArray _xMask;

	public:
		inline Term(size_t size, BitArray term);
		inline Term(Term<BitArray> const& other, BitArray mask);
		~Term() = default;

		std::unique_ptr<Term<BitArray>> compareIfImplicant(Term& other);
		inline int getSetBitNum() const;
		inline bool isChecked() const;
	};



	template<typename BitArray>
	inline Term<BitArray>::Term(size_t size, BitArray term)
		:_numberOfOne(0),
		 _checked(true),
		 _size(size),
		 _bitArray(term),
		 _xMask(0)
	{
		BitArray end = 1 << size;
		for(BitArray it = 1; it != end; it <<= 1)
		{
			if(_bitArray & it)
				++_numberOfOne;
		}
	}


	template<typename BitArray>
	inline Term<BitArray>::Term(Term<BitArray> const& other,
								BitArray mask)
		:_numberOfOne(other._numberOfOne),
		 _checked(true),
		 _size(other._size),
		 _bitArray(other._bitArray),
		 _xMask(mask)
	{}

	template<typename BitArray>
	std::unique_ptr<Term<BitArray>> Term<BitArray>::compareIfImplicant(Term<BitArray> &other)
	{
		if(_xMask != other._xMask)
			return nullptr;

		auto preMasked = _bitArray ^ other._bitArray; //XOR operation
		auto result = preMasked & ~_xMask;

		// if the result has only one '1' then it's an implicant

		//std::cout << "preMasked: " << preMasked  << std::endl;
		//std::cout << "result: " << result << std::endl;

		if(result != 0U && result && !(result & (result - 1)))
		{
			this->_checked = false;
			other._checked = false;

			auto newMask = result | _xMask;

			return std::make_unique<Term<BitArray>>(Term(*this, newMask));
		}	
		else
			return nullptr;
	}

	template<typename BitArray>
	inline int Term<BitArray>::getSetBitNum() const
	{
		return _numberOfOne;
	}


	template<typename BitArray>
	inline bool Term<BitArray>::isChecked() const
	{
		return _checked;
	}
}
#endif
