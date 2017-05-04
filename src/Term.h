#ifndef QUINEMCCLUSKEY_TERM_HPP
#define QUINEMCCLUSKEY_TERM_HPP

#include <cstdlib>
#include <array>

namespace QM
{
    template<size_t Tsize>
    class Term
    {
    private:
        std::array<unsigned, Tsize> _digits;
    public:
        Term() = default;
        Term(std::array<unsigned, Tsize> const& )
        ~Term();
    };
}
#endif
