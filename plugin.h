#include <string>
#include <dlfcn.h>

typedef int (* loguser)(char* ,char*,char* ,int);
typedef int (* logconv)(char* ,char*,char*);
typedef int (* readUserfunc)(char* ,char*);

using namespace std;

class plugin
{
public:
	void* handle;
	loguser userLog;
	logconv conversationLog;
	readUserfunc readUser;
	char* lastTimestamp;

	int initPlugin(char* plugin);
	void closePlugin();
};
