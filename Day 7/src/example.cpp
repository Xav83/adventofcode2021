#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

using HorizontalPosition = int;

class Crab
{
public:
    Crab(HorizontalPosition initialPosition_) : initialPosition(initialPosition_) {}

    int howFarFrom(HorizontalPosition otherPosition) const { return std::abs(initialPosition - otherPosition); }
    int howFarFrom_2(HorizontalPosition otherPosition) const
    {
        auto totalFuel{0};
        auto rawDistance = howFarFrom(otherPosition);
        for(auto i=rawDistance; i>0; --i)
        {
            totalFuel += i;
        }
        return totalFuel;
    }

    int getPosition() const { return initialPosition; }

    bool operator<(const Crab& other) const { return initialPosition < other.initialPosition; }

private:
    HorizontalPosition initialPosition{0};
};

const std::array<Crab, 10> input_crab_position {16,1,2,0,4,2,7,1,2,14};

void firstPart()
{
    auto [min, max] = std::minmax_element(std::begin(input_crab_position), std::end(input_crab_position));
    auto minimumFuelFound = std::numeric_limits<int>::max();
    for(auto potentialBestPosition=min->getPosition(); potentialBestPosition<max->getPosition(); ++potentialBestPosition)
    {
        auto fuelUsed = std::accumulate(std::begin(input_crab_position), std::end(input_crab_position), 0,
                                        [&potentialBestPosition](const auto& sum, const auto& crab){ return sum + crab.howFarFrom(potentialBestPosition); });
        minimumFuelFound = std::min(minimumFuelFound, fuelUsed);
    }

    std::cout << "The solution is: " << minimumFuelFound << std::endl;
}

void secondPart()
{
    auto [min, max] = std::minmax_element(std::begin(input_crab_position), std::end(input_crab_position));
    auto minimumFuelFound = std::numeric_limits<int>::max();
    for(auto potentialBestPosition=min->getPosition(); potentialBestPosition<max->getPosition(); ++potentialBestPosition)
    {
        auto fuelUsed = std::accumulate(std::begin(input_crab_position), std::end(input_crab_position), 0,
                                        [&potentialBestPosition](const auto& sum, const auto& crab){ return sum + crab.howFarFrom_2(potentialBestPosition); });
        minimumFuelFound = std::min(minimumFuelFound, fuelUsed);
    }

    std::cout << "The solution is: " << minimumFuelFound << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
