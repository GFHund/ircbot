
class irc
{
	
	protected:
		irc_session_t* session;

	
		int initIRC(bool connect,bool join,bool channel,bool privmsg);
		void runIRC();
		virtual void event_connect(irc_session_t* session,const char* event,const char* origin, const char** params, unsigned int count)=0;
		virtual void event_join(irc_session_t* session,const char* event,const char* origin,const char**params,unsigned int count)=0;
		virtual void event_channel(irc_session_t* session,const char* event,const char* origin,  const char** params,unsigned int count)=0;
		virtual void event_privmsg(irc_session_t* sessionm const char* event,const char* origin, const char** params, unsignede int count)=0;
}