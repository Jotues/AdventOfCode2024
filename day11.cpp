#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <unordered_map>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    auto nums = utils::getIntsFromString<uint64_t>(lines[0]);
    
    std::unordered_map<uint64_t, uint64_t> markWithNumOfStones;
    
    auto insertToMap = [&markWithNumOfStones](uint64_t mark, uint64_t num = 1) -> void
    {
        auto [_, inserted] = markWithNumOfStones.insert(std::make_pair<uint64_t, uint64_t>(std::forward<uint64_t>(mark), std::forward<uint64_t>(num)));
        if (inserted == false)
        {
            markWithNumOfStones[mark] += num;
        }
    };

    auto removeFromMap = [&markWithNumOfStones](uint64_t mark, uint64_t num = 1) -> void
    {
        if (markWithNumOfStones[mark] == num)
        {
            markWithNumOfStones.erase(mark);
        }
        else
        {
            markWithNumOfStones[mark] -= num;
        }
    };

    auto numOfDigitits = [](uint64_t testedVal) -> uint64_t
    {
        uint64_t count = 0;
        while (testedVal > 0)
        {
            testedVal /= 10;
            count++;
        }
        return count;
    };

    for (auto i = 0; i < nums.size(); i++)
    {
        insertToMap(nums[i]);
    }
    
    const auto BLINKS_COUNT_PART1 = 25;
    const auto BLINKS_COUNT_PART2 = 75;
    
    for (int i = 0; i < BLINKS_COUNT_PART2; i++)
    {
        auto mapCopy = markWithNumOfStones;
        
        for (const auto& [mark, count] : mapCopy)
        {
            if (mark == 0)
            {
                insertToMap(1, count);
                removeFromMap(0, count);
            }
            else if (numOfDigitits(mark) % 2 == 0)
            {
                auto strTemp = std::to_string(mark);
                insertToMap(stoul(strTemp.substr(0, strTemp.size() / 2)), count);
                insertToMap(stoul(strTemp.substr(strTemp.size() / 2)), count);
                removeFromMap(mark, count);
            }
            else
            {
                insertToMap(mark * 2024, count);
                removeFromMap(mark, count);
            }
        }
        
        if (i == BLINKS_COUNT_PART1 - 1)
        {
            for (const auto& [mark, count] : markWithNumOfStones)
            {
                resultPart1 += count;
            }
        }
    }
    
    for (const auto& [mark, count] : markWithNumOfStones)
    {
        resultPart2 += count;
    }
    
    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example11.txt");
    Solution real("../inputs/input11.txt");

    task.endTaskAndPrintTime();
    return 0;
}