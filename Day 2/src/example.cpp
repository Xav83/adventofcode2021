#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

constexpr std::array<std::string_view, 6> input = { "forward 5", "down 5", "forward 8", "up 3", "down 8", "forward 2" };

constexpr bool isForwardInstruction (const std::string_view instruction) { return instruction.substr(0, 7) == "forward" ;}
constexpr bool isDownInstruction (const std::string_view instruction) { return instruction.substr(0, 4) == "down" ;}
constexpr bool isUpInstruction (const std::string_view instruction) { return instruction.substr(0, 2) == "up" ;}

void firstPart()
{
    size_t horizontalPosition{0}, depth{0};

    for(const auto& instruction : input)
    {
        if(isForwardInstruction(instruction)) { horizontalPosition += std::stoi(instruction.substr(8).data()); continue; }
        if(isDownInstruction(instruction)) { depth += std::stoi(instruction.substr(5).data()); continue; }
        if(isUpInstruction(instruction)) { depth -= std::stoi(instruction.substr(3).data()); continue; }
        assert(false); // Unkwnow input
    }

    std::cout << "The solution is: " << (horizontalPosition * depth) << std::endl;
}

void secondPart()
{
    size_t horizontalPosition{0}, depth{0};
    long aim{0};

    for(const auto& instruction : input)
    {
        if(isDownInstruction(instruction)) { aim += std::stoi(instruction.substr(5).data()); continue; }
        if(isUpInstruction(instruction)) { aim -= std::stoi(instruction.substr(3).data()); continue; }
        if(isForwardInstruction(instruction))
        {
            const auto units = std::stoi(instruction.substr(8).data());
            horizontalPosition += units;
            depth += units * aim;
            continue;
        }
        assert(false); // Unkwnow input
    }

    std::cout << "The solution is: " << (horizontalPosition * depth) << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
