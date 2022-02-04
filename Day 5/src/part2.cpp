#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>

struct Point
{
    int x{0}, y{0};
};

struct Line
{
    Point start{0, 0}, end{0, 0};
};

constexpr std::array<Line, 500> input_lines{ Line {{973,543}, {601,915}}, Line {{758,846}, {758,168}}, Line {{511,976}, {568,976}}, Line {{858,536}, {858,677}}, Line {{256,238}, {265,238}}, Line {{475,919}, {718,919}}, Line {{973,912}, {134,73}}, Line {{984,159}, {175,968}}, Line {{166,641}, {15,490}}, Line {{504,798}, {504,946}}, Line {{717,796}, {128,207}}, Line {{302,713}, {168,713}}, Line {{830,964}, {830,444}}, Line {{151,288}, {549,686}}, Line {{530,908}, {820,908}}, Line {{540,394}, {717,394}}, Line {{581,614}, {581,496}}, Line {{111,593}, {230,712}}, Line {{938,884}, {938,917}}, Line {{923,71}, {20,974}}, Line {{530,677}, {530,332}}, Line {{144,723}, {144,980}}, Line {{700,376}, {700,917}}, Line {{501,95}, {198,95}}, Line {{251,900}, {435,900}}, Line {{912,931}, {96,115}}, Line {{962,140}, {181,921}}, Line {{104,244}, {104,178}}, Line {{504,865}, {504,612}}, Line {{301,284}, {301,173}}, Line {{973,980}, {17,24}}, Line {{886,166}, {886,455}}, Line {{380,150}, {971,741}}, Line {{57,405}, {135,405}}, Line {{515,569}, {774,310}}, Line {{227,233}, {874,880}}, Line {{75,33}, {75,290}}, Line {{487,434}, {983,930}}, Line {{17,279}, {20,279}}, Line {{719,838}, {508,627}}, Line {{262,254}, {555,254}}, Line {{516,626}, {631,511}}, Line {{352,305}, {352,715}}, Line {{876,827}, {876,731}}, Line {{372,85}, {372,344}}, Line {{619,773}, {619,799}}, Line {{885,627}, {441,627}}, Line {{779,731}, {42,731}}, Line {{806,756}, {806,237}}, Line {{378,540}, {187,540}}, Line {{840,296}, {210,296}}, Line {{250,234}, {171,234}}, Line {{249,100}, {757,608}}, Line {{787,23}, {787,826}}, Line {{690,175}, {365,175}}, Line {{238,166}, {238,738}}, Line {{52,350}, {574,872}}, Line {{297,518}, {297,590}}, Line {{133,263}, {133,219}}, Line {{438,955}, {939,955}}, Line {{621,500}, {621,948}}, Line {{93,39}, {530,476}}, Line {{988,866}, {220,98}}, Line {{483,30}, {329,184}}, Line {{205,937}, {419,723}}, Line {{314,910}, {842,910}}, Line {{472,944}, {923,944}}, Line {{487,700}, {586,601}}, Line {{59,17}, {333,17}}, Line {{553,307}, {553,746}}, Line {{810,37}, {810,167}}, Line {{898,662}, {858,662}}, Line {{191,837}, {191,157}}, Line {{83,950}, {83,910}}, Line {{229,513}, {559,843}}, Line {{825,192}, {44,973}}, Line {{37,80}, {460,503}}, Line {{648,357}, {29,357}}, Line {{603,592}, {425,770}}, Line {{137,141}, {693,141}}, Line {{179,69}, {479,69}}, Line {{851,164}, {172,164}}, Line {{916,143}, {99,960}}, Line {{908,20}, {28,900}}, Line {{178,404}, {700,404}}, Line {{122,43}, {645,43}}, Line {{548,495}, {155,888}}, Line {{216,725}, {216,583}}, Line {{790,97}, {51,836}}, Line {{98,214}, {98,200}}, Line {{90,464}, {141,464}}, Line {{32,905}, {912,25}}, Line {{253,743}, {253,115}}, Line {{521,826}, {304,826}}, Line {{733,392}, {733,485}}, Line {{315,95}, {964,744}}, Line {{386,749}, {553,916}}, Line {{698,985}, {59,346}}, Line {{380,969}, {820,969}}, Line {{134,641}, {310,641}}, Line {{66,899}, {860,105}}, Line {{827,304}, {560,37}}, Line {{824,213}, {132,905}}, Line {{93,138}, {200,245}}, Line {{54,450}, {54,436}}, Line {{163,276}, {31,408}}, Line {{959,333}, {976,333}}, Line {{499,129}, {645,129}}, Line {{924,321}, {924,332}}, Line {{629,166}, {629,901}}, Line {{505,769}, {864,410}}, Line {{80,360}, {48,360}}, Line {{22,971}, {983,10}}, Line {{500,87}, {721,87}}, Line {{227,737}, {227,540}}, Line {{698,177}, {698,713}}, Line {{20,106}, {20,204}}, Line {{187,176}, {902,891}}, Line {{803,806}, {574,806}}, Line {{413,785}, {413,858}}, Line {{736,728}, {28,728}}, Line {{158,870}, {20,870}}, Line {{78,475}, {75,472}}, Line {{481,434}, {80,434}}, Line {{975,208}, {425,208}}, Line {{59,639}, {304,639}}, Line {{287,919}, {923,283}}, Line {{940,933}, {104,97}}, Line {{699,429}, {466,429}}, Line {{240,988}, {929,299}}, Line {{970,873}, {396,873}}, Line {{441,585}, {441,697}}, Line {{337,259}, {36,259}}, Line {{45,759}, {45,382}}, Line {{220,468}, {373,315}}, Line {{10,262}, {793,262}}, Line {{753,268}, {147,874}}, Line {{664,560}, {603,560}}, Line {{974,81}, {974,26}}, Line {{575,331}, {254,331}}, Line {{754,378}, {727,378}}, Line {{354,394}, {298,450}}, Line {{108,814}, {108,804}}, Line {{848,375}, {604,375}}, Line {{697,530}, {697,288}}, Line {{977,54}, {967,44}}, Line {{241,754}, {484,754}}, Line {{793,745}, {755,745}}, Line {{974,415}, {974,98}}, Line {{677,367}, {677,731}}, Line {{69,744}, {695,118}}, Line {{50,39}, {940,929}}, Line {{414,721}, {414,917}}, Line {{870,587}, {870,396}}, Line {{881,759}, {583,759}}, Line {{679,798}, {679,226}}, Line {{826,917}, {217,917}}, Line {{896,919}, {102,919}}, Line {{528,881}, {498,881}}, Line {{15,89}, {15,212}}, Line {{887,280}, {747,280}}, Line {{763,303}, {967,507}}, Line {{904,964}, {562,964}}, Line {{157,752}, {433,752}}, Line {{752,199}, {34,917}}, Line {{60,970}, {921,109}}, Line {{934,434}, {683,183}}, Line {{748,427}, {748,601}}, Line {{20,47}, {957,984}}, Line {{71,691}, {332,691}}, Line {{782,637}, {782,137}}, Line {{483,623}, {704,623}}, Line {{11,965}, {274,965}}, Line {{285,172}, {700,172}}, Line {{613,845}, {855,845}}, Line {{955,296}, {738,296}}, Line {{596,750}, {596,974}}, Line {{332,851}, {360,851}}, Line {{176,388}, {107,388}}, Line {{116,328}, {325,119}}, Line {{932,588}, {403,588}}, Line {{247,420}, {247,69}}, Line {{52,965}, {52,740}}, Line {{541,579}, {541,48}}, Line {{321,530}, {321,115}}, Line {{124,33}, {986,895}}, Line {{575,950}, {922,603}}, Line {{231,814}, {755,814}}, Line {{940,445}, {957,462}}, Line {{365,743}, {432,810}}, Line {{488,286}, {777,286}}, Line {{988,905}, {887,905}}, Line {{715,846}, {842,846}}, Line {{481,894}, {481,954}}, Line {{297,868}, {297,441}}, Line {{368,928}, {368,348}}, Line {{951,981}, {49,79}}, Line {{46,743}, {551,743}}, Line {{900,241}, {50,241}}, Line {{441,942}, {441,762}}, Line {{488,58}, {488,482}}, Line {{945,187}, {945,639}}, Line {{263,779}, {476,779}}, Line {{593,290}, {593,985}}, Line {{781,498}, {914,498}}, Line {{351,557}, {351,324}}, Line {{809,966}, {709,966}}, Line {{912,545}, {522,155}}, Line {{985,681}, {903,599}}, Line {{837,881}, {532,881}}, Line {{728,485}, {753,460}}, Line {{79,680}, {79,448}}, Line {{917,769}, {917,456}}, Line {{135,845}, {135,777}}, Line {{460,922}, {981,401}}, Line {{516,830}, {516,403}}, Line {{230,419}, {230,267}}, Line {{770,297}, {583,297}}, Line {{577,782}, {488,693}}, Line {{118,728}, {791,55}}, Line {{983,192}, {983,340}}, Line {{307,252}, {393,338}}, Line {{83,345}, {83,628}}, Line {{318,461}, {318,670}}, Line {{809,385}, {809,383}}, Line {{145,124}, {444,124}}, Line {{906,892}, {906,990}}, Line {{295,22}, {295,617}}, Line {{828,312}, {828,227}}, Line {{546,132}, {546,100}}, Line {{398,750}, {398,237}}, Line {{27,770}, {299,770}}, Line {{863,517}, {863,869}}, Line {{700,806}, {168,806}}, Line {{279,262}, {169,152}}, Line {{954,285}, {681,12}}, Line {{896,102}, {127,871}}, Line {{527,532}, {404,532}}, Line {{853,397}, {168,397}}, Line {{642,273}, {595,273}}, Line {{422,123}, {422,805}}, Line {{879,789}, {879,177}}, Line {{233,171}, {917,855}}, Line {{82,148}, {559,148}}, Line {{95,969}, {95,65}}, Line {{876,779}, {876,257}}, Line {{753,35}, {51,737}}, Line {{421,756}, {735,756}}, Line {{637,602}, {637,886}}, Line {{275,689}, {275,360}}, Line {{714,77}, {714,353}}, Line {{617,645}, {764,645}}, Line {{131,702}, {689,702}}, Line {{752,795}, {524,567}}, Line {{606,716}, {632,716}}, Line {{261,700}, {261,104}}, Line {{196,894}, {377,713}}, Line {{812,626}, {812,76}}, Line {{739,368}, {360,747}}, Line {{976,646}, {976,981}}, Line {{459,948}, {500,948}}, Line {{154,669}, {179,644}}, Line {{410,896}, {661,645}}, Line {{312,187}, {248,123}}, Line {{507,655}, {513,655}}, Line {{649,726}, {649,447}}, Line {{874,19}, {24,19}}, Line {{951,64}, {57,958}}, Line {{29,60}, {533,60}}, Line {{559,262}, {941,644}}, Line {{665,319}, {531,185}}, Line {{835,601}, {918,601}}, Line {{269,556}, {871,556}}, Line {{410,708}, {410,163}}, Line {{271,105}, {860,105}}, Line {{143,427}, {475,95}}, Line {{716,656}, {716,270}}, Line {{111,771}, {822,60}}, Line {{170,775}, {233,775}}, Line {{730,588}, {730,106}}, Line {{592,161}, {901,470}}, Line {{486,802}, {289,802}}, Line {{113,770}, {726,157}}, Line {{127,98}, {825,796}}, Line {{392,957}, {794,957}}, Line {{529,793}, {529,117}}, Line {{347,196}, {347,310}}, Line {{893,613}, {360,80}}, Line {{961,362}, {961,399}}, Line {{577,52}, {577,566}}, Line {{792,578}, {792,622}}, Line {{35,883}, {35,395}}, Line {{499,779}, {499,752}}, Line {{921,359}, {921,90}}, Line {{557,224}, {290,224}}, Line {{863,190}, {874,190}}, Line {{100,190}, {100,519}}, Line {{909,38}, {33,914}}, Line {{44,421}, {98,421}}, Line {{731,787}, {731,462}}, Line {{722,28}, {722,685}}, Line {{913,538}, {274,538}}, Line {{149,648}, {149,186}}, Line {{302,594}, {521,594}}, Line {{927,333}, {546,714}}, Line {{503,42}, {333,42}}, Line {{474,260}, {835,621}}, Line {{825,363}, {825,188}}, Line {{335,140}, {227,32}}, Line {{914,613}, {914,15}}, Line {{955,734}, {398,734}}, Line {{506,913}, {506,232}}, Line {{612,271}, {612,881}}, Line {{155,856}, {282,856}}, Line {{207,820}, {898,129}}, Line {{329,463}, {475,463}}, Line {{371,719}, {371,737}}, Line {{103,503}, {103,722}}, Line {{846,779}, {360,293}}, Line {{597,247}, {253,247}}, Line {{305,912}, {305,960}}, Line {{283,277}, {283,358}}, Line {{369,327}, {418,327}}, Line {{107,190}, {107,269}}, Line {{469,247}, {918,247}}, Line {{944,213}, {990,213}}, Line {{930,158}, {594,158}}, Line {{459,844}, {459,519}}, Line {{493,387}, {107,387}}, Line {{514,173}, {669,328}}, Line {{818,876}, {73,131}}, Line {{405,783}, {405,54}}, Line {{583,151}, {583,654}}, Line {{211,462}, {211,938}}, Line {{639,224}, {639,728}}, Line {{561,33}, {561,719}}, Line {{607,244}, {47,244}}, Line {{772,61}, {772,795}}, Line {{777,920}, {63,206}}, Line {{121,281}, {90,281}}, Line {{668,99}, {893,99}}, Line {{352,620}, {652,620}}, Line {{589,50}, {547,50}}, Line {{845,252}, {845,974}}, Line {{666,870}, {94,870}}, Line {{724,524}, {344,904}}, Line {{569,40}, {482,40}}, Line {{224,619}, {741,619}}, Line {{935,110}, {143,902}}, Line {{107,37}, {906,836}}, Line {{308,298}, {821,298}}, Line {{983,619}, {868,734}}, Line {{659,166}, {497,328}}, Line {{60,423}, {60,507}}, Line {{483,283}, {90,283}}, Line {{568,309}, {568,873}}, Line {{262,461}, {890,461}}, Line {{328,633}, {94,867}}, Line {{892,195}, {177,910}}, Line {{310,874}, {915,269}}, Line {{647,54}, {531,54}}, Line {{749,523}, {408,864}}, Line {{597,882}, {857,882}}, Line {{756,498}, {468,498}}, Line {{671,248}, {671,510}}, Line {{676,855}, {130,309}}, Line {{46,18}, {659,18}}, Line {{144,164}, {87,221}}, Line {{412,774}, {412,930}}, Line {{67,368}, {745,368}}, Line {{246,704}, {619,331}}, Line {{714,113}, {159,113}}, Line {{203,109}, {203,641}}, Line {{418,708}, {110,708}}, Line {{619,546}, {619,531}}, Line {{617,957}, {545,957}}, Line {{630,423}, {630,909}}, Line {{584,379}, {679,474}}, Line {{572,918}, {572,16}}, Line {{101,712}, {755,58}}, Line {{167,317}, {912,317}}, Line {{836,130}, {570,130}}, Line {{759,847}, {523,847}}, Line {{901,40}, {901,479}}, Line {{908,157}, {908,558}}, Line {{351,252}, {280,181}}, Line {{648,730}, {253,730}}, Line {{330,984}, {110,984}}, Line {{717,552}, {746,581}}, Line {{206,831}, {904,133}}, Line {{684,232}, {684,20}}, Line {{889,73}, {155,73}}, Line {{896,728}, {896,589}}, Line {{55,983}, {988,50}}, Line {{342,746}, {342,617}}, Line {{138,683}, {795,26}}, Line {{968,226}, {787,226}}, Line {{311,713}, {355,713}}, Line {{201,789}, {201,401}}, Line {{909,623}, {205,623}}, Line {{540,130}, {540,722}}, Line {{695,511}, {191,511}}, Line {{221,320}, {221,68}}, Line {{75,118}, {599,642}}, Line {{982,977}, {30,25}}, Line {{534,598}, {720,784}}, Line {{355,579}, {13,921}}, Line {{137,516}, {137,665}}, Line {{510,244}, {510,392}}, Line {{845,52}, {327,570}}, Line {{167,100}, {909,100}}, Line {{573,133}, {34,672}}, Line {{371,341}, {371,823}}, Line {{959,981}, {20,42}}, Line {{143,793}, {143,134}}, Line {{815,798}, {914,897}}, Line {{286,212}, {188,114}}, Line {{28,987}, {985,30}}, Line {{652,108}, {652,540}}, Line {{978,565}, {507,94}}, Line {{817,166}, {402,166}}, Line {{250,723}, {128,845}}, Line {{676,274}, {53,897}}, Line {{981,985}, {12,16}}, Line {{682,195}, {270,195}}, Line {{409,113}, {114,113}}, Line {{585,83}, {585,514}}, Line {{897,978}, {569,650}}, Line {{158,420}, {158,709}}, Line {{603,335}, {966,698}}, Line {{484,53}, {972,541}}, Line {{149,128}, {149,329}}, Line {{555,926}, {555,393}}, Line {{143,849}, {614,378}}, Line {{816,79}, {507,79}}, Line {{525,502}, {812,502}}, Line {{736,509}, {736,579}}, Line {{612,179}, {629,179}}, Line {{821,70}, {821,566}}, Line {{665,90}, {416,90}}, Line {{63,80}, {837,854}}, Line {{151,873}, {890,134}}, Line {{698,204}, {698,973}}, Line {{936,693}, {612,369}}, Line {{369,628}, {947,50}}, Line {{308,407}, {308,590}}, Line {{367,156}, {963,752}}, Line {{949,943}, {536,530}}, Line {{589,553}, {256,886}}, Line {{348,171}, {348,759}}, Line {{546,488}, {546,585}}, Line {{351,486}, {779,58}}, Line {{952,45}, {33,964}}, Line {{187,896}, {187,100}}, Line {{725,679}, {725,486}}, Line {{756,147}, {264,639}}, Line {{281,205}, {281,764}}, Line {{630,221}, {73,221}}, Line {{919,953}, {775,953}}, Line {{552,821}, {925,821}}, Line {{294,854}, {922,226}}, Line {{772,642}, {961,831}}, Line {{705,159}, {308,556}}, Line {{107,983}, {393,697}}, Line {{403,277}, {403,802}}, Line {{719,824}, {719,187}}, Line {{947,956}, {253,956}}, Line {{453,135}, {952,135}}, Line {{905,491}, {574,160}}, Line {{498,225}, {764,491}}, Line {{741,111}, {597,111}}, Line {{881,130}, {881,668}}, Line {{308,616}, {866,616}}, Line {{172,434}, {855,434}}, Line {{218,412}, {218,861}}, Line {{293,318}, {293,770}}, Line {{712,513}, {679,513}}, Line {{100,586}, {434,920}}, Line {{338,407}, {176,407}}, Line {{481,534}, {715,768}}, Line {{805,127}, {216,127}}, Line {{406,425}, {322,425}}, Line {{154,769}, {823,100}}, Line {{813,508}, {159,508}}, Line {{286,637}, {286,24}}, Line {{55,836}, {665,836}}, Line {{571,857}, {459,969}}, Line {{414,977}, {414,604}}, Line {{133,884}, {972,45}}, Line {{383,522}, {383,141}}, Line {{889,14}, {62,841}}, Line {{122,49}, {43,49}}, Line {{544,846}, {544,76}}, Line {{948,19}, {62,905}}, Line {{798,577}, {833,542}}, Line {{973,267}, {751,45}}, Line {{620,648}, {620,419}}, Line {{102,813}, {633,813}}, Line {{255,263}, {826,263}}, Line {{231,394}, {231,811}}};
constexpr bool isVertical(const Line& line) { return line.start.y == line.end.y; }
constexpr bool isHorizontal(const Line& line) { return line.start.x == line.end.x; }
bool isDiagonal(const Line& line) { return std::abs(line.start.x - line.end.x) == std::abs(line.start.y - line.end.y); }

