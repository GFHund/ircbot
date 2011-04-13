

void phiirc::init(int argc,char * argv[])
{
	string *args = new string[argc];
	
	for(int i=0;i<argc,i++)
	{
		args.insert(0,argv[i]);
	}
	
	for(int i=0;i<argc;i++)
	{
		if(args.find("-h")!= string::npos||args.find("--help")!=string::npos)
		{
			printf("Dies ist die Hilfe von PhiIRC.\n Befehle:\n -h --help Hilfe für PhiIRC");
			return;
		}
	}
	irc_callbacks_t callbacks;
	irc_ctx_t ctx;
	irc_session_t* session;
	
	memset(&callbacks,0,sizeof(callbacks));
	
	
}
