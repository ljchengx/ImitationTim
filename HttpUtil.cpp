#include "StdAfx.h"
#include "HttpUtil.h"

HttpUtil& HttpUtil::Get()
{
	static HttpUtil m_httpUtil;
	return m_httpUtil;
}
HttpUtil::HttpUtil()
{

}

string UTF8ToGBK(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	WCHAR* wszGBK = new WCHAR[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}

string HttpUtil::HttpPost(const char* url)
{
	CURL* curl;
	CURLcode res;
	struct curl_slist* headerlist = NULL;
	std::string readBuffer;

	curl = curl_easy_init();

	headerlist = curl_slist_append(headerlist, "Expect:");
	headerlist = curl_slist_append(headerlist, "Content-Type: application/json;charset=UTF-8");

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlSaveResponseToStdString);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		curl_slist_free_all(headerlist);

		if (res == CURLE_OK)
		{
			return UTF8ToGBK(readBuffer) ;
		}

	}
	return string();
}

string HttpUtil::HttpGet(const char* url)
{
	CURL* curl;
	CURLcode res;
	struct curl_slist* headerlist = NULL;
	std::string readBuffer;

	curl = curl_easy_init();

	headerlist = curl_slist_append(headerlist, "Expect:");
	headerlist = curl_slist_append(headerlist, "Content-Type: application/json;charset=UTF-8");

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlSaveResponseToStdString);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		curl_slist_free_all(headerlist);

		if (res == CURLE_OK)
		{
			return UTF8ToGBK(readBuffer);
		}

	}
	return string();
}

size_t HttpUtil::curlSaveResponseToStdString(void* contents, size_t size, size_t nmemb, string* s)
{
	size_t newLength = size * nmemb;
	size_t oldLength = s->size();
	s->resize(oldLength + newLength);
	std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);

	return size * nmemb;
}
