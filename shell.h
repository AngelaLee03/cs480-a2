#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>

void displayPrompt();
bool handleCommand(std::string input);
void pipeCommand(std::vector<std::vector<std::string>> commands);

#endif

