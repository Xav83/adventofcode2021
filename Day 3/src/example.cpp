#include <algorithm>
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

void firstPart()
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
}

size_t binaryToDecimal(const std::string_view binary)
{
    auto decimalNumber{0};
    for(auto index = 0; index < binary.size(); ++index)
    {
        const auto& figure = binary[index];
        const auto powerOfTwo = binary.size() - 1 - index;
        if(figure == '1') { decimalNumber += std::pow(2, powerOfTwo); continue; }
    }
    return decimalNumber;
}

void secondPart()
{
    size_t oxygenGeneratorRating{0}, co2ScrubberRating{0};

    std::vector<std::string_view> potentialsOxygenGeneratorRating(input.begin(), input.end());
    std::vector<std::string_view> potentialsCo2ScrubberRating(input.begin(), input.end());

    for(auto index = 0; index < input.front().size(); ++index)
    {
        Counter co2Counter, o2Counter;
        for(const auto& binary: potentialsCo2ScrubberRating)
        {
            const auto figure = binary[index];
            if(figure == '0') { ++(co2Counter.numberOfZero) ; continue; }
            if(figure == '1') { ++(co2Counter.numberOfOne) ; continue; }
            assert(false); // Wrong input
        }

        for(const auto& binary: potentialsOxygenGeneratorRating)
        {
            const auto figure = binary[index];
            if(figure == '0') { ++(o2Counter.numberOfZero) ; continue; }
            if(figure == '1') { ++(o2Counter.numberOfOne) ; continue; }
            assert(false); // Wrong input
        }

        if(potentialsCo2ScrubberRating.size() != 1)
        {
            if(co2Counter.numberOfZero > co2Counter.numberOfOne)
            {
                /* removes the binaries with a 0 in this position for CO2 */
                potentialsCo2ScrubberRating.erase(std::remove_if(potentialsCo2ScrubberRating.begin(), potentialsCo2ScrubberRating.end(),
                                                                    [index](const auto& binary){ return binary[index] == '0'; }),
                                                    potentialsCo2ScrubberRating.end());
            }
            else
            {
                /* removes the binaries with a 1 in this position for CO2 */
                potentialsCo2ScrubberRating.erase(std::remove_if(potentialsCo2ScrubberRating.begin(), potentialsCo2ScrubberRating.end(),
                                                                    [index](const auto& binary){ return binary[index] == '1'; }),
                                                    potentialsCo2ScrubberRating.end());
            }
        }

        if(potentialsOxygenGeneratorRating.size() != 1)
        {
            if(o2Counter.numberOfZero > o2Counter.numberOfOne)
            {
                /* removes the binaries with a 1 in this position for O2 */
                potentialsOxygenGeneratorRating.erase(std::remove_if(potentialsOxygenGeneratorRating.begin(), potentialsOxygenGeneratorRating.end(),
                                                                    [index](const auto& binary){ return binary[index] == '1'; }),
                                                    potentialsOxygenGeneratorRating.end());
            }
            else
            {
                /* removes the binaries with a 0 in this position for O2 */
                potentialsOxygenGeneratorRating.erase(std::remove_if(potentialsOxygenGeneratorRating.begin(), potentialsOxygenGeneratorRating.end(),
                                                                    [index](const auto& binary){ return binary[index] == '0'; }),
                                                    potentialsOxygenGeneratorRating.end());
            }
        }
    }

    assert(potentialsCo2ScrubberRating.size() == 1);
    assert(potentialsOxygenGeneratorRating.size() == 1);

    oxygenGeneratorRating = binaryToDecimal(potentialsOxygenGeneratorRating.front());
    co2ScrubberRating = binaryToDecimal(potentialsCo2ScrubberRating.front());

    std::cout << "The solution is: " << (oxygenGeneratorRating * co2ScrubberRating) << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
