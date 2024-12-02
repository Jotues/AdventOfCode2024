#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <optional>
#include "Solution.hh"

using namespace std;

bool checkNumbers(std::vector<std::string>& numbers)
{
    auto previous = stoul(numbers[0]);
    std::optional<bool> isIncreasing;
    auto safe = true;
    for (size_t i = 1; i < numbers.size(); i++)
    {
        auto current = stoul(numbers[i]);
        if (!isIncreasing.has_value())
        {
            isIncreasing = previous < current;
        }

        if ((isIncreasing == true  && (current - previous) >= 1 && (current - previous) <= 3)  ||
            (isIncreasing == false && (previous - current) >= 1 && (previous - current) <= 3))
        {
            previous = current;
            continue;
        }
        else
        {
            safe = false;
            break;
        }
    }
    return safe;
}

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);

    for (const auto& line: lines)
    {
        auto numbers = utils::splitStringByDelimeter(line, " ");
        if (checkNumbers(numbers))
        {
            resultPart1++;
            resultPart2++;
        }
        else
        {
            for (size_t i = 0; i < numbers.size(); i++)
            {
                auto copyVec = numbers;
                copyVec.erase(copyVec.begin() + i);
                if (checkNumbers(copyVec))
                {
                    resultPart2++;
                    break;
                }
            }
        }
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example02.txt");
    Solution real("../inputs/input02.txt");

    task.endTaskAndPrintTime();
    return 0;
}