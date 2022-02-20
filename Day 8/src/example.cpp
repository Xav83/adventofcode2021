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

    constexpr bool isNumber1() const { return message.size() == 2; }
    constexpr bool isNumber4() const { return message.size() == 4; }
    constexpr bool isNumber7() const { return message.size() == 3; }
    constexpr bool isNumber8() const { return message.size() == 7; }

private:
    std::string_view message;
};

struct Message
{
    int getNumberOf1_4_7_8_inOuputs() const {
        return std::accumulate(std::begin(ouputValues), std::end(ouputValues), 0, [](const auto sum, const auto& signalPattern){
            return sum + ((signalPattern.isNumber1() or signalPattern.isNumber4() or signalPattern.isNumber7() or signalPattern.isNumber8()) ? 1 : 0);
        });
    }

    std::array<SignalPattern, 10> testValues;
    std::array<SignalPattern, 4> ouputValues;
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

int main()
{
    firstPart();
    return 0;
}
