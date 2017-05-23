#ifndef QUINEMCCLUSKEY_QM_H
#define QUINEMCCLUSKEY_QM_H

#include <vector>
#include <array>
#include <cstdlib>
#include <initializer_list>
#include <functional>
#include <unordered_map>

#include "Term.hpp"

namespace QM
{
	template<typename BitArray>
	class Reducer
	{
	private:
		using TermUniquePtrVector = std::vector<std::unique_ptr<Term<BitArray>>>;

		TermUniquePtrVector _minTerms;
		TermUniquePtrVector _dTerms;
		size_t const _inputNum;

		inline auto computeBySetBits(std::unordered_map<int, TermUniquePtrVector>& map);
		inline auto computeImplicant(TermUniquePtrVector& first, TermUniquePtrVector& second);
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

		inline Reducer& operator=(Reducer const&);
		inline Reducer(Reducer const&);

		void reduce();
	};


	template<typename BitArray>
	template<typename T>
	Reducer<BitArray>::Reducer(int inputNum,
							   std::vector<T> const& minTerms,
							   std::vector<T> const& dTerms)
		:_minTerms(),
		 _dTerms(),
		 _inputNum(inputNum)
	{
		_minTerms.reserve(minTerms.size());
		_dTerms.reserve(dTerms.size()); 

		for (auto it : minTerms)
			_minTerms.emplace_back(new Term<BitArray>(_inputNum,
													  static_cast<BitArray>(it)));
		for (auto it : dTerms)
			_dTerms.emplace_back(new Term<BitArray>(_inputNum,
			static_cast<BitArray>(it)));
	}

	template<typename BitArray>
	template<typename T>
	Reducer<BitArray>::Reducer(int inputNum,
							   std::initializer_list<T> const& minTerms,
							   std::initializer_list<T> const& dTerms)
		: _minTerms(),
		  _dTerms(),
		  _inputNum(inputNum)
	{
		_minTerms.reserve(minTerms.size());
		_dTerms.reserve(dTerms.size());

		for (auto it : minTerms)
			_minTerms.emplace_back(new Term<BitArray>(_inputNum,
													  static_cast<BitArray>(it)));
		for (auto it : dTerms)
			_dTerms.emplace_back(new Term<BitArray>(_inputNum,
			static_cast<BitArray>(it)));
	}


	template<typename BitArray>
	Reducer<BitArray>& Reducer<BitArray>::operator=(Reducer<BitArray> const& other)
	{
		_minTerms.clear();
		_dTerms.clear();

		for(auto const& it : other._minTerms)
			_minTerms.push_back(std::make_unique<Term<BitArray>>(*it));
		for(auto const& it : other._dTerms)
			_dTerms.push_back(std::make_unique<Term<BitArray>>(*it));

		return *this;
	}

	template<typename BitArray>
	Reducer<BitArray>::Reducer(Reducer<BitArray> const& other)
		: _minTerms(),
		  _dTerms(),
		  _inputNum(other._inputNum)
	{
		for(auto const& it : other._minTerms)
			_minTerms.push_back(std::make_unique<Term<BitArray>>(*it));
		for(auto const& it : other._dTerms)
			_dTerms.push_back(std::make_unique<Term<BitArray>>(*it));
	}

	template<typename BitArray>
	void Reducer<BitArray>::reduce()
	{
		std::vector<std::unordered_map<int, TermUniquePtrVector>> termsByBitCount;

		// seperating the bitsets by the number of 1s

		termsByBitCount.emplace_back(std::unordered_map<int, TermUniquePtrVector>());

		for(auto&& it : _minTerms)
			termsByBitCount[0][it.getSetBitCount()].push_back(std::move(it));
		for(auto&& it : _dTerms)
			termsByBitCount[0][it.getSetBitCount()].push_back(std::move(it));

		for(auto it = termsByBitCount.begin(); it != termsByBitCount.end(); ++it)
		{
			auto result = findImplicants(*it);

			if(result.empty())
				continue;
			else
				termsByBitCount.push_back(std::move(result));
		}
		
		/*	
		// compare the terms which have n, n+1 numbers of '1's
		auto end = _inputNum - 1;
		for(auto it = 0; it < end; ++it)
		{
			if(termsByBitCount.count(it) <= 0 || termsByBitCount.count(it + 1) <= 0)
				continue;
			
			auto result = findImplicants(termsByBitCount[it], termsByBitCount[it + 1]);
			}*/
	}

	template<typename BitArray>
	auto Reducer<BitArray>::computeBySetBits(std::unordered_map<int, TermUniquePtrVector>& map)
	{
		std::unordered_map<int, TermUniquePtrVector> result;

		auto end = _inputNum;
		for(auto i = 0; i < end; ++i)
		{
			result[i] = computeImplicant(map[i], map[i+1]); 
		}
		return result;
	}

	template<typename BitArray>
	auto Reducer<BitArray>::computeImplicant(TermUniquePtrVector& first,
											 TermUniquePtrVector& second)
	{
		TermUniquePtrVector vec;
		for(auto i = vec.begin(); i != vec.end(); ++i)
		{
			for(auto j = i; j != vec.end(); ++j)
			{
				auto ret = (*i)->compareIfImplicant(**j);
				if(ret != nullptr)
					vec.push_back(std::move(ret));
			}
		}

		return vec;
	}
}
#endif
