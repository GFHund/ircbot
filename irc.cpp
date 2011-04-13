
int irc::initIRC(bool connect,bool join,bool channel,bool privmsg)
{
	irc_callbacks_t callbacks;
	irc_ctx_t ctx;
	
	memset(&callbacks,0,sizeof(callbacks));
	
	if(connect)
		callbacks.event_connect = event_connect;
	if(join)
		callbacks.event_join=event_join;
	if(channel)
		callbacks.event_channel=event_channel;
	if(privmsg)
		callbacks.event_privmsg=event_privmsg;
	
	this->session = irc_create_session(&callbacks);
	
	if(!this->session)
	{
		printf("configuration Fehlgeschlagen");
		return -1;
	}
	irc_set_ctx(this->session,&ctx);
	irc_options_set(this->session,LIBIRC_OPTION_STRIPNICKS);
	
	
}

void irc::runIRC()
{
	irc_run(this->session);
}