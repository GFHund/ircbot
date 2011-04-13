static void phiirc::deamonize()
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
			syslog(LOG_ERR,"Unable to create lock1 file %s,code=%d (s)",
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

void phiirc::init(int argc,char * argv[])
{
	string *args = new string[argc];
	
	for(int i=0;i<argc,i++)
	{
		args.insert(0,argv[i]);
	}
	
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
	
	this->initIRC(false,false,false,false);
	
	if(deamon==true)
	{
		this->deamonize();
		this->runIRC();
	}
	else
	{
		this->runIRC();
	}
	
	
}


void phiirc::event_privmsg(irc_session_t* session,const char* event,const char* origin,const char** params,unsigned int count)
{
	
}