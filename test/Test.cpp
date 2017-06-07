/*  
   Copyright 2017 Red-Portal

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <gtest/gtest.h>
#include <vector>
#include <functional>

#include "../src/QM.hpp"

TEST(QuineMccluskeyTest, Test1)
{
    using namespace std::placeholders;

    std::vector<int> mTerms{4, 8, 10, 11, 12, 15};
    std::vector<int> dTerms{9, 14};

    auto reducer = QM::Reducer<uint64_t>(4, mTerms, dTerms);
    auto reduced = reducer.getBooleanFunction();

    auto comp = [](std::vector<int> compare,
                   std::vector<int> const& vec) -> bool {
        return std::equal(vec.begin(), vec.end(), compare.begin());
    };

    EXPECT_EQ(reduced.size(), 3u);

    EXPECT_NE(std::find_if(reduced.begin(),
                           reduced.end(),
                           std::bind(comp,
                                     _1,
                                     std::vector<int>{2, -3, -4})
                  ),  reduced.end());

    EXPECT_NE(std::find_if(reduced.begin(),
                           reduced.end(),
                           std::bind(comp,
                                     _1,
                                     std::vector<int>{1, -2})
                  ), reduced.end());

    EXPECT_NE(std::find_if(reduced.begin(),
                           reduced.end(),
                           std::bind(comp,
                                     _1,
                                     std::vector<int>{1, 3})
                  ), reduced.end());
}

TEST(QuineMccluskeyTest, Test2)
{
    using namespace std::placeholders;

    std::vector<int> mTerms{0, 1, 4, 8, 9, 10, 11, 20, 22};
    std::vector<int> dTerms{7, 13, 14, 16,};

    auto reducer = QM::Reducer<uint64_t>(5, mTerms, dTerms);
    auto reduced = reducer.getBooleanFunction();

    auto comp = [](std::vector<int> compare,
                   std::vector<int> const& vec) -> bool {
        return std::equal(vec.begin(), vec.end(), compare.begin());
    };

    EXPECT_EQ(reduced.size(), 4u);

    EXPECT_NE(std::find_if(reduced.begin(),
                           reduced.end(),
                           std::bind(comp,
                                     _1,
                                     std::vector<int>{-1, -3, -4})
                  ),  reduced.end());

    EXPECT_NE(std::find_if(reduced.begin(),
                           reduced.end(),
                           std::bind(comp,
                                     _1,
                                     std::vector<int>{-2, -4, -5})
                  ), reduced.end());

    EXPECT_NE(std::find_if(reduced.begin(),
                           reduced.end(),
                           std::bind(comp,
                                     _1,
                                     std::vector<int>{-1, 2, -3})
                  ), reduced.end());

    EXPECT_NE(std::find_if(reduced.begin(),
                           reduced.end(),
                           std::bind(comp,
                                     _1,
                                     std::vector<int>{1, -2, 3, -5})
                  ), reduced.end());
}
