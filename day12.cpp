#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include "geometry.hh"
#include <unordered_set>
#include <functional>

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    
    struct Node 
    {
        utils::Point p;
        char val;
        
        Node (int x, int y, char val): p{x, y}, val(val) {}
    };
    
    using resultVal = std::pair<uint32_t, uint32_t>; //area, delimeter;
    
    utils::Grid<Node> grid(lines);
    std::unordered_set<utils::Point> visitedPart1;
    std::function<resultVal(const utils::Point& p, char val)> countResultPart1 = [&visitedPart1, &grid, &countResultPart1](const utils::Point& p, char val) -> resultVal
    {
        uint32_t area = 1;
        uint32_t delimeter = 0;
        visitedPart1.insert(p);
        
        for (auto dir: utils::AllDirs)
        {
            auto newP = p + utils::dirToPointArithmetic.at(dir);
            if (grid.isPointInGrid(newP))
            {
                if (grid.getNode(newP.x, newP.y).val == val && !visitedPart1.contains(newP))
                {
                    auto [newArea, newDelimeter] = countResultPart1(newP, val);
                    area += newArea;
                    delimeter += newDelimeter;
                }
                else if (grid.getNode(newP.x, newP.y).val != val)
                {
                    delimeter++;
                }
                
            }
            else if (!grid.isPointInGrid(newP))
            {
                delimeter++;
            }
        }
        return {area, delimeter};
    };
    
    std::unordered_map<utils::Point, std::unordered_set<utils::Dir>> visitedPart2;
    std::function<resultVal(const utils::Point& p, char val)> countResultPart2 = [&visitedPart2, &grid, &countResultPart2](const utils::Point& p, char val) -> resultVal
    {
        uint32_t area = 1;
        uint32_t delimeter = 0;
        visitedPart2.insert({p, std::unordered_set<utils::Dir>{}});
        
        for (auto dir: utils::AllDirs)
        {
            auto newP = p + utils::dirToPointArithmetic.at(dir);
            if (grid.isPointInGrid(newP) && grid.getNode(newP.x, newP.y).val == val && !visitedPart2.contains(newP))
            {
                auto [newArea, newDelimeter] = countResultPart2(newP, val);
                area += newArea;
                delimeter += newDelimeter;
            }
            else if ((grid.isPointInGrid(newP) && grid.getNode(newP.x, newP.y).val != val) || !grid.isPointInGrid(newP))
            {
                visitedPart2[p].insert(dir);
                utils::Dir checkedDirs[2];
                if (dir == utils::Dir::UP || dir == utils::Dir::DOWN)
                {
                    checkedDirs[0] = utils::Dir::LEFT;
                    checkedDirs[1] = utils::Dir::RIGHT;
                }
                else
                {
                    checkedDirs[0] = utils::Dir::UP;
                    checkedDirs[1] = utils::Dir::DOWN;
                }
                bool additionalSide = true;
                auto containsNum = 0u;
                for (auto dir2: checkedDirs)
                {
                    auto newP2 = p + utils::dirToPointArithmetic.at(dir2);
                    if (grid.isPointInGrid(newP2) && grid.getNode(newP2.x, newP2.y).val == val
                        && visitedPart2.contains(newP2))
                    {
                        if (visitedPart2[newP2].contains(dir))
                        {
                            additionalSide = false;
                            containsNum++;
                        }
                    }
                }
                if (additionalSide)
                {
                    delimeter++;
                }
                if (containsNum == 2)
                {
                    delimeter--;
                }
            }
        }
        return {area, delimeter};
    };
    
    for (auto i = 0u; i < grid.maxRows; i++)
    {
        for (auto j = 0u; j < grid.maxColumns; j++)
        {
            auto p = utils::Point(j, i);
            if (!visitedPart2.contains(p))
            {
                auto [area1, delimeter1] = countResultPart1(p, grid.getNode(j, i).val);
                auto [area2, delimeter2] = countResultPart2(p, grid.getNode(j, i).val);
                // printf("Area: %d, delimeter: %d in Zone %c\n", area2, delimeter2, grid.getNode(j, i).val);
                resultPart1 += area1*delimeter1;
                resultPart2 += area2*delimeter2;
            }
        }
    }
    
    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example12.txt");
    Solution real("../inputs/input12.txt");

    task.endTaskAndPrintTime();
    return 0;
}