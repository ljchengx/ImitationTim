#pragma once
#include "StdAfx.h"
#include <string>

class UserInfo
{
public:
	UserInfo();
	~UserInfo();
	string getId();
	string getUserName();
	string getPwd();


	void setId(string id);
	void setUserName(string userName);
	void setPwd(string pwd);
	friend void from_json(const json& j, UserInfo& h);

private:
	 string id;
	string name;
	string pwd;
};