#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include "geometry.hh"
#include <unordered_set>
#include <set>

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);

    struct Node
    {
        utils::Point p{};
        char val;
        
        Node(int x, int y, char c): p{x, y}, val{c} {};
    };

    const std::map<utils::Dir, utils::Dir> dirChange {
        {utils::Dir::UP, utils::Dir::RIGHT},
        {utils::Dir::RIGHT, utils::Dir::DOWN},
        {utils::Dir::DOWN, utils::Dir::LEFT},
        {utils::Dir::LEFT, utils::Dir::UP}
    };

    utils::Grid<Node> grid(lines);
    utils::Point start {};

    bool startFound { false };
    for (auto i = 0u; i < grid.maxRows; i++)
    {
        for (auto j = 0u; j < grid.maxColumns; j++)
        {
            if (grid.getNode(j, i).val == '^')
            {
                start.x = j;
                start.y = i;
                startFound = true;
                break;
            }
        }
        if (startFound)
        {
            break;
        }
    }

    //part 1
    utils::Point current = start;
    utils::Dir dir = utils::Dir::UP;
    std::unordered_set<utils::Point> visited;
    while (true)
    {
        visited.insert(current);
        auto nextPoint = current + utils::dirToPointArithmetic.at(dir);
        if (!grid.isPointInGrid(nextPoint))
        {
            break;
        }
        while (grid.getNode(nextPoint.x, nextPoint.y).val == '#')
        {
            dir = dirChange.at(dir);
            nextPoint = current + utils::dirToPointArithmetic.at(dir);
        }
        current = nextPoint;
    }
    resultPart1 = visited.size();

    //part 2
    for (auto& pt: visited)
    {
        grid.getNode(pt.x, pt.y).val = '#';

        current = start;
        utils::Dir dir = utils::Dir::UP;
        std:set<std::pair<utils::Point, utils::Dir>> changesMade;
        while (true)
        {
            bool dirChanged = false;
            auto nextPoint = current + utils::dirToPointArithmetic.at(dir);
            if (!grid.isPointInGrid(nextPoint))
            {
                break;
            }
            while (grid.getNode(nextPoint.x, nextPoint.y).val == '#')
            {
                dir = dirChange.at(dir);
                nextPoint = current + utils::dirToPointArithmetic.at(dir);
                dirChanged = true;
            }

            if (dirChanged)
            {
                auto change = std::make_pair<utils::Point, utils::Dir>(utils::Point{current.x, current.y}, utils::Dir{dir});
                auto [_, inserted] = changesMade.insert(change);
                if (!inserted)
                {
                    resultPart2++;
                    break;
                }
            }
            current = nextPoint;
        }
        grid.getNode(pt.x, pt.y).val = '.';
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example06.txt");
    Solution real("../inputs/input06.txt");

    task.endTaskAndPrintTime();
    return 0;
}