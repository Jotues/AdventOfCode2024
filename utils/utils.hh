#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <ranges>
#include <sstream>

namespace utils 
{
    using namespace std;


    vector<std::string> getLinesOfFile(const std::string& filename);
    vector<std::string> splitStringByDelimeter(const std::string& str, const std::string& delimiter);

    template <typename T>
    concept Printable = requires(std::ostream& os, T a)
    {
        os<<a;
    };

    template<Printable T1, Printable T2>
    std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> pair)
    {
        os<<"{"<<pair.first<<" "<<pair.second<<"}";
        return os;
    }

    template<std::ranges::range T>
    void printRange(const T& v)
    {
        std::cout<<"[";
        for (const auto& e: v)
        {
            if constexpr (std::is_same<decltype(e), const int8_t&>::value)
            {
                std::cout<<static_cast<int>(e)<<", ";
            }
            else
            {
                std::cout<<e<<", ";
            }
        }
        std::cout<<"]\n";
    }

    template<integral T>
    std::vector<T> getIntsFromString(const std::string& str)
    {
        std::vector<T> vec;
        std::stringstream ss;
        ss << str;
        if constexpr(std::is_same<T, int8_t>::value)
        {
            int16_t num = 0;
            while (ss >> num)
            {
                vec.push_back(static_cast<int8_t>(num));
            } 
        }
        else
        {
            T num = 0;
            while (ss >> num)
            {
                vec.push_back(num);
            }
        }
        return vec;
    }

}