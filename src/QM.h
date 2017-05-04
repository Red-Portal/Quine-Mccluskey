#ifndef QUINEMCCLUSKEY_QM_H
#define QUINEMCCLUSKEY_QM_H

#include <vector>
#include <array>
#include <cstdlib>
#include "Term.h"

namespace QM
{


    template<size_t terms>
    class Reducer
    {
    public:
        explicit Reducer(std::vector<int> const& minTerms, std::vector<int> const& dTerms);
        explicit Reducer(int minTerms[], int dTerms[]);

        Reducer();

        ~Reducer() = default;
    };
}

#endif
