char* getCurrDir(){

	char* cwd = smalloc(sizeof(char)*1024);
	
	if (getcwd(cwd, sizeof(char)*1024) != NULL)
       return cwd;
	
	return NULL;
}