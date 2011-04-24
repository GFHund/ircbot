#include "irc.h"

int irc::initIRC(string ip,int port,string channel)
{
	//int sock;
	struct sockaddr_in server;
	unsigned long addr;
	struct hostent* hostinfo;
	int fehler;
	
	//this->mstr_ip = ip;
	//this->mi_port = port;
	//this->mstr_channel(channel);
	
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
	
	printf("Verbinde mit %s:%i...\n",ip.c_str(),port);
	
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
	establishConnection+=" :Mr.Chatbot\r\n";
	//JOIN #";
	//establishConnection +=channel;
	//establishConnection+="\r\n";
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
	
	char temp=' ';
	string message;
	while(temp!='\0' && temp != 0x0a)
	{
		recv(this->sock,(char*)&temp,sizeof(char),0);
		message += temp;
	}
	
	printf("nachricht eingetroffen: %s\n",message.c_str());
	
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
			if(message.size() > 0)
				param[i]=message;
			numparam = i;
			break;
		}
		//printf("Erstes Zeichen: %c %c\n",message.c_str()[0],message.c_str()[1]);
		if(message.c_str()[0]==':')
		{
			param[i] = message;
			
			numparam = i;
			break;
		}
		param[i] = message.substr(0,pos);
		message = message.substr(pos+1);
		
	}
	
	for(int i =0;i<=numparam;i++)
		printf("Befehl: %s Param %i: %s\n",command.c_str(),i,param[i].c_str());
	
	if(command.find("JOIN")!=string::npos)
	{
		irc_command_join(prefix,param,numparam);
	}
	else if(command.find("PRIVMSG") != string::npos)
	{
		irc_command_privmsg(prefix,param,numparam);
	}
	else if(command.find("NICK")!=string::npos)
	{
		irc_command_nick(prefix,param,numparam);
	}
	else if(command.find("QUIT")!=string::npos)
	{
		irc_command_quit(prefix,param,numparam);
	}
	else if(command.find("PING")!=string::npos)
	{
		int fehler;
		
		string channel("help");
		
		string pong("PONG ");
		pong += param[0];
		pong += "\r\n";
		printf("schicke Nachricht: %s\n",pong.c_str());
		send(this->sock,(char*)pong.c_str(),pong.size(),0);
		
		string join="";
		join+="JOIN #";
		join+= channel;
		join += "\r\n";
		
		fehler = send(this->sock,(char*)join.c_str(),join.size(),0);
		
		if(fehler==-1)
		{
			perror("Fehler beim aufbau der Verbindung\n");
			close(this->sock);
			//return -1;
		}
	}
	
}

void irc::closeIRC()
{
	close(this->sock);
}


void irc::irc_send_command_privmsg(string message)
{
	string msg(":Chatbot PRIVMSG #");
	msg+=this->mstr_channel;
	msg += " :";
	msg += message;
	msg += "\r\n";
	printf("%s\n",msg.c_str());
	send(this->sock,(char*)msg.c_str(),msg.size(),0);
}

void irc::irc_send_command_quit(string msg)
{
	string quit("Quit ");
	quit+=msg;
	quit+="\r\n";
	
	send(this->sock,(char*)quit.c_str(),quit.size(),0);
}