#include <utils.hh>
#include <utils_time.hh>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include "Solution.hh"
#include <cmath>
#include <unordered_set>
#include <set>

using namespace std;

Solution::Solution(const std::string& input)
{

    auto lines = utils::getLinesOfFile(input);

    uint64_t registerA = stoull(lines[0].substr(lines[0].find("A: ") + 3));
    uint64_t registerB = stoull(lines[1].substr(lines[1].find("B: ") + 3));
    uint64_t registerC = stoull(lines[2].substr(lines[2].find("C: ") + 3));
    std::string result = "";

    auto numCalculated = 0u;
    auto operation = [&registerA, &registerB, &registerC, &result, &numCalculated](uint8_t opcode, uint8_t operand, size_t& ip)
    {
        // printf("Program %u %u, IP: %lu, Registers {%llu, %llu, %llu} | \n", opcode, operand, ip, registerA, registerB, registerC);

        auto comboOperand = [&](uint8_t operand) -> uint64_t
        {
            switch (operand)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                {
                    return operand;
                }
                case 4:
                {
                    return registerA;
                }
                case 5:
                {
                    return registerB;
                }
                case 6:
                {
                    return registerC;
                }
                default:
                {
                    assert(false);
                }
            }
        };

        switch (opcode)
        {
            case 0:
            {
                registerA = registerA/(std::pow(2, comboOperand(operand)));
                ip += 2;
                break;
            }
            case 1:
            {
                registerB = registerB ^ operand;
                ip += 2;
                break;
            }
            case 2:
            {
                registerB = comboOperand(operand) % 8;
                ip += 2;
                break;
            }
            case 3:
            {
                if (registerA == 0)
                {
                    ip += 2;
                }
                else
                {
                    ip = operand;
                }
                break;
            }
            case 4:
            {
                registerB = registerB ^ registerC;
                ip += 2;
                break;
            }
            case 5:
            {
                numCalculated = comboOperand(operand) % 8;
                stringstream ss;
                ss << numCalculated << ",";
                result += ss.str();
                ip += 2;
                break;
            }
            case 6:
            {
                registerB = registerA/(std::pow(2, comboOperand(operand)));
                ip += 2;
                break;
            }
            case 7:
            {
                registerC = registerA/(std::pow(2, comboOperand(operand)));
                ip += 2;
                break;
            }
            default:
            {
                assert(false);
            }
        }
    };

    auto program = lines[4].substr(lines[4].find(": ") + 2);
    auto vec = utils::splitStringByDelimeter(program, ",");
    utils::printRange(vec);

    std::vector<uint8_t> vecNum;

    for (auto& str: vec)
    {
        vecNum.push_back(stoul(str));
    }
    registerA = 107416732707226;
    for (auto i = 0ul; i < vecNum.size(); )
    {
        operation(vecNum[i], vecNum[i+1], i);
    }
    printf("%s\n", result.c_str());

    registerB = 0;
    registerC = 0;
    result = "";

    //program = 16 digits, each time we bit shift register A 3bits to right - starting regA must be between 45-48bits
    auto registerAMin = 35184372088832;
    auto registerAMax = 281474976710655ull;

    std::unordered_map<uint16_t, uint8_t> hashMap;
    std::set<uint32_t> valuesOk8Digits;

    // STEP 1
    // prepare first 31 bits (2147483647 = 2^31 - 1) = which is equal to 8 printed digits
    // then we can find the rest about 48-31 = 17 bits (MSB)
    for (auto j = registerAMin; j <= registerAMin + 2147483647; j++)
    {
        registerA = j;
        auto iter = 0u;

        while (true)
        {
            int numToUse = registerA & 0b01111111111;
            if (hashMap.contains(numToUse))
            {
                numCalculated = hashMap[numToUse];
            }
            else
            {
                for (auto i = 0ul; i < vecNum.size(); )
                {
                    auto opcode = vecNum[i];
                    operation(opcode, vecNum[i+1], i);

                    if (opcode == 5)
                    {
                        break;
                    }
                }
                hashMap.emplace(numToUse, numCalculated);
            }

            if (numCalculated != vecNum[iter])
            {
                break;
            }
            else if (iter >= 7) // 8 digits musut be quel (7 0-based)
            {
                valuesOk8Digits.insert(j - registerAMin);
                break;
            }
            iter++;
            registerA = registerA >> 3;
        }
    }

    result.clear();

    //STEP 2 - find 17 most significant bits - LSB are values hidden in valuesOk8Digits set
    for (auto j = 0llu; j <= 131071; j++)
    {
        for (auto bits31: valuesOk8Digits)
        {
            uint64_t valueTested = registerAMin + (j << 31) + bits31;

            registerA = valueTested;
            auto iter = 0u;

            while (true)
            {
                int numToUse = registerA & 0b01111111111;

                numCalculated = hashMap[numToUse];

                if (numCalculated != vecNum[iter])
                {
                    break;
                }
                else if (iter >= 15)
                {
                    printf("Value found =  %llu\n", valueTested);
                    return;
                }
                iter++;
                registerA = registerA >> 3;
            }
        }
    }
}

int main()
{
    TaskTime task;
    // Solution example("../inputs/example17.txt");
    // Solution example("../inputs/example17_2.txt");
    Solution real("../inputs/input17.txt");

    task.endTaskAndPrintTime();
    return 0;
}