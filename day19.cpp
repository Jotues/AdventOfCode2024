#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include <unordered_set>
#include <set>

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);

    auto avaliable = utils::splitStringByDelimeter(lines[0], ", ");

    auto cmp = [](const std::string& a, const std::string& b)
    {
        return a.size() >= b.size();
    };
    std::set<std::string, decltype(cmp)> resources;

    for (auto& a: avaliable)
    {
        resources.insert(a);
    }

    std::unordered_map<std::string, uint64_t> cache;

    std::function<uint64_t(std::string_view)> findCombination =
            [&findCombination, &resources, &cache](std::string_view str) -> uint64_t
    {
        uint64_t combinations = 0;

        for (auto& towel: resources)
        {
            if (str.starts_with(towel))
            {
                auto newStr = str.substr(towel.size());
                if (newStr.empty())
                {
                    combinations++;
                }
                else
                {
                    std::string newStrStr(newStr);
                    if (cache.contains(newStrStr))
                    {
                        combinations += cache.at(newStrStr);
                    }
                    else
                    {
                        combinations += findCombination(newStr);
                    }

                }
            }
        }
        cache.insert({str.data(), combinations});
        return combinations;
    };

    for (auto i = 2lu; i < lines.size(); i++)
    {
        auto& str = lines[i];
        auto result = findCombination(str);
        if (result != 0)
        {
            resultPart1++;
        }
        resultPart2 += result;
    }
    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example19.txt");
    Solution real("../inputs/input19.txt");

    task.endTaskAndPrintTime();
    return 0;
}