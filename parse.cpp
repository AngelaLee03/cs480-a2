#include "parse.h"
#include <sstream>

using namespace std;

bool parseInput(const string& input,
                vector<Command>& commands)
{
    string segment;
    stringstream ss(input);

    while(getline(ss, segment, '|'))
    {
        stringstream cmdStream(segment);

        Command cmd;

        if(!(cmdStream >> cmd.executable))
            return false;

        string extra;

        if(cmdStream >> cmd.argument)
        {
            if(cmdStream >> extra)
                return false;
        }

        commands.push_back(cmd);
    }

    return !commands.empty();
}
