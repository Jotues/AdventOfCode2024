#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include <functional>
#include <unordered_set>
#include <geometry.hh>

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    
    struct Node
    {
        utils::Point p{};
        char val;
        
        Node(int x, int y, char val): p(x, y), val(val) {};
    };
    
    utils::Grid<Node> grid(lines);
    
    std::unordered_set<utils::Point> reachablePoints;
    
    std::function<uint64_t(utils::Grid<Node>&, const utils::Point&, char)> countScores = [&countScores, &reachablePoints](utils::Grid<Node>& data, const utils::Point& p, char startC) -> uint64_t
    {
        uint64_t result = 0;
        for (const auto dir: utils::AllDirs)
        {
            const auto nextP = p + utils::dirToPointArithmetic.at(dir);
            if (data.isPointInGrid(nextP) && data.getNode(nextP.x, nextP.y).val == startC + 1)
            {
                if (startC == '8')
                {
                    reachablePoints.insert(nextP);
                    result++;
                }
                else
                {
                    result += countScores(data, nextP, startC + 1);
                }
            }
        }
        return result;
    };
    
    for (auto i=0ul; i<grid.maxRows; i++)
    {
        for (auto j=0ul; j<grid.maxColumns; j++)
        {
            if (grid.getNode(j, i).val == '0')
            {
                resultPart2 += countScores(grid, grid.getNode(j, i).p, '0');
                resultPart1 += reachablePoints.size();
                reachablePoints.clear();
            }
        }
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example10.txt");
    Solution real("../inputs/input10.txt");

    task.endTaskAndPrintTime();
    return 0;
}