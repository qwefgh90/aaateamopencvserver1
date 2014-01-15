#include"stdafx.h"
#include "DB_manager.h"

DB_manager::DB_manager(void)
{
	int a;
	ret = SQL_SUCCESS;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	ret = SQLConnect(hDbc,(SQLCHAR *)"AAA", SQL_NTS, (SQLCHAR *)"AAA", SQL_NTS, (SQLCHAR *)"ghkdlxld", SQL_NTS);
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	if((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO))
	{
		cout<<"Connection:fail\n"<<ret;
		cin>>a;
	}
	else
	{
		cout<<"Connection:success\n";
	}
}


DB_manager::~DB_manager(void)
{
	SQLFreeHandle(SQL_HANDLE_STMT, hStmt );
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

bool DB_manager::Query_signup(IN_Signup in_signup, OUT_Signup &out_signup)
{
	sprintf_s(sql, "insert into member values (%s,%s,%s)", in_signup.ID, in_signup.pass, in_signup.nick);
	Sql_run(sql);
	if(ret==SQL_SUCCESS)
	{	
		return true;
	}
	else
	{
		return false;
	}
}

bool DB_manager::Query_login(IN_Login in_login, IN_Login &db_login)
{
	sprintf_s(sql, "select * from member where ID='%s' and pass='%s'", in_login.ID, in_login.pass);
	Sql_run(sql);
	if(ret==SQL_SUCCESS)
	{
		SQLFetch(hStmt);
		SQLGetData(hStmt, 1, SQL_C_CHAR, db_login.ID, 20, NULL);
		SQLGetData(hStmt, 2, SQL_C_CHAR, db_login.pass, 20, NULL);
		
		return true;
	}
	else
	{
		return false;
	}
}

bool DB_manager::Query_leave()
{

}

void DB_manager::Query_images()
{

}

void DB_manager::Query_image_register()
{

}

void DB_manager::Query_opi_search()
{

}

void DB_manager::Query_opi_register()
{

}

void DB_manager::Query_opi_delete()
{

}

void DB_manager::Sql_run(char* sql)
{
	ret = SQLExecDirect(hStmt, (SQLCHAR*)sql, SQL_NTS);
}