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
	private:
		std::vector<std::bitset<_Size>> _minTerms;
		std::vector<std::bitset<_Size>> _dTerms;


    public:
        explicit Reducer(std::vector<int> const& minTerms,
				std::vector<int> const& dTerms);
        explicit Reducer(std::array<int, _Size> const& minTerms,
				std::array<int, _Size> const& dTerms);
        ~Reducer() = default;

		void reduce();
    };
}

// constructor for initialization using std::vectors
// generate vectors of bits
template<size_t _Size>
QM::Reducer<_Size>::Reducer(std::vector<int> const& minTerms_,
							std::vector<int> const& dTerms_)
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

// constructor for initialization using std::arrays
// generate vectors of bits
template<size_t _Size>
QM::Reducer<_Size>::Reducer(std::array<int, _Size> const& minTerms_,
							std::array<int, _Size> const& dTerms_)
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
template<size_t _Size>
void QM::Reducer<_Size>::reduce()
{
	std::array<std::vector<std::reference_wrapper<std::bitset<_Size>>>, _Size + 1> bitsByCount;

	// seperating the bitsets by the number of 1s
	for(auto& it : _minTerms)
		bitsByCount[it.count()].push_back(std::ref(it));
    for(auto& it : _dTerms)
        bitsByCount[it.count()].push_back(std::ref(it));



}
#endif
