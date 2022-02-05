#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

class LanternFish
{
public:
    constexpr LanternFish() = default;
    constexpr LanternFish(int timeLeftBeforeDuplicating_) : timeLeftBeforeDuplicating(timeLeftBeforeDuplicating_) {}

    constexpr void gettingOlder()
    {
        if(isGoingToDuplicate ())
        {
            timeLeftBeforeDuplicating = 6;
            return;
        }
        --timeLeftBeforeDuplicating;
    }

    constexpr bool isGoingToDuplicate () const { return timeLeftBeforeDuplicating == 0 ; }

private:
    int timeLeftBeforeDuplicating{8};
};

constexpr std::array<LanternFish, 5> input_lines {3,4,3,1,2};

int getNumberOfLanterFishToBeBorn(const std::vector<LanternFish>& fishes)
{
    return std::count_if(std::begin(fishes), std::end(fishes), [](const auto& fish){ return fish.isGoingToDuplicate(); });
}

void fishesGettingOlder (std::vector<LanternFish>& fishes)
{
    for(auto& fish : fishes)
    {
        fish.gettingOlder();
    }
}

void firstPart()
{
    std::vector<LanternFish> fishes(input_lines.begin(), input_lines.end());
    for(auto i=0; i<80; ++i)
    {
        const auto numberOfNewBorn = getNumberOfLanterFishToBeBorn(fishes);
        fishesGettingOlder(fishes);
        for(auto j=0; j<numberOfNewBorn; ++j)
        {
            fishes.emplace_back();
        }
    }

    std::cout << "The solution is: " << fishes.size() << std::endl;
}

int main()
{
    firstPart();
    return 0;
}
