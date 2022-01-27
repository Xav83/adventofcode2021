#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>

struct Point
{
    int x{0}, y{0};
};

struct Line
{
    Point start{0, 0}, end{0, 0};
};

constexpr std::array<Line, 10> input_lines
{
Line {{0,9}, {5,9}},
Line {{8,0}, {0,8}},
Line {{9,4}, {3,4}},
Line {{2,2}, {2,1}},
Line {{7,0}, {7,4}},
Line {{6,4}, {2,0}},
Line {{0,9}, {2,9}},
Line {{3,4}, {1,4}},
Line {{0,0}, {8,8}},
Line {{5,5}, {8,2}},
};

constexpr bool isVertical(const Line& line) { return line.start.y == line.end.y; }
constexpr bool isHorizontal(const Line& line) { return line.start.x == line.end.x; }
constexpr bool isDiagonal(const Line& line) { return std::abs(line.start.x - line.end.x) == std::abs(line.start.y - line.end.y); }

constexpr int getGridSize() {
    int max{0};
    for(const auto& line : input_lines)
    {
        max = std::max({max, line.start.x, line.start.y, line.end.x, line.end.y});
    }
    return max;
}

void firstPart()
{
    std::array<std::array<int, getGridSize()>, getGridSize()> grid{0};
    for(const auto& line : input_lines)
    {
        if(isVertical(line))
        {
            auto[min, max] = std::minmax(line.start.x, line.end.x);
            for(int i = min; i<= max; ++i)
            {
                ++grid[i][line.start.y];
            }
        }
        if(isHorizontal(line))
        {
            auto[min, max] = std::minmax(line.start.y, line.end.y);
            for(int i = min; i<= max; ++i)
            {
                ++grid[line.start.x][i];
            }
        }
    }

    const auto numberOfDangerousAreas = std::accumulate(std::begin(grid), std::end(grid), 0, [](const auto& sum, const auto& line){
       return sum + std::count_if(std::begin(line), std::end(line), [](const auto& point){ return point >= 2; }); 
    });
    std::cout << "The solution is: " << numberOfDangerousAreas << std::endl;
}

void secondPart()
{
    std::array<std::array<int, getGridSize()>, getGridSize()> grid{0};
    for(const auto& line : input_lines)
    {
        if(isVertical(line))
        {
            auto[min, max] = std::minmax(line.start.x, line.end.x);
            for(int i = min; i<= max; ++i)
            {
                ++grid[i][line.start.y];
            }
        }
        if(isHorizontal(line))
        {
            auto[min, max] = std::minmax(line.start.y, line.end.y);
            for(int i = min; i<= max; ++i)
            {
                ++grid[line.start.x][i];
            }
        }
        if(isDiagonal(line))
        {
            auto lineSize = std::abs(line.start.x - line.end.x);
            auto xdirection = (line.start.x - line.end.x) < 0 ? 1 : -1 ;
            auto ydirection = (line.start.y - line.end.y) < 0 ? 1 : -1 ;
            for(int i = 0; i<= lineSize; ++i)
            {
                ++grid[line.start.x + (i * xdirection)][line.start.y + (i * ydirection)];
            }
        }
    }

    const auto numberOfDangerousAreas = std::accumulate(std::begin(grid), std::end(grid), 0, [](const auto& sum, const auto& line){
       return sum + std::count_if(std::begin(line), std::end(line), [](const auto& point){ return point >= 2; }); 
    });
    std::cout << "The solution is: " << numberOfDangerousAreas << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
