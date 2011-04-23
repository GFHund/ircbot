#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>

#include <string.h>
#include <string>

#include "irc.h"
#include "plugin.h"

using namespace std;

class phiirc : public irc
{
public:
	phiirc();
	~phiirc();


private:
	plugin pluginsystem;
	char* logname;

	static void child_handler(int signum);
	static void deamonize(string name);
	int charToInt(char* zahl);
	int potenz(int Basis,int exponent);
	

protected:
	
	void irc_command_join(string prefix,string param[5],int countParam);
	void irc_command_privmsg(string prefix,string param[5],int countParam);
	void irc_command_nick(string prefix,string param[5],int countParam);
	void irc_command_quit(string prefix,string param[5],int countParam);
	
public:
	
	void init(int argc,char* argv[]);

};
