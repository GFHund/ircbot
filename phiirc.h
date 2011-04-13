#include <stdio.h>
#include <string.h>
#include <sting>
#include "libircclient.h"

using namespace std;

class phiirc
{
private:
	struct struct
	{
		char* channel;
		char* nick;
	}irc_ctx_t;
	
	static void deamonize();
	
	void event_privmsg(irc_session_t* session,const char* event,const char* origin,const char** params,unsigned int count);
public:
	void init(int argc,char* argv[]);
	
	
}