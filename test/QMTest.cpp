#include <gtest/gtest.h>

#define private public

#include "../src/QM.hpp"

TEST(QuineMccluskeyTest, MinTermGeneration)
{
	std::vector<int> minTerms{1,2,3,4,5};
	std::vector<int> dTerms{6,7,8};
	auto reducer = QM::Reducer<uint64_t>(4, minTerms, dTerms);

	EXPECT_EQ(static_cast<uint64_t>(minTerms[0]),
			  reducer._minTerms[0]->_bitArray);
	EXPECT_EQ(static_cast<uint64_t>(minTerms[1]),
			  reducer._minTerms[1]->_bitArray);
	EXPECT_EQ(static_cast<uint64_t>(minTerms[2]),
			  reducer._minTerms[2]->_bitArray);
	EXPECT_EQ(static_cast<uint64_t>(minTerms[3])
			  , reducer._minTerms[3]->_bitArray);
	EXPECT_EQ(static_cast<uint64_t>(minTerms[4]),
			  reducer._minTerms[4]->_bitArray);

	EXPECT_EQ(static_cast<uint64_t>(dTerms[0]),
			  reducer._dTerms[0]->_bitArray);
	EXPECT_EQ(static_cast<uint64_t>(dTerms[1]),
			  reducer._dTerms[1]->_bitArray);
	EXPECT_EQ(static_cast<uint64_t>(dTerms[2]),
	reducer._dTerms[2]->_bitArray); 
}
