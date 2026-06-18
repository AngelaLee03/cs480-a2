/*
 * CS480 Summer 2026
 * Programming Assignment #2 - XSH
 * Angela Lee (cssc3130)
 * Caitlin Corpus (cssc3114)      
 */

#include <iostream>
#include <string>
#include "shell.h"

using namespace std;

/*
 * Main function for XSH.
 * The main function acts like a table of contents:
 * display the prompt, read input, process command, and repeat.
 */
int main()
{
    string input;
   
    while(true)
    {
        // Display shell prompt
        displayPrompt();

	// Read full command line from user
        getline(cin, input);

	// Process command; false means exit shell
        if(!handleCommand(input))
            break;
    }

    return 0;
}
