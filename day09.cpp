#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{   
    constexpr auto SPACE = -1;
    
    auto lines = utils::getLinesOfFile(input);
    auto line = lines[0];

    std::vector<int32_t> spaces;
    auto currentId = 0;
    auto nowFile = true;

    for (auto c: line)
    {
        auto num = static_cast<int32_t>(c - '0');
        for (int i = 0; i < num; i++)
        {
            spaces.emplace_back(nowFile ? currentId : SPACE);
        }
        if (nowFile)
        {
            currentId++;
        }
        nowFile = !nowFile;
    }

    //copy of original vector to part2
    auto spacesToPart2 = spaces;
    
    auto countResult = [](const std::vector<int32_t>& data) -> uint64_t
    {
        uint64_t result = 0;
        for (auto i = 0u; i < data.size(); i++)
        {
            if (data[i] != SPACE)
            {
                result += data[i] * i;
            }
        }
        return result;
    };

    // part 1
    auto left = 0u;
    auto right = spaces.size() - 1;
    bool stop = false;

    while(left != right)
    {
        if (spaces[right] == SPACE)
        {
            right--;
        }
        else
        {
            while (spaces[left] != SPACE)
            {
                left++;
                if (left == right)
                {
                    stop = true;
                    break;
                }
            }
            if (stop)
            {
                break;
            }
            std::swap(spaces[left], spaces[right]);
        }
    }
    
    resultPart1 = countResult(spaces);
    
    // part 2
    auto countBlockSize = [](const std::vector<int32_t>& data, uint32_t start, int direction) -> uint32_t
    {
        const auto blockType = data[start];
        auto count = 1u;
        auto current = start;
        current += direction;
        while (data[current] == blockType)
        {
            count++;
            if (current >= data.size() - 1 || current == 0)
            {
                break;
            }
            current += direction;
        }
        return count;
    };

    left = 0;
    right = spacesToPart2.size() - 1;
    while (true)
    {
        if (spacesToPart2[right] == SPACE)
        {
            right--;
            continue;
        }
        else
        {
            auto blockSize = countBlockSize(spacesToPart2, right, -1);
            auto nextLeft = left;
            while (true)
            {
                if (spacesToPart2[nextLeft] == SPACE && countBlockSize(spacesToPart2, nextLeft, 1) >= blockSize)
                {
                    //swapping
                    for (auto i = 0u; i < blockSize; i++)
                    {
                        std::swap(spacesToPart2[nextLeft + i], spacesToPart2[right - i]);
                    }
                    break;
                }
                nextLeft++;
                
                if (nextLeft >= right)
                {
                    break;
                }
            }
            
            //make sure left is optimised
            while (spacesToPart2[left] != SPACE)
            {
                left++;
                if (left == right)
                {
                    break;
                }
            }
            
            right -= blockSize;

            //should exit here
            if (left >= right)
            {
                break;
            }
        }
    }

    resultPart2 = countResult(spacesToPart2);

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example09.txt");
    Solution real("../inputs/input09.txt");

    task.endTaskAndPrintTime();
    return 0;
}