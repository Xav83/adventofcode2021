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

private:
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

constexpr std::array<Message, 200> input {
Message {{{{"dbc"}, {"gfecab"}, {"afcdg"}, {"dfebcag"}, {"bd"}, {"dgbe"}, {"bcaeg"}, {"dcefab"}, {"ecgadb"}, {"agcbd"}}},{{{"acdgb"}, {"gbcda"}, {"gdecfba"}, {"bacge"}}}},
Message {{{{"bacdegf"}, {"aefbdc"}, {"ebf"}, {"fdbcag"}, {"edbfa"}, {"gdaeb"}, {"acfdb"}, {"cdegbf"}, {"face"}, {"fe"}}},{{{"ebf"}, {"ecdabf"}, {"fcbad"}, {"afcdbg"}}}},
Message {{{{"cabgde"}, {"gd"}, {"becgfd"}, {"dgfe"}, {"cebgf"}, {"gfdeacb"}, {"fdbac"}, {"bcgaef"}, {"bgdfc"}, {"gdc"}}},{{{"cbfad"}, {"dg"}, {"dgef"}, {"ecfbdg"}}}},
Message {{{{"adecgf"}, {"egfdc"}, {"cgeadb"}, {"adbfce"}, {"dafg"}, {"bcfeg"}, {"dge"}, {"dg"}, {"fadec"}, {"dcbegaf"}}},{{{"dg"}, {"dcegf"}, {"cdgafe"}, {"gbacfed"}}}},
Message {{{{"badeg"}, {"gdbfcea"}, {"acgef"}, {"fgdc"}, {"bgcaef"}, {"cd"}, {"ebcfda"}, {"gadce"}, {"edcgaf"}, {"edc"}}},{{{"dce"}, {"efcga"}, {"dbgea"}, {"dc"}}}},
Message {{{{"bgfec"}, {"dbfgec"}, {"ebgafc"}, {"afegcdb"}, {"fca"}, {"af"}, {"cgdabf"}, {"aegf"}, {"badce"}, {"cfabe"}}},{{{"caf"}, {"ebacf"}, {"bafgec"}, {"cbfeag"}}}},
Message {{{{"begacd"}, {"bd"}, {"cfadbeg"}, {"fbecg"}, {"begfd"}, {"bgd"}, {"cdfeag"}, {"gbaedf"}, {"fdba"}, {"agefd"}}},{{{"cbgfe"}, {"fdab"}, {"efbdg"}, {"bd"}}}},
Message {{{{"bg"}, {"gfdebc"}, {"beg"}, {"gabd"}, {"fcbae"}, {"fgaeb"}, {"afegd"}, {"gafdce"}, {"dacbfge"}, {"efgbda"}}},{{{"gdba"}, {"dfgae"}, {"dgba"}, {"gb"}}}},
Message {{{{"cfd"}, {"edcfbg"}, {"abfcg"}, {"gfdcb"}, {"gbcefda"}, {"dgcbe"}, {"defg"}, {"df"}, {"acebfd"}, {"caedbg"}}},{{{"agedcbf"}, {"dgbfaec"}, {"gbfecd"}, {"cdf"}}}},
Message {{{{"bdcag"}, {"acgebfd"}, {"eac"}, {"ae"}, {"bade"}, {"abcdgf"}, {"bdacge"}, {"bcgea"}, {"aedgcf"}, {"efcbg"}}},{{{"cfdagb"}, {"degacb"}, {"eac"}, {"edab"}}}},
Message {{{{"ga"}, {"ebcadgf"}, {"gdaf"}, {"bga"}, {"fgecb"}, {"dfabcg"}, {"adcfb"}, {"gadecb"}, {"fecdab"}, {"gbacf"}}},{{{"fgda"}, {"gdaf"}, {"agb"}, {"gfda"}}}},
Message {{{{"gbcdaf"}, {"fabdceg"}, {"gbe"}, {"ebfgad"}, {"bfdga"}, {"eg"}, {"cefabg"}, {"fdge"}, {"adegb"}, {"cedba"}}},{{{"ge"}, {"fcaedbg"}, {"ebg"}, {"aecbdfg"}}}},
Message {{{{"ab"}, {"bdeag"}, {"gbdefc"}, {"cgafdb"}, {"fgedb"}, {"agb"}, {"befa"}, {"bagfdec"}, {"ecgda"}, {"agfedb"}}},{{{"ab"}, {"aefb"}, {"abg"}, {"ab"}}}},
Message {{{{"fgceab"}, {"fcgdb"}, {"fdcebg"}, {"cbf"}, {"gafbd"}, {"cegfd"}, {"bced"}, {"cb"}, {"cadfge"}, {"cbdgafe"}}},{{{"ecbagf"}, {"cbfdeg"}, {"cb"}, {"bc"}}}},
Message {{{{"fgb"}, {"eafdgcb"}, {"cefg"}, {"ebdgac"}, {"fcbged"}, {"fbade"}, {"fg"}, {"gbfed"}, {"gbecd"}, {"fcabdg"}}},{{{"fg"}, {"eadfcgb"}, {"fgcbda"}, {"gedcb"}}}},
Message {{{{"ecgfda"}, {"faebc"}, {"cb"}, {"fadeb"}, {"adecbg"}, {"edfgabc"}, {"bfgc"}, {"cab"}, {"gecaf"}, {"ecbfag"}}},{{{"fcgb"}, {"bca"}, {"gbcf"}, {"cgbf"}}}},
Message {{{{"gfaed"}, {"cg"}, {"cgab"}, {"abdcf"}, {"fabcgd"}, {"gcfda"}, {"fgc"}, {"fdgacbe"}, {"cbdaef"}, {"fcebdg"}}},{{{"fgc"}, {"cfdageb"}, {"cbfgad"}, {"degfa"}}}},
Message {{{{"fbacd"}, {"gedfac"}, {"fadegbc"}, {"gbf"}, {"degb"}, {"ecgdf"}, {"gb"}, {"bdecfg"}, {"gcdbf"}, {"efbcag"}}},{{{"cgedfb"}, {"gb"}, {"bcdfa"}, {"cfdagbe"}}}},
Message {{{{"dceg"}, {"deacbg"}, {"acfbeg"}, {"egdafbc"}, {"ebfda"}, {"dc"}, {"bcd"}, {"cgabe"}, {"gbdafc"}, {"dbace"}}},{{{"cged"}, {"fabegc"}, {"febad"}, {"ebgcfa"}}}},
Message {{{{"gbdcae"}, {"cfgade"}, {"dc"}, {"dgbface"}, {"fdage"}, {"cbgfa"}, {"adc"}, {"gdafc"}, {"dcfe"}, {"gbdaef"}}},{{{"fedc"}, {"adgcf"}, {"fcde"}, {"dgacbfe"}}}},
Message {{{{"afdgbe"}, {"cgfabe"}, {"dcgeab"}, {"aef"}, {"feacb"}, {"fbgcade"}, {"bgace"}, {"cgef"}, {"bcafd"}, {"fe"}}},{{{"ebacf"}, {"abfdegc"}, {"dbfac"}, {"facgeb"}}}},
Message {{{{"fbeg"}, {"dgfecba"}, {"cfgabd"}, {"eafcb"}, {"gb"}, {"edacg"}, {"gecfab"}, {"aebcdf"}, {"ebcag"}, {"gcb"}}},{{{"cfadeb"}, {"gecda"}, {"bg"}, {"gb"}}}},
Message {{{{"bfcaeg"}, {"gd"}, {"fbagc"}, {"fgad"}, {"fgcaedb"}, {"fdgbac"}, {"cdaeb"}, {"dgfecb"}, {"cagdb"}, {"bdg"}}},{{{"cbfgda"}, {"dg"}, {"afcedgb"}, {"egfacb"}}}},
Message {{{{"gd"}, {"dcafgb"}, {"dacfbe"}, {"edbgacf"}, {"gfbdc"}, {"fbceg"}, {"dbg"}, {"dfag"}, {"bdfca"}, {"begdac"}}},{{{"aecfdb"}, {"eagdcfb"}, {"fdcbgea"}, {"fgdbc"}}}},
Message {{{{"gf"}, {"dfgc"}, {"ebfgac"}, {"bfdace"}, {"gabfd"}, {"adgfbc"}, {"acbfd"}, {"ecfagbd"}, {"bgf"}, {"aedgb"}}},{{{"dfgc"}, {"fdcg"}, {"gfb"}, {"gbf"}}}},
Message {{{{"gbdae"}, {"ebadf"}, {"dbcfag"}, {"acfdb"}, {"dfec"}, {"feacdbg"}, {"geafcb"}, {"dcbafe"}, {"fe"}, {"fae"}}},{{{"efa"}, {"bdcfa"}, {"eaf"}, {"debacgf"}}}},
Message {{{{"deafgc"}, {"fbgedca"}, {"gfd"}, {"dcga"}, {"dcgbef"}, {"aecfg"}, {"dg"}, {"agfebc"}, {"adgfe"}, {"dfabe"}}},{{{"dgf"}, {"badgcef"}, {"fgace"}, {"cabefgd"}}}},
Message {{{{"badcg"}, {"bagdce"}, {"bdafgce"}, {"efgbc"}, {"df"}, {"cbgfda"}, {"cfdbg"}, {"edgfac"}, {"fgd"}, {"adbf"}}},{{{"dfcbg"}, {"df"}, {"cgbdae"}, {"bdfgc"}}}},
Message {{{{"dgabe"}, {"beagc"}, {"gbd"}, {"gfcbdae"}, {"gd"}, {"bdegfa"}, {"bgfedc"}, {"fbcdae"}, {"bafde"}, {"fagd"}}},{{{"bcdfge"}, {"bgd"}, {"bcage"}, {"dfga"}}}},
Message {{{{"adgf"}, {"adgfce"}, {"aecfg"}, {"cdega"}, {"dbgaecf"}, {"abcgfe"}, {"egd"}, {"egcdfb"}, {"dg"}, {"deabc"}}},{{{"cdgae"}, {"dafg"}, {"dfag"}, {"afdg"}}}},
Message {{{{"fbadec"}, {"afcbg"}, {"begac"}, {"be"}, {"ebcgda"}, {"dceag"}, {"edgb"}, {"efdcga"}, {"ebdacgf"}, {"cbe"}}},{{{"adfcebg"}, {"ecafbd"}, {"debgac"}, {"edcafg"}}}},
Message {{{{"cbd"}, {"dcga"}, {"cagbf"}, {"dcafb"}, {"cd"}, {"cdebfg"}, {"dgafcb"}, {"baefd"}, {"cbfaeg"}, {"cfdgeab"}}},{{{"fcdab"}, {"geacbf"}, {"gfbdce"}, {"dgcafb"}}}},
Message {{{{"becd"}, {"abfdc"}, {"cgbaf"}, {"efcda"}, {"bd"}, {"ebdcaf"}, {"gdfaceb"}, {"bdf"}, {"bdgeaf"}, {"cedfga"}}},{{{"ebdc"}, {"fbd"}, {"bdf"}, {"fbgdae"}}}},
Message {{{{"gefacd"}, {"adcg"}, {"fedbc"}, {"cdgfe"}, {"egd"}, {"dg"}, {"dbfega"}, {"cgbfeda"}, {"aecfg"}, {"bcefga"}}},{{{"defbcga"}, {"efcga"}, {"afgced"}, {"gdecf"}}}},
Message {{{{"gfacbd"}, {"fbcgde"}, {"cefba"}, {"efdcga"}, {"bfgcead"}, {"egcdf"}, {"gfb"}, {"gcfbe"}, {"bg"}, {"edgb"}}},{{{"gb"}, {"fdegc"}, {"gfb"}, {"fgb"}}}},
Message {{{{"ag"}, {"agfdcb"}, {"egfad"}, {"fag"}, {"adefb"}, {"fdgec"}, {"bdfgcae"}, {"acfegd"}, {"gebfdc"}, {"aecg"}}},{{{"fga"}, {"ag"}, {"egafd"}, {"fcgebd"}}}},
Message {{{{"cadgbf"}, {"cd"}, {"gefbac"}, {"cdfba"}, {"fbead"}, {"cedagb"}, {"gdcf"}, {"adc"}, {"gacbf"}, {"fgebcda"}}},{{{"gcbafd"}, {"bdcaf"}, {"gfcd"}, {"abdfe"}}}},
Message {{{{"fgebda"}, {"fd"}, {"afceb"}, {"fcdeb"}, {"fcad"}, {"cgbed"}, {"gabfcde"}, {"dcabfe"}, {"def"}, {"befagc"}}},{{{"eacfb"}, {"efd"}, {"efagcb"}, {"def"}}}},
Message {{{{"beaf"}, {"gfcaebd"}, {"fdeag"}, {"dae"}, {"acdgeb"}, {"gcdfa"}, {"dgabef"}, {"gbedf"}, {"ea"}, {"dcbgef"}}},{{{"ae"}, {"aed"}, {"ae"}, {"ade"}}}},
Message {{{{"gb"}, {"dgeca"}, {"gecab"}, {"gcdfaeb"}, {"ceafb"}, {"bgc"}, {"fagb"}, {"adfceb"}, {"baegcf"}, {"gebfdc"}}},{{{"fgba"}, {"bg"}, {"fecgab"}, {"bg"}}}},
Message {{{{"daf"}, {"gbfda"}, {"afcedg"}, {"geadfb"}, {"fbcdg"}, {"fgaebc"}, {"ad"}, {"dbagefc"}, {"dbae"}, {"aebgf"}}},{{{"aebd"}, {"eadcbgf"}, {"dfa"}, {"beda"}}}},
Message {{{{"dcbaef"}, {"cabfd"}, {"efgcba"}, {"cbdgfa"}, {"aedfg"}, {"abecfdg"}, {"ace"}, {"cbde"}, {"dfcae"}, {"ce"}}},{{{"cbefag"}, {"ebcd"}, {"cdabgf"}, {"cbfda"}}}},
Message {{{{"bcgefa"}, {"bgfcead"}, {"cd"}, {"fcbadg"}, {"bdcga"}, {"dac"}, {"gbaed"}, {"gafdce"}, {"cfbd"}, {"bcagf"}}},{{{"cbfag"}, {"acd"}, {"cfbd"}, {"bdfc"}}}},
Message {{{{"dgfcb"}, {"aebgd"}, {"gadefc"}, {"bgfdec"}, {"cbafgd"}, {"cgbad"}, {"egbdafc"}, {"ac"}, {"acbf"}, {"cga"}}},{{{"ca"}, {"ac"}, {"cabf"}, {"abcf"}}}},
Message {{{{"cgaed"}, {"gafbdec"}, {"fgaedc"}, {"ba"}, {"baegcd"}, {"edfbg"}, {"agcb"}, {"bcdeaf"}, {"ebdag"}, {"bea"}}},{{{"gfceda"}, {"ecabfgd"}, {"defgacb"}, {"aeb"}}}},
Message {{{{"cbfag"}, {"cgdaf"}, {"dcefab"}, {"bac"}, {"ba"}, {"bdfceg"}, {"cfgeb"}, {"eagb"}, {"cbfgea"}, {"abcfdge"}}},{{{"ba"}, {"bac"}, {"gabe"}, {"cfbeda"}}}},
Message {{{{"efcgd"}, {"ecbafdg"}, {"fgabed"}, {"edb"}, {"ebcg"}, {"adcfb"}, {"be"}, {"efcdgb"}, {"dfcgae"}, {"dbefc"}}},{{{"dcgef"}, {"ebd"}, {"becg"}, {"gdfaebc"}}}},
Message {{{{"fgedabc"}, {"dafeb"}, {"eg"}, {"ged"}, {"aegfbd"}, {"afbecd"}, {"fbgdc"}, {"edfgb"}, {"egaf"}, {"dacegb"}}},{{{"gaecdb"}, {"cbegad"}, {"fega"}, {"fega"}}}},
Message {{{{"bgfcdae"}, {"fbcda"}, {"df"}, {"eafd"}, {"gbcaed"}, {"bdeca"}, {"gfbac"}, {"gfdbce"}, {"bfadce"}, {"bdf"}}},{{{"afcbdeg"}, {"gabfcde"}, {"deaf"}, {"cbeda"}}}},
Message {{{{"fcgebda"}, {"fcga"}, {"bgfcd"}, {"ebdfcg"}, {"degba"}, {"baf"}, {"bafgd"}, {"dfagbc"}, {"bfcade"}, {"af"}}},{{{"afb"}, {"agfc"}, {"af"}, {"cfegabd"}}}},
Message {{{{"cbfg"}, {"bfd"}, {"eabfdg"}, {"facbdg"}, {"edfcgab"}, {"bf"}, {"fcabd"}, {"aedcf"}, {"ebgdac"}, {"badcg"}}},{{{"eafdc"}, {"bdf"}, {"bf"}, {"fbcg"}}}},
Message {{{{"fbdgce"}, {"eagbfd"}, {"dbacfeg"}, {"dagb"}, {"geabf"}, {"cdeaf"}, {"ebd"}, {"bd"}, {"fgbcae"}, {"afebd"}}},{{{"defac"}, {"bed"}, {"edb"}, {"db"}}}},
Message {{{{"aegcd"}, {"bad"}, {"gdaebcf"}, {"cabfg"}, {"db"}, {"ecbd"}, {"gafdce"}, {"gcabd"}, {"gbcade"}, {"faebdg"}}},{{{"dab"}, {"dba"}, {"dba"}, {"cgfba"}}}},
Message {{{{"ecdba"}, {"bedacfg"}, {"cdgeba"}, {"dagcb"}, {"bdge"}, {"gdbfac"}, {"fcadeg"}, {"ced"}, {"de"}, {"acfeb"}}},{{{"ed"}, {"badfgc"}, {"beacf"}, {"bcgdafe"}}}},
Message {{{{"fg"}, {"abdeg"}, {"fgebdca"}, {"agdceb"}, {"gfbd"}, {"gdfae"}, {"fga"}, {"cdefa"}, {"efagbc"}, {"febgad"}}},{{{"fg"}, {"bgaefc"}, {"gf"}, {"bgafcde"}}}},
Message {{{{"beadc"}, {"gcbfed"}, {"fdc"}, {"bacf"}, {"fc"}, {"cbadefg"}, {"feadc"}, {"dgfea"}, {"dcbefa"}, {"dcgeba"}}},{{{"cdf"}, {"gefda"}, {"dfc"}, {"fbca"}}}},
Message {{{{"bd"}, {"bgcedf"}, {"decafg"}, {"gafcdb"}, {"acgdf"}, {"agbce"}, {"bafd"}, {"gaefbcd"}, {"cdb"}, {"acbdg"}}},{{{"fcdga"}, {"afbd"}, {"cbfdeg"}, {"cafdgb"}}}},
Message {{{{"dabe"}, {"bgcda"}, {"egcdb"}, {"fcdage"}, {"dcebga"}, {"bcfge"}, {"dafgebc"}, {"gdafcb"}, {"ed"}, {"ecd"}}},{{{"ebad"}, {"deba"}, {"de"}, {"gcbde"}}}},
Message {{{{"ga"}, {"gadcb"}, {"ebcfdg"}, {"egbcd"}, {"agebdc"}, {"eagb"}, {"afcedg"}, {"dbfca"}, {"dfceagb"}, {"dga"}}},{{{"dabgc"}, {"ga"}, {"agd"}, {"adbcg"}}}},
Message {{{{"cbfagde"}, {"ecdgf"}, {"eabgfc"}, {"fbd"}, {"egbdf"}, {"fageb"}, {"edba"}, {"dacbgf"}, {"bdaegf"}, {"bd"}}},{{{"beda"}, {"deab"}, {"abgfe"}, {"cegfd"}}}},
Message {{{{"gcdfa"}, {"gfea"}, {"ef"}, {"bdacfeg"}, {"aedbc"}, {"efc"}, {"gfebdc"}, {"adgbcf"}, {"fecad"}, {"aefcdg"}}},{{{"feadc"}, {"fe"}, {"efc"}, {"fgcad"}}}},
Message {{{{"gdcae"}, {"fga"}, {"af"}, {"acegfb"}, {"fbda"}, {"gfead"}, {"edfgbc"}, {"agdfecb"}, {"dbgafe"}, {"fdbge"}}},{{{"fabd"}, {"gfaed"}, {"efgbd"}, {"dagce"}}}},
Message {{{{"afdebg"}, {"febc"}, {"cdbae"}, {"abe"}, {"eb"}, {"dbfcea"}, {"dabcfeg"}, {"aecgdf"}, {"dabgc"}, {"dafce"}}},{{{"cefb"}, {"cedgaf"}, {"eab"}, {"acefd"}}}},
Message {{{{"fgc"}, {"dcabg"}, {"gbdefac"}, {"dfeg"}, {"ecfdgb"}, {"bfgcd"}, {"gebcaf"}, {"beafdc"}, {"fg"}, {"edbfc"}}},{{{"cdfeb"}, {"fcagbe"}, {"fgbdace"}, {"febdc"}}}},
Message {{{{"aegfbd"}, {"gacdeb"}, {"fdeacgb"}, {"dea"}, {"dgcefb"}, {"faeg"}, {"bdfac"}, {"dgefb"}, {"ae"}, {"debaf"}}},{{{"debfg"}, {"dea"}, {"ea"}, {"ead"}}}},
Message {{{{"acgedb"}, {"cfgae"}, {"egfcbda"}, {"fdeac"}, {"eacbfd"}, {"fd"}, {"bdagfe"}, {"dabec"}, {"def"}, {"fdcb"}}},{{{"fed"}, {"fd"}, {"fcbd"}, {"fde"}}}},
Message {{{{"dba"}, {"bgcfde"}, {"da"}, {"cdaf"}, {"acfbgde"}, {"fbgdc"}, {"fgadeb"}, {"dcbag"}, {"agbec"}, {"acgfdb"}}},{{{"gacbdef"}, {"adfgbe"}, {"bgcad"}, {"fcdabge"}}}},
Message {{{{"acdfe"}, {"cfgdab"}, {"cdgea"}, {"afgcebd"}, {"dcgbae"}, {"daf"}, {"gfea"}, {"fa"}, {"egdfac"}, {"bedfc"}}},{{{"fa"}, {"fad"}, {"fa"}, {"cedga"}}}},
Message {{{{"caedg"}, {"bafgde"}, {"egcba"}, {"dabegc"}, {"agd"}, {"fecdbga"}, {"bcfeag"}, {"fecdg"}, {"ad"}, {"abdc"}}},{{{"gad"}, {"cbeag"}, {"dag"}, {"cabd"}}}},
Message {{{{"adfebg"}, {"fedcagb"}, {"fagdc"}, {"gda"}, {"eadc"}, {"degcf"}, {"gdafec"}, {"ad"}, {"cdbfge"}, {"facbg"}}},{{{"da"}, {"aedc"}, {"cbfgdea"}, {"ad"}}}},
Message {{{{"ecfdba"}, {"dg"}, {"dgafec"}, {"gcabdfe"}, {"fbadg"}, {"fadcb"}, {"gbdfca"}, {"gfd"}, {"bgefa"}, {"dgbc"}}},{{{"cgbd"}, {"dbcaf"}, {"cgdb"}, {"dbgcfa"}}}},
Message {{{{"ebacg"}, {"eb"}, {"begd"}, {"dcebaf"}, {"cdgea"}, {"gafdce"}, {"ecb"}, {"cagfb"}, {"bfadcge"}, {"egcdba"}}},{{{"bgdaecf"}, {"bedacg"}, {"dbeg"}, {"cbdgae"}}}},
Message {{{{"ebdagcf"}, {"cgbea"}, {"fe"}, {"agefbc"}, {"abgdf"}, {"agfeb"}, {"egafdc"}, {"bcef"}, {"feg"}, {"deabcg"}}},{{{"cegabd"}, {"ecgafbd"}, {"ef"}, {"fe"}}}},
Message {{{{"cd"}, {"cgebdfa"}, {"fgeabd"}, {"cbd"}, {"cabed"}, {"gfbdec"}, {"adcf"}, {"abgce"}, {"eafbd"}, {"fcebad"}}},{{{"efabcdg"}, {"bcefgd"}, {"baedc"}, {"abfde"}}}},
Message {{{{"acfg"}, {"gbacfd"}, {"edgfabc"}, {"bdcaf"}, {"dca"}, {"caebdg"}, {"dafbe"}, {"gbcdf"}, {"ac"}, {"dfbgec"}}},{{{"bgcfed"}, {"cda"}, {"dbgfc"}, {"acd"}}}},
Message {{{{"agdbefc"}, {"abdc"}, {"ecd"}, {"gfcae"}, {"aedbf"}, {"gbcdef"}, {"ebafdg"}, {"ecadbf"}, {"efadc"}, {"cd"}}},{{{"afdeb"}, {"cde"}, {"dbafce"}, {"bfadge"}}}},
Message {{{{"begad"}, {"de"}, {"fged"}, {"gfbea"}, {"dbe"}, {"gbdac"}, {"ebfgdac"}, {"efgabd"}, {"cadfbe"}, {"fegabc"}}},{{{"de"}, {"dgfe"}, {"cgfaeb"}, {"gadbc"}}}},
Message {{{{"gefdc"}, {"gdfb"}, {"gdbcaef"}, {"deb"}, {"ebfcd"}, {"gcebad"}, {"bd"}, {"dacefg"}, {"gdcbef"}, {"fabce"}}},{{{"gfedabc"}, {"deb"}, {"gcfade"}, {"fdgb"}}}},
Message {{{{"bdec"}, {"dagcf"}, {"cefbg"}, {"bfgace"}, {"bgedfc"}, {"edacfbg"}, {"fgdec"}, {"fde"}, {"adgefb"}, {"de"}}},{{{"dbfaegc"}, {"cedb"}, {"edfabcg"}, {"fcdeg"}}}},
Message {{{{"eaf"}, {"gabed"}, {"cabegdf"}, {"fe"}, {"ecbgaf"}, {"fadeg"}, {"gadfc"}, {"fcdega"}, {"cfde"}, {"cbgafd"}}},{{{"adgef"}, {"fced"}, {"cgdbafe"}, {"fae"}}}},
Message {{{{"fcbaedg"}, {"gadce"}, {"abcg"}, {"ceb"}, {"bgedf"}, {"adfbec"}, {"decagf"}, {"bc"}, {"dbceg"}, {"eabdcg"}}},{{{"ceb"}, {"bgafecd"}, {"cabg"}, {"acefbd"}}}},
Message {{{{"dagb"}, {"cfgde"}, {"acgfeb"}, {"fbgac"}, {"fcgdb"}, {"bd"}, {"dbf"}, {"cbfagd"}, {"fcbeda"}, {"bcefgad"}}},{{{"db"}, {"fegdbca"}, {"dbceafg"}, {"aedbfc"}}}},
Message {{{{"edagb"}, {"da"}, {"dab"}, {"fbdge"}, {"cgdfbe"}, {"acegb"}, {"adfe"}, {"abdgfce"}, {"dfgeab"}, {"bfgcad"}}},{{{"abd"}, {"dab"}, {"gfbead"}, {"eagbc"}}}},
Message {{{{"bdfega"}, {"dcbgf"}, {"efcgabd"}, {"ce"}, {"fec"}, {"fcegd"}, {"agce"}, {"fegad"}, {"daebfc"}, {"efdcga"}}},{{{"ec"}, {"ecf"}, {"dgacef"}, {"bfecad"}}}},
Message {{{{"cdabgef"}, {"bgdfe"}, {"aecgb"}, {"gcfa"}, {"fc"}, {"acgebf"}, {"dcaebf"}, {"dcbgae"}, {"cfgeb"}, {"efc"}}},{{{"fc"}, {"fcga"}, {"bfecga"}, {"faecbdg"}}}},
Message {{{{"dfeac"}, {"gdfcea"}, {"fcg"}, {"acdebf"}, {"cdge"}, {"cgefa"}, {"bdcgaf"}, {"cg"}, {"fegbdac"}, {"bfage"}}},{{{"cfg"}, {"cfg"}, {"gfeca"}, {"fegac"}}}},
Message {{{{"bfad"}, {"bcf"}, {"bedcga"}, {"cadeb"}, {"bf"}, {"bceafd"}, {"bcegfd"}, {"dbaegfc"}, {"ecfga"}, {"cfbae"}}},{{{"efacdb"}, {"afbd"}, {"bcf"}, {"fb"}}}},
Message {{{{"aegfcd"}, {"bcdeg"}, {"abcefg"}, {"gcfea"}, {"bcgafed"}, {"bga"}, {"afbe"}, {"bagec"}, {"ab"}, {"fbdgac"}}},{{{"gceba"}, {"gacbe"}, {"gbacef"}, {"gab"}}}},
Message {{{{"dca"}, {"ebda"}, {"bdfaceg"}, {"acgdb"}, {"gbcdea"}, {"begcd"}, {"efbdcg"}, {"efacgd"}, {"bfagc"}, {"ad"}}},{{{"adcbeg"}, {"ad"}, {"cbfga"}, {"cfbgeda"}}}},
Message {{{{"fadebc"}, {"gcfbea"}, {"becgf"}, {"gf"}, {"fgc"}, {"abfg"}, {"ecgbd"}, {"dfecabg"}, {"fcedag"}, {"eafcb"}}},{{{"ebfgc"}, {"gaedfc"}, {"bgcef"}, {"gedabfc"}}}},
Message {{{{"fadg"}, {"eafgb"}, {"gbead"}, {"bdaec"}, {"ecagbf"}, {"dg"}, {"gdb"}, {"agfebd"}, {"aedcgfb"}, {"cfgbde"}}},{{{"bfecdag"}, {"bgd"}, {"badce"}, {"gd"}}}},
Message {{{{"egcd"}, {"efadb"}, {"gacbfd"}, {"bcaeg"}, {"ecadgb"}, {"adc"}, {"bacegf"}, {"adecb"}, {"dc"}, {"agedcfb"}}},{{{"fcgabe"}, {"degc"}, {"acd"}, {"cd"}}}},
Message {{{{"bedfcag"}, {"gc"}, {"fagdec"}, {"gfabce"}, {"bfgec"}, {"acgb"}, {"befac"}, {"gfc"}, {"bgdef"}, {"aecfbd"}}},{{{"cg"}, {"ebfdg"}, {"cfg"}, {"gc"}}}},
Message {{{{"aegbdf"}, {"gfabced"}, {"fadebc"}, {"gfde"}, {"ed"}, {"bcaeg"}, {"fbgda"}, {"eadbg"}, {"fgbacd"}, {"bde"}}},{{{"dbcefag"}, {"bed"}, {"afcbged"}, {"aegdb"}}}},
Message {{{{"agd"}, {"fagec"}, {"cfbgda"}, {"bfceagd"}, {"fgeacb"}, {"cdae"}, {"gdbef"}, {"dagef"}, {"da"}, {"efcdga"}}},{{{"edbgf"}, {"gda"}, {"gedaf"}, {"cdgfaeb"}}}},
Message {{{{"fgaec"}, {"eb"}, {"fcgbd"}, {"agfdeb"}, {"cedb"}, {"fabcdeg"}, {"egb"}, {"febcg"}, {"dfbgec"}, {"cdfgab"}}},{{{"fgbcde"}, {"dbeafg"}, {"egcfdba"}, {"gcbfd"}}}},
Message {{{{"gfe"}, {"fdbae"}, {"ge"}, {"bfgdc"}, {"dgfaec"}, {"cgeb"}, {"dcfgbe"}, {"dabfgc"}, {"fdegb"}, {"eabgcdf"}}},{{{"gebc"}, {"gceb"}, {"defbcag"}, {"afbcedg"}}}},
Message {{{{"dfce"}, {"cgbed"}, {"fbcagd"}, {"bcdgf"}, {"ged"}, {"bdfgae"}, {"ed"}, {"bdfceg"}, {"agebc"}, {"fabdegc"}}},{{{"fcde"}, {"gde"}, {"gecdbf"}, {"de"}}}},
Message {{{{"dba"}, {"dcafbg"}, {"gcdefb"}, {"fbged"}, {"dgeab"}, {"bfegad"}, {"gaecd"}, {"ba"}, {"aebf"}, {"egafdcb"}}},{{{"beadg"}, {"cfdbage"}, {"bgafde"}, {"acdge"}}}},
Message {{{{"bcgdef"}, {"cbdgeaf"}, {"ae"}, {"fbdace"}, {"afbde"}, {"gcdabe"}, {"gdbfa"}, {"edbcf"}, {"fcea"}, {"bea"}}},{{{"dgafb"}, {"adbfce"}, {"ea"}, {"fbdecga"}}}},
Message {{{{"afdg"}, {"fgebc"}, {"fdeacbg"}, {"fd"}, {"gadcb"}, {"fdcgb"}, {"gfacbd"}, {"gbeacd"}, {"acdfeb"}, {"dfc"}}},{{{"fd"}, {"bdcafeg"}, {"caefbd"}, {"dafg"}}}},
Message {{{{"dfebag"}, {"defa"}, {"bdgfa"}, {"beafg"}, {"agbcfd"}, {"eab"}, {"cbagefd"}, {"cfgbe"}, {"ea"}, {"acbgde"}}},{{{"abdcge"}, {"abe"}, {"ae"}, {"fecbg"}}}},
Message {{{{"ef"}, {"bgfdeac"}, {"bdcefg"}, {"cfdba"}, {"ecf"}, {"dgecba"}, {"gfae"}, {"abgefc"}, {"ecbga"}, {"acefb"}}},{{{"debcag"}, {"afge"}, {"efag"}, {"fe"}}}},
Message {{{{"cg"}, {"gbfc"}, {"gabcd"}, {"bgade"}, {"dgc"}, {"gbecafd"}, {"egdfac"}, {"dfbac"}, {"abdcfe"}, {"gabfdc"}}},{{{"gcbad"}, {"degfabc"}, {"cgafbd"}, {"adbgcf"}}}},
Message {{{{"edbcgf"}, {"acgbf"}, {"fbaedc"}, {"cbfae"}, {"gfc"}, {"agcdb"}, {"dagecfb"}, {"fg"}, {"fcgbea"}, {"eagf"}}},{{{"fg"}, {"adcbef"}, {"fbeac"}, {"fadcgeb"}}}},
Message {{{{"deacg"}, {"daeb"}, {"dagbce"}, {"ecdbgf"}, {"edc"}, {"ed"}, {"bgaefc"}, {"gecba"}, {"dagcf"}, {"abdgecf"}}},{{{"cdaeg"}, {"abcge"}, {"dec"}, {"ecd"}}}},
Message {{{{"fcgadb"}, {"caged"}, {"bedc"}, {"cdabeg"}, {"dfaecbg"}, {"befag"}, {"db"}, {"dgb"}, {"eagbd"}, {"gacdef"}}},{{{"fecagdb"}, {"begad"}, {"dgb"}, {"db"}}}},
Message {{{{"fbcdga"}, {"fgcad"}, {"fecdg"}, {"gcedab"}, {"bfca"}, {"adc"}, {"ac"}, {"bfdga"}, {"dbfega"}, {"eafbcdg"}}},{{{"adc"}, {"cbgade"}, {"fgcadb"}, {"ceabgd"}}}},
Message {{{{"cefdbg"}, {"gde"}, {"bgfeac"}, {"ed"}, {"begcd"}, {"cbefg"}, {"bfde"}, {"aedcgf"}, {"cbafegd"}, {"gacbd"}}},{{{"fegbdac"}, {"gcbefd"}, {"cbgef"}, {"bgedc"}}}},
Message {{{{"bfdagc"}, {"afdc"}, {"bagcf"}, {"gbfdc"}, {"begcd"}, {"begdaf"}, {"beafgc"}, {"dbefgac"}, {"gfd"}, {"fd"}}},{{{"fcda"}, {"df"}, {"dfac"}, {"dcbfg"}}}},
Message {{{{"gcbfe"}, {"bfeacg"}, {"cedbf"}, {"ge"}, {"bfcga"}, {"gfe"}, {"gfecda"}, {"ecbgdfa"}, {"bgfadc"}, {"bage"}}},{{{"feg"}, {"eagb"}, {"gef"}, {"abfgc"}}}},
Message {{{{"bgfec"}, {"bac"}, {"abecdfg"}, {"ab"}, {"gdcea"}, {"ebgcfa"}, {"fagb"}, {"aebcg"}, {"caebfd"}, {"gfcbed"}}},{{{"ab"}, {"ab"}, {"cba"}, {"acgbe"}}}},
Message {{{{"gdbcf"}, {"cbedg"}, {"ce"}, {"ceg"}, {"abcgde"}, {"adbeg"}, {"efgcab"}, {"bdfegac"}, {"adec"}, {"adfbeg"}}},{{{"gaecdfb"}, {"bedga"}, {"cge"}, {"cead"}}}},
Message {{{{"eafcb"}, {"cfdbe"}, {"aeb"}, {"acfeg"}, {"ab"}, {"dcgbfe"}, {"adfb"}, {"fgacedb"}, {"ecabgd"}, {"fdbcae"}}},{{{"fbcde"}, {"aedfcbg"}, {"bea"}, {"edcbf"}}}},
Message {{{{"ebdca"}, {"egc"}, {"cgabe"}, {"fbge"}, {"cgbfda"}, {"ge"}, {"bacfg"}, {"geacbf"}, {"afdgec"}, {"gebacfd"}}},{{{"badce"}, {"cge"}, {"bgfcea"}, {"ge"}}}},
Message {{{{"gdfecb"}, {"bdge"}, {"gdf"}, {"dgbcaf"}, {"aefbgc"}, {"bfecg"}, {"fgdec"}, {"dg"}, {"ecdbfga"}, {"deacf"}}},{{{"dgf"}, {"fedcagb"}, {"gd"}, {"gcedf"}}}},
Message {{{{"agdeb"}, {"cfdbag"}, {"gcabd"}, {"ed"}, {"dacegbf"}, {"gebfa"}, {"eagbdc"}, {"acde"}, {"efcgbd"}, {"edb"}}},{{{"ed"}, {"eagdb"}, {"de"}, {"de"}}}},
Message {{{{"feag"}, {"cfgbed"}, {"feacbdg"}, {"cfgade"}, {"efcdg"}, {"fcgdab"}, {"afd"}, {"dfeac"}, {"af"}, {"abedc"}}},{{{"cbagfde"}, {"dbagfc"}, {"faeg"}, {"dgabcf"}}}},
Message {{{{"cdg"}, {"efgbcd"}, {"decgfa"}, {"dcegb"}, {"dgbf"}, {"gd"}, {"ebdcfga"}, {"adebc"}, {"gbcfe"}, {"cefagb"}}},{{{"bfecg"}, {"dgbf"}, {"gdbf"}, {"dg"}}}},
Message {{{{"gab"}, {"dfceag"}, {"gdcb"}, {"bg"}, {"gbead"}, {"agdefbc"}, {"gcabef"}, {"acged"}, {"efdba"}, {"agdceb"}}},{{{"gdcb"}, {"bgdc"}, {"edbfa"}, {"bag"}}}},
Message {{{{"bgafde"}, {"afdgc"}, {"gcafed"}, {"efgdc"}, {"ceda"}, {"gdcebfa"}, {"gdbacf"}, {"de"}, {"gbcef"}, {"edg"}}},{{{"edg"}, {"gde"}, {"eadfcbg"}, {"cade"}}}},
Message {{{{"gdb"}, {"egcfadb"}, {"gdef"}, {"abcfd"}, {"dg"}, {"ebfag"}, {"gadbef"}, {"abdgf"}, {"aefbgc"}, {"cbgaed"}}},{{{"fedgba"}, {"dbegfac"}, {"bfeagd"}, {"gefcdba"}}}},
Message {{{{"gad"}, {"bdcag"}, {"becdg"}, {"gceabd"}, {"dceafbg"}, {"fgdeca"}, {"fcgab"}, {"ad"}, {"baed"}, {"dfcbge"}}},{{{"cfaegdb"}, {"gda"}, {"ad"}, {"gaedcfb"}}}},
Message {{{{"dafbeg"}, {"eadgbfc"}, {"fgd"}, {"bagcf"}, {"gedb"}, {"abdfce"}, {"gafdb"}, {"fcdgea"}, {"gd"}, {"efbda"}}},{{{"gebd"}, {"fdg"}, {"gaefcd"}, {"deagcf"}}}},
Message {{{{"cdbe"}, {"adefb"}, {"ecfgbad"}, {"bfcgad"}, {"bacdf"}, {"agcefd"}, {"efd"}, {"cdeafb"}, {"aegfb"}, {"de"}}},{{{"gacebdf"}, {"bdce"}, {"fbcagd"}, {"dcefab"}}}},
Message {{{{"cb"}, {"acdgbe"}, {"bce"}, {"cdegabf"}, {"bgdefa"}, {"aegdb"}, {"cdbg"}, {"acbde"}, {"fcebga"}, {"fdace"}}},{{{"ebc"}, {"abfdecg"}, {"ceb"}, {"gbacdfe"}}}},
Message {{{{"cg"}, {"fcedg"}, {"edfbag"}, {"ceag"}, {"fdbec"}, {"gdc"}, {"faedcg"}, {"bdcefag"}, {"gbafcd"}, {"dfeag"}}},{{{"geca"}, {"dgfacb"}, {"cgd"}, {"cg"}}}},
Message {{{{"bcafde"}, {"defac"}, {"dcage"}, {"dgfbce"}, {"gafc"}, {"cgaedf"}, {"cgd"}, {"cg"}, {"fgcedab"}, {"gdeab"}}},{{{"cdg"}, {"ebadg"}, {"aedgcf"}, {"fagc"}}}},
Message {{{{"bdec"}, {"dagbf"}, {"ecagfb"}, {"decbfa"}, {"aefdc"}, {"aeb"}, {"dcegfa"}, {"adefcbg"}, {"ebadf"}, {"be"}}},{{{"cdbe"}, {"gfadb"}, {"eadfc"}, {"dcbe"}}}},
Message {{{{"bcgeda"}, {"fc"}, {"badfe"}, {"gbfdaec"}, {"fcge"}, {"cfd"}, {"bedfc"}, {"cedbg"}, {"adfgbc"}, {"dcgebf"}}},{{{"cf"}, {"ebacgfd"}, {"fgce"}, {"fdbceag"}}}},
Message {{{{"gd"}, {"fgbdea"}, {"dbg"}, {"badce"}, {"gdcab"}, {"fcagedb"}, {"fbacg"}, {"beacfg"}, {"cgfd"}, {"dcafbg"}}},{{{"fcdg"}, {"gdcbfa"}, {"dbg"}, {"gdfc"}}}},
Message {{{{"cag"}, {"cdfa"}, {"cgade"}, {"edgcbf"}, {"fcebga"}, {"begfcad"}, {"gfdcae"}, {"egabd"}, {"defgc"}, {"ac"}}},{{{"ca"}, {"agc"}, {"fgbace"}, {"gac"}}}},
Message {{{{"ecabf"}, {"geacfb"}, {"eabdcf"}, {"dec"}, {"cd"}, {"bgecfda"}, {"gfdbce"}, {"edcba"}, {"cdaf"}, {"adgeb"}}},{{{"ced"}, {"aedfgbc"}, {"dc"}, {"gbeda"}}}},
Message {{{{"fbdac"}, {"ea"}, {"cadefg"}, {"fae"}, {"beag"}, {"facbe"}, {"bfgeacd"}, {"cfdegb"}, {"bgfec"}, {"gfecba"}}},{{{"agbe"}, {"ea"}, {"bafce"}, {"egbdcf"}}}},
Message {{{{"bdc"}, {"dbega"}, {"abcdg"}, {"gbcfa"}, {"dc"}, {"gcde"}, {"cgbaefd"}, {"cdfbae"}, {"eagdbf"}, {"ebgadc"}}},{{{"adefcb"}, {"agcfb"}, {"cdb"}, {"gced"}}}},
Message {{{{"ceb"}, {"ce"}, {"debfca"}, {"abgdfe"}, {"bdaeg"}, {"cabegd"}, {"caeg"}, {"dbgec"}, {"dcbfg"}, {"bdecgfa"}}},{{{"ce"}, {"abegd"}, {"gdfcb"}, {"fcbdgae"}}}},
Message {{{{"cafedgb"}, {"dgf"}, {"bcfd"}, {"cgdfbe"}, {"acedfg"}, {"gbfed"}, {"agedb"}, {"aecgfb"}, {"bfgec"}, {"fd"}}},{{{"fdgbec"}, {"feacdg"}, {"df"}, {"bgcfe"}}}},
Message {{{{"ef"}, {"abgfc"}, {"cagfeb"}, {"gdebfc"}, {"fbae"}, {"bcadfg"}, {"defgabc"}, {"feg"}, {"gefac"}, {"gceda"}}},{{{"degac"}, {"gfbac"}, {"gabfc"}, {"gfcea"}}}},
Message {{{{"bfdeca"}, {"bd"}, {"eabfgc"}, {"degbcfa"}, {"cgdb"}, {"gefbc"}, {"dbf"}, {"ecfbgd"}, {"gaedf"}, {"edgfb"}}},{{{"dbfge"}, {"bdf"}, {"egbfca"}, {"db"}}}},
Message {{{{"fac"}, {"cbdfg"}, {"eacfbg"}, {"gaecfdb"}, {"bacfd"}, {"bfeda"}, {"acgd"}, {"ac"}, {"gbfecd"}, {"cgfadb"}}},{{{"dagc"}, {"ac"}, {"dcga"}, {"bedfa"}}}},
Message {{{{"egfbca"}, {"aegcf"}, {"gdcfab"}, {"fdc"}, {"adce"}, {"fcedg"}, {"cd"}, {"cfgead"}, {"fdebg"}, {"cedagbf"}}},{{{"dcgfe"}, {"fdgbcea"}, {"aedc"}, {"cfebga"}}}},
Message {{{{"da"}, {"bfged"}, {"afedcb"}, {"gcebdf"}, {"gefda"}, {"fedbga"}, {"edgbfca"}, {"gdba"}, {"eagfc"}, {"eda"}}},{{{"ead"}, {"dcfebg"}, {"defcgb"}, {"efgbcd"}}}},
Message {{{{"adefgb"}, {"ecgf"}, {"gcedb"}, {"fedacb"}, {"bec"}, {"fbecdg"}, {"cdfaebg"}, {"gedfb"}, {"gcbad"}, {"ce"}}},{{{"dcbfeag"}, {"cfbged"}, {"efgbad"}, {"bcdfage"}}}},
Message {{{{"dfec"}, {"gcd"}, {"agdbe"}, {"bdafgc"}, {"afcbge"}, {"bgecfad"}, {"bgcde"}, {"bgfce"}, {"bgedfc"}, {"cd"}}},{{{"fbecag"}, {"beagdfc"}, {"cgd"}, {"cedf"}}}},
Message {{{{"edbc"}, {"agcfbe"}, {"adefg"}, {"cd"}, {"defca"}, {"gfabdc"}, {"cad"}, {"dgabefc"}, {"dfebac"}, {"bceaf"}}},{{{"dbce"}, {"ebdc"}, {"febcdga"}, {"cdgbefa"}}}},
Message {{{{"ecdb"}, {"eb"}, {"acgebdf"}, {"ebf"}, {"dcfebg"}, {"bgdefa"}, {"fcgbd"}, {"gcdbaf"}, {"feacg"}, {"cfebg"}}},{{{"bef"}, {"ecfbg"}, {"egdcbfa"}, {"cdgfb"}}}},
Message {{{{"ebfcgd"}, {"aefcb"}, {"bfadge"}, {"efd"}, {"ed"}, {"adfcgb"}, {"fbgdc"}, {"bfedagc"}, {"fcebd"}, {"dcge"}}},{{{"gced"}, {"fbcgd"}, {"edgc"}, {"ed"}}}},
Message {{{{"beagf"}, {"cefbag"}, {"ebafc"}, {"gfce"}, {"gdfeab"}, {"fcaedbg"}, {"ec"}, {"dfcba"}, {"ecb"}, {"gbadec"}}},{{{"ce"}, {"acfdb"}, {"dbgcafe"}, {"ec"}}}},
Message {{{{"abegfc"}, {"fbcged"}, {"bgfea"}, {"fecabdg"}, {"gef"}, {"ge"}, {"abdgf"}, {"gaec"}, {"afecb"}, {"cfbdea"}}},{{{"cbfaedg"}, {"bface"}, {"gfe"}, {"efabgc"}}}},
Message {{{{"bdg"}, {"bacd"}, {"edagb"}, {"fbegac"}, {"fgaed"}, {"bdgcae"}, {"cgbea"}, {"dfbegc"}, {"ecgafdb"}, {"bd"}}},{{{"gdeaf"}, {"cfdgbe"}, {"gbcaed"}, {"bd"}}}},
Message {{{{"fbce"}, {"fdegca"}, {"egafb"}, {"aef"}, {"egdcfba"}, {"eabgc"}, {"fe"}, {"ecdabg"}, {"agfbd"}, {"ecgbaf"}}},{{{"fadgb"}, {"cbage"}, {"bcgdea"}, {"abfgec"}}}},
Message {{{{"dbafge"}, {"fedgcab"}, {"efgdbc"}, {"bc"}, {"fbac"}, {"fbdea"}, {"gceda"}, {"bfceda"}, {"bdcea"}, {"ebc"}}},{{{"eadcb"}, {"fcdeab"}, {"cafb"}, {"bdecgf"}}}},
Message {{{{"cbgae"}, {"fec"}, {"aefgcb"}, {"acfeg"}, {"fe"}, {"efgcbd"}, {"bgceafd"}, {"fbea"}, {"cagbed"}, {"dcfga"}}},{{{"edbagfc"}, {"acefg"}, {"gbdface"}, {"ecf"}}}},
Message {{{{"cbfdga"}, {"bae"}, {"ebdf"}, {"fbadge"}, {"afdgb"}, {"gfeac"}, {"acbdge"}, {"bdacfeg"}, {"eb"}, {"agfeb"}}},{{{"edbf"}, {"bea"}, {"efdcbag"}, {"aeb"}}}},
Message {{{{"efdcgab"}, {"bedgaf"}, {"aecbgf"}, {"cgfe"}, {"gfaeb"}, {"cbgea"}, {"ecbfad"}, {"ec"}, {"gdcab"}, {"ecb"}}},{{{"cgfe"}, {"eabfg"}, {"eabgf"}, {"ec"}}}},
Message {{{{"bdefa"}, {"dfebgca"}, {"bfe"}, {"eadfcb"}, {"dcbage"}, {"bfgad"}, {"debca"}, {"cgebaf"}, {"ef"}, {"cdfe"}}},{{{"gacdbe"}, {"eagcfbd"}, {"afcgebd"}, {"dfgbace"}}}},
Message {{{{"gca"}, {"ebdcfa"}, {"fdcgea"}, {"acedb"}, {"bdcgf"}, {"eabg"}, {"gbacde"}, {"bcgdeaf"}, {"ga"}, {"gacdb"}}},{{{"ebag"}, {"abge"}, {"gac"}, {"aecdb"}}}},
Message {{{{"abcgf"}, {"afgcbe"}, {"baeg"}, {"gbc"}, {"ecdbgf"}, {"gafce"}, {"facbd"}, {"cfgade"}, {"bg"}, {"egabdfc"}}},{{{"aegb"}, {"cgb"}, {"bcdgef"}, {"abcgf"}}}},
Message {{{{"ecagbf"}, {"bdfgca"}, {"ecgfd"}, {"gbe"}, {"fecgb"}, {"dafgecb"}, {"bacfg"}, {"bgadec"}, {"efba"}, {"eb"}}},{{{"geb"}, {"cadfebg"}, {"beaf"}, {"be"}}}},
Message {{{{"agcdb"}, {"bgcaf"}, {"bf"}, {"fadebgc"}, {"daecbf"}, {"gbdf"}, {"fbc"}, {"ebgcda"}, {"afegc"}, {"bgcafd"}}},{{{"facgdeb"}, {"dbfg"}, {"fb"}, {"bf"}}}},
Message {{{{"fdbeag"}, {"cgd"}, {"bdefcag"}, {"afegd"}, {"eacgdf"}, {"dc"}, {"dgefc"}, {"ebcagd"}, {"gfebc"}, {"facd"}}},{{{"geadf"}, {"dc"}, {"dc"}, {"cdg"}}}},
Message {{{{"adcgfe"}, {"cgebf"}, {"acdbf"}, {"abcedf"}, {"dgfbaec"}, {"edba"}, {"cabef"}, {"ea"}, {"afe"}, {"dfagcb"}}},{{{"bfgec"}, {"bfeca"}, {"ae"}, {"deba"}}}},
Message {{{{"adegb"}, {"bgcd"}, {"cbdfgea"}, {"dc"}, {"cedba"}, {"cagefd"}, {"dcbgae"}, {"gebdaf"}, {"faebc"}, {"ced"}}},{{{"egadb"}, {"ced"}, {"dcbg"}, {"dc"}}}},
Message {{{{"fdeg"}, {"gd"}, {"fdbaec"}, {"bfacg"}, {"dgcfa"}, {"ecfdga"}, {"fadcegb"}, {"fdcea"}, {"dceabg"}, {"gda"}}},{{{"efgd"}, {"eacdfb"}, {"bcfadeg"}, {"dag"}}}},
Message {{{{"af"}, {"ebgfda"}, {"ecagdb"}, {"febgc"}, {"afe"}, {"dabce"}, {"cfda"}, {"febcda"}, {"baecf"}, {"becafdg"}}},{{{"fa"}, {"dbfega"}, {"fa"}, {"bfeagd"}}}},
Message {{{{"debagfc"}, {"cbdgfe"}, {"dcb"}, {"fdbeg"}, {"cegb"}, {"fbced"}, {"fcead"}, {"cbdfga"}, {"bc"}, {"fabdeg"}}},{{{"dcb"}, {"efadgb"}, {"dgcfeab"}, {"ebafdg"}}}},
Message {{{{"cgfdae"}, {"bdef"}, {"becfg"}, {"gcbefa"}, {"ed"}, {"abcdg"}, {"gedcb"}, {"cgbdef"}, {"bdcgefa"}, {"ecd"}}},{{{"cde"}, {"dec"}, {"bfed"}, {"bfcgdea"}}}},
Message {{{{"dcfegab"}, {"becdg"}, {"gcaedb"}, {"egd"}, {"bcdaef"}, {"gcfdb"}, {"eg"}, {"eafcdg"}, {"cdeab"}, {"ageb"}}},{{{"ged"}, {"cegafbd"}, {"egd"}, {"eg"}}}},
Message {{{{"ba"}, {"eafcd"}, {"fcbegda"}, {"acfgbd"}, {"bedcgf"}, {"ebgcfa"}, {"fabdc"}, {"dcgfb"}, {"bagd"}, {"baf"}}},{{{"ba"}, {"cafed"}, {"efdbcag"}, {"efdac"}}}},
Message {{{{"aebcdgf"}, {"cd"}, {"efbgac"}, {"bfcgd"}, {"cbfga"}, {"gbefd"}, {"bfdcga"}, {"bcad"}, {"geafcd"}, {"dgc"}}},{{{"fabcged"}, {"fgaceb"}, {"cbda"}, {"dc"}}}},
Message {{{{"cgbaedf"}, {"fbceg"}, {"eafbcd"}, {"degcf"}, {"gfdcae"}, {"gdcfa"}, {"dbagcf"}, {"dgae"}, {"edf"}, {"ed"}}},{{{"fcgeb"}, {"efd"}, {"ed"}, {"gdea"}}}},
Message {{{{"ac"}, {"agfdcbe"}, {"gcea"}, {"dgecf"}, {"fgdca"}, {"efgcad"}, {"dfbeac"}, {"fca"}, {"fdgba"}, {"gcebfd"}}},{{{"agbdf"}, {"ca"}, {"ac"}, {"gbdfa"}}}},
Message {{{{"gbedaf"}, {"dbgfc"}, {"cbg"}, {"abdfgc"}, {"geadbc"}, {"fecbd"}, {"ebcgafd"}, {"cafg"}, {"gc"}, {"dafbg"}}},{{{"cdbfg"}, {"gcfbad"}, {"gcbdea"}, {"fadcegb"}}}},
Message {{{{"bagfec"}, {"efg"}, {"bfcdga"}, {"egac"}, {"abfecdg"}, {"afdbge"}, {"dbefc"}, {"ge"}, {"cgbfe"}, {"acfbg"}}},{{{"fbdeag"}, {"eg"}, {"eg"}, {"cbdfe"}}}},
Message {{{{"edbgcf"}, {"dgbac"}, {"bdceag"}, {"dbagf"}, {"cgd"}, {"ecagb"}, {"bceagf"}, {"cd"}, {"adce"}, {"cgbafed"}}},{{{"aecd"}, {"egdbca"}, {"gacbe"}, {"gcd"}}}},
Message {{{{"bgfdc"}, {"gdfbe"}, {"afdbgc"}, {"gc"}, {"fbdac"}, {"bacg"}, {"gbafdec"}, {"cdg"}, {"cbdefa"}, {"defagc"}}},{{{"egdfb"}, {"gcabdef"}, {"cdbfa"}, {"dgacfb"}}}},
Message {{{{"adgcfb"}, {"gcd"}, {"dfecgb"}, {"cgebfa"}, {"bgcaf"}, {"adgcf"}, {"cdbafeg"}, {"dg"}, {"ecafd"}, {"adbg"}}},{{{"bcgaf"}, {"fadcgeb"}, {"gd"}, {"cgbaedf"}}}},
Message {{{{"bafgd"}, {"cfaebg"}, {"cefa"}, {"cfbgead"}, {"bcf"}, {"bgcea"}, {"defgcb"}, {"bgacf"}, {"ebcgda"}, {"cf"}}},{{{"fcbgae"}, {"adfbg"}, {"cdfgeb"}, {"adgbf"}}}},
Message {{{{"becfa"}, {"bcgdf"}, {"gbceadf"}, {"gebcfa"}, {"defa"}, {"adbcge"}, {"de"}, {"dec"}, {"cebdf"}, {"bdefac"}}},{{{"faed"}, {"fdcagbe"}, {"edc"}, {"bfacge"}}}},
Message {{{{"ebfgd"}, {"gabd"}, {"gd"}, {"gfbcaed"}, {"abgfec"}, {"faegb"}, {"dge"}, {"aefdbg"}, {"agdfec"}, {"cfebd"}}},{{{"faecdg"}, {"cgaedf"}, {"baefgd"}, {"dcfeb"}}}},
Message {{{{"ecabd"}, {"ged"}, {"aebgfc"}, {"ecagd"}, {"dg"}, {"fdcegb"}, {"afgce"}, {"dgaf"}, {"dcaegf"}, {"cedbgaf"}}},{{{"edcga"}, {"gfda"}, {"gd"}, {"dge"}}}},
Message {{{{"dfg"}, {"fg"}, {"eafdb"}, {"aegdc"}, {"faged"}, {"gfba"}, {"debafg"}, {"ebgfcad"}, {"gfbdce"}, {"acedbf"}}},{{{"fedagb"}, {"edbfac"}, {"gf"}, {"fgd"}}}},
Message {{{{"dbgca"}, {"fedca"}, {"bfgcad"}, {"adgcf"}, {"agdecb"}, {"dgf"}, {"cefdgba"}, {"bgaedf"}, {"fcgb"}, {"gf"}}},{{{"acefdgb"}, {"beafdg"}, {"gfd"}, {"cfbg"}}}},
Message {{{{"edgacf"}, {"adegcb"}, {"fd"}, {"dbacgfe"}, {"fabd"}, {"dfbce"}, {"egcfb"}, {"edfbac"}, {"cbeda"}, {"fde"}}},{{{"dafb"}, {"bafd"}, {"acefbd"}, {"fd"}}}},
Message {{{{"bcefa"}, {"gbfd"}, {"eadcgb"}, {"bgfdae"}, {"gedcfa"}, {"abefd"}, {"efd"}, {"df"}, {"gedba"}, {"fbdgeac"}}},{{{"bfdae"}, {"fgeacdb"}, {"bacfe"}, {"gdceba"}}}},
Message {{{{"bdcefg"}, {"aefgcd"}, {"gadcb"}, {"gfb"}, {"decbfag"}, {"dfecg"}, {"bfdgc"}, {"defb"}, {"cefagb"}, {"fb"}}},{{{"defb"}, {"fbcged"}, {"dbfegac"}, {"egfdc"}}}},
Message {{{{"fe"}, {"cedgab"}, {"cbfe"}, {"dacbfge"}, {"cedba"}, {"fed"}, {"gafcd"}, {"dfaec"}, {"edbfac"}, {"efdgab"}}},{{{"abgedf"}, {"efcb"}, {"bedac"}, {"gefbad"}}}},
Message {{{{"afcgbe"}, {"cf"}, {"fbc"}, {"cegadb"}, {"bfcdea"}, {"fcgabed"}, {"aebdc"}, {"adfgb"}, {"cedf"}, {"cfadb"}}},{{{"dafbc"}, {"bfeagc"}, {"bcf"}, {"deacbgf"}}}},
Message {{{{"ebcafdg"}, {"ecfbg"}, {"bae"}, {"dgcabf"}, {"bcaedg"}, {"dfbeca"}, {"ae"}, {"ebcag"}, {"gdacb"}, {"dage"}}},{{{"cadbeg"}, {"gbacd"}, {"bfdegca"}, {"eba"}}}},
Message {{{{"cadbe"}, {"efgbc"}, {"feacbg"}, {"dgfecb"}, {"bgd"}, {"dg"}, {"bgfcad"}, {"ebdgc"}, {"dgef"}, {"gbdefca"}}},{{{"aefcgb"}, {"gd"}, {"bfagced"}, {"dgb"}}}},
Message {{{{"edgcfa"}, {"dgbecfa"}, {"bgedac"}, {"dfbaec"}, {"acgdf"}, {"dg"}, {"abfgc"}, {"egdf"}, {"adcef"}, {"gdc"}}},{{{"cgd"}, {"cbgfa"}, {"eacgdb"}, {"gcafd"}}}},
Message {{{{"cad"}, {"cfbead"}, {"abceg"}, {"edfa"}, {"fadbcg"}, {"becad"}, {"edgfcb"}, {"bgfaedc"}, {"cdbfe"}, {"da"}}},{{{"egcab"}, {"afde"}, {"dcabfe"}, {"ecfabd"}}}},
Message {{{{"fgbdc"}, {"be"}, {"egb"}, {"bcdefag"}, {"ceba"}, {"gedbac"}, {"egcda"}, {"dcfgae"}, {"debcg"}, {"gbdaef"}}},{{{"ceba"}, {"edgac"}, {"eadcfg"}, {"bcdaeg"}}}},
Message {{{{"cg"}, {"adcfgbe"}, {"edbcga"}, {"gbead"}, {"cbdfa"}, {"cga"}, {"bgedaf"}, {"faecdg"}, {"dbacg"}, {"cebg"}}},{{{"gcdabfe"}, {"fdacge"}, {"cga"}, {"bcgad"}}}},
Message {{{{"gacf"}, {"gf"}, {"bgeafd"}, {"gef"}, {"gefbc"}, {"efbagc"}, {"bdceag"}, {"fdebc"}, {"acfbedg"}, {"gbaec"}}},{{{"bcgaedf"}, {"egf"}, {"gcefb"}, {"cafdegb"}}}},
Message {{{{"fgbadce"}, {"cdbag"}, {"agcfd"}, {"faec"}, {"acfegd"}, {"fa"}, {"fag"}, {"cfged"}, {"fdabeg"}, {"dbfcge"}}},{{{"agf"}, {"bagefd"}, {"edgfc"}, {"gdbacef"}}}},
Message {{{{"agcdb"}, {"gcadfb"}, {"dgfcb"}, {"gfdbec"}, {"adebg"}, {"adc"}, {"ac"}, {"cfab"}, {"beagdcf"}, {"daecfg"}}},{{{"ac"}, {"ca"}, {"bedga"}, {"ca"}}}},
Message {{{{"dfa"}, {"abdcfg"}, {"agbf"}, {"cfabd"}, {"dacgb"}, {"dcebf"}, {"eadgcb"}, {"fa"}, {"gbdafce"}, {"ecfgad"}}},{{{"af"}, {"fa"}, {"bcdaf"}, {"bgaf"}}}},
Message {{{{"ebdfc"}, {"cgbaed"}, {"eg"}, {"edabfc"}, {"gefb"}, {"adfgc"}, {"gdfec"}, {"deg"}, {"ebdfgc"}, {"debgcaf"}}},{{{"abfcde"}, {"bfge"}, {"gde"}, {"dge"}}}},
Message {{{{"dabfegc"}, {"dfegb"}, {"cbgf"}, {"cf"}, {"fdebgc"}, {"dcbaef"}, {"gcfed"}, {"adecg"}, {"fbdgea"}, {"fce"}}},{{{"cf"}, {"gbfc"}, {"fgcb"}, {"begcadf"}}}}
};

int main()
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
    return 0;
}
