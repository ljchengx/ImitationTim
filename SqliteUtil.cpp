#include "StdAfx.h"
#include "SqliteUtil.h"
#include "sqlite3.h"


sqlite3* pDB = NULL;

SqliteUtil& SqliteUtil::Get()
{
	static SqliteUtil m_sqliteUtil;
	return m_sqliteUtil;
}

bool SqliteUtil::saveUserInfoToFile(UserInfo info, const string& filepath)
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

		;

		char* cErrMsg;
		int nRes = sqlite3_exec(pDB, StringUtil::Get().G2U(strSql.c_str()), 0, 0, &cErrMsg);

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

UserInfo SqliteUtil::getUserInfoFromFile(const string& filepath)
{

	UserInfo info;

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

			// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				// 取出第0列字段的值
				const char* name = (char*)sqlite3_column_text(stmt, 0);
				// 取出第1列字段的值
				const char* pwd = (char*)sqlite3_column_text(stmt, 1);

				info.setUserName(StringUtil::Get().U2G(name));
				info.setPwd(StringUtil::Get().U2G(pwd));

			}

		}
	}



QUIT:
	sqlite3_close(pDB);
	return info;
}
