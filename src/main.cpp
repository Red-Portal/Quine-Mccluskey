#include "QM.h"
#include <iostream>

int main( int argc, char** argv)
{
    int const termNum = 4;
    std::vector<int> minTerms = {4, 8, 10, 11, 12, 15};
    std::vector<int> dTerms = {9, 14};

    auto qm = QM::Reducer<termNum>(minTerms, dTerms);
    qm.reduce();

    return 0;
}