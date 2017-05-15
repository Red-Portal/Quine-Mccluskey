#include "Term.hpp"
#include <iostream>

int main( int argc, char** argv)
{
    int const termNum = 4;
    //std::vector<int> minTerms = {4, 8, 10, 11, 12, 15};
    //std::vector<int> dTerms = {9, 14};

	auto term = QM::Term(4, 3);

	std::cout << term.getNumberOfOnes() << std::endl;

    return 0;
}
