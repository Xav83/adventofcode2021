#include <array>
#include <iostream>
#include <optional>

constexpr std::array<int, 10> input = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};

void firstPart()
{
    std::optional<int> previousNumber;
    size_t numberOfIncrements{0};
    for(const auto number : input)
    {
        if(not previousNumber.has_value())
        {
            previousNumber = number;
            continue;
        }
        if(*previousNumber < number)
        {
            ++numberOfIncrements;
        }
        previousNumber = number;
    }

    std::cout << "The solution of the example for the first part is: " << numberOfIncrements << std::endl;
}

void secondPart()
{
    std::optional<int> previousSum;
    size_t numberOfIncrements{0};
    for(auto index = 0; index <= input.size() - 3 ; ++index)
    {
        const auto sum = input[index] + input[index + 1] + input[index + 2];
        if(not previousSum.has_value())
        {
            previousSum = sum;
            continue;
        }
        if(*previousSum < sum)
        {
            ++numberOfIncrements;
        }
        previousSum = sum;
    }

    std::cout << "The solution of the example for the second part is: " << numberOfIncrements << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
