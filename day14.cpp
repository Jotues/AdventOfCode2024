#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    constexpr int maxX = 101;
    constexpr int maxY = 103;
    // constexpr int maxY = 7;
    // constexpr int maxX = 11;

    struct Robot 
    {
        uint32_t x;
        uint32_t y;
        int32_t vx;
        int32_t vy;

        void interMove(int& cord, const int maxCord)
        {
            if (cord < 0)
            {
                cord = cord % maxCord;
                cord = cord + maxCord;
            }
            else if (cord >= maxCord)
            {
                cord = cord % maxCord;
            }
        }
        void move()
        {
            int newX = static_cast<int>(x) + vx;
            int newY = static_cast<int>(y) + vy;

            interMove(newX, maxX);
            interMove(newY, maxY);

            x = static_cast<uint32_t>(newX);
            y = static_cast<uint32_t>(newY);
        }

        void print() const
        {
            printf("R pos = {%u, %u}, vel = {%d %d}\n", x, y, vx, vy);
        }
    };

    auto lines = utils::getLinesOfFile(input);

    std::vector<Robot> robots;
    
    for (const auto& line: lines)
    {
        Robot r;
        r.x = stoul(line.substr(2, line.find(",")+ 1 - 2));
        r.y = stoul(line.substr(line.find(",") + 1, line.find(" ") - line.find(",")));
        r.vx = stoi(line.substr(line.find("v=") + 2, line.find_last_of(',') - line.find("v=") - 2));
        r.vy = stoi(line.substr(line.find_last_of(',') + 1));
        r.print();
        robots.push_back(r);
    }

    auto printGrid = [](const int g[maxX][maxY])
    {
        for (auto i = 0u; i< maxY; i++)
        {
           for (auto j = 0u; j< maxX; j++) 
           {
                if (g[j][i] == 0)
                {
                    printf(".");
                }
                else
                {
                    printf("%d", g[j][i]);
                }
           }
           printf("\n");
        }
    };

    auto checkTouching = [](const int g[maxX][maxY]) -> uint32_t
    {
        auto resultTouching = 0u;
        for (auto i = 0; i< maxY; i++)
        {
           for (auto j = 0; j< maxX; j++) 
           {
                if (g[j][i] == 0)
                {
                    continue;
                }
                bool touch = false;
                if (i - 1 >= 0 && g[j][i - 1] != 0) touch = true;
                else if (j - 1 >= 0 && g[j - 1][i] != 0) touch = true;
                else if (j + 1 < maxX - 1 && g[j+1][i] != 0) touch = true;
                else if (i + 1 < maxY - 1 && g[j][i+1] != 0) touch = true;

                if (touch)
                {
                    resultTouching++;
                }
           }
        }
        return resultTouching;
    };

    constexpr auto MAX_MOVES = 10000u;

    for (auto i = 0u; i < MAX_MOVES; i++)
    {
        int grid[maxX][maxY] = {0};
        for (auto& robot: robots)
        {
            robot.move();
            grid[robot.x][robot.y]++;
        }
        auto touching = checkTouching(grid);
        printf("MOVE = %d, touching = %u\n", i + 1, touching);
        if (touching >= robots.size()/2)
        {
            printGrid(grid);
            break;
        }
    }

    uint32_t quadrantResults[4] = {0};
    const uint32_t xHalf = (maxX ) / 2;
    const uint32_t yHalf = (maxY ) / 2;
    printf("%u %u\n", xHalf, yHalf);
    for (auto& robot: robots)
    {
        // robot.print();
        if (robot.x <= xHalf - 1 && robot.y <= yHalf - 1) quadrantResults[0]++;
        else if (robot.x <= xHalf -1 && robot.y >= yHalf + 1) quadrantResults[1]++;
        else if (robot.x >= xHalf + 1 && robot.y <= yHalf - 1) quadrantResults[2]++;
        else if (robot.x >= xHalf + 1 && robot.y >= yHalf + 1 )quadrantResults[3]++;
    }
    resultPart1 = quadrantResults[0] * quadrantResults[1] * quadrantResults[2] * quadrantResults[3];

    


    printResult(input);
}

int main()
{
    TaskTime task;
    // Solution example("../inputs/example14.txt");
    Solution real("../inputs/input14.txt");

    task.endTaskAndPrintTime();
    return 0;
}