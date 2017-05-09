#ifndef QUINEMCCLUSKEY_QM_H
#define QUINEMCCLUSKEY_QM_H


#include <vector>
#include <array>
#include <bitset>
#include <cstdlib>
#include <functional>

namespace QM
{

  class bitset;

  class Reducer
  {
    using TermRef = std::reference_wrapper<bitset>;
    
  private:
    size_t _SIZE;
    std::vector<bitset> _minTerms;
    std::vector<bitset> _dTerms;

    auto findImplicants(std::vector<TermRef> const&, std::vector<TermRef> const&)
      -> std::vector<std::pair<bitset, bool>>;

  public:
    explicit Reducer(std::vector<int> const& minTerms,
		     std::vector<int> const& dTerms);
    explicit Reducer(int* const minTerms,
		     int* const dTerms);
    ~Reducer() = default;

    void reduce();
  };
}
#endif
