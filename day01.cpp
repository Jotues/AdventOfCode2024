#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    
    for (const auto& line: lines)
    {

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