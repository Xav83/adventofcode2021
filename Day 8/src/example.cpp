#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

class SignalPattern
{
public:
    constexpr SignalPattern(std::string_view message_) : message(message_) {}

    bool operator==(const SignalPattern& other) const {
        auto messageCopy = std::string(message);
        auto otherMessageCopy = std::string(other.message);

        std::sort(std::begin(messageCopy), std::end(messageCopy));
        std::sort(std::begin(otherMessageCopy), std::end(otherMessageCopy));

        return messageCopy == otherMessageCopy;
    }

    int getNumberOfCommonSegment(const SignalPattern& other) const {
        return std::accumulate(std::begin(message), std::end(message), 0, [&other](const auto sum, const auto& c){ return sum + (other.message.find(c) != std::string_view::npos ? 1 : 0); });
    }

    constexpr bool isNumber1() const { return message.size() == 2; }
    constexpr bool isNumber4() const { return message.size() == 4; }
    constexpr bool isNumber7() const { return message.size() == 3; }
    constexpr bool isNumber8() const { return message.size() == 7; }

    constexpr bool isNumber0_6_or_9() const { return message.size() == 6; }
    constexpr bool isNumber2_3_or_5() const { return message.size() == 5; }

//private:
    std::string_view message;
};

struct Message
{
    int getNumberOf1_4_7_8_inOuputs() const {
        return std::accumulate(std::begin(outputValues), std::end(outputValues), 0, [](const auto sum, const auto& signalPattern){
            return sum + ((signalPattern.isNumber1() or signalPattern.isNumber4() or signalPattern.isNumber7() or signalPattern.isNumber8()) ? 1 : 0);
        });
    }

    void orderTestValues() {
        for(auto i=0; i<testValues.size(); ++i) {
            if(testValues[i].isNumber1()) { std::swap(testValues[i], testValues[1]); if(i < 1) { --i; } }
            else if(testValues[i].isNumber4()) { std::swap(testValues[i], testValues[4]); if(i < 4) { --i; } }
            else if(testValues[i].isNumber7()) { std::swap(testValues[i], testValues[7]); if(i < 7) { --i; } }
            else if(testValues[i].isNumber8()) { std::swap(testValues[i], testValues[8]); if(i < 8) { --i; } }
        }
        for(auto i=0; i<testValues.size(); ++i) {
            if(testValues[i].isNumber2_3_or_5()) { 
                if(testValues[i].getNumberOfCommonSegment(testValues[1]) == 2) {
                    std::swap(testValues[i], testValues[3]);
                    if(i < 3) { --i; }
                    continue;
                }
                else if(testValues[i].getNumberOfCommonSegment(testValues[4]) == 2) {
                    std::swap(testValues[i], testValues[2]);
                    if(i < 2) { --i; }
                    continue;
                }
                else {
                    std::swap(testValues[i], testValues[5]);
                    if(i < 5) { --i; }
                }
            }
        }
        for(auto i=0; i<testValues.size(); ++i) {
            if(testValues[i].isNumber0_6_or_9()) { 
                if(testValues[i].getNumberOfCommonSegment(testValues[3]) == 5) {
                    std::swap(testValues[i], testValues[9]);
                    if(i < 9) { --i; }
                    continue;
                }
                if(testValues[i].getNumberOfCommonSegment(testValues[5]) == 4) { 
                    std::swap(testValues[i], testValues[0]);
                    continue;
                }
                if(testValues[i].getNumberOfCommonSegment(testValues[1]) == 1) {
                    std::swap(testValues[i], testValues[6]);
                    if(i < 6) { --i; }
                    continue;
                }
                assert(false);
            }
        }
    }

    std::array<SignalPattern, 10> testValues;
    std::array<SignalPattern, 4> outputValues;
};

