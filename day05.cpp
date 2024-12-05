#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <map>
#include <set>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    
    using Data = std::map<uint16_t, std::set<uint16_t>>;

    Data data;

    size_t i = 0;
    auto line = lines[i];
    while (line !=  "") 
    {
        auto num1 = std::stoul(line.substr(0, 2));
        auto num2 = std::stoul(line.substr(3));
        printf("num1 = %u, num2 = %u\n", num1, num2);
        line = lines[++i];
        if (data.contains(num1))
        {
            data[num1].insert(num2);
        }
        else
        {
            data[num1] = std::set<uint16_t>{num2};
        }
    }

    line = lines[++i];
    auto indexForPart2 = i;
    std::set<uint16_t> goodOrderLines;

    //part 1
    while (line != "")
    {
        std::vector<uint16_t> order;
        size_t j = 0;
        bool badOrder = false;
        while (j < line.size())
        {
            auto num = std::stoul(line.substr(j, 2));
            for (const auto el: order)
            {
                if (data[num].contains(el))
                {
                    // printf("Bad order - %u should be before %u\n", num, el);
                    badOrder = true;
                    break;
                }
            }
            order.push_back(num);
            if (badOrder)
            {
                break;
            }
            j += 3;
        }
        if (!badOrder)
        {
            resultPart1 += order[(order.size() - 1)/2];
            goodOrderLines.insert(i);
        }
        line = lines[++i];
    }

    //part 2
    line = lines[indexForPart2];
    
    while (line != "")
    {
        if (goodOrderLines.contains(indexForPart2))
        {
            line = lines[++indexForPart2];
            continue;
        }

        std::vector<uint16_t> order;
        size_t j = 0;
        bool badOrder = false;
        while (j < line.size())
        {
            auto num = std::stoul(line.substr(j, 2));
            order.push_back(num);
            j += 3;
        }

        utils::printRange(order);

        //sorting
        std::ranges::sort(order, [&data](uint16_t a, uint16_t b) {
            if (data[b].contains(a))
            {
                return false;
            }
            return true;
        });
        
        resultPart2 += order[(order.size() - 1)/2];

        line = lines[++indexForPart2];
    }

    
    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example05.txt");
    Solution real("../inputs/input05.txt");

    task.endTaskAndPrintTime();
    return 0;
}