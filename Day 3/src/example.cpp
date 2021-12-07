#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <string_view>

constexpr std::array<std::string_view, 12> input{"00100", "11110", "10110", "10111", "10101", "01111", "00111", "11100", "10000", "11001", "00010", "01010"};

struct Counter
{
    size_t numberOfZero{0};
    size_t numberOfOne{0};
};

int main()
{
    auto gammaRate{0}, epsilonRate{0};
    std::array<Counter, input.front().size()> counters;

    for(const auto& binary: input)
    {
        for(auto index = 0; index < binary.size(); ++index)
        {
            const auto figure = binary[index];
            if(figure == '0') { ++(counters[index].numberOfZero) ; continue; }
            if(figure == '1') { ++(counters[index].numberOfOne) ; continue; }
            assert(false); // Wrong input
        }
    }

    for(auto index = 0; index < counters.size(); ++index)
    {
        const auto& counter = counters[index];
        const auto powerOfTwo = counters.size() - 1 - index;
        if(counter.numberOfZero > counter.numberOfOne) { gammaRate += std::pow(2, powerOfTwo); continue; }
        if(counter.numberOfZero < counter.numberOfOne) { epsilonRate += std::pow(2, powerOfTwo); continue; }
        assert(false); // equality ??!!
    }

    std::cout << "The solution is: " << (gammaRate * epsilonRate) << std::endl;
    return 0;
}
