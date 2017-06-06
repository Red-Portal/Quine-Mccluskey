#ifndef QUINEMCCLUSKEY_QM_H
#define QUINEMCCLUSKEY_QM_H

#include <vector>
#include <array>
#include <cstdlib>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <set>

#include "Term.hpp"

namespace QM
{
    template<typename BitArray>
    class Reducer
    {
    private:
        using TermVector = std::vector<Term<BitArray>>;

        size_t const _inputNum;
        std::vector<std::vector<int>> _result;

        
        // the procedure call is as follows
        //
        // reduce is the phase 1 procedure
        //
        // computeByNumberOfSetBits is called for each iteration in the process
        // the iteration process stops if there isn't any more reducable terms.
        //
        // computeImplicant is called in each iteration, it starts a loop that
        // calls a getImplicant for each "N, N+1 number of set bits" groups
        //
        // select is the prime implicant selection, phase 2
        // 
        // set result sets the result into a integer representation of boolean equation


        // call computeImplcant procedure for each grouped Implcant size
        inline auto computeByNumberOfSetBits(
            std::unordered_map<BitArray, TermVector>& map) const;


        // find implicants between groups of terms with n, n+1 numbers of set bits
        inline auto computeImplicant(TermVector& first,
                                     TermVector& second) const;

        // find checked implicants
        inline auto getImplicants(
            std::unordered_map<BitArray, TermVector> const&) const;

        // start phase 1: reduction procedure 
        inline auto reduce(TermVector const& mTerms, TermVector const& dTerms) const;

        // select prime implicants
        inline auto select(TermVector const& implicants, TermVector const& mTerms) const;

        // store reduction result into boolean equation representation
        inline void setResult(TermVector const& implicants);

    public:
        template<typename T>
        inline explicit Reducer(int inputNum,
                                std::vector<T> const& minTerms,
                                std::vector<T> const& dTerms);
        template<typename T>
        inline explicit Reducer(int inputNum,
                                std::initializer_list<T> const& minTerms,
                                std::initializer_list<T> const& dTerms);

        ~Reducer() = default;
    };


    template<typename BitArray>
    template<typename T>
    Reducer<BitArray>::Reducer(int inputNum,
                               std::vector<T> const& minTerms,
                               std::vector<T> const& dTerms)
        :_inputNum(inputNum)
    {
        TermVector mTerms_;
        TermVector dTerms_;

        mTerms_.reserve(minTerms.size());
        dTerms_.reserve(dTerms.size()); 

        // converting user provided minTerm, dontcareTerm representation
        // into local representation
        for (auto it : minTerms)
            mTerms_.emplace_back(Term<BitArray>(inputNum, it));
        for (auto it : dTerms)
            dTerms_.emplace_back(Term<BitArray>(inputNum, it));

        // reduction procedure
        auto implicants = reduce(mTerms_, dTerms_);
        auto primeImpl = select(implicants, mTerms_);

        setResult(primeImpl);
    }

    template<typename BitArray>
    template<typename T>
    Reducer<BitArray>::Reducer(int inputNum,
                               std::initializer_list<T> const& minTerms,
                               std::initializer_list<T> const& dTerms)
        : _inputNum(inputNum)
    {
        TermVector mTerms_;
        TermVector dTerms_;

        mTerms_.reserve(minTerms.size());
        dTerms_.reserve(dTerms.size());

        // converting user provided minTerm, dontcareTerm representation
        // into local representation
        for (auto it : minTerms)
            mTerms_.emplace_back(Term<BitArray>(inputNum, it));
        for (auto it : dTerms)
            dTerms_.emplace_back(Term<BitArray>(inputNum, it));

        // reduction procedure
        auto implicants = reduce(mTerms_, dTerms_);
        auto primeImpl = select(implicants, mTerms_);

        setResult(primeImpl);
    }

