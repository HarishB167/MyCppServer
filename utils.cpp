#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <valarray>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include <fstream>

#include "utils.h"

using namespace std;

// Ref : https://stackoverflow.com/questions/13172158/c-split-string-by-line
vector<string> doSegment(char *sentence, char separator)
{
    stringstream ss(sentence);
    string to;
    vector<string> stringList;

    if (sentence != NULL)
    {
        while (getline(ss, to, separator))
        {
            stringList.push_back(to);
        }
    }

    return stringList;
}

vector<string> doSegment(string str_sentence, char separator)
{
    char *sentence = &str_sentence[0];
    stringstream ss(sentence);
    string to;
    vector<string> stringList;

    if (sentence != NULL)
    {
        while (getline(ss, to, separator))
        {
            stringList.push_back(to);
        }
    }

    return stringList;
}

int printFirstNLines(int numberOfLines, char *sentence)
{
    vector<string> sList;
    sList = doSegment(sentence);
    sList = std::vector<string>(sList.begin(), sList.begin() + numberOfLines);
    for (auto i : sList)
        std::cout
            << i << endl;
    return 1;
}

void print(string text)
{
    cout << text << endl;
}

void processHTTPRequest_old(string data)
{
    print("/////////////////////////////////////");
    print("Processing HTTP Request");
    vector<string> sList;
    sList = doSegment(data);
    string firstLine = sList[0];
    print(firstLine);
    vector<string> firstLineWords;
    firstLineWords = doSegment(firstLine, ' ');
    string requestType = firstLineWords[0];
    string requestRoute = firstLineWords[1];
    requestRoute = requestRoute.substr(1);
    print("Request type : '" + requestType + "'");
    print("Route requested : '" + requestRoute + "'");
    if (fileExists(requestRoute))
    {
        print("Given file exists.");
        ifstream t(requestRoute);
        stringstream buffer;
        buffer << t.rdbuf();
        print("File read as ");
        print(buffer.str());
    }
    else
    {
        print("Given file NOT exists.");
    }
    print("/////////////////////////////////////");
}

bool fileExists(string path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

// Ref : https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
void sleep(int milliseconds)
{
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}