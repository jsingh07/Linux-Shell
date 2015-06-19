#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <errno.h>
#include <string>


void other(vector<char> vcmd, vector<char> varg){

	int k = 0, c  = 0;
	vector<int> size;

	if(varg[varg.size()-1] != ' ')
		varg.push_back(' ');
	for(unsigned int j = 0 ; j < varg.size(); j++){
		if(varg[j] == '>')
			c = 1;
		if(varg[j] != ' ' && varg[j] != '>')
			k++;
		else{ 
			size.push_back(k);
			k= 0;
		}

	}
	char *args[size.size()+1];
	int l = 0;
	k = 0;
	char *cmd = new char[size[l]];
	for(unsigned int i = 0 ; i < varg.size(); i++){
	
		if (varg[i] != ' ' && varg[i] != '>')
		{
			cmd[k] = varg[i];
			k++;
			//write(STDIN_FILENO, &varg[i], 1);
		}
		else{
			args[l] = cmd;
			l++;
			k= 0;
			cmd = new char[size[l]];
		}
		//write(STDIN_FILENO, &varg[i], 1);
	}
	//cerr<<args[0];
	args[size.size()] = NULL;
	//cerr<<args[2];
	
	pid_t pid;
	int RDsave =-1;
	int FDs[2];
	int out;
	int child_status;
	RDsave = FDs[0];
	//cerr<<cmd[1];
	if(pipe(FDs)== -1)
		perror("Fail");
	else{
		pid = fork();
		if(pid == -1)
			perror("fail at fork");
		else{
			if(c == 1)
				FDs[1] = open("output.txt",O_WRONLY|O_CREAT,0666);

			if(pid == 0){
				close(FDs[0]);
				dup2(FDs[1], STDOUT_FILENO);
				//close(FDs[1]);
;				execvp(args[0], args);
			}
			else{
				wait(NULL);

			}



		}




	}




}
