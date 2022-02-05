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

constexpr std::array<LanternFish, 300> input_lines {3,3,2,1,4,1,1,2,3,1,1,2,1,2,1,1,1,1,1,1,4,1,1,5,2,1,1,2,1,1,1,3,5,1,5,5,1,1,1,1,3,1,1,3,2,1,1,1,1,1,1,4,1,1,1,1,1,1,1,4,1,3,3,1,1,3,1,3,1,2,1,3,1,1,4,1,2,4,4,5,1,1,1,1,1,1,4,1,5,1,1,5,1,1,3,3,1,3,2,5,2,4,1,4,1,2,4,5,1,1,5,1,1,1,4,1,1,5,2,1,1,5,1,1,1,5,1,1,1,1,1,3,1,5,3,2,1,1,2,2,1,2,1,1,5,1,1,4,5,1,4,3,1,1,1,1,1,1,5,1,1,1,5,2,1,1,1,5,1,1,1,4,4,2,1,1,1,1,1,1,1,3,1,1,4,4,1,4,1,1,5,3,1,1,1,5,2,2,4,2,1,1,3,1,5,5,1,1,1,4,1,5,1,1,1,4,3,3,3,1,3,1,5,1,4,2,1,1,5,1,1,1,5,5,1,1,2,1,1,1,3,1,1,1,2,3,1,2,2,3,1,3,1,1,4,1,1,2,1,1,1,1,3,5,1,1,2,1,1,1,4,1,1,1,1,1,2,4,1,1,5,3,1,1,1,2,2,2,1,5,1,3,5,3,1,1,4,1,1,4};

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

int main()
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
    return 0;
}
