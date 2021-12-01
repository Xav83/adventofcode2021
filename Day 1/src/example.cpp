#include <array>
#include <iostream>
#include <optional>

constexpr std::array<int, 10> input = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};

int main()
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

    std::cout << "The solution is: " << numberOfIncrements << std::endl;
    return 0;
}
