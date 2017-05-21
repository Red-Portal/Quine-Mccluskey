//#include <cstdlib>
#include <gtest/gtest.h>

#include "../src/Term.hpp"

TEST(TermTest, TermFunctionStyleConstruction)
{
	auto term = QM::Term<uint64_t>(4, 3);
	EXPECT_EQ(term.getNumberOfOnes(), 2);
	EXPECT_TRUE(term.isChecked()); 
}

TEST(TermTest, TermDefaultStyleConstruction)
{
	QM::Term<uint64_t> term(4, 3);
	EXPECT_EQ(term.getNumberOfOnes(), 2);
	EXPECT_TRUE(term.isChecked()); 
}


TEST(TermTest, TermCopying)
{
	auto termOriginal = QM::Term<uint64_t>(4, 3);
	auto termCopyOp = termOriginal;
	EXPECT_EQ(termOriginal.getNumberOfOnes(),
			  termCopyOp.getNumberOfOnes());

	auto termCopyCons(termOriginal);
	EXPECT_EQ(termOriginal.getNumberOfOnes(),
			  termCopyCons.getNumberOfOnes());
}
