#include <vector>
using namespace std;

vector<char> pwd;
vector<char> cd;
vector<char> ex;
vector<char> ls;
vector<char> his;

void createcmd(){
	pwd.push_back(0x70);
	pwd.push_back(0x77);
	pwd.push_back(0x64);
	
	cd.push_back(0x63);
	cd.push_back(0x64);

	ex.push_back(0x65);
	ex.push_back(0x78);
	ex.push_back(0x69);
	ex.push_back(0x74);

	ls.push_back(0x6c);
	ls.push_back(0x73);

	his.push_back(0x68);
	his.push_back(0x69);
	his.push_back(0x73);
	his.push_back(0x74);
	his.push_back(0x6f);
	his.push_back(0x72);
	his.push_back(0x79);




}