    template<typename BitArray>
    auto Reducer<BitArray>::reduce(TermVector const& mTerms,
                                   TermVector const& dTerms) const
    {
        std::vector<std::unordered_map<BitArray, TermVector>> byImplicantSize;
        TermVector result;
        result.reserve(mTerms.size() + dTerms.size());

        // seperating the bitsets by the number of setBits 
        byImplicantSize.emplace_back(std::unordered_map<BitArray, TermVector>());
        auto& sizeZero = byImplicantSize.front();
        for(auto& it : mTerms)
            sizeZero[it.getSetBitNum()].push_back(it);
        for(auto& it : dTerms)
            sizeZero[it.getSetBitNum()].push_back(it);

        // phase 1 reduction procedure
        for(BitArray idx = 0; idx < byImplicantSize.size(); ++idx)
        {
            auto implicant = computeByNumberOfSetBits(byImplicantSize[idx]);

            if(implicant.empty())
                continue;

            byImplicantSize.push_back(std::move(implicant));
        } 

        // finding all the checked implicants
        for(auto& i : byImplicantSize)
        {
            auto realImp = getImplicants(i);
            result.insert(result.end(),
                          std::make_move_iterator(realImp.begin()),
                          std::make_move_iterator(realImp.end()));
        }

        return result;
    }

    template<typename BitArray>
    auto Reducer<BitArray>::computeByNumberOfSetBits(
        std::unordered_map<BitArray, TermVector>& map) const
    {
        std::unordered_map<BitArray, TermVector> result;

        for(BitArray i = 0; i < _inputNum; ++i)
        {
            // checking if there adjacent "set bit number" groups actually exist
            auto first = map.find(i);
            if(first == map.end())
                continue;

            auto second = map.find(i+1);
            if(second == map.end())
                continue;

            result[i] = computeImplicant(first->second,
                                         second->second);
        }

        return result;
    }

    template<typename BitArray>
    auto Reducer<BitArray>::computeImplicant(TermVector& first,
                                             TermVector& second) const
    {
        std::set<Term<BitArray>> set;

        // iterating through 'N set bits group' first, 'N+1 set bits group' second
        for(auto i = first.begin(); i != first.end(); ++i)
        {
            for(auto j = second.begin(); j != second.end(); ++j)
            {
                if(i->isGrayAdjacent(*j))
                {
                    auto ret = i->getGroupedTerm(*j);
                    set.insert(ret);
                }
            }
        }
        return TermVector(set.begin(), set.end());
    }

    template<typename BitArray>
    auto Reducer<BitArray>::getImplicants(
        std::unordered_map<BitArray, TermVector> const& map) const
    {
        TermVector result;

        // iterate through all the terms used in computation
        // and check if they are marked as 'checked'
        for(auto& i : map)
        {
            if(i.second.size() == 0)
                continue;
            
            for(auto& j : i.second)
            {
                if(j.isChecked())
                    result.push_back(std::move(j));
            }
        }

        return result;
    }

    template<typename BitArray>
    auto Reducer<BitArray>::select(TermVector const& implicants,
                                   TermVector const& mTerms) const
    {
        std::unordered_map<BitArray, std::vector<Term<BitArray> const*>> chart;
        std::unordered_map<Term<BitArray> const*, bool> implicantsCheckList; 
        std::set<Term<BitArray>> result;

        for(auto& i : implicants)
        {
            implicantsCheckList[&i] = false;

            for(auto& j : i._minTerm)
            {
                chart[j].push_back(&i);
            }
        }

        // selection of prime implicants
        for(auto& i : chart)
        {
            if(i.second.size() == 1)
            {
                result.emplace(*(i.second.front()));
                implicantsCheckList[i.second.front()] = true;
            }
        }

        // selection of non-prime implicants
        for(auto& i : chart)
        {
            if(i.second.size() > 1)
            {
                // j is a pointer
                for(auto j : i.second)
                {
                    if(result.find(*j) != result.end())
                    {
                        result.emplace(*j);
                        goto OUT;
                    }
                }

                for(auto j : i.second)
                {
                    
                    if(implicantsCheckList[j] != true)
                    {
                        result.emplace(*j);
                        break;
                    }
                }
            }

        OUT:
            ;
        }

        return TermVector(result.begin(), result.end());
    }

    template<typename BitArray>
    void Reducer<BitArray>::setResult(TermVector const& implicants)
    {
        _result.reserve(implicants.size());
        for(auto& i : implicants)
        {
            _result.emplace_back();

            auto equation = i.getEquation();

            auto& back = _result.back();
            back.reserve(equation.size());
            back.insert(back.end(),
                        std::make_move_iterator(equation.begin()),
                        std::make_move_iterator(equation.end()));
        }
    }
}
#endif
