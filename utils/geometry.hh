#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <vector>
#include <map>

namespace utils
{
    struct Point
    {
        int32_t x = 0;
        int32_t y = 0;

        friend std::ostream& operator<<(std::ostream& os, const Point& pt);
        Point operator+(const Point& pt) const;
        Point& operator+=(const Point& pt);
        Point operator*(const int32_t val) const;
        Point& operator*=(const int32_t val);
        auto operator<=>(const Point&) const = default;
    };

    template <typename T>
    struct Node
    {
        Point pos;
        T val;

    };

    template <typename TNode>
    concept NodeFromChar = requires(TNode node)
    {
        { node(int32_t(), int32_t(), char()) } -> std::same_as<TNode>;
    };

    template <typename NodeFromChar>
    struct Grid
    {
        std::vector<std::vector<NodeFromChar>> grid {};

        size_t maxRows {0ul};
        size_t maxColumns {0ul};

        Grid(const std::vector<std::string>& data)
        {
            maxRows = data.size();
            maxColumns = data[0].size();

            for (auto i = 0ul; i < maxRows; i++)
            {
                grid.push_back(std::vector<NodeFromChar>{});
                for (auto j = 0ul; j < maxColumns; j++)
                {
                    grid[i].push_back(NodeFromChar(static_cast<int32_t>(j), static_cast<int32_t>(i), data[i][j]));
                }
            } 
        }

        NodeFromChar& getNode(const size_t x, const size_t y) { return grid[y][x]; }
        // Point& getPoint(const size_t x, const size_t y) { return grid[y][x].pos; }
        // T getVal(const size_t x, const size_t y) { return grid[y][x].val; }
        bool isPointInGrid(const Point&& p) { return (p.x >= 0 && p.x < maxColumns && p.y >= 0 && p.y < maxRows); }
        bool isPointInGrid(const Point& p) { return (p.x >= 0 && p.x < maxColumns && p.y >= 0 && p.y < maxRows); }
    };

    enum class Dir
    {
        UP,
        DOWN,
        RIGHT,
        LEFT,
    };

    const std::map<Dir, Point> dirToPointArithmetic
    {
        {Dir::UP, Point {.x = 0, .y = -1}},
        {Dir::LEFT, Point {.x = -1, .y = 0}},
        {Dir::DOWN, Point {.x = 0, .y = 1}},
        {Dir::RIGHT, Point {.x = 1, .y = 0}},
    };

    constexpr std::array<Dir, 4> AllDirs = {Dir::UP, Dir::DOWN, Dir::LEFT, Dir::RIGHT};
    
    const std::map<Dir, std::string> dirToString
    {
        {Dir::UP, "UP"},
        {Dir::DOWN, "DOWN"},
        {Dir::LEFT, "LEFT"},
        {Dir::RIGHT, "RIGHT"},
    };
}

template<>
struct std::hash<utils::Point> 
{
    size_t operator() (const utils::Point& pt) const
    {
        return hash<int32_t>{}(pt.x) ^ hash<int32_t>{}(pt.y);
    }
};
