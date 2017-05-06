#ifndef QUINEMCCLUSKEY_QM_H
#define QUINEMCCLUSKEY_QM_H

#include<iostream>

#include <vector>
#include <array>
#include <bitset>
#include <cstdlib>
#include <functional>

namespace QM
{
  template<size_t _Size>
  class Reducer
  {
    using TermRef = std::reference_wrapper<std::bitset<_Size>>;
    
  private:
    std::vector<std::bitset<_Size>> _minTerms;
    std::vector<std::bitset<_Size>> _dTerms;

    auto findImplicants(std::vector<TermRef> const&, std::vector<TermRef> const&)
      -> std::vector<std::pair<std::bitset<_Size>, bool>>;

  public:
    explicit Reducer(std::vector<int> const& minTerms,
		     std::vector<int> const& dTerms);
    explicit Reducer(std::array<int, _Size> const& minTerms,
		     std::array<int, _Size> const& dTerms);
    ~Reducer() = default;

    void reduce();
  };
}


#include "QM.tpp"

#endif
