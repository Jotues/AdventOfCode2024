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
        utils::Dir dir = utils::Dir::UP;

        Node (int x, int y, char val): p{x, y}, val(val) {}
    };

     utils::Grid<Node> grid(lines);

    //find Start and Stop
    utils::Point start, stop;
    for (auto i = 0u; i < grid.maxRows; i++)
    {
        for (auto j = 0u; j < grid.maxColumns; j++)
        {
            if (grid.getNode(j, i).val == 'S')
            {
                start = {j, i};
            }
            else if (grid.getNode(j, i).val == 'E')
            {
                stop = {j, i};
            }
        }
    }

    auto dijkstra = [&start, &stop](utils::Grid<Node>& grid) -> int
    {
        std::unordered_set<utils::Point> visited;
        std::unordered_set<utils::Point> neighbours;

        utils::Point current = start;

        while (true)
        {
            for (auto dir: utils::AllDirs)
            {
                visited.insert(current);

                if (current == stop)
                {
                    return grid.getNode(current.x, current.y).cost;
                }

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
    };

    std::unordered_set<utils::Point> visited;
    std::unordered_set<utils::Point> neighbours;


    utils::Point current = start;

    auto resultWithoutCheats { 0u };
    std::set<utils::Point> pathWithoutCheat;

    while (true)
    {
        for (auto dir: utils::AllDirs)
        {
            visited.insert(current);

            if (current == stop)
            {
                 resultWithoutCheats = grid.getNode(current.x, current.y).cost;
                 goto end;
            }

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

        neighbours.erase(current);

    }
    end:


    const std::map<utils::Dir, utils::Dir> opossiteDir = {{utils::Dir::UP, utils::Dir::DOWN}, {utils::Dir::DOWN, utils::Dir::UP},
                                                          {utils::Dir::LEFT, utils::Dir::RIGHT}, {utils::Dir::RIGHT, utils::Dir::LEFT}};
    while (current != start)
    {
        grid.getNode(current.x, current.y).val = 'X';
        current += utils::dirToPointArithmetic.at(opossiteDir.at(grid.getNode(current.x, current.y).dir));
        pathWithoutCheat.insert(current);
    }

    // utils::printRange(pathWithoutCheat);
    printf("Result without cheats: %d, path WithoutChehat szie = %lu\n", resultWithoutCheats, pathWithoutCheat.size());

    std::set<utils::Point> cheatChecked;
    std::map<int, int> cheatResults; //saved time, number of occurances

    int visitedCount = 0;
    auto maxVisited = visited.size();
    for (const auto& p: visited)
    {
        visitedCount++;
        if (visitedCount%100 == 0)
        {
            printf("Visited %d/%d\n", visitedCount, maxVisited);
        }

        for (auto dir : utils::AllDirs)
        {
            auto newP = p + utils::dirToPointArithmetic.at(dir);
            if (grid.isPointInGrid(newP) && grid.getNode(newP.x, newP.y).val == '#' && !cheatChecked.contains(newP))
            {
                // printf("Checking %d %d\n", newP.x, newP.y);
                auto& node = grid.getNode(newP.x, newP.y);
                node.val = '.';
                auto tryResult = dijkstra(grid);
                node.val = '#';
                cheatChecked.insert(newP);

                if (tryResult < resultWithoutCheats)
                {
                    // printf("Saved %d moves with cheat on %d %d\n", resultWithoutCheats - tryResult, newP.x, newP.y);
                    if (cheatResults.contains(resultWithoutCheats - tryResult))
                    {
                        cheatResults[resultWithoutCheats - tryResult] ++;
                    }
                    else
                    {
                        cheatResults[resultWithoutCheats - tryResult] = 1;
                    }
                    // goto end2;
                }
            }
        }
    }

    end2:
    for (auto [savedTime, occurances]: cheatResults)
    {
        if (savedTime >= 100)
        {
            resultPart1 += occurances;
        }
    }
    printResult(input);
}

int main()
{
    TaskTime task;
    // Solution example("../inputs/example20.txt");
    Solution real("../inputs/input20.txt");

    task.endTaskAndPrintTime();
    return 0;
}