/*
 * CS480 Summer 2026
 * Programming Assignment #2 - XSH
 * Angela Lee (cssc3130)
 * Caitlin Corpus (cssc3114)      
 */

#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>

void displayPrompt();
bool handleCommand(std::string input);
void pipeCommand(std::vector<std::vector<std::string>> commands);

#endif

