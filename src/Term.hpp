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
		inline Term() = default;
		inline Term(Term<BitArray>&& other) = default;
		inline Term(Term<BitArray> const& other) = default;
		inline Term(size_t size, BitArray term);
		inline Term(Term<BitArray> const& other, BitArray mask);
		inline Term<BitArray>& operator=(Term const& other) = default;
		inline Term<BitArray>& operator=(Term&& other) = default;
		~Term() = default;

		std::unique_ptr<Term<BitArray>> compareIfImplicant(Term& other);
		inline int getNumberOfOnes() const;
		inline bool isChecked() const;
	};



	template<typename BitArray>
	inline Term<BitArray>::Term(size_t size, BitArray term)
		:_size(size),
		 _bitArray(term),
		 _numberOfOne(0),
		 _checked(true),
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
		:_size(other._size),
		 _bitArray(other._size),
		 _numberOfOne(other._numberOfOne),
		 _checked(true),
		 _xMask(mask)
	{}

	template<typename BitArray>
	std::unique_ptr<Term<BitArray>> Term<BitArray>::compareIfImplicant(Term &other)
	{
		auto result = _bitArray ^ other._bitArray; //XOR operation
		// if the result has only one '1' then it's an implicant

		if(result > 0 && result % 2 == 0)
		{
			auto masked = ~(result & _xMask);
			if(masked > 0)
			{
				_checked = false;
				other._checked = false;

				return std::make_unique(Term(*this, _xMask | result));
			}
			else
				return nullptr;
		}	
		else
			return nullptr;
	}

	template<typename BitArray>
	inline int Term<BitArray>::getNumberOfOnes() const
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
