
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

#include <vector>
#include <iostream>
#include <functional>
#include <string>
#include <chrono>

#include "../include/QM.hpp"

std::string decoder(int in)
{
    if(in < 0)
    {
	std::string temp(1, static_cast<char>(-in + 64));
	temp.push_back('\'');
	return temp;
    }
    else
	return std::string(1, static_cast<char>(in + 64));
}

int main(int argc, char* argv[])
{
    using namespace std::placeholders;


	{
		std::vector<int> mTerms{ 4, 8, 10, 11, 12, 15 };
		std::vector<int> dTerms{ 9, 14 };

		auto start = std::chrono::high_resolution_clock::now();

		auto reducer = QM::Reducer<uint64_t>(4, mTerms, dTerms);
		auto reduced = reducer.getBooleanFunction();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = end - start;
		auto time = std::chrono::duration<double, std::micro>(duration);

		std::cout << "duration: " << time.count()
			<< " ns"
			<< std::endl;

		std::cout << "result: ";
		for (auto i = 0u; i < reduced.size(); ++i)
		{
			for (auto j : reduced[i])
			{
				std::cout << decoder(j);
			}

			if (i < reduced.size() - 1)
				std::cout << " + ";
		}
		std::cout << std::endl;
	}

	{
		std::vector<int> mTerms{ 0, 1, 4, 8, 9, 10, 11, 20, 22 };
		std::vector<int> dTerms{ 7, 13, 14, 16, };

		auto start = std::chrono::high_resolution_clock::now();

		auto reducer = QM::Reducer<uint64_t>(5, mTerms, dTerms);
		auto reduced = reducer.getBooleanFunction();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = end - start;

		auto time = std::chrono::duration<double, std::micro>(duration);

		std::cout << "duration: " << time.count()
			<< " ns" << std::endl;

		std::cout << "result: ";
		for (auto i = 0u; i < reduced.size(); ++i)
		{
			for (auto j : reduced[i])
			{
				std::cout << decoder(j);
			}

			if (i < reduced.size() - 1)
				std::cout << " + ";
		}
		std::cout << std::endl;
	}
	return 0;
}
