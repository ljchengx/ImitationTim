#include "StdAfx.h"
#include "UserInfo.h"
#include "StringUtil.h"

class SqliteUtil
{
public:
	static SqliteUtil& Get();
	static bool saveUserInfoToFile(UserInfo info, const string& filepath);
	static UserInfo getUserInfoFromFile(const string& filepath);

private:

};
