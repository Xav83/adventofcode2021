#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

constexpr bool isOpeningCharacter(char c)
{
    return c == '(' or c == '[' or c == '{' or c == '<';
}

constexpr char getMatchingCharacterOf(char c)
{
    if(c == '(') { return ')'; }
    if(c == ')') { return'('; }
    if(c == '[') { return ']'; }
    if(c == ']') { return '['; }
    if(c == '{') { return '}'; }
    if(c == '}') { return '{'; }
    if(c == '<') { return '>'; }
    if(c == '>') { return '<'; }
    assert(false);
    return '\0';
}

constexpr int getCharacterScoreOfCorruptedLines(char c)
{
    if(c == ')') { return 3; }
    if(c == ']') { return 57; }
    if(c == '}') { return 1197; }
    if(c == '>') { return 25137; }
    assert(false);
    return 0;
}

constexpr std::array <std::string_view, 10> input {{
"[({(<(())[]>[[{[]{<()<>>",
"[(()[<>])]({[<{<<[]>>(",
"{([(<{}[<>[]}>{[]{[(<()>",
"(((({<>}<{<{<>}{[]{[]{}",
"[[<[([]))<([[{}[[()]]]",
"[{[{({}]{}}([{[{{{}}([]",
"{<[[]]>}<{[{[{[]{()[[[]",
"[<(<(<(<{}))><([]([]()",
"<{([([[(<>()){}]>(<<{{",
"<{([{{}}[<[[[<>{}]]]>[]]"
}};

void firstPart()
{
    std::stack<char> openChunks;
    auto score{0};
    for(const auto& line : input)
    {
        for(const auto& character : line)
        {
            if(isOpeningCharacter(character))
            {
                openChunks.push(character);
                continue;
            }
            if(openChunks.top() == getMatchingCharacterOf(character))
            {
                openChunks.pop();
                continue;
            }
            score += getCharacterScoreOfCorruptedLines(character);
            break;
        }
    }

    std::cout << "The solution is: " << score << std::endl;
}

constexpr int getCharacterScoreOfIncompleteLines(char c)
{
    if(c == ')') { return 1; }
    if(c == ']') { return 2; }
    if(c == '}') { return 3; }
    if(c == '>') { return 4; }
    assert(false);
    return 0;
}

void secondPart()
{
    std::vector<int> scores;
    for(const auto& line : input)
    {
        std::stack<char> openChunks;
        bool isCorruptedLine{false};
        for(const auto& character : line)
        {
            if(isOpeningCharacter(character))
            {
                openChunks.push(character);
                continue;
            }
            if(openChunks.top() == getMatchingCharacterOf(character))
            {
                openChunks.pop();
                continue;
            }
            isCorruptedLine = true;
            break;
        }
        if(not isCorruptedLine)
        {
            auto lineScore{0};
            while (not openChunks.empty())
            {
                lineScore = lineScore * 5 + getCharacterScoreOfIncompleteLines(getMatchingCharacterOf(openChunks.top()));
                openChunks.pop();
            }
            scores.push_back(lineScore);
        }
    }
    std::sort(std::begin(scores), std::end(scores));

    std::cout << "The solution is: " << scores[scores.size() / 2] << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
