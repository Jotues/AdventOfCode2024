#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include <cmath>

using namespace std;

Solution::Solution(const std::string& input)
{
    auto lines = utils::getLinesOfFile(input);

    struct Machine
    {
        uint32_t A_x;
        uint32_t A_y;
        uint32_t B_x;
        uint32_t B_y;

        uint64_t prize_X;
        uint64_t prize_Y;

        void print() const
        {
            printf("Ax %u Ay %u Bx %u By %u  pr X %u pr Y %u\n", A_x, A_y, B_x, B_y, prize_X, prize_Y);
        }
    };
    
    std::vector<Machine> machines;
    for (auto i = 0u; i< lines.size(); i += 4)
    {
        Machine m;
        m.A_x = stoul(lines[i].substr(lines[i].find("X+") + 2, 2));
        m.A_y = stoul(lines[i].substr(lines[i].find("Y+") + 2, 2));
        m.B_x = stoul(lines[i + 1].substr(lines[i + 1].find("X+") + 2, 2));
        m.B_y = stoul(lines[i + 1].substr(lines[i + 1].find("Y+") + 2, 2));
        m.prize_X = stoul(lines[i + 2].substr(lines[i + 2].find("X=") + 2, lines[i + 2].find(',') - lines[i + 2].find("X=") - 2));
        m.prize_Y = stoul(lines[i + 2].substr(lines[i + 2].find("Y=") + 2));
        machines.push_back(m);
    }

    for (const auto& m: machines)
    {
        // m.print();
        int32_t det = (m.A_x * m.B_y) - (m.A_y * m.B_x);
        if (det == 0)
        {
            // printf("No result possible det = 0!\n");
            continue;
        }

        int32_t dy = (m.A_x * m.prize_Y) - (m.A_y * m.prize_X);
        int32_t dx = (m.prize_X * m.B_y) - (m.prize_Y * m.B_x);
        double b = static_cast<double>(dy)/static_cast<double>(det);
        double a = static_cast<double>(dx)/static_cast<double>(det);
        double a_integral {};
        double b_integral {};
        double fractionalA = std::modf(a, &a_integral);
        double fractionalB = std::modf(b, &b_integral);

        if (std::abs(fractionalA) > 0.01 || std::abs(fractionalB) > 0.01)
        {
            // printf("No int result - skipping (a = %lf, b = %lf)\n", a, b);
            continue;
        }

        if (a > 100 || b > 100)
        {

            // printf("No <100 result - skipping (a = %lf, b = %lf)\n", a, b);
            continue;
        }

        auto tokens = static_cast<uint32_t>(a_integral) * 3 + static_cast<uint32_t>(b_integral);
        // printf("Tokens = %u\n\n");
        resultPart1 += tokens;

    }

     //part 2
    for (auto& m: machines)
    {
        m.prize_X += 10000000000000u;
        m.prize_Y += 10000000000000u;
        int64_t det = static_cast<int64_t>(m.A_x * m.B_y) - static_cast<int64_t>(m.A_y * m.B_x);
        if (det == 0)
        {
            printf("No result possible det = 0!\n");
            continue;
        }
        int64_t dy = (static_cast<uint64_t>(m.A_x) * m.prize_Y) - (static_cast<uint64_t>(m.A_y) * m.prize_X);
        int64_t dx = (m.prize_X * static_cast<uint64_t>(m.B_y)) - (m.prize_Y * static_cast<uint64_t>(m.B_x));
        double b = static_cast<double>(dy)/static_cast<double>(det);
        double a = static_cast<double>(dx)/static_cast<double>(det);
        double a_integral {};
        double b_integral {};
        double fractionalA = std::modf(a, &a_integral);
        double fractionalB = std::modf(b, &b_integral);
        if (std::abs(fractionalA) > 0.01 || std::abs(fractionalB) > 0.01)
        {
            // printf("No int result - skipping (a = %lf, b = %lf)\n", a, b);
            continue;
        }

        auto tokens = static_cast<uint64_t>(a_integral) * 3 + static_cast<uint64_t>(b_integral);
        // printf("Tokens = %lu\n\n", tokens);
        resultPart2 += tokens;
    }

    printResult(input);
}

int main()
{
    TaskTime task;
    Solution example("../inputs/example13.txt");
    Solution real("../inputs/input13.txt");

    task.endTaskAndPrintTime();
    return 0;
}