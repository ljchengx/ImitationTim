#pragma once
#include "StdAfx.h"
#include <string>

class StringUtil
{
public:
	static StringUtil& Get();
	static char* U2G(const char* utf8);
	static char* G2U(const char* utf8);


private:
};