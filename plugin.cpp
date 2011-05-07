#include "plugin.h"

int plugin::initPlugin(char* plugin)
{
	char * error;
	
	string pfad("./Plugins/");
	pfad+=plugin;
	pfad +="/";
	pfad += plugin;
	pfad += ".so";
	this->handle=dlopen(pfad.c_str(),RTLD_LAZY);
	//this->handle=dlopen(pfad.c_str(),RTLD_NOW);
	if(!this->handle)
	{
		return -1;
	}
	
	dlerror();//Leert die Error anzeige
	
	this->userLog = (loguser) dlsym(this->handle,"logUser");
	if((error = dlerror())!=NULL)
	{
		printf("Error UserLog: %s\n",error);
		return -1;
	}
	this->conversationLog = (logconv) dlsym(this->handle,"logMsg");
	if((error = dlerror())!=NULL)
	{
		printf("Error conversationLog: %s\n",error);
		return -1;
	}
	this->readUser = (readUserfunc) dlsym(this->handle,"readUser");
	if((error = dlerror())!=NULL)
	{
		printf("Error readUser: %s\n",error);
		return -1;
	}
	this->lastTimestamp = (char*)dlsym(this->handle,"lastTimestamp");
	if((error = dlerror())!=NULL)
	{
		printf("Error lastTimestamp: %s\n",error);
		return -1;
	}
	 
	
	//userLog("ircbotdb","Chatbot","2011-05-07 12:05:00.000",0);
	
}

void plugin::closePlugin()
{
	dlclose(this->handle);
}