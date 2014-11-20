#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>


std::vector<std::string> tokenize(std::string line, char delim) // particiona una line, en varios token y lo almacena en un vector<string>
{
    std::vector<std::string> tokens;

    std::istringstream iss(line); // trata un string como un stream object.
    std::string token;
    while (!iss.eof()) // sino llega al final
    {
        std::getline(iss, token, delim);
        tokens.push_back(token);
    }

    return std::move(tokens);
}

static inline std::string toLowerCase(std::string s)
{
    for (auto& c : s)
        c = std::tolower(c);

    return s;
}



#endif // UTIL_H
