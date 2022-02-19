#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

#include "utils.h"

using namespace std;

struct HTTP_Request
{
    string requestType;
    string requestRoute;
    string body;
    int responseType;
};

map<int, string> RequestTypeDict{
    {200, "OK"},
    {404, "Not Found"},
    {400, "Bad request"},
};

string getResponseType(HTTP_Request request)
{
    return RequestTypeDict[request.responseType];
}

string prepareResponse(HTTP_Request request)
{
    string response = "HTTP/1.1 " + to_string(request.responseType) + " " + getResponseType(request) + "\n";
    response += "Content-Type: text/html\n";
    response += "Content-Length: " + to_string(request.body.size()) + "\n\n";
    response += request.body;
    return response;
}

string processHTTPRequest(string data)
{
    HTTP_Request httpRequest;
    vector<string> sList;
    sList = doSegment(data);
    string firstLine = sList[0];
    print(firstLine);
    vector<string> firstLineWords;
    firstLineWords = doSegment(firstLine, ' ');
    httpRequest.requestType = firstLineWords[0];
    httpRequest.requestRoute = firstLineWords[1];
    httpRequest.requestRoute = httpRequest.requestRoute.substr(1);
    print("Request type : '" + httpRequest.requestType + "'");
    print("Route requested : '" + httpRequest.requestRoute + "'");
    if (fileExists(httpRequest.requestRoute))
    {
        print("Given file exists.");
        ifstream t(httpRequest.requestRoute);
        stringstream buffer;
        buffer << t.rdbuf();
        print("File read as ");
        print(buffer.str());
        httpRequest.body = buffer.str();
        httpRequest.responseType = 200;
    }
    else
    {
        print("Given file NOT exists.");
        httpRequest.body = "<h2>404 Not Found</h2>";
        httpRequest.responseType = 404;
    }

    return prepareResponse(httpRequest);
}