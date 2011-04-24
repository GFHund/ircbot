#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
/*
toDo: 
- readUser SQL query fertig schreiben
*/

/*
void initLog()
{
	
}
*/
int logUser(char* logname, char* user, char* time, bool quit)
{
	sqlite3* db;
	
	char* Error=0;
	
	int rc;
	
	rc = sqlite3_open(logname,&db);
	if(rc)
	{
		fprintf(stderr,"Kann Datenbank %s nicht öffnen:%s\n",logname,sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	
	char sql[80];
	strcpy(sql,"INSERT INTO userTimestamp(user,time,quit) VALUES (");
	strcat(sql,user);
	strcat(sql,",date('now'),");
	strcat(sql,quit);
	strcat(sql,");");
	
	rc = sqlite3_exec(db,sql,NULL,0,&Error);
	if(rc!=SQLITE_OK)
	{
		sqlite3_free(Error);
		sqlite3_close(db);
		return -1;
	}
	sqlite3_close(db);
	return 0;
}

int logMsg(char* logname,char* user,char* message)
{
		sqlite3* db;
	
	char* Error=0;
	
	int rc;
	
	rc = sqlite3_open(logname,&db);
	if(rc)
	{
		fprintf(stderr,"Kann Datenbank %s nicht öffnen:%s\n",logname,sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	
	char sql[80];
	strcpy(sql,"INSERT INTO conversation(user,message) VALUES (");
	strcat(sql,user);
	strcat(sql,",");
	strcat(sql,message);
	strcat(sql,");");
	
	rc = sqlite3_exec(db,sql,NULL,0,&Error);
	if(rc!=SQLITE_OK)
	{
		sqlite3_free(Error);
		sqlite3_close(db);
		return -1;
	}
	sqlite3_close(db);
	return 0;
}

char* lastTimestamp;

int ergReadUser(void* NotUsed,int argc,char**argv,char**colname)
{
	lastTimestamp = argv[0];
}



int readUser(char* logname,char* user)
{
	sqlite3* db;
	
	char* Error=0;
	
	int rc;
	
	rc = sqlite3_open(logname,&db);
	if(rc)
	{
		fprintf(stderr,"Kann Datenbank %s nicht öffnen:%s\n",logname,sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	
	char sql[80];
	strcpy(sql,"SELECT time FROM userTimestamp WHERE user = ");
	strcat(sql,user);
	strcat(sql,"ORDER BY time DESC LIMIT 1;");
	
	rc = sqlite3_exec(db,sql,ergReadUser,0,&Error);
	if(rc!=SQLITE_OK)
	{
		sqlite3_free(Error);
		sqlite3_close(db);
		return -1;
	}
	sqlite3_close(db);
	return 0;
}

/*
void finiLog()
{
	
}
*/
