void sigchldLogger(int s, siginfo_t* data, void * d){
	
	char buff[128];
	sprintf(buff,"Child %d did finish.",data->si_pid);

	if(writeToLog(buff) == _log_io_FILE_ERR){
		printToUser("SIGCHLD","LOG FILE ISN'T ACCESSIBLE" ,_shell_io_msg_state_WARNING,0,0);
	}
}

void SIGCHLDhandler(){
	struct sigaction sigChldHandler;
	sigChldHandler.sa_sigaction = sigchldLogger;
	sigemptyset(&sigChldHandler.sa_mask);
	sigChldHandler.sa_flags = 0;
	sigaction(SIGCHLD, &sigChldHandler, NULL);
}