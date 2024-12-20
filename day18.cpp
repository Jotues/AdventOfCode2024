#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include "geometry.hh"
#include <unordered_set>

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);

    constexpr auto maxSize = 70ul;

    struct Node
    {
        utils::Point p;
        char val {'.'};
        uint32_t cost {0};

        Node(int32_t x, int32_t y): p{x, y} {}
    };

    utils::Grid<Node> grid(maxSize + 1 , maxSize + 1);

    auto maxBytes = 1024;

    auto clearGrid = [&grid]()
    {
        for (auto i = 0ul; i < grid.maxRows; i++)
        {
            for (auto j = 0ul; j < grid.maxColumns; j++)
            {
                auto& node = grid.getNode(j, i);
                node.cost = 0;
                node.val = '.';
            }
        }
    };

    while (true)
    {
        auto i = 0;
        utils::Point loadingByte;
        for (const auto& line: lines)
        {
            if (i == maxBytes)
            {
                break;
            }
            loadingByte = {stoi(line.substr(0, line.find(","))), stoi(line.substr(line.find(',') + 1))};
            grid.getNode(loadingByte.x, loadingByte.y).val = '#';
            i++;
        }

        std::unordered_set<utils::Point> visited;
        std::unordered_set<utils::Point> neighbours;

        utils::Point current{0, 0};

        while (true)
        {
            if (current.x == maxSize && current.y == maxSize)
            {
                resultPart1 = grid.getNode(current.x, current.y).cost;
                break;
            }

            for (auto dir: utils::AllDirs)
            {
                visited.insert(current);

                auto newP = current + utils::dirToPointArithmetic.at(dir);
                if (grid.isPointInGrid(newP) && grid.getNode(newP.x, newP.y).val != '#' && !visited.contains(newP))
                {
                    auto newCost = grid.getNode(current.x, current.y).cost + 1;

                    auto [_, inserted] = neighbours.insert(newP);
                    if (!inserted)
                    {
                        if (newCost < grid.getNode(newP.x, newP.y).cost)
                        {
                            grid.getNode(newP.x, newP.y).cost = newCost;
                        }
                    }
                    else
                    {
                        grid.getNode(newP.x, newP.y).cost = newCost;
                    }
                }
            }

            //find lowest in neighbours
            auto lowest = std::numeric_limits<int>::max();
            utils::Point lowestP{};

            if (neighbours.empty())
            {
                printf("ENDING loadingByte = {%d, %d}\n", loadingByte.x, loadingByte.y);
                goto end;
            }

            for (const auto& p: neighbours)
            {
                if (grid.getNode(p.x, p.y).cost < lowest)
                {
                    lowest = grid.getNode(p.x, p.y).cost;
                    lowestP = p;
                }
            }

            current = lowestP;

            neighbours.erase(current);

        }
        maxBytes++;
        clearGrid();
    }
end:
    ;
}

int main()
{
    TaskTime task;
    // Solution example("../inputs/example18.txt");
    Solution real("../inputs/input18.txt");

    task.endTaskAndPrintTime();
    return 0;
}