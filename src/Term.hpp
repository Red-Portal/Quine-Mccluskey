#ifndef TERM_HPP
#define TERM_HPP

#include <vector>
#include <memory>
#include <cstdlib>

namespace QM
{
    template<typename BitArray>
    class Term
    {
        // this class is an abstraction over computations directly
        // involving 'terms'
        //
        // isGrayAdjacent and getGroupedTerm are methods computing
        // whether compared terms are gray adjacent, and if they are,
        // generate a new term that groups the two terms.
        //


    private:
        // number of set bits.
        // this dominates which group this term will be in
        int _numberOfOne;
        bool _checked;
        size_t _size;
        
        // the bit array containing the boolean representation of this term
        BitArray _bitArray;
        // X bits, or don't care bits' bit Array representation
        BitArray _xMask;

        // temporary variable.
        BitArray _result;

        // the terms this bit covers.
        // initially zero, and if this term is a grouped term,
        // all the terms this term covers should be in this container.
        std::vector<BitArray> _minTerm;

    public:
        inline Term(size_t size, BitArray term);

        // constructor for grouped term
        inline Term(Term<BitArray> const& first,
                    Term<BitArray> const& second,
                    BitArray mask);
        inline Term(Term const&) = default;
        inline Term(Term&&) noexcept = default;
        inline Term& operator=(Term const& other) = default;
        ~Term() = default;

        // returns true if this term and the other term are gray adjacent.
        // this method has side effect on _result.
        inline bool isGrayAdjacent(Term& other);

        // get the newly grouped term.
        // this has a side effect dependency on _result
        inline Term<BitArray> getGroupedTerm(Term& other);
        inline bool operator==(Term const& other) const;
        inline bool operator!=(Term const& other) const;
        inline bool operator<(Term const& oter) const;

        inline int getSetBitNum() const;
        inline bool isChecked() const;
        inline auto const& getMinterms() const;

        // get Boolean Equation representation
        inline auto getEquation() const;
    };



    template<typename BitArray>
    inline Term<BitArray>::Term(size_t size, BitArray term)
        :_numberOfOne(0),
         _checked(true),
         _size(size),
         _bitArray(term),
         _xMask(0),
         _result(0)
    {
        BitArray end = 1 << size;
        for(BitArray it = 1; it != end; it <<= 1)
        {
            if(_bitArray & it)
                ++_numberOfOne;
        }
        _minTerm.push_back(term);
    }


    template<typename BitArray>
    inline Term<BitArray>::Term(Term<BitArray> const& first,
                                Term<BitArray> const& second,
                                BitArray mask)
        :_numberOfOne(first._numberOfOne),
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

    template<typename BitArray>
    bool Term<BitArray>::isGrayAdjacent(Term<BitArray> &other)
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

    template<typename BitArray>
    Term<BitArray> Term<BitArray>::getGroupedTerm(Term<BitArray> &other) 
    {
        this->_checked = false;
        other._checked = false;

        auto newMask = _result | _xMask;

        return Term(*this, other, newMask);
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

    template<typename BitArray>
    bool Term<BitArray>::operator==(Term const& other) const
    {
        return _bitArray == other._bitArray
            && _xMask == other._xMask
            && _checked == other._checked;
    }

    template<typename BitArray>
    bool Term<BitArray>::operator!=(Term const& other) const
    {
        return _bitArray != other._bitArray
            || _xMask != other._xMask
            || _checked != other._checked;
    }

    template<typename BitArray>
    bool Term<BitArray>::operator<(Term const& other) const
    {
        if(_bitArray == other._bitArray)
            return _xMask < other._xMask;
        return _bitArray < other._bitArray;
    }

    template<typename BitArray>
    auto const& Term<BitArray>::getMinterms() const
    {
        return _minTerm;
    }

    template<typename BitArray>
    auto Term<BitArray>::getEquation() const
    {
        std::vector<int> equation;

        // x, don't care bits are ommited in the boolean equation representation
        // set bits correspond to a boolen term,
        // unset bits correspond to a negative boolean term
        for(auto i = 1; i < static_cast<int>(_size); ++i)
        {
            BitArray mask = 1 << (_size - 1);
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
