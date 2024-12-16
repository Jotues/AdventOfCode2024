#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include <unordered_set>
#include "geometry.hh"
#include <set>

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);

    struct Node
    {
        utils::Point p;
        char val;
        int cost {0};
        utils::Dir dir {utils::Dir::UP};

        Node (int x, int y, char val): p{x, y}, val(val) {}
    };

    utils::Grid<Node> grid(lines);

    //find Start
    utils::Point current{};
    for (auto i = 0u; i < grid.maxRows; i++)
    {
        for (auto j = 0u; j < grid.maxColumns; j++)
        {
            if (grid.getNode(j, i).val == 'S')
            {
                current = {j, i};
                goto startAlgorithm;
            }
        }
    }
    startAlgorithm:
    printf("Start = %d %d\n", current.x, current.y);

    std::unordered_set<utils::Point> visited;
    std::unordered_set<utils::Point> neighbours;

    auto currentDir = utils::Dir::RIGHT;

    constexpr auto TurnCost = 1000;
    auto iter = 0;
    while (true)
    {
        if (grid.getNode(current.x, current.y).val == 'E')
        {
            resultPart1 = grid.getNode(current.x, current.y).cost;
            break;
        }

        // printf("Current: %d %d, dir = %s, cost = %d\n", current.x, current.y, utils::dirToString.at(currentDir).c_str(), grid.getNode(current.x, current.y).cost);
        for (auto dir: utils::AllDirs)
        {
            visited.insert(current);

            auto newP = current + utils::dirToPointArithmetic.at(dir);
            if (grid.isPointInGrid(newP) && grid.getNode(newP.x, newP.y).val != '#' && !visited.contains(newP))
            {
                auto newCost = grid.getNode(current.x, current.y).cost + 1;
                if (currentDir != dir)
                {
                   newCost += TurnCost;
                }
                auto [_, inserted] = neighbours.insert(newP);
                if (!inserted)
                {
                    if (newCost < grid.getNode(newP.x, newP.y).cost)
                    {
                        grid.getNode(newP.x, newP.y).cost = newCost;
                        grid.getNode(newP.x, newP.y).dir = dir;
                    }
                }
                else
                {
                    grid.getNode(newP.x, newP.y).cost = newCost;
                    grid.getNode(newP.x, newP.y).dir = dir;
                }
            }
        }
        // printf("Finding lowest, size = %d, visited size = %d\n", neighbours.size(), visited.size());
        //find lowest in neighbours
        auto lowest = std::numeric_limits<int>::max();
        utils::Point lowestP{};
        for (const auto& p: neighbours)
        {
            if (grid.getNode(p.x, p.y).cost < lowest)
            {
                lowest = grid.getNode(p.x, p.y).cost;
                lowestP = p;
            }
        }

        current = lowestP;
        currentDir = grid.getNode(current.x, current.y).dir;

        neighbours.erase(current);
        iter++;
        if (iter == 20);
            // break;
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example16_1.txt");
    Solution example2("../inputs/example16_2.txt");
    Solution real("../inputs/input16.txt");

    task.endTaskAndPrintTime();
    return 0;
}