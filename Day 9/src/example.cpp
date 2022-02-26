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

int main()
{
    firstPart();
    return 0;
}
