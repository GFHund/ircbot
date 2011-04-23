#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

class irc
{
private: 
	//extern int h_errno;
	int sock;
	
protected:	
	int initIRC(string ip,int port,string channel);
	void updateIRC();
	void closeIRC();
	virtual void irc_command_join(string prefix,string param[5],int countParam)=0;
	virtual void irc_command_privmsg(string prefix,string param[5],int countParam)=0;
	virtual void irc_command_nick(string prefix,string param[5],int countParam)=0;
	virtual void irc_command_quit(string prefix,string param[5],int countParam)=0;
};
