#include <iostream>
#include <string>
#include <cstdlib>
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
    if(input == "exit")
    {
        cout << "Exiting XSH..." << endl;
        return false;
    }

    cout << "Command entered: "
         << input
         << endl;

    return true;
}
