#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include "shell.h"

using namespace std;

/*
 * Executes commands connected by pipes.
 */
void pipeCommand(vector<vector<string>> commands)
{
    int n = commands.size();

    // Ensures to create enough pipes for all commands
    int pipes[n - 1][2];

    // Creates the pipes
    for(int i = 0; i < n - 1; i++)
    {
        if(pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return;
        }
    }

    // Create ONE child process PER command
    for(int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if(pid == 0)
        {
            // If its not the first command then read from previous pipe
            if(i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);

            // If its not the last command then write to the next pipe
            if(i < n - 1)
                dup2(pipes[i][1], STDOUT_FILENO);

            // Close pipe file discriptors (all)
            for(int j = 0; j < n - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            vector<char*> args;

            for(size_t k = 0; k < commands[i].size(); k++)
                args.push_back(const_cast<char*>(commands[i][k].c_str()));

            // NULL terminator required by execvp
            args.push_back(NULL);

            execvp(args[0], args.data());

            // If execvp fails
            perror("execvp");
            exit(1);
        }
    }

    for(int i = 0; i < n - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Must wait for all child processes to finish
    for(int i = 0; i < n; i++)
        wait(NULL);
}
