#include "plugin.h"

int plugin::initPlugin(char* plugin)
{
	string pfad("./Plugins/");
	pfad+=plugin;
	pfad +="/";
	pfad += plugin;
	pfad += ".so";
	this->handle=dlopen(pfad.c_str(),RTLD_LAZY);
	if(!this->handle)
	{
		return -1;
	}
	
	this->userLog = (loguser) dlsym(this->handle,"logUser");
	this->conversationLog = (logconv) dlsym(this->handle,"logMsg");
	this->readUser = (readUserfunc) dlsym(this->handle,"readUser");
	this->lastTimestamp = (char*)dlsym(this->handle,"lastTimestamp");
	
}

void plugin::closePlugin()
{
	dlclose(this->handle);
}