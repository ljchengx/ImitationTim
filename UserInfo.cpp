#include "StdAfx.h"
#include "UserInfo.h"

UserInfo::UserInfo()
{
}

UserInfo::~UserInfo()
{
}

string UserInfo::getId()
{
	return id;
}

string UserInfo::getUserName()
{
	return name;
}

string UserInfo::getPwd()
{
	return pwd;
}

void UserInfo::setId(string id)
{
	this->id = id;
}

void UserInfo::setUserName(string userName)
{
	this->name = userName;
}

void UserInfo::setPwd(string pwd)
{
	this->pwd = pwd;
}

void from_json(const json& j, UserInfo& h) {
	j.at("id").get_to(h.id);
	j.at("name").get_to(h.name);
	j.at("pwd").get_to(h.pwd);
}