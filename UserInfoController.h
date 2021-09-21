#pragma once
#include "StdAfx.h"
#include <string>
#include "UserInfo.h"
#include "SqliteUtil.h"

class UserController
{
public:
	UserController();
	~UserController();

	UserInfo parseFromJson(const string& jsonstr);
	bool saveUserInfoToFile(UserInfo info, const string& filepath);
	UserInfo getUserInfoFromFile(const string& filepath);
private:

};

