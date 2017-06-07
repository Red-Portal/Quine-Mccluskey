#include <gtest/gtest.h>
#define private public

#include "../src/QM.hpp"
#include "../src/Term.hpp"

struct QuineMccluskeyTest
    : public testing::Test, public QM::Reducer<uint64_t>
{
    QuineMccluskeyTest()
        : Reducer<uint64_t>(4, {4, 8, 10, 11, 12, 15}, {9, 14})
    {}
    ~QuineMccluskeyTest() = default;
};

TEST_F(QuineMccluskeyTest, reduce)
{
    using namespace std::placeholders;
    std::vector<uint64_t> mTerms{4, 8, 10, 11, 12, 15};
    std::vector<uint64_t> dTerms{9, 14};

    //4  -> 0100
    //8  -> 1000
    //10 -> 1010
    //11 -> 1011
    //12 -> 1100

    //9  -> 1001
    //14 -> 1110

    std::vector<QM::Term<uint64_t>> mTermObj{};
    std::vector<QM::Term<uint64_t>> dTermObj{};

    auto comp = [](QM::Term<uint64_t> a, uint64_t num, uint64_t mask){
        return a._bitArray == num && a._xMask ==  mask;
    };

    for(auto& i : mTerms)
    {
        mTermObj.emplace_back(4, i);
    }
    for(auto& i : dTerms)
    {
        dTermObj.emplace_back(4, i);
    }

    auto result = this->identify(mTermObj, dTermObj);

    EXPECT_NE(std::find_if(result.begin(),
                           result.end(),
                           std::bind(comp, _1, 8, 6)),
              result.end());
    EXPECT_NE(std::find_if(result.begin(),
                           result.end(),
                           std::bind(comp, _1, 8, 3)),
              result.end());
    EXPECT_NE(std::find_if(result.begin(),
                           result.end(),
                           std::bind(comp, _1, 10, 5)),
              result.end());
    EXPECT_NE(std::find_if(result.begin(),
                           result.end(),
                           std::bind(comp, _1, 4, 8)),
              result.end());
}

TEST_F(QuineMccluskeyTest, computeImplicant)
{
    std::vector<QM::Term<uint64_t>> vec;

    std::vector<QM::Term<uint64_t>> first;
    std::vector<QM::Term<uint64_t>> second;

    first.emplace_back(QM::Term<uint64_t>(4, 1)); // 0001
    first.emplace_back(QM::Term<uint64_t>(4, 8)); // 1000

    second.emplace_back(QM::Term<uint64_t>(4, 10)); // 1010
    second.emplace_back(QM::Term<uint64_t>(4, 6)); // 0110
    second.emplace_back(QM::Term<uint64_t>(4, 9)); // 1001

    auto result = iterateThroughGroup(first, second);

    EXPECT_EQ(result.size(), 3u); 
    EXPECT_FALSE(first[0].isChecked()); 
    EXPECT_TRUE(second[1].isChecked()); 
}

TEST_F(QuineMccluskeyTest, computeBySetBits)
{
    std::unordered_map<uint64_t, TermVector> map;
    std::vector<QM::Term<uint64_t>> vec;

    vec.push_back(QM::Term<uint64_t>(4, 1)); // 0001
    vec.push_back(QM::Term<uint64_t>(4, 8)); // 1000

    vec.push_back(QM::Term<uint64_t>(4, 10)); // 1010
    vec.push_back(QM::Term<uint64_t>(4, 6)); // 0110
    vec.push_back(QM::Term<uint64_t>(4, 9)); // 1001

    for(auto& i : vec)
        map[i.getSetBitNum()].push_back(i);

    auto result = this->iterateThroughCollumn(map);

    EXPECT_EQ(result[1].size() , 3u);
    EXPECT_EQ(result[2].size() , 0u);
}

TEST_F(QuineMccluskeyTest, selectPrimeImplicant)
{
    std::vector<uint64_t> mTerms{4, 8, 10, 11, 12, 15};
    std::vector<uint64_t> dTerms{9, 14};

    //4  -> 0100
    //8  -> 1000
    //10 -> 1010
    //11 -> 1011
    //12 -> 1100

    //9  -> 1001
    //14 -> 1110

    std::vector<QM::Term<uint64_t>> mTermObj{};
    std::vector<QM::Term<uint64_t>> dTermObj{};

    for(auto& i : mTerms)
    {
        mTermObj.emplace_back(4, i);
    }
    for(auto& i : dTerms)
    {
        dTermObj.emplace_back(4, i);
    }

    auto result = this->identify(mTermObj, dTermObj);
    auto prime = select(result, mTermObj);

    EXPECT_EQ(prime.size(), 3u);
}
