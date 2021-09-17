#include "StdAfx.h"
#include "UserInfoController.h"


sqlite3* pDB = NULL;

UserController::UserController()
{
}

UserController::~UserController()
{

}

//parseFromJson
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

//UtoG
char* U2G(const char* utf8)
{


	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//GtoU
char* G2U(const char* gb2312)
{


	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//save db 
bool UserController::saveUserInfoToFile(UserInfo info, const string& filepath)
{
	int nRes = sqlite3_open(filepath.c_str(), &pDB);
	if (nRes != SQLITE_OK)
	{
		goto QUIT;
	}
	else
	{

		string strSql = "";
		strSql += "insert into tim_user(id,name,pwd)";
		strSql += "values('";
		strSql += info.getId();
		strSql += "','";
		strSql += info.getUserName();
		strSql += "','";
		strSql += info.getPwd();
		strSql += "'";
		strSql += ");";


		char* cErrMsg;
		int nRes = sqlite3_exec(pDB, G2U(strSql.c_str()), 0, 0, &cErrMsg);

		if (nRes != SQLITE_OK)
		{
			goto QUIT;
		}
		else
		{
			return true;
		}
	}



QUIT:
	sqlite3_close(pDB);
	return false;
}


//get db
UserInfo UserController::getUserInfoFromFile(const string& filepath)
{
	UserInfo info ;

	int nRes = sqlite3_open(filepath.c_str(), &pDB);
	if (nRes != SQLITE_OK)
	{
		goto QUIT;
	}
	else
	{

		sqlite3_stmt* stmt = NULL;

		int nRes = sqlite3_prepare_v2(pDB, "select name , pwd  from tim_user", -1, &stmt, NULL);

		if (nRes == SQLITE_OK)
		{

			// ÿ��һ��sqlite3_step()������stmt������ͻ�ָ����һ����¼
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				// ȡ����0���ֶε�ֵ
				const char* name = (char*)sqlite3_column_text(stmt, 0);
				// ȡ����1���ֶε�ֵ
				const char* pwd = (char*)sqlite3_column_text(stmt, 1);

				info.setUserName(U2G(name));
				info.setPwd(U2G(pwd));

			}

		}
	}



QUIT:
	sqlite3_close(pDB);
	return info;
}

