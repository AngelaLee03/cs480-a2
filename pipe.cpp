#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include "shell.h"

using namespace std;

void executePipeCommand(vector<vector<string>> commands)
{
    int n = commands.size();

    int pipes[n - 1][2];

    for(int i = 0; i < n - 1; i++)
    {
        if(pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return;
        }
    }

    for(int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if(pid == 0)
        {
            if(i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);

            if(i < n - 1)
                dup2(pipes[i][1], STDOUT_FILENO);

            for(int j = 0; j < n - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            vector<char*> args;

            for(size_t k = 0; k < commands[i].size(); k++)
                args.push_back(const_cast<char*>(commands[i][k].c_str()));

            args.push_back(NULL);

            execvp(args[0], args.data());

            perror("execvp");
            exit(1);
        }
    }

    for(int i = 0; i < n - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for(int i = 0; i < n; i++)
        wait(NULL);
}
