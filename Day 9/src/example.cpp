#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

using Input = std::array<std::array<int, 10>, 5>;

std::vector<int> getAdjacentValuesTo(Input input, size_t x_pos, size_t y_pos) {
    std::vector<int> adjacents;

    if(x_pos != 0) { adjacents.emplace_back(input[x_pos-1][y_pos]); }
    if(y_pos != 0) { adjacents.emplace_back(input[x_pos][y_pos-1]); }
    if(x_pos != input.size()-1) { adjacents.emplace_back(input[x_pos+1][y_pos]); }
    if(y_pos != input.front().size()-1) { adjacents.emplace_back(input[x_pos][y_pos+1]); }

    return adjacents;
}

bool isLowPoint(Input input, size_t x_pos, size_t y_pos) {
    auto adjacents = getAdjacentValuesTo(input, x_pos, y_pos);

    return input[x_pos][y_pos] < *std::min_element(std::begin(adjacents), std::end(adjacents));
}

constexpr Input input {{
{2,1,9,9,9,4,3,2,1,0},
{3,9,8,7,8,9,4,9,2,1},
{9,8,5,6,7,8,9,8,9,2},
{8,7,6,7,8,9,6,7,8,9},
{9,8,9,9,9,6,5,6,7,8}
}};

void firstPart()
{
    auto sumOfRiskLevels{0};
    for(auto i=0; i<input.size(); ++i)
    {
        for(auto j=0; j<input[i].size(); ++j)
        {
            if(isLowPoint(input, i, j))
            {
                sumOfRiskLevels += input[i][j] + 1;
            }
        }
    }
    std::cout << "The solution is: " << sumOfRiskLevels << std::endl;
}

struct Position
{
    constexpr bool operator==(const Position& other) const { return x == other.x and y == other.y; }

    size_t x{0}, y{0};
};

void basinExploration(const Input& input, std::vector<Position>& alreadyVisitedPosition, const Position& currentPosition)
{
    if(std::any_of(std::begin(alreadyVisitedPosition), std::end(alreadyVisitedPosition), [&currentPosition](const auto& position){ return position == currentPosition; })
       or input[currentPosition.x][currentPosition.y] == 9)
    {
        return;
    }
    alreadyVisitedPosition.push_back(currentPosition);

    if(currentPosition.x != 0) { basinExploration(input, alreadyVisitedPosition, {currentPosition.x-1, currentPosition.y}); }
    if(currentPosition.y != 0) { basinExploration(input, alreadyVisitedPosition, {currentPosition.x, currentPosition.y-1}); }
    if(currentPosition.x != input.size()-1) { basinExploration(input, alreadyVisitedPosition, {currentPosition.x+1, currentPosition.y}); }
    if(currentPosition.y != input.front().size()-1) { basinExploration(input, alreadyVisitedPosition, {currentPosition.x, currentPosition.y+1}); }
}

int getBasinSize(const Input& input, const Position& lowPointPosition)
{
    std::vector<Position> alreadyVisitedPosition;
    basinExploration(input, alreadyVisitedPosition, {lowPointPosition.x, lowPointPosition.y});
    return alreadyVisitedPosition.size();
}

void secondPart()
{
    std::vector<int> basinSizes;
    for(size_t i=0; i<input.size(); ++i)
    {
        for(size_t j=0; j<input[i].size(); ++j)
        {
            if(isLowPoint(input, i, j))
            {
                basinSizes.emplace_back(getBasinSize(input, {i, j}));
            }
        }
    }

    std::sort(std::begin(basinSizes), std::end(basinSizes));
    const auto result = basinSizes[basinSizes.size() - 1] * basinSizes[basinSizes.size() - 2] * basinSizes[basinSizes.size() - 3];
    std::cout << "The solution is: " << result << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