constexpr int getGridSize() {
    int max{0};
    for(const auto& line : input_lines)
    {
        max = std::max({max, line.start.x, line.start.y, line.end.x, line.end.y});
    }
    return max;
}

int main()
{
    std::array<std::array<int, getGridSize()>, getGridSize()> grid{0};
    for(const auto& line : input_lines)
    {
        if(isVertical(line))
        {
            auto[min, max] = std::minmax(line.start.x, line.end.x);
            for(int i = min; i<= max; ++i)
            {
                ++grid[i][line.start.y];
            }
        }
        if(isHorizontal(line))
        {
            auto[min, max] = std::minmax(line.start.y, line.end.y);
            for(int i = min; i<= max; ++i)
            {
                ++grid[line.start.x][i];
            }
        }
        if(isDiagonal(line))
        {
            auto lineSize = std::abs(line.start.x - line.end.x);
            auto xdirection = (line.start.x - line.end.x) < 0 ? 1 : -1 ;
            auto ydirection = (line.start.y - line.end.y) < 0 ? 1 : -1 ;
            for(int i = 0; i<= lineSize; ++i)
            {
                ++grid[line.start.x + (i * xdirection)][line.start.y + (i * ydirection)];
            }
        }
    }

    const auto numberOfDangerousAreas = std::accumulate(std::begin(grid), std::end(grid), 0, [](const auto& sum, const auto& line){
       return sum + std::count_if(std::begin(line), std::end(line), [](const auto& point){ return point >= 2; }); 
    });
    std::cout << "The solution is: " << numberOfDangerousAreas << std::endl;

    return 0;
}
