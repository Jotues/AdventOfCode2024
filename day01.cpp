#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    std::vector<int> first;
    std::vector<int> second;
    
    for (const auto& line: lines)
    {
        auto split = utils::splitStringByDelimeter(line, "  ");
        first.push_back(stoi(split[0]));
        second.push_back(stoi(split[1]));
    }

    std::ranges::sort(first);
    std::ranges::sort(second);

    for (auto i = 0; i < first.size(); i++)
    {
        resultPart1 += abs(first[i] - second[i]);
    }

    for (const auto e: first)
    {
        resultPart2 += e * std::ranges::count_if(second, [e](int secondE) { return secondE == e;});
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example01.txt");
    Solution real("../inputs/input01.txt");

    task.endTaskAndPrintTime();
    return 0;
}