#pragma once

#include <string>
#include <iostream>

class Solution
{
    public:
    uint64_t resultPart1 = 0;
    uint64_t resultPart2 = 0;

    Solution(const std::string& input);

    void printResult(const std::string& input)
    {
        std::cout << "File: " << input << " | Part1 = " << resultPart1 << ", part2 = " << resultPart2 << "\n";
    }

    uint64_t getResultPart1() { return resultPart1; }
    uint64_t getResultPart2() { return resultPart2; }
};