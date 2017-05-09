#ifndef QM_TPP
#define QM_TPP

#include "QM.hpp"
#include "bitset.hpp"

// constructor for initialization using std::vectors
// generate vectors of bits
QM::Reducer::Reducer(std::vector<int> const& minTerms_,
			    std::vector<int> const& dTerms_)
{
  _minTerms.reserve(minTerms_.size());
  _dTerms.reserve(dTerms_.size());

  for (auto const& it : minTerms_)
    _minTerms.emplace_back(bitset(static_cast<unsigned long>(it)));
  for (auto const& it : dTerms_)
    _dTerms.emplace_back(bitset(static_cast<unsigned long>(it)));

  _minTerms.shrink_to_fit();
  _dTerms.shrink_to_fit();
}

// constructor for initialization using std::arrays
// generate vectors of bits
QM::Reducer::Reducer(int* const minTerms_,
		     int* const dTerms_)
{
  _minTerms.reserve(minTerms_.size());
  _dTerms.reserve(dTerms_.size());

  for (auto const& it : minTerms_)
    _minTerms.emplace_back(std::bitset<_Size>(static_cast<unsigned long>(it)));
  for (auto const& it : dTerms_)
    _dTerms.emplace_back(std::bitset<_Size>(static_cast<unsigned long>(it)));

  _minTerms.shrink_to_fit();
  _dTerms.shrink_to_fit();
}

// start boolean reduction using quine-mccluskey method
void QM::Reducer::reduce()
{
  auto bitsByCount = std::array<std::vector<TermRef>, _Size + 1>();

  // seperating the bitsets by the number of 1s
  for(auto& it : _minTerms)
    bitsByCount[it.count()].push_back(std::ref(it));
  for(auto& it : _dTerms)
    bitsByCount[it.count()].push_back(std::ref(it));

 
  // compare the terms which have n, n+1 numbers of '1's
  auto end = bitsByCount.end();
  for(auto& it = bitsByCount.begin(); it != end - 1; ++it)
    findImplicants(*it, *(it + 1));
}

std::vector<std::pair<bitset, bool>>
QM::Reducer::findImplicants(std::vector<TermRef> const& first,
				   std::vector<TermRef> const& second)
{
  auto result = std::vector<std::pair<std::bitset<_Size>, bool>>();
  result.reserve(first.size() + second.size());

  for(auto const& i : first)
  {
    for(auto const& j : second)
    {
      auto xorMasked = i.get() ^ j.get();

      if(xorMasked.count() == 1)
	result.emplace_back( /* implement */);
    }
  }

  return std::vector<std::pair<std::bitset<_Size>, bool>>();
}

#endif
