#ifndef QM_TPP
#define QM_TPP

#include "QM.hpp"
#include "Term.hpp"

// constructor for initialization using std::vectors
// generate vectors of bits
QM::Reducer::Reducer(int inputNum,
					 std::vector<int> const& minTerms,
					 std::vector<int> const& dTerms)
	:_inputNum(static_cast<size_t>(inputNum))
{
	_minTerms.reserve(minTerms.size());
	_dTerms.reserve(dTerms.size()); 

	for (auto it : minTerms)
		_minTerms.emplace_back(Term(_inputNum,
									static_cast<unsigned int>(it)));
	for (auto it : dTerms)
		_dTerms.emplace_back(Term(_inputNum,
								  static_cast<unsigned int>(it)));
}

// constructor for initialization using std::arrays
// generate vectors of bits
QM::Reducer::Reducer(int inputNum,
					 std::initializer_list<int> const& minTerms,
					 std::initializer_list<int> const& dTerms)
	:_inputNum(inputNum)
{
	_minTerms.reserve(minTerms.size());
	_dTerms.reserve(dTerms.size());

	for (auto it : minTerms)
		_minTerms.emplace_back(Term(_inputNum,
									static_cast<unsigned int>(it)));
	for (auto it : dTerms)
		_dTerms.emplace_back(Term(_inputNum,
								  static_cast<unsigned int>(it)));
}

// start boolean reduction using quine-mccluskey method
void QM::Reducer::reduce()
{
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

auto QM::Reducer::findImplicants(std::vector<Term> const& first,
								 std::vector<Term> const& second)
{

}

#endif
