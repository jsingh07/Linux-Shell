#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

void cls(vector<char> &directory)
{
	/*char * loc = new char[directory.size()];
	vector<char> files;
	DIR *dir;
	struct dirent * reading;
	struct stat filestat;
	int i;
	for (i = 0; i < directory.size(); i++)
		loc[i] = directory[i];
	
	if (directory.size() == 0)
	{
		if ((dir = opendir(".")) == NULL)
			write(STDIN_FILENO, "Fuck" , 4);
	}
	else
	{
		if ((dir = opendir(loc)) == NULL)
			write(STDIN_FILENO, "Duck" , 4);
	}
	while ( (reading = readdir(dir)) != NULL)
	{
			char buff[512];
			for (int h = 0; h < 512; h++)
				buff[h] = '\0';
			for (i = 0; i < directory.size(); i++)
				buff[i] = directory[i];
			buff[directory.size()] = '/';
			for(i = directory.size()+1; (reading->d_name)[i - directory.size()+1] != '\0'; i++)
				buff[i] = (reading->d_name)[i - directory.size()+1];
			for (int t = 0; buff[t] != '\0';t++)
				write(STDIN_FILENO, &buff[t], 1);
			write(STDIN_FILENO, "\n", 1);
			stat(buff, &filestat);
			//stat(name, &filestat);
			if (S_ISDIR(filestat.st_mode))
			{
				write(STDIN_FILENO, "d", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IRUSR)
			{
				write(STDIN_FILENO, "r", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IWUSR)
			{
				write(STDIN_FILENO, "w", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IXUSR)
			{
				write(STDIN_FILENO, "x", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IRGRP)
			{
				write(STDIN_FILENO, "r", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IWGRP)
			{
				write(STDIN_FILENO, "w", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IXGRP)
			{
				write(STDIN_FILENO, "x", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IROTH)
			{
				write(STDIN_FILENO, "r", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IWOTH)
			{
				write(STDIN_FILENO, "w", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IXOTH)
			{
				write(STDIN_FILENO, "x", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			write(STDIN_FILENO, " ", 1);
			for (i = 0; (reading->d_name)[i] != '\0';i++)
			{
				files.push_back((reading->d_name)[i]);
			}
			i = 0;
			while (i < files.size())
			{
				write(STDIN_FILENO, &files[i], 1);
				i++;
			}
			files.clear();
	}*/
	unsigned int i;
	int arrsiz = 128;
	char * name = new char[arrsiz];
	while (NULL == getcwd(name, arrsiz))
	{
		delete [] name;
		arrsiz *= 2;
		name = new char[arrsiz];
	}
	vector<char> files;
	DIR * dir;
	struct dirent * reader;
	struct stat filestat;
	if (directory.size() != 0)
	{
		char * usrdir = new char[directory.size()];
		for (i = 0; i < directory.size(); i++)
		{
			usrdir[i] = directory[i];
		}
		usrdir[directory.size()] = '\0';
		//dir = opendir(usrdir);
		chdir(usrdir);
		delete [] usrdir;
	}
	int k = 0;
	dir = opendir(".");
	while ( (reader = readdir(dir)) != NULL)
	{
			if (k != 0)
				write(STDIN_FILENO, "\n", 1);
			/*char * name = new char[512];
			for (l = 0; l < directory.size(); l++)
				name[l] = directory[i];
			for (l = directory.size(); (reader->d_name)[l - directory.size()] != '\0';l++)
			{
				name[l] = (reader->d_name)[l - directory.size()];
			}*/
			stat(reader->d_name, &filestat);
			//stat(name, &filestat);
			if (S_ISDIR(filestat.st_mode))
			{
				write(STDIN_FILENO, "d", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IRUSR)
			{
				write(STDIN_FILENO, "r", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IWUSR)
			{
				write(STDIN_FILENO, "w", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IXUSR)
			{
				write(STDIN_FILENO, "x", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IRGRP)
			{
				write(STDIN_FILENO, "r", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IWGRP)
			{
				write(STDIN_FILENO, "w", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IXGRP)
			{
				write(STDIN_FILENO, "x", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IROTH)
			{
				write(STDIN_FILENO, "r", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IWOTH)
			{
				write(STDIN_FILENO, "w", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			
			if (filestat.st_mode & S_IXOTH)
			{
				write(STDIN_FILENO, "x", 1);
			}
			else
			{
				write(STDIN_FILENO, "-", 1);
			}
			write(STDIN_FILENO, " ", 1);
			for (i = 0; (reader->d_name)[i] != '\0';i++)
			{
				files.push_back((reader->d_name)[i]);
			}
			i = 0;
			while (i < files.size())
			{
				write(STDIN_FILENO, &files[i], 1);
				i++;
			}
			files.clear();
			//delete [] name;
			k++;
	}
	write(STDIN_FILENO, "\n", 1);
	closedir(dir);
	chdir(name);
	delete [] name;
}