#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <list>
char newline = '\n'; 

#define MAX_PATH 70
char dir[MAX_PATH+1];
using namespace std;
void pdir(vector<char> path){
	char d;
	for(vector<char>::iterator it = path.begin(); it != path.end(); it++){
		d = *it;
		write(STDIN_FILENO, &d, 1);
	}
}

void curdir(vector<char>& fpath){
	vector<char> path, rpath;
	fpath.clear();
	path.clear();

	getcwd(dir, MAX_PATH+1);
	for(int i = 0; i <50 && dir[i] != '\0'; i++){
		path.push_back(dir[i]);
		//write(STDIN_FILENO, &dir[i], 1);
	}

    vector<char>::iterator f = fpath.end();
	if(path.size()>16){
		fpath.push_back('/');
		fpath.push_back('.');
		fpath.push_back('.');
		fpath.push_back('.');
		fpath.push_back('/');
		for(vector<char>::iterator i = path.end(); i != path.begin(); i--){
			
			if((*i) == 0x2f && i == path.end()){
				path[path.size()] = ' ';
				i = path.end();}
			else if((*i) == 0x2f)
				break;
			else 
 				rpath.push_back(*i);
 		}
 		//pdir(rpath);
 		for(vector<char>::iterator it = rpath.end()-1; it != rpath.begin(); it--){
 			fpath.push_back(*it);
 		}
 		//pdir(fpath);
	}
	else 
		fpath = path;

	fpath.push_back('>');
}
void cpwd(){
	for(int i = 0; i < MAX_PATH; i++){
		write(STDIN_FILENO, &dir[i], 1);
	}
	
	write(STDIN_FILENO, &newline, 1);

}

void cleardir(){
	for(int i = 0; i < MAX_PATH+1; i++)
		dir[i] = ' ';
}
void chistory(list<vector<char> >history){
	char k = 0x01;
	char s = 0x30;
	char sp = ' ';
	list<vector<char> >::iterator i = history.end();
	list<vector<char> >::iterator e = history.begin();
	i--;//start one back for the first element or else it will print latest command
	e--;//incluse the very first element which is the latest command
	for(; i != e; i--){
		write(STDIN_FILENO, &s,1);
		write(STDIN_FILENO, &sp, 1);
		s = k + s;
		pdir(*i);
		write(STDIN_FILENO, &newline, 1);
	}

}
void ccd(vector<char> path, vector<char>& ws){
	char const *home = "/home/";
	char* user = getlogin();
	char *target = new char[path.size()];
	char *de = new char[strlen(user)+strlen(home)];
	strcpy(de, home);
	strcat(de, user);
	target[path.size()] = '\0';
	unsigned int i;
	if(path.size() == 0)
		i = chdir(de);
	else{	
		unsigned int k;
		for(k = 0; k < path.size(); k++)
			target[k] = path[k];
		i = chdir(target);
	}
	if(i != 0)
		perror("Error changing directory.");
	cleardir();
	curdir(ws);

}