#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

struct Command
{
    std::string executable;
    std::string argument;
};

bool parseInput(const std::string& input,
                std::vector<Command>& commands);

#endif
