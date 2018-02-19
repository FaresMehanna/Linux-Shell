_log_io_state writeToLog(char* line){

	FILE *fp;

	//ful path to the file
	char buffer[1024];
	char* dir = getenv("1ShellHome");

	if(!dir){
		return _log_io_FILE_ERR;
	}

	//format the log line
	sprintf(buffer,"%s/ShellLog.txt",dir);
	
	//open the file
	fp = fopen(buffer, "a");
	if(!fp){
		return _log_io_FILE_ERR;
	}
	
	//print the line
	fprintf(fp,"%s\n",line);
	
	//close the line
	fclose(fp);
	
	return _log_io_SUCC;
}