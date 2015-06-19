#include <list>
#include <fstream>
#include <vector> 

using namespace std;
void whistory(vector<char>& buffer, list<vector<char> > history, int hpos, int t, int& size)
{
	int i = hpos;
	char d;
	//if going up in history
	if(t == 0){
		//create list =iterator from the start
		list< vector<char> >::iterator it = history.begin();

		while(i != 0){
			it++;
			i--;
		}
		for(; size >0; size--)
			write(STDIN_FILENO, "\b \b", 3);
		size = 0;
		for(vector<char>::iterator i = (*it).begin(); i != (*it).end(); i++)
		{
			size++;
			d = *i;
			buffer.push_back(d);
			write(STDIN_FILENO, &d, 1);
		}
	}
	//else going down makesure we are already in a high place in history 
	else{
		if(hpos <0){
			hpos = 0;
			for(; size >0; size--)
				write(STDIN_FILENO, "\b \b", 3);
			size = 0;
		}
		
		else{

			list< vector<char> >::iterator it = history.begin();
			int t = i;
			while(i != 0){
				it++;
				i--;
			}
		
			for(; size >0; size--)
				write(STDIN_FILENO, "\b \b", 3);
			size = 0;
			if(t != 0){
			 it--;    //-1 after reaching spot in history we were i

			for(vector<char>::iterator i = (*it).begin(); i != (*it).end(); i++)
			{
				size++;
				d = *i;
				write(STDIN_FILENO, &d, 1);
			}
		}
		}
	}


}