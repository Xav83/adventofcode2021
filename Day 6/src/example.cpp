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

    constexpr int getTimeLeftBeforeDuplicating () const { return timeLeftBeforeDuplicating; }

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

void secondPart_Solution1()
{
    std::array<size_t, 9> sortedFishes{0};
    for(auto i=0; i<sortedFishes.size(); ++i)
    {
        sortedFishes[i] = std::count_if(std::begin(input_lines), std::end(input_lines), [i](const auto& fish){ return fish.getTimeLeftBeforeDuplicating () == i; });
    }

    for(auto i=0; i<256; ++i)
    {
        std::array<size_t, 9> nextDaySortedFishes{0};
        nextDaySortedFishes[6] += sortedFishes.front();
        nextDaySortedFishes[8] += sortedFishes.front();
        for(auto i=1; i<sortedFishes.size(); ++i)
        {
            nextDaySortedFishes[i-1] += sortedFishes[i];
        }
        sortedFishes = nextDaySortedFishes;
    }

    const auto numberOfFishes = std::accumulate(std::begin(sortedFishes), std::end(sortedFishes), size_t{0});
    std::cout << "The solution is: " << numberOfFishes << std::endl;
}

int main()
{
    firstPart();
    secondPart_Solution1();
    return 0;
}
