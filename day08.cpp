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

    struct Node
    {
        utils::Point p;
        char val;

        Node(int x, int y, char c): p{x, y}, val(c) {};
    };
    
    utils::Grid<Node> grid(lines);
    std::map<char, std::vector<utils::Point>> antennas;
    std::unordered_set<utils::Point> unique;

    auto maxX = lines[0].size();
    auto maxY = lines.size();

    auto checkInBounds = [maxX, maxY](int x, int y) -> bool
    {
        if (x >= 0 && x < maxX && y >= 0 && y < maxY)
        {
            return true;
        }
        return false;
    };

    for (auto i = 0u; i < lines.size(); i++) 
    {
        auto line = lines[i];
        for (auto j = 0u; j < line.size(); j++)
        {
            auto c = line[j];
            if (c == '.')
            {
                continue;
            }
            else 
            {
                if (antennas.contains(c)) 
                {
                    antennas.at(c).emplace_back(j, i);
                }
                else
                {
                    antennas[c] = std::vector<utils::Point>{utils::Point{static_cast<int32_t>(j), static_cast<int32_t>(i)}};
                }
            }
        }
    }

    for (auto& [c, vec]: antennas)
    {
        for (auto i = 0u; i < vec.size(); i++)
        {
            auto& p1 = vec[i];

            for (auto j = i + 1; j < vec.size(); j++)
            {
                auto& p2 = vec[j];

                auto diffX = p1.x - p2.x;
                auto diffY = p1.y - p2.y;

                auto newPX = p1.x + diffX;
                auto newPY = p1.y + diffY;
                
                if (checkInBounds(newPX, newPY))
                {
                    unique.insert(utils::Point{newPX, newPY});
                }

                newPX = p2.x - diffX;
                newPY = p2.y - diffY;

                if (checkInBounds(newPX, newPY))
                {
                    unique.insert(utils::Point{newPX, newPY});
                }
            }
        }
    }
    resultPart1 = unique.size();
    unique.clear();

    for (auto& [c, vec]: antennas)
    {
        for (auto i = 0u; i < vec.size(); i++)
        {
            auto& p1 = vec[i];

            unique.insert(utils::Point{p1.x, p1.y});

            for (auto j = i + 1; j < vec.size(); j++)
            {
                auto& p2 = vec[j];
                auto diffX = p1.x - p2.x;
                auto diffY = p1.y - p2.y;

                auto newPX = p1.x + diffX;
                auto newPY = p1.y + diffY;
                
                while (checkInBounds(newPX, newPY))
                {
                    unique.insert(utils::Point{newPX, newPY});
                    newPX = newPX + diffX;
                    newPY = newPY + diffY;
                }

                newPX = p2.x - diffX;
                newPY = p2.y - diffY;

                while (checkInBounds(newPX, newPY))
                {
                    unique.insert(utils::Point{newPX, newPY});
                    newPX = newPX - diffX;
                    newPY = newPY - diffY;
                }
            }
        }
        resultPart2 = unique.size();
    }
    
    
    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example08.txt");
    Solution real("../inputs/input08.txt");

    task.endTaskAndPrintTime();
    return 0;
}