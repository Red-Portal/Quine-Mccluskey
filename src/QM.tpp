#ifndef QM_TPP
#define QM_TPP


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
	auto bitsByCount = std::array<std::vector<std::reference_wrapper<std::bitset<_Size>>>, _Size + 1>() ;

	// seperating the bitsets by the number of 1s
	for(auto& it : _minTerms)
		bitsByCount[it.count()].push_back(std::ref(it));
    for(auto& it : _dTerms)
        bitsByCount[it.count()].push_back(std::ref(it));

	for(auto& it : bitsByCount)
		findImplicants(it);
}

template<size_t _Size>
std::vector<std::pair<std::bitset<_Size>, bool>>
QM::Reducer<_Size>::findImplicants(std::vector<std::reference_wrapper<std::bitset<_Size>>> const&)
{
	return std::vector<std::pair<std::bitset<_Size>, bool>>();
}

#endif
