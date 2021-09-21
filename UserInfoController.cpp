#include "StdAfx.h"
#include "UserInfoController.h"



UserController::UserController()
{
}

UserController::~UserController()
{

}

//Json�����л�
UserInfo UserController::parseFromJson(const string& jsonstr)
{
	UserInfo info;

	auto _json = json::parse(jsonstr);
	auto _info = _json.get<UserInfo>();

	info.setId(_info.getId());
	info.setUserName(_info.getUserName());
	info.setPwd(_info.getPwd());
	return info;
}



//�������ݿ�
bool UserController::saveUserInfoToFile(UserInfo info, const string& filepath)
{
	return SqliteUtil::Get().saveUserInfoToFile(info,filepath);
}


//�����ݿ��ȡ
UserInfo UserController::getUserInfoFromFile(const string& filepath)
{
	return SqliteUtil::Get().getUserInfoFromFile(filepath);
}

