#include "plugin.h"

int plugin::initPlugin(char* plugin)
{
	string pfad("./Plugins/");
	pfad+=plugin;
	pfad +="/";
	pfad += plugin;
	pfad += ".so";
	this->handle=dlopen(pfad,RTLD_LAZY);
	if(!this->handle)
	{
		return -1;
	}
	
	this->userLog = dlsym(this->handle,"logUser");
	this->conversationLog = dlsym(this->handle,"logMsg");
	this->readUser = dlsym(this->handle,"readUser");
	this->lastTimestamp = dlsym(this->handle,"lastTimestamp");
	
}

void plugin::closePlugin()
{
	dlclose(this->handle);
}