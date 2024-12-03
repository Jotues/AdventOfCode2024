#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <regex>
#include <numeric>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    
    const std::regex regex1("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
    const std::regex regex2("mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\)");
    std::smatch smatch;
    
    auto calculateMulOperation = [](const std::string& sv)
    {
        auto start = sv.find('(') + 1;
        auto end = sv.find(',');
        auto first = stoul(sv.substr(start, end - start));
        start = end + 1;
        end = sv.find(')');
        auto second = stoul(sv.substr(start, end - start));
        return first * second;
    };

    auto oneLine = std::accumulate(lines.begin(), lines.end(), std::string{});
    auto line = oneLine;

    while (std::regex_search(line, smatch, regex1))
    {
        resultPart1 += calculateMulOperation(smatch[0].str());
        line = smatch.suffix().str();
    }

    line = oneLine;

    bool allowed = true;
    while (std::regex_search(line, smatch, regex2))
    {
        auto match = smatch[0].str();
        if (match == "do()")
        {
            allowed = true;
        }
        else if (match == "don't()")
        {
            allowed = false;
        }
        else if (allowed)
        {   
            resultPart2 += calculateMulOperation(match);
        }
        line = smatch.suffix().str();
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example03_2.txt");
    Solution real("../inputs/input03.txt");

    task.endTaskAndPrintTime();
    return 0;
}