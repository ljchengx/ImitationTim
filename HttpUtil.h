#pragma once
#include "StdAfx.h"
#include "libcURL/include/curl.h"
#include <string>


class HttpUtil
{
public:
	static HttpUtil& Get();
	static string HttpPost(const char* url);

	static string HttpGet(const char* url);

private:
	HttpUtil();
	static size_t curlSaveResponseToStdString(void* contents, size_t size, size_t nmemb, string* s);
};
