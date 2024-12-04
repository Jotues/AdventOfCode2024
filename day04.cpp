#include <utils.hh>
#include <utils_time.hh>
#include <geometry.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);
    
    enum class Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        LEFT_UP,
        LEFT_DOWN,
        RIGHT_UP,
        RIGHT_DOWN,
    };
    
    using MoveFunction = std::function<utils::Point(utils::Point)>;
    
    std::map<Direction, MoveFunction> moveFunctions
    {
        {Direction::LEFT, [](utils::Point p) { return utils::Point{p.x - 1, p.y}; }},
        {Direction::RIGHT, [](utils::Point p) { return utils::Point{p.x + 1, p.y}; }},
        {Direction::UP, [](utils::Point p) { return utils::Point{p.x, p.y - 1}; }},
        {Direction::DOWN, [](utils::Point p) { return utils::Point{p.x, p.y + 1}; }},
        {Direction::LEFT_UP, [](utils::Point p) { return utils::Point{p.x - 1, p.y - 1}; }},
        {Direction::LEFT_DOWN, [](utils::Point p) { return utils::Point{p.x - 1, p.y + 1}; }},
        {Direction::RIGHT_UP, [](utils::Point p) { return utils::Point{p.x + 1, p.y - 1}; }},
        {Direction::RIGHT_DOWN, [](utils::Point p) { return utils::Point{p.x + 1, p.y + 1}; }},
    };

    constexpr char XMAS[] = { 'X', 'M', 'A', 'S' };

    struct Node
    {
        utils::Point pos;
        char val;
        
        Node(int32_t x, int32_t y, char val_): pos{utils::Point{x, y}}, val{val_} {};
    };

    utils::Grid<Node> grid(lines);

    for (auto i = 0ul; i < grid.maxRows; i++)
    {
        for (auto j = 0ul; j < grid.maxColumns; j++)
        {
            auto xmasIndex = 0ul;
            if (grid.getNode(j, i).val == XMAS[xmasIndex])
            {
                for (const auto& [dir, moveFunction]: moveFunctions)
                {
                    auto currentPos = grid.getNode(j, i).pos;
                    auto nextPos = moveFunction(currentPos);
                    xmasIndex++;
                    while (grid.isPointInGrid(nextPos) && xmasIndex < 4)
                    {
                        if (grid.getNode(nextPos.x, nextPos.y).val == XMAS[xmasIndex])
                        {
                            currentPos = nextPos;
                            nextPos = moveFunction(currentPos);
                            xmasIndex++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (xmasIndex == 4)
                    {
                        resultPart1++;
                    }
                    xmasIndex = 0;
                }
            }
        }
    }
    
    //PART 2
    auto checkBox = [](char leftUp, char rightUp, char leftDown, char rightDown) -> bool
    {
        return ((leftUp == 'M' && rightDown == 'S' && rightUp == 'M' && leftDown == 'S') ||
                (leftUp == 'S' && rightDown == 'M' && rightUp == 'M' && leftDown == 'S') ||
                (leftUp == 'M' && rightDown == 'S' && rightUp == 'S' && leftDown == 'M') ||
                (leftUp == 'S' && rightDown == 'M' && rightUp == 'S' && leftDown == 'M'));
    };
    
    for (auto i = 0ul; i < grid.maxRows; i++)
    {
        for (auto j = 0ul; j < grid.maxColumns; j++)
        {
            if (grid.getNode(j, i).val == 'A')
            {
                //get 3x3 box
                utils::Point currentPos = grid.getNode(j, i).pos;
                utils::Point leftUp = moveFunctions[Direction::LEFT_UP](currentPos);
                utils::Point rightUp = moveFunctions[Direction::RIGHT_UP](currentPos);
                utils::Point leftDown = moveFunctions[Direction::LEFT_DOWN](currentPos);
                utils::Point rightDown = moveFunctions[Direction::RIGHT_DOWN](currentPos);
                if (grid.isPointInGrid(leftUp) && grid.isPointInGrid(rightUp) && grid.isPointInGrid(leftDown) && grid.isPointInGrid(rightDown))
                {
                    if (checkBox(grid.getNode(leftUp.x, leftUp.y).val, grid.getNode(rightUp.x, rightUp.y).val, 
                                 grid.getNode(leftDown.x, leftDown.y).val, grid.getNode(rightDown.x, rightDown.y).val))
                    {
                        resultPart2++;
                    }
                }
            }
        }
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example04.txt");
    Solution real("../inputs/input04.txt");

    task.endTaskAndPrintTime();
    return 0;
}