constexpr std::array<Message, 10> input {
Message {{{{"be"}, {"cfbegad"}, {"cbdgef"}, {"fgaecd"}, {"cgeb"}, {"fdcge"}, {"agebfd"}, {"fecdb"}, {"fabcd"}, {"edb"}}},{{{"fdgacbe"}, {"cefdb"}, {"cefbgd"}, {"gcbe"}}}},
Message {{{{"edbfga"}, {"begcd"}, {"cbg"}, {"gc"}, {"gcadebf"}, {"fbgde"}, {"acbgfd"}, {"abcde"}, {"gfcbed"}, {"gfec"}}},{{{"fcgedb"}, {"cgb"}, {"dgebacf"}, {"gc"}}}},
Message {{{{"fgaebd"}, {"cg"}, {"bdaec"}, {"gdafb"}, {"agbcfd"}, {"gdcbef"}, {"bgcad"}, {"gfac"}, {"gcb"}, {"cdgabef"}}},{{{"cg"}, {"cg"}, {"fdcagb"}, {"cbg"}}}},
Message {{{{"fbegcd"}, {"cbd"}, {"adcefb"}, {"dageb"}, {"afcb"}, {"bc"}, {"aefdc"}, {"ecdab"}, {"fgdeca"}, {"fcdbega"}}},{{{"efabcd"}, {"cedba"}, {"gadfec"}, {"cb"}}}},
Message {{{{"aecbfdg"}, {"fbg"}, {"gf"}, {"bafeg"}, {"dbefa"}, {"fcge"}, {"gcbea"}, {"fcaegb"}, {"dgceab"}, {"fcbdga"}}},{{{"gecf"}, {"egdcabf"}, {"bgf"}, {"bfgea"}}}},
Message {{{{"fgeab"}, {"ca"}, {"afcebg"}, {"bdacfeg"}, {"cfaedg"}, {"gcfdb"}, {"baec"}, {"bfadeg"}, {"bafgc"}, {"acf"}}},{{{"gebdcfa"}, {"ecba"}, {"ca"}, {"fadegcb"}}}},
Message {{{{"dbcfg"}, {"fgd"}, {"bdegcaf"}, {"fgec"}, {"aegbdf"}, {"ecdfab"}, {"fbedc"}, {"dacgb"}, {"gdcebf"}, {"gf"}}},{{{"cefg"}, {"dcbef"}, {"fcge"}, {"gbcadfe"}}}},
Message {{{{"bdfegc"}, {"cbegaf"}, {"gecbf"}, {"dfcage"}, {"bdacg"}, {"ed"}, {"bedf"}, {"ced"}, {"adcbefg"}, {"gebcd"}}},{{{"ed"}, {"bcgafe"}, {"cdgba"}, {"cbgef"}}}},
Message {{{{"egadfb"}, {"cdbfeg"}, {"cegd"}, {"fecab"}, {"cgb"}, {"gbdefca"}, {"cg"}, {"fgcdab"}, {"egfdb"}, {"bfceg"}}},{{{"gbdfcae"}, {"bgc"}, {"cg"}, {"cgb"}}}},
Message {{{{"gcafb"}, {"gcf"}, {"dcaebfg"}, {"ecagb"}, {"gf"}, {"abcdeg"}, {"gaef"}, {"cafbge"}, {"fdbac"}, {"fegbdc"}}},{{{"fgae"}, {"cfgab"}, {"fg"}, {"bagce"}}}}
};

void firstPart()
{
    const auto result = std::accumulate(std::begin(input), std::end(input), 0, [](const auto sum, const auto& message){
        return sum + message.getNumberOf1_4_7_8_inOuputs(); });
    std::cout << "The solution is: " << result << std::endl;
}

void secondPart()
{
    auto messages = input;
    for(auto& message : messages) { message.orderTestValues(); }

    auto result{0};
    for(const auto& message: messages) {
        std::string value;
        for(const auto& outputValue : message.outputValues) {
            auto it = std::find(std::begin(message.testValues), std::end(message.testValues), outputValue);
            assert(it != std::end(message.testValues));
            auto number = std::distance(std::begin(message.testValues), it);
            value += std::to_string(number);
        }
        result += std::stoi(value);
    }

    std::cout << "The solution is: " << result << std::endl;
}

int main()
{
    firstPart();
    secondPart();
    return 0;
}
