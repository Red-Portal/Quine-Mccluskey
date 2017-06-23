/*
   Copyright 2017 Red-Portal

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef TERM_HPP
#define TERM_HPP

#include <vector>

#include "boost/dynamic_bitset.hpp"

namespace QM
{
    using bit_array = boost::dynamic_bitset<>;

    class Term
    {
        // this class is an abstraction over computations directly
        // involving 'terms'
        //
        // isGrayAdjacent and getGroupedTerm are methods computing
        // whether compared terms are gray adjacent, and if they are,
        // generate a new term that groups the two terms.
    private:
        // number of set bits.
        // this dominates which group this term will be in
        int _number_of_setbit;
        bool _checked;
        size_t _size;
        
        // the bit array containing the boolean representation of this term
	bit_array _bitArray;
        // X bits, or don't care bits' bit Array representation
        bit_array _xMask;

        // temporary variable.
        bit_array _result;

        // the terms this bit covers.
        // initially zero, and if this term is a grouped term,
        // all the terms this term covers should be in this container.
        std::vector<bit_array> _minTerm;

    public:
        inline Term(size_t size, bit_array term);

        // constructor for grouped term
        inline Term(Term const& first,
                    Term const& second,
                    bit_array mask);
        inline Term(Term const&) = default;
        inline Term(Term&&) noexcept = default;
        inline Term& operator=(Term const& other) = default;
        ~Term() = default;

        // returns true if this term and the other term are gray adjacent.
        // this method has side effect on _result.
        inline bool isGrayAdjacent(Term& other);

        // get the newly grouped term.
        // this has a side effect dependency on _result
        inline Term getGroupedTerm(Term& other);
        inline bool operator==(Term const& other) const;
        inline bool operator!=(Term const& other) const;
        inline bool operator<(Term const& oter) const;

        inline int getSetBitNum() const;
        inline bool isChecked() const;
        inline std::vector<bit_array> const& getMinterms() const;

        // get Boolean Equation representation
        inline std::vector<int> getEquation() const;
    };



    Term::
    Term(size_t size, bit_array term)
        :_number_of_setbit(0),
         _checked(true),
         _size(size),
         _bitArray(term),
         _xMask(0),
         _result(0)
    {
        bit_array end = 1 << size;
        for(bit_array it = 1; it != end; it <<= 1)
        {
            if(_bitArray & it)
                ++_number_of_setbit;
        }
        _minTerm.push_back(term);
    }


    Term::
    Term(Term const& first,  Term const& second,
	 bit_array mask)
	:_number_of_setbit(first._number_of_setbit),
	 _checked(true),
	 _size(first._size),
	 _bitArray(first._bitArray),
	 _xMask(mask),
	 _result(0)
    {
	_minTerm.insert(_minTerm.end(),
			first._minTerm.begin(),
			first._minTerm.end());
        _minTerm.insert(_minTerm.end(),
                        second._minTerm.begin(),
                        second._minTerm.end());
    }

    bool
    Term::
    isGrayAdjacent(Term &other)
    {
        // X, don't care bits must be equal in order to be gray adjacent
        // comparing them first is a short-circuit optimization
        if(_xMask != other._xMask)
            return false;

        // compute different bits
        _result = (_bitArray ^ other._bitArray) & ~_xMask; //XOR operation

        // if only one bit is different, it is gray adjacent 
        return _result && !(_result & (_result - 1));
    }

    Term
    Term::
    getGroupedTerm(Term &other) 
    {
        this->_checked = false;
        other._checked = false;

        auto newMask = _result | _xMask;

        return Term(*this, other, newMask);
    }

    int
    Term::
    getSetBitNum() const
    {
        return _number_of_setbit;
    }

    bool
    Term::
    isChecked() const
    {
        return _checked;
    }

    bool
    Term::
    operator==(Term const& other) const
    {
        return _bitArray == other._bitArray
            && _xMask == other._xMask
            && _checked == other._checked;
    }

    bool
    Term::
    operator!=(Term const& other) const
    {
        return _bitArray != other._bitArray
            || _xMask != other._xMask
            || _checked != other._checked;
    }

    bool
    Term::
    operator<(Term const& other) const
    {
        if(_bitArray == other._bitArray)
            return _xMask < other._xMask;
        return _bitArray < other._bitArray;
    }

    std::vector<bit_array> const&
    Term::
    getMinterms() const
    {
        return _minTerm;
    }

    std::vector<int>
    Term::
    getEquation() const
    {
        std::vector<int> equation;

        // x, don't care bits are ommited in the boolean equation representation
        // set bits correspond to a boolen term,
        // unset bits correspond to a negative boolean term
        for(auto i = 1; i < static_cast<int>(_size + 1); ++i)
        {
            bit_array mask = 1 << (_size - 1);
            mask = mask >> (i - 1);

            // x, don't care bit
            if((_xMask & mask) != 0)
                continue;

            // set bit
            if((_bitArray & mask) != 0)
                equation.push_back(i);
            else
            {
                // unset bit. negative term
                equation.push_back(-i);
            }
        }
        return equation;
    }
}
#endif
