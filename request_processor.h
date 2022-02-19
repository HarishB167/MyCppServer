#include <string>

#pragma once

using namespace std;

struct HTTP_Request;
string prepareResponse(HTTP_Request request);
string processHTTPRequest(string data);
