#include "irc.h"

int irc::initIRC(string ip,int port,string channel)
{
	//int sock;
	struct sockaddr_in server;
	unsigned long addr;
	struct hostent* hostinfo;
	int fehler;
	
	this->sock = socket(AF_INET,SOCK_STREAM,0);
	if(this->sock == -1)
	{
		perror("Fehler bei Initalisieren des Netzwerks:\n");
		close(this->sock);
		return -1;
	}
	printf("Netzwerk initialisiert\n");
	memset(&server,0,sizeof(server));
	
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	
	addr = inet_addr(ip.c_str());
	
	if(addr == INADDR_NONE)
	{
		hostinfo = gethostbyname(ip.c_str());
		if(!hostinfo)
		{
			printf("Fehler: Name konnte nicht aufgelöst werden\n");
			return -1;
		}
		else
		{
			memcpy((char*)&server.sin_addr,&addr,sizeof(addr));
		}
	}
	else
	{
		memcpy((char*)&server.sin_addr,&addr,sizeof(addr));
	}
	
	fehler = connect(this->sock,(struct sockaddr*)&server,sizeof(server));
	if(fehler == -1)
	{
		perror("Fehler beim verbinden mit dem Server:\n");
		close(this->sock);
		return -1;
	}
	printf("Verbindung erfolgreich hergestellt\n");
	
	string establishConnection="NICK Chatbot\r\nUSER Chatbot A1RRZN001 ";
	establishConnection+=ip.c_str();
	establishConnection+=" Mr.Chatbot\r\nJOIN #";
	establishConnection +=channel;
	establishConnection+="\r\n";
	fehler = send(this->sock,(char*)establishConnection.c_str(),establishConnection.size(),0);
	if(fehler==-1)
	{
		perror("Fehler beim aufbau der Verbindung\n");
		close(this->sock);
		return -1;
	}
	return 0;
	
}

void irc::updateIRC()
{
	char temp;
	string message;
	while(temp!='\0' && temp != 0x0a)
	{
		recv(this->sock,(char*)&temp,sizeof(char),0);
		message += temp;
	}
	
	string prefix="";
	size_t num = message.find(':',0);
	
	if(num != string::npos&&num==0)
	{
		size_t prefixpos = message.find(' ');
		prefix = message.substr(0,prefixpos);
		message = message.substr(prefixpos+1);
	}
	int numparam;
	string param[5];
	size_t pos = message.find(' ');
	string command= message.substr(0,pos);
	message = message.substr(pos+1);
	
	for(int i=0;i<5;i++)
	{
		pos = message.find(' ');
		if(pos == string::npos)
		{
			numparam = i;
			break;
		}
		if(message.c_str()[0]==':')
		{
			param[i] = message;
			numparam = i;
			break;
		}
		param[i] = message.substr(0,pos);
		message = message.substr(pos+1);
		
	}
	
	if(message.find("JOIN")!=string::npos)
	{
		irc_command_join(prefix,param,numparam);
	}
	else if(message.find("PRIVMSG") != string::npos)
	{
		irc_command_privmsg(prefix,param,numparam);
	}
	else if(message.find("NICK")!=string::npos)
	{
		irc_command_nick(prefix,param,numparam);
	}
	else if(message.find("QUIT")!=string::npos)
	{
		irc_command_quit(prefix,param,numparam);
	}
	
}

void irc::closeIRC()
{
	close(this->sock);
}