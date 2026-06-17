#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>
#include "shell.h"

using namespace std;

/*
 * Displays shell prompt.
 */
void displayPrompt()
{
    char* user = getenv("USER");

    if(user != NULL)
        cout << user << "% ";
    else
        cout << "xsh% ";
}

/*
 * Processes user commands.
 */
bool handleCommand(string input)
{
    vector<string> tokens;
    string token;
    stringstream ss(input);

    while(ss >> token)
    {
        tokens.push_back(token);
    }

    // Empty input just shows a new prompt
    if(tokens.size() == 0)
        return true;

    // Exit builtin
    if(tokens[0] == "exit")
    {
        if(tokens.size() == 1)
        {
            cout << "Exiting XSH..." << endl;
            return false;
        }

        cout << "Error: exit does not take arguments." << endl;
        return true;
    }

    // Reject more than one argument for non-pipe commands
    if(tokens.size() > 2)
    {
        cout << "Error: invalid command format." << endl;
        return true;
    }

    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return true;
    }

    if(pid == 0)
    {
        vector<char*> args;

        for(size_t i = 0; i < tokens.size(); i++)
            args.push_back(const_cast<char*>(tokens[i].c_str()));

        args.push_back(NULL);

        execvp(args[0], args.data());

        perror("execvp");
        exit(-1);
    }

    if(wait(NULL) == -1)
    {
        perror("wait");
    }

    return true;
}
