#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <functional>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);

    enum class Operation 
    {
        ADD,
        MULTIPLY,
        CONCANATE,
    };

    using u64 = uint64_t;

    std::function<bool(u64, const u64&, Operation, std::span<u64>)> checkRowPart1 = [&checkRowPart1] (u64 current, const u64& expected, Operation op, std::span<u64> nums) -> bool
    {
        if (op == Operation::ADD)
        {
            current += nums.front();
        }
        else
        {
            current *= nums.front();
        }
        
        if (current < expected)
        {
            if (nums.size() > 1)
            {
                nums = nums.subspan(1);
                return (checkRowPart1(current, expected, Operation::ADD, nums) || checkRowPart1(current, expected, Operation::MULTIPLY, nums));
            }
            else
            {
                return false;
            }
        }
        else if (current == expected && nums.size() == 1)
        {
            return true;
        }
        else if (current >= expected)
        {
            if (current == expected && std::ranges::all_of(nums.subspan(1), [](u64 v) {return v == 1;}))
            {
                return true;
            }
            return false;
        }
        throw std::runtime_error("Shouldn't be here!!");
    };

    std::function<bool(u64, const u64&, Operation, std::span<u64>)> checkRowPart2 = [&checkRowPart2] (u64 current, const u64& expected, Operation op, std::span<u64> nums) -> bool
    {
        if (op == Operation::ADD)
        {
            current += nums.front();
        }
        else if (op == Operation::MULTIPLY)
        {
            current *= nums.front();
        }
        else
        {
            current = stoul(std::to_string(current) + std::to_string(nums.front()));
        }
        
        if (current < expected)
        {
            if (nums.size() > 1)
            {
                nums = nums.subspan(1);
                return (checkRowPart2(current, expected, Operation::ADD, nums) || checkRowPart2(current, expected, Operation::MULTIPLY, nums) || checkRowPart2(current, expected, Operation::CONCANATE, nums));
            }
            else
            {
                return false;
            }
        }
        else if (current == expected && nums.size() == 1)
        {
            return true;
        }
        else if (current >= expected)
        {
            if (current == expected && std::ranges::all_of(nums.subspan(1), [](u64 v) {return v == 1;}))
            {
                return true;
            }
            return false;
        }
        throw std::runtime_error("Shouldn't be here!!");

    };
    
    for (const auto& line: lines)
    {
        auto stringNums = utils::splitStringByDelimeter(line, " ");
        uint64_t expectedResult = stoul(stringNums[0].substr(0, stringNums[0].size()));
        std::vector<uint64_t> nums;
        for (auto i = 1u; i < stringNums.size(); i++)
        {
            nums.emplace_back(stoul(stringNums[i]));
        }

        std::span<u64> sp {nums.begin() + 1, nums.end()};
        if (checkRowPart1(nums[0], expectedResult, Operation::ADD, sp) || 
            checkRowPart1(nums[0], expectedResult, Operation::MULTIPLY, sp))
        {
            resultPart1 += expectedResult;
        }

        if (checkRowPart2(nums[0], expectedResult, Operation::ADD, sp) || 
            checkRowPart2(nums[0], expectedResult, Operation::MULTIPLY, sp) || 
            checkRowPart2(nums[0], expectedResult, Operation::CONCANATE, sp))
        {
            resultPart2 += expectedResult;
        }
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example07.txt");
    Solution real("../inputs/input07.txt");

    task.endTaskAndPrintTime();
    return 0;
}