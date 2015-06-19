#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <errno.h>
#include "history.h"
#include "commands.h"
#include "Scommands.h"
#include "vectorc.h"
#include "fp.h"
char carrot = 0x3e;
char bk = 0x7f;
char enter = 0x0a;
void ResetCanonicalMode(int fd, struct termios *savedattributes){
    tcsetattr(fd, TCSANOW, savedattributes);
}

void SetNonCanonicalMode(int fd, struct termios *savedattributes){
    struct termios TermAttributes;
    
    // Make sure stdin is a terminal. 
    if(!isatty(fd)){
        fprintf (stderr, "Not a terminal.\n");
        exit(0);
    }
    
    // Save the terminal attributes so we can restore them later. 
    tcgetattr(fd, savedattributes);
    
    // Set the funny terminal modes. 
    tcgetattr (fd, &TermAttributes);
    TermAttributes.c_lflag &= ~(ICANON | ECHO); // Clear ICANON and ECHO. 
    TermAttributes.c_cc[VMIN] = 1;
    TermAttributes.c_cc[VTIME] = 0;
    tcsetattr(fd, TCSAFLUSH, &TermAttributes);
}

void findcmd(list<vector<char> > history, vector<char> buffer, vector<char>& path){
	vector<char> cmd;
	vector<char> arg;
    unsigned int t=0;

	//parse string till space or end for command
	for(unsigned int i = 0; i < buffer.size() && buffer[i] != ' '; i++){
		cmd.push_back(buffer[i]);
		t++;
	}
	t++;
	for(; t < buffer.size() && buffer[t] != ' '; t++)
		arg.push_back(buffer[t]);
	//check which command it is
//	for(unsigned int p = 0; p < buffer.size(); p++)
//		if(buffer[p] == '>')
//		{	
//			other(cmd, buffer);
//			break;
//		}

	if(cmd == pwd)
		cpwd();
	
	else if(cmd == cd){ 
			//path.clear();
			ccd(arg, path);
	}

	else if(cmd == his){
		chistory(history);
	}
	
	else if (cmd == ls)
	{
			cls(arg);
	}
	else
		other(cmd, buffer);


}

int main(){
	 createcmd();
     struct termios terminal;
	 char Input;
	 vector<char> buffer, home, path;
	 int size = 0;
	 int hpos = 0; //size of current input hpos is the current pos in list
	 list<vector<char> > history;
	 SetNonCanonicalMode(STDIN_FILENO, &terminal);

	 curdir(path); //grab current directory
	 pdir(path);
	 while(1){
		 read(STDIN_FILENO, &Input, 1);
		 size++;
		 //cout<<size<<endl;
		 if(0x04 == Input){
			 break;
		 }

		 //check if up arrow or down arrow
		 if(0x1b == Input){
		 	size--;
			read(STDIN_FILENO, &Input, 1);
		     if(0x5b == Input){
		        read(STDIN_FILENO, &Input, 1);
		        if(0x41==Input && (unsigned int)hpos != history.size()){
		        	buffer.clear();    //must clear recorded inputs and fill buffer from history                           
		        	whistory(buffer, history, hpos, 0, size);
					if((unsigned int)hpos < history.size())
						hpos++;  //hit up so go up in list
				}

			    else if(0x42==Input ){
			    	buffer.clear();
			    	hpos--;
					whistory(buffer, history, hpos, 1, size);
					if(hpos < 0)
					    hpos = 0;
				}
			}
		 }
		
		 else{ 

		 	if(enter == Input){
		 		if(buffer == ex)
		 			break;
		 		write(STDIN_FILENO, &newline, 1);
		 		hpos = 0;
		 		size = 0;
		 		if(history.size() == 10)
		 			history.pop_front();
				history.push_front(buffer);
		 		findcmd(history, buffer, path);  //check if a command has been entered
		 		pdir(path);
		 		
				buffer.clear();

		 	}
		 	
		 	//check if user is erasing
		 	else if(Input == bk){
		 		size--;      
		 		hpos = 0;     //user hit backspace delete history position
		 		if(size > 0){
					buffer.pop_back();
		 		    write(STDIN_FILENO, "\b \b", 3);
		 		}
		 		size--;
		 	}

		    else{
		 		buffer.push_back(Input);
				write(STDIN_FILENO,  &Input, 1);
			}

	 }
	}
	write(STDIN_FILENO, &newline, 1);

	ResetCanonicalMode(STDIN_FILENO, &terminal);
    return 0;

}

