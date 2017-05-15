#ifndef QUINEMCCLUSKEY_QM_H
#define QUINEMCCLUSKEY_QM_H


#include <vector>
#include <array>
#include <cstdlib>
#include <initializer_list>
#include <functional>

#include "Term.hpp"

namespace QM
{
	class Reducer
	{
	private:
		std::vector<Term> _minTerms;
		std::vector<Term> _dTerms;
		size_t const _inputNum;

		auto findImplicants(std::vector<Term> const&,
							std::vector<Term> const& );

	public:
		explicit Reducer(int inputNum,
						 std::vector<int> const& minTerms,
						 std::vector<int> const& dTerms);

		explicit Reducer(int inputNum,
						 std::initializer_list<int> const& minTerms,
						 std::initializer_list<int> const& dTerms);

		~Reducer() = default;

		void reduce();
	};
}
#endif
