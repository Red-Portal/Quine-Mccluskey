#include <gtest/gtest.h>

#define private public

#include "../src/Term.hpp"

TEST(TermDefaultTest, TermFunctionStyleConstruction)
{
	auto term = QM::Term<uint64_t>(4, 3);
	EXPECT_EQ(term.getSetBitNum(), 2);
	EXPECT_EQ(term._bitArray, static_cast<uint64_t>(3));
	EXPECT_EQ(term._size, static_cast<uint64_t>(4));
	EXPECT_EQ(term._xMask , static_cast<uint64_t>(0));
}

TEST(TermDefaultTest, TermDefaultStyleConstruction)
{
	QM::Term<uint64_t> term(4, 3);
	EXPECT_EQ(term.getSetBitNum(), 2);
	EXPECT_EQ(term._bitArray, static_cast<uint64_t>(3));
	EXPECT_EQ(term._size, static_cast<uint64_t>(4));
	EXPECT_EQ(term._xMask , static_cast<uint64_t>(0));
}


TEST(TermDefaultTest, TermCopying)
{
	auto termOriginal = QM::Term<uint64_t>(4, 3);
	auto termCopyOp = termOriginal;
	EXPECT_EQ(termOriginal.getSetBitNum(),
			  termCopyOp.getSetBitNum());
	EXPECT_EQ(termOriginal._bitArray,
			  termCopyOp._bitArray);
	EXPECT_EQ(termOriginal._size,
			  termCopyOp._size);
	EXPECT_EQ(termOriginal._xMask,
			  termCopyOp._xMask);

	auto termCopyCons(termOriginal);
	EXPECT_EQ(termOriginal.getSetBitNum(),
			  termCopyCons.getSetBitNum());
	EXPECT_EQ(termOriginal._bitArray,
			  termCopyCons._bitArray);
	EXPECT_EQ(termOriginal._size,
			  termCopyCons._size);
	EXPECT_EQ(termOriginal._xMask,
			  termCopyCons._xMask);
}

TEST(TermCompareTest, NothingInCommon) 
{
	auto termFirst = QM::Term<uint64_t>(4, 3);
	auto termSecond = QM::Term<uint64_t>(4, 4);

	auto ptr = termFirst.compareIfImplicant(termSecond);

	EXPECT_FALSE(ptr);
}

TEST(TermCompareTest, CompareResultMaskedoff)
{
	auto term = QM::Term<uint64_t>(4, 3);
	auto termMask = QM::Term<uint64_t>(term, 1);
	auto termSecond = QM::Term<uint64_t>(4, 2);

	auto ptr = termMask.compareIfImplicant(termSecond);

	EXPECT_FALSE(ptr);
}

TEST(TermCompareTest, CompareResultImplicant)
{
	auto termFirst = QM::Term<uint64_t>(4, 3); // 0011
	auto termSecond = QM::Term<uint64_t>(4, 2); // 0010

	auto ptr = termFirst.compareIfImplicant(termSecond); // 001X

	EXPECT_TRUE(ptr != nullptr);

	EXPECT_FALSE(termFirst.isChecked());
	EXPECT_FALSE(termSecond.isChecked());

	EXPECT_EQ(ptr->_bitArray, termFirst._bitArray);
	EXPECT_EQ(ptr->_size, termFirst._size);
	EXPECT_EQ(ptr->getSetBitNum(), termFirst.getSetBitNum());
	EXPECT_EQ(ptr->_xMask, static_cast<uint64_t>(1));
}

TEST(TermCompareTest, CompareResultImplicantFromImplicant)
{

	auto termFirst = QM::Term<uint64_t>(4, 3); // 0011
	auto termSecond = QM::Term<uint64_t>(4, 2); // 0010

	auto ptr = termFirst.compareIfImplicant(termSecond); // 001X

	auto termThird = QM::Term<uint64_t>(4, 10); // 1010
	auto termThirdMasked = QM::Term<uint64_t>(termThird, 1);
	auto resultPtr = ptr->compareIfImplicant(termThirdMasked); // X01X

	EXPECT_TRUE(resultPtr != nullptr);

	EXPECT_FALSE(termFirst.isChecked());
	EXPECT_FALSE(termSecond.isChecked());
	EXPECT_TRUE(resultPtr->isChecked());

	EXPECT_EQ(resultPtr->_bitArray, termFirst._bitArray);
	EXPECT_EQ(resultPtr->_size, termFirst._size);
	EXPECT_EQ(resultPtr->getSetBitNum(), termFirst.getSetBitNum());
	EXPECT_EQ(resultPtr->_xMask, static_cast<uint64_t>(9));
}

TEST(TermCompareTest, ComparingMasks)
{
	auto termFirst = QM::Term<uint64_t>(4, 3); // 0011
	auto termSecond = QM::Term<uint64_t>(4, 2); // 0010

	auto termMaskedFirst = QM::Term<uint64_t>(termFirst, 4); // 0X11
	auto termMaskedSecond = QM::Term<uint64_t>(termSecond, 8); // X010

	auto ret = termMaskedFirst.compareIfImplicant(termMaskedSecond);

	EXPECT_FALSE(ret);
}
