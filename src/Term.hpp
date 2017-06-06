#ifndef TERM_HPP
#define TERM_HPP

#include <vector>
#include <memory>
#include <cstdlib>

//#include <iostream>

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
        BitArray _result;
        std::vector<BitArray> _minTerm;

    public:
        inline Term(size_t size, BitArray term);
        inline Term(Term<BitArray> const& first,
                    Term<BitArray> const& second,
                    BitArray mask);
        inline Term(Term const&) = default;
        inline Term(Term&&) noexcept = default;
        inline Term& operator=(Term const& other) = default;
        ~Term() = default;

        inline bool isGreyAdjacent(Term& other);
        inline Term<BitArray> getGroupedTerm(Term& other);
        inline bool operator==(Term const& other) const;
        inline bool operator!=(Term const& other) const;
        inline bool operator<(Term const& oter) const;

        inline int getSetBitNum() const;
        inline bool isChecked() const;
        inline auto const& getMinterms() const;
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
    bool Term<BitArray>::isGreyAdjacent(Term<BitArray> &other)
    {
        if(_xMask != other._xMask)
            return false;

        _result = (_bitArray ^ other._bitArray) & ~_xMask; //XOR operation

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

        for(auto i = 1; i < static_cast<int>(_size); ++i)
        {
            BitArray mask = 1 << (_size - 1);
            mask = mask >> (i - 1);

            if((_xMask & mask) != 0)
                continue;

            if((_bitArray & mask) != 0)
                equation.push_back(i);
            else
            {
                equation.push_back(-i);
            }
        }
        return equation;
    }
}
#endif
