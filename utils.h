#include <vector>
#include <string>
#pragma once

using namespace std;

// Ref : https://stackoverflow.com/questions/13172158/c-split-string-by-line
vector<string> doSegment(char *sentence, char separtor = '\n');
vector<string> doSegment(string str_sentence, char separator = '\n');

int printFirstNLines(int numberOfLines, char *sentence);
void print(string text);
bool fileExists(string path);

// Ref : https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
void sleep(int milliseconds);
