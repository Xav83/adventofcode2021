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

constexpr std::array<LanternFish, 300> input_lines {3,3,2,1,4,1,1,2,3,1,1,2,1,2,1,1,1,1,1,1,4,1,1,5,2,1,1,2,1,1,1,3,5,1,5,5,1,1,1,1,3,1,1,3,2,1,1,1,1,1,1,4,1,1,1,1,1,1,1,4,1,3,3,1,1,3,1,3,1,2,1,3,1,1,4,1,2,4,4,5,1,1,1,1,1,1,4,1,5,1,1,5,1,1,3,3,1,3,2,5,2,4,1,4,1,2,4,5,1,1,5,1,1,1,4,1,1,5,2,1,1,5,1,1,1,5,1,1,1,1,1,3,1,5,3,2,1,1,2,2,1,2,1,1,5,1,1,4,5,1,4,3,1,1,1,1,1,1,5,1,1,1,5,2,1,1,1,5,1,1,1,4,4,2,1,1,1,1,1,1,1,3,1,1,4,4,1,4,1,1,5,3,1,1,1,5,2,2,4,2,1,1,3,1,5,5,1,1,1,4,1,5,1,1,1,4,3,3,3,1,3,1,5,1,4,2,1,1,5,1,1,1,5,5,1,1,2,1,1,1,3,1,1,1,2,3,1,2,2,3,1,3,1,1,4,1,1,2,1,1,1,1,3,5,1,1,2,1,1,1,4,1,1,1,1,1,2,4,1,1,5,3,1,1,1,2,2,2,1,5,1,3,5,3,1,1,4,1,1,4};

int main()
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

    return 0;
}
