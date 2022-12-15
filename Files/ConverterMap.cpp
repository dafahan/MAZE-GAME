#include<fstream>
#include<conio.h>
#include<curses.h>
#include<Windows.h>
#include<bits/stdc++.h>
using namespace std;
bool acc;
int main()
{	initscr();
	ifstream file("MAP_DUMP\\8.txt",ios::app);
	char tmp;
	while(!file.eof()){
		file.get(tmp);
		if(tmp==' ')cout<<'0';
		else cout<<tmp;
	}
	getch();
	endwin();
}
