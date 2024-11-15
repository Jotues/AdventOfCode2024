#include "utils.hh"

#include <fstream>

namespace utils 
{
    vector<string> splitStringByDelimeter(const string& str, const string& delimiter)
    {
        string edited = str;
        vector<string> result;

        std::string token;
        size_t pos = 0;
        while ((pos = edited.find(delimiter)) != std::string::npos) 
        {
            token = edited.substr(0, pos);
            result.push_back(token);
            edited.erase(0, pos + delimiter.length());
        }

        result.push_back(edited);

        return result;
    }

    vector<string> getLinesOfFile(const string& filename)
    {
        std::ifstream infile(filename);
        vector<string> result;
        if (!infile.is_open())
        {
            printf("Can't open file %s! It doesn't exist!\n", filename.c_str());
            return result;
        }
        std::string line;
        while (std::getline(infile, line))
        {
            result.push_back(line);
        }
        return result;
    }

}