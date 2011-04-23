#include "phiirc.h"


phiirc::phiirc(){}

phiirc::~phiirc()
{
	closeIRC();
	this->pluginsystem.closePlugin();
}


void phiirc::child_handler(int signum)
{
	switch (signum)
	{
		case SIGALRM:exit(1);break;
		case SIGUSR1:exit(0);break;
		case SIGCHLD:exit(1);break;
		case SIGINT:exit(0);break;
	}
}

void phiirc::deamonize(string name)
{
	pid_t sid, pid, parent;
	int lfp=-1;
	char lockfile[30]="/var/lock/deamon";
	//Sind wir bereits deamon;
	if(getppid()==1)return;
	
	//Lock file erzeugen
	
	if(lockfile && lockfile[0])
	{
		lfp = open(lockfile,O_RDWR|O_CREAT,0640);
		if(lfp < 0 )
		{
			syslog(LOG_ERR,"Unable to create lock1 file %s,code=%d (%s)",
			lockfile,errno,strerror(errno));
			exit(1);
		}
	}
	
	// Benutzer ändern
	
	if(getuid()==0 || geteuid()==0)
	{
		struct passwd *pw;
		 pw = getpwnam("deamon");
		if(pw)
		{
			syslog(LOG_NOTICE,"Setting UID to deamon");
			setuid(pw->pw_uid);
		}
	}
	
	/*signal handler einrichten*/
	signal(SIGCHLD,child_handler);
	signal(SIGUSR1,child_handler);
	signal(SIGALRM,child_handler);
	//Und in der Praxis noch mehr
	signal(SIGINT,child_handler);
	
	//Fork off
	
	pid = fork();
	if(pid <0)
		syslog(LOG_ERR,"scheise wars");
	
	//Parent Process
	if(pid > 0)
	{
		/*
		Auf bestätigung warten via sigterm oder sigchild, 
		oder für 2 Sekunden auf alarm warten... 
		pause sollte nicht mehr zurückkehren
		*/
		
		alarm(2);
		pause();
		exit(1);
	}
	
	/*Wir sind im Childprozess*/
	parent = getppid();
	
	/* Von allen meogliche signalen sollte man sich abmelden*/
	
	signal (SIGCHLD,SIG_DFL);//Childn terminiert
	signal (SIGTSTP,SIG_IGN); //Diverse TTY Signale
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGHUP,SIG_IGN);//HANGup signal
	signal(SIGTERM,SIG_DFL);//Term Signal, hier Default Verhalten
	
	//File Node Mask
	umask(0);
	//neue Prozessumgebung (sid) setzen
	sid=setsid();
	if(sid<0)
	{
		syslog(LOG_ERR,"Error Der Benutzer ist zu blöd");
		exit(0);
	}
	
	//Ändern des Arbeitsverzeichnis
	if((chdir("/")<0)) 
	{
		syslog(LOG_ERR,"der x te Fehler");
		exit(1);
	}
	
	/*Aendern der default datei descriptoren*/
	freopen("/dev/null","r",stdin);
	freopen("/dev/null","w",stdout);
	freopen("/dev/null","w",stderr);
	
	/* Dem Elternprozess mitteilen dass alles in ordnung ist...*/
	kill(parent,SIGUSR1);
}

int phiirc::potenz(int Basis,int exponent)
{
	int ret = Basis;
	for(int i=1;i<exponent;i++)
	{
		ret *= ret;
	}
	return ret;
}

int phiirc::charToInt(char* zahl)
{
	int size = sizeof(zahl);
	int ret=0;
	for(int i=0;i<size;i++)
	{
		ret+=(zahl[i]-0x30)*(potenz(10,size-i));
	}
	return ret;
}


void phiirc::init(int argc,char * argv[])
{
	//printf("%i\n",argc);
	char* plugin="sqlite";
	logname = "sqlite";
	//char* database="ircbotdb";
	if(argc >=4)
	{
		bool deamon = false;
		for(int i=0;i<argc;i++)
		{
			printf("%s\n",argv[i]);
			if(strcmp(argv[i],"-d")==0)
			{
				deamon = true;
			}
			if(strcmp(argv[i],"-p")==0)
			{
				plugin = argv[i+1];
			}
			if(strcmp(argv[i],"-d")==0)
			{
				this->logname = argv[i+1];
			}
		}
		//toDo: Server Channel und port Varibalen zuweisen und deamon starten irc initialisieren und join und privmsg methoden implementieren
		
		string server (argv[1]);
		int port = charToInt(argv[2]);
		string channel (argv[3]);
		
		this->pluginsystem.initPlugin(plugin);
		
		if(deamon==true)
		{
			printf("Erzeuge Deamon\n");
			deamonize(argv[0]);
		}
		
		initIRC(server,port,channel);
		printf("Server wurde gestartet und ist bereit\n");
		while(true)
		{
			updateIRC();
		}
	}
	else 
	{
		for(int i=1;i<argc;i++)
		{
			if(strcmp(argv[i],"-h")==0||strcmp(argv[i],"--help")==0)
			{
				printf("Dies ist die Hilfe von PhiIRC.\n Befehle:\n -h --help Hilfe für PhiIRC\n-d schaltet den Deamon Ab\n");
			}
				
		}
	}
	
	
	
	
	
	
	/*
	bool deamon=true;
	
	for(int i=0;i<argc;i++)
	{
		if(args.find("-h")!= string::npos||args.find("--help")!=string::npos)
		{
			printf("Dies ist die Hilfe von PhiIRC.\n Befehle:\n -h --help Hilfe für PhiIRC\n-d schaltet den Deamon Ab");
			return;
		}
		
		if(args.find("-d")!=string::npos)
			deamon=false;
	}
	
	this->initIRC();
	
	if(deamon==true)
	{
		this->deamonize();
		this->runIRC();
	}
	else
	{
		this->runIRC();
	}
	
	*/
}


void phiirc::irc_command_join(string prefix,string param[5],int countParam)
{
	/*
	if(prefix!="")
	{
		//printf("%s betritt den %s Kanal\n",prefix.c_str(),param[0].c_str());
		
	}
	else
	{
		//printf("Jemand betritt den %s Kanal\n",param[0].c_str());
		
	}
	*/
}

void phiirc::irc_command_privmsg(string prefix,string param[5],int countParam)
{
	if(prefix!="")
	{
		printf("%s an %s: %s\n",prefix.c_str(),param[0].c_str(),param[1].c_str());
	}
	else
	{
		printf("Jemand an %s: %s\n",param[0].c_str(),param[1].c_str());
	}
}

void phiirc::irc_command_nick(string prefix,string param[5],int countParam)
{
	this->pluginsystem.userLog(this->logname,param[0],
}

void phiirc::irc_command_quit(string prefix,string param[5],int countParam)
{
	
}
	