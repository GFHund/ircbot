#include <dlfcn.h>


typedef int (*loguser)(char* ,char*,char* ,bool);
typedef int (*logconv)(char* ,char*,char*);
typedef int (*read)(char* ,char*);

class plugin
{
public:
	void* handle;
	loguser userLog;
	logconv conversationLog;
	read readUser;
	char* lastTimestamp;

	void initPlugin(char* plugin);
	void closePlugin();
}