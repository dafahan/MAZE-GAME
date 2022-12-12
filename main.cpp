#include<fstream>
#include<conio.h>
#include<curses.h>
#include<Windows.h>
#include<bits/stdc++.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27
#define FOR(a,b,c) for(int a=b;c;a++)
#define RFOR(a,b,c) for(int a=b;c;a--)
#define all(a) a.begin(),a.end()
using namespace std;


const int Height=25,Width=100;
enum eDirecton {STOP = 0, LEFT,RIGHT, UP, DOWN}; // Controls
bool Game,Verify,Quit,Dev,Cheat,Ghost,Logout;
int Score,X,Y,XB,YB,Select,Selection,SelectMOD,GameSpeed,dirb;
eDirecton dir;
string Password,Usertmp,FileMap;
char Username[100];
vector<vector<int>>MAP(Height,vector<int>(Width,0));

vector<int>Level(11,0);
vector<string>Lvm(11);
vector<string>UserList;

//DECLARE NUB SOLUTION KRN UDH PUSING
int MAP1[25][100]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void DevMenu(){
	bool menu;
	SelectMOD=1;
while(!menu){
			mvprintw(3,107,"DEV MOD");
	FOR(i,1,i<=6){
		if(i==i&&SelectMOD==i){
			mvprintw(i+5,100," >>  ");
		}
		else{
			mvprintw(i+5,100,"     ");
		}
		if(i==6){
		mvprintw(i+5,106,"Close");
			
		}else{
		 if(i==5)mvprintw(i+5,106,"Save Map");
		 if(i==4)mvprintw(i+5,106,"Destroy Block");
		 if(i==3)mvprintw(i+5,106,"Create Block");
		 if(i==2)mvprintw(i+5,106,"Ghost");
		 if(i==1)mvprintw(i+5,106,"Set Gamespeed");
		}
	}	
		int Selected=0;
		refresh();
		mvprintw(29,117," ");
		switch(getch()){
			case KEY_DOWN: SelectMOD++; break;
			case KEY_UP: SelectMOD--; break;
			case '\n': Selected=SelectMOD;break;
			case KEY_RIGHT: Selected=SelectMOD;break;
			case ESC: menu=1; Selected=6;break;
		}
		if(SelectMOD>6)SelectMOD=1;
		if(SelectMOD<1)SelectMOD=6;
		refresh();
	
	if(Selected==6){
		menu=1;
		Cheat=false;	
	}
	if(!Cheat){
			mvprintw(3,107,"        ");
			FOR(i,1,i<=6){
			
			mvprintw(i+5,100,"     ");
	
			mvprintw(i+5,106,"               ");
			
		}
	}
	if(Selected==1){
		mvprintw(Height+1,15,"==SET SPEED 1-10====");	
		mvprintw(Height+3,15,"====================");
		mvprintw(Height+2,15,"=                  =");
		mvprintw(Height+2,19,"");
		int tmp=0;
		while(int i=getch()){
			if(i=='\n')break;
			else tmp=tmp*10+i;
		}
			tmp%=11;
		GameSpeed=10-tmp;
		mvprintw(Height+1,15,"                    ");	
		mvprintw(Height+3,15,"                    ");
		mvprintw(Height+2,15,"                    ");
		menu=0;
		}
	if(Selected==2){
			if(Ghost){
				Ghost=0;
			mvprintw(Height+1,15,"====================");	
			mvprintw(Height+3,15,    "====================");
			mvprintw(Height+2,15,"= GHOST NONACTIVED =");
					refresh();
			}
			else {
				Ghost=1;
			mvprintw(Height+1,15,"====================");	
			mvprintw(Height+3,15,    "====================");
			mvprintw(Height+2,15,	"=   GHOST ACTIVED  =" );
				refresh();
			}
		getch();
			mvprintw(Height+1,15,"                    ");	
		mvprintw(Height+3,15,"                    ");
		mvprintw(Height+2,15,"                    ");
		refresh();
			menu=0;
		}
	if(Selected==3){
		if(dirb==1){
		MAP[Y][X-1]=1;mvprintw(Y,X-1,"#");
		}
		if(dirb==3){
		MAP[Y][X+1]=1;mvprintw(Y,X+1,"#");
		}
		if(dirb==4){
		MAP[Y+1][X]=1;mvprintw(Y+1,X,"#");
		}
		if(dirb==2){
		MAP[Y-1][X]=1;mvprintw(Y-1,X,"#");	
		}
		mvprintw(Height+1,15,"====================");	
		mvprintw(Height+3,15,    "====================");
		mvprintw(Height+2,15,	 "=   BLOCK CREATED  =");
		refresh();
		getch();
		mvprintw(Height+1,15,"                    ");	
		mvprintw(Height+3,15,"                    ");
		mvprintw(Height+2,15,"                    ");
		refresh();
		menu=0;
		}
	
	if(Selected==4){
		if(dirb==1){
		MAP[Y][X-1]=0;mvprintw(Y,X-1," ");
		}
		if(dirb==3){
		MAP[Y][X+1]=0;mvprintw(Y,X+1," ");
		}
		if(dirb==4){
		MAP[Y+1][X]=0;mvprintw(Y+1,X," ");
		}
		if(dirb==2){
		MAP[Y-1][X]=0;mvprintw(Y-1,X," ");	
		}
		mvprintw(Height+1,15,"====================");
		mvprintw(Height+3,15,    "====================");
		mvprintw(Height+2,15,	 "= BLOCK DESTROYED  =");
		refresh();
		getch();
		mvprintw(Height+1,15,"                    ");	
		mvprintw(Height+3,15,"                    ");
		mvprintw(Height+2,15,"                    ");
		refresh();
		menu=0;
		}
	if(Selected==5){
		ofstream svmap(Lvm[Select]);
		if(svmap.fail()){
			mvprintw(Height+1,15,"Fail");
			continue;
		}else {
			mvprintw(Height+1,15,"====================");
			mvprintw(Height+3,15,    "====================");
		mvprintw(Height+2,15,	     "=     MAP SAVED    =");
		refresh();
		getch();
		mvprintw(Height+1,15,"                    ");	
		mvprintw(Height+3,15,"                    ");
		mvprintw(Height+2,15,"                    ");
		refresh();
		string temp="";
		FOR(i,1,i<Height-1){
			FOR(j,1,j<Width-1){
			if(MAP[i][j]){
				temp+=to_string(i);
				temp+=" ";
				temp+=to_string(j);
				temp+=" ";
				
				}
			}
		}
		FOR(k,0,k<temp.size()){
			svmap.put(temp[k]);
		}
		svmap.close();
			}
		}
	}
}
void CreateUser(){
	ifstream UserLi("ListUser.txt");
	char tmp;
	string temp;
	int cnt=0;
	while(!UserLi.eof()){
		UserLi.get(tmp);
		mvprintw(cnt,0,"%s",tmp);
		cnt++;
		if(tmp==' '||tmp=='\n'){
			UserList.push_back(temp);
			temp="";
		}else{
		temp+=tmp;
		}
	}
	getch();
	temp.erase(temp.end()-1);
	UserList.push_back(temp);
	UserLi.close();	
}

bool CheckUser(string UserCtmp){
	bool found=false;
	for(auto i:UserList){
		if(i==UserCtmp)found=true;
	}
	return found;
}
void CreateAccount(){
	repeat:
	string Password;
	string Passtmp;
	clear();
	mvprintw(0,0,"Enter Username   : ");
	getstr(Username);
	if(CheckUser(Username)){
		clear();
		mvprintw(2,2,"USER ALREADY EXIST");
		getch();
		Verify=0;
	}else{
	mvprintw(1,0,"Enter Password   : ");
	char ch='=';
	int cn=19;
		while(ch!='\n'){
			ch=getch();
			if(ch!='\n')Password+=ch;
			mvprintw(1,cn,"*");
			cn++;
		}
		mvprintw(1,cn-1," ");
	 cn=19;
	 ch='=';
	mvprintw(2,0,"Confirm Password : ");
		while(ch!='\n'){
			ch=getch();
			if(ch!='\n')Passtmp+=ch;
			mvprintw(2,cn,"*");
			cn++;
		}
	clear();
	if(Password!=Passtmp){
		mvprintw(2,2,"Passwords don't match");
		getch();
		goto repeat;
	}
	else{
		string txt=".txt";
		string Usertmp=Username;
		FileMap="User\\"+Usertmp+Password+txt;
		ofstream files(FileMap);
		files.close();
		Verify=1;
		ofstream UserLiIn("ListUser.txt",ios::app);
		UserLiIn<<" "<<Username;
		UserLiIn.close();
		}
	}
	
}

void LoadingMenu(){
	bool menu=0;
	Selection=1;
while(!menu){
	
	FOR(i,1,i<=4){
		if(i==4&&Selection==4)mvprintw(i+6,40," >>  ");
		else if(i==Selection)mvprintw(i+5,40," >>  ");
		if(i==4){
		mvprintw(i+6,44,"Quit Game");
			continue;
		}else{
		 if(i==1)mvprintw(i+5,44,"Sign In ");
		 if(i==2)mvprintw(i+5,44,"Sign Up");
		 if(i==3)mvprintw(i+5,44,"Log in As a Guest"); 
		}
	}
		mvprintw(29,117," ");

		switch(getch()){
			case KEY_DOWN: Selection++; break;
			case KEY_UP: Selection--; break;
			case '\n': menu=1;break;
			case KEY_RIGHT: menu=1;break;
			case ESC: exit(0);break;
		}
		if(Selection>4)Selection=1;
		if(Selection<1)Selection=4;
		refresh();
		clear();
	}
	if(Selection==4)exit(0);	
}

void Login(){
	string Password;
	clear();
	mvprintw(0,0,"Enter Username : ");
	getstr(Username);
	mvprintw(1,0,"Enter Password : ");
	char ch='=';
	int cn=17;
		while(ch!='\n'){
			ch=getch();
			if(ch!='\n')Password+=ch;
			mvprintw(1,cn,"*");
			cn++;
		}	
		string Usertmp=Username;
		if(Usertmp=="admin")Dev=1;
		string txt=".txt";
		string filename="User\\"+Usertmp+Password+txt;
		FileMap=filename;
		ifstream Account(filename);
	if(!Account){
		 clear();
		 mvprintw(2,2,"WRONG USERNAME OR PASSWORD");
		 getch();
		 Account.close();
	}else{
		clear();
		mvprintw(2,2,"LOGIN SUCCESS");
		char ctmp;
		while(!Account.eof()){
		Account.get(ctmp);
		if(isdigit(ctmp)){
			Level[ctmp-'0'+1]=1;
		}
		}
		Account.close();
		getch();
		clear();
		Verify=1;
	}
}
void Item(){
	Level[1]=1;
	if(!Verify){
	
	Username[0]='G';
	Username[1]='u';
	Username[2]='e';
	Username[3]='s';
	Username[4]='t';
	}
	string bs="Map\\Map";
		for(int i=1;i<=10;i++){
		string tmp=to_string(i);
		Lvm[i]=bs+tmp+".txt";
	}
	Lvm[0]="TitleAni.txt";
}

void Menu(){
	bool menu;
	Select=1;
while(!menu){
	int Selected=0;
	mvprintw(1,3,"%s",Username);
	FOR(i,1,i<=12){
		if((i==11||i==12)&&Select==i)mvprintw(i+6,40," >>  ");
		else if(i==Select)mvprintw(i+5,40," >>  ");
		if(i==11||i==12){
			if(i==11)mvprintw(i+6,44,"Instructions");
			if(i==12) mvprintw(i+6,44,"Quit Game");
		}else{
		 mvprintw(i+5,44,"Level ");
		mvprintw(i+5,52,"%d",i);
		
		if(!Level[i])mvprintw(i+5,54," (Locked)");
		
		}
	}
		mvprintw(29,117," ");

		switch(char c=getch()){
			case KEY_DOWN: Select++; break;
			case KEY_UP: Select--; break;
			case '\n':if(Level[Select]) menu=1;Selected=Select;break;
			case KEY_RIGHT:if(Level[Select])menu=1;Selected=Select;break;
			case ESC:menu=1;Game=1;Logout=1;Verify=0;break;
		}
		if(Selected==12)exit(0);
		if(Select>12)Select=1;
		if(Select<1)Select=12;
		refresh();
		clear();
		if(Selected==11){
	 	 mvprintw(6,30,"The Character can move in any of the four directions \n\t\t\t\t      as per the player's control.W,A,S,D / Arrow");
	 	 mvprintw(8,30,"The game ends as soon as the Character is on the right side");
	 	 mvprintw(9,30,"\t     Press ESC to Pause\n\t\t\t\t");
	 	 mvprintw(11,30,"\t\t(PRESS ANY BUTTON TO CONTINUE)");
		getch();
		menu=0;
		}
		clear();
		
	}	
}

void Setup(){
	Quit=0;
	Verify=1;
	FOR(i,0,i<Height)FOR(j,0,j<Width)MAP[i][j]=0;
		XB=YB=999;
		Game=0;
		Score=0;
		X=Y=1;
		int temp=1;
		int xm,ym;
	ifstream file(Lvm[Select]);
		char a;
		int now=-1;
		int bf=-1;
	while(!file.eof()){
		file.get(a);
		if(isdigit(a)){
			if(bf!=-1){
				now=bf*10+(a-'0');
			}else{
				now=a-'0';
				bf=a-'0';
			}

		}else{
			bf=-1 ;
			if(now!=-1){
				if(temp%2){
					xm=now;
				}else{
					ym=now;
					MAP[xm][ym]=1;
				}	
				temp++;
			}
			now=-1;
		}
	}
	file.close();
	
	
	
	
	if(Select==11)Game=1;
}

void Console(){
		mvprintw(29,117," ");
		switch (getch()) {
				case 'a': dir = LEFT; break;
				case 'd': dir = RIGHT; break;
				case 'w': dir = UP; break; 
				case 's': dir = DOWN ; break;
				case 'A': dir = LEFT; break;
				case 'D': dir = RIGHT; break;
				case 'W': dir = UP; break; 
				case 'S': dir = DOWN ; break;
				case KEY_LEFT: dir = LEFT; break;
				case KEY_RIGHT: dir = RIGHT; break;
				case KEY_UP: dir = UP; break; 
				case KEY_DOWN: dir = DOWN ; break;
				case 'x': Game = true; break;
				case 'm': Game = true; Quit=true; break;
				case ESC: Game = true; Quit=true; break;
				case '\t': if(Dev)Cheat = true; break;
			}	
	
}

void Algorithm(){
	YB=Y; XB=X;
	if(Ghost){
		if(dir==LEFT&&X>1){
			X--;
			dirb=1;
		}
		if(dir==RIGHT&&X<Width-3){
			X++;
			dirb=3;
		}
		if(dir==UP&&Y>1){
			Y--;
			dirb=4;
		}
		if(dir==DOWN&&Y<Height-2){
			Y++;
		}
		if(X>=90){	
		Quit=1;
		Level[Select+1]=1;
		Game=1;
		clear(); 
			do{
				mvprintw(12	,45,"YOU WINNN! (PRESS ENTER)");
				mvprintw(29,117," ");
			}while(getch()!='\n');
		
			
		}
	}else{
		if(dir==LEFT&&X>1&&!MAP[Y][X-1]){
				X--; dirb=1;
		}
		if(dir==RIGHT&&X<Width-3&&!MAP[Y][X+1]){
				X++; dirb=3;
		}
		if(dir==UP&&Y>1&&!MAP[Y-1][X]){
				Y--; dirb=2;
		}
		if(dir==DOWN&&Y<Height-2&&!MAP[Y+1][X]){
				Y++; dirb=4; 
		}
			if(X>=90){	
			Quit=1;
			Game=1;
			clear(); 
			
				ofstream Record(FileMap,ios::app);
				if(!Level[Select+1])Record.put(Select+'0');
				Record.close();
			
			do{

				mvprintw(12	,45,"YOU WINNN! (PRESS ENTER)");
				mvprintw(29,117," ");
				
			}while(getch()!='\n');
			Level[Select+1]=1;
		}
	}
	
	dir=STOP;
}

void Draw(){
	Sleep(GameSpeed);
	WINDOW *win = newwin(Height, Width, 0, 0);
    refresh();
    box(win, 0, 0);
    FOR(i,1,i<Height-1)FOR(j,1,j<Width-1){
    	
    	if(MAP[i][j])mvprintw(i,j,"#"); 	
		
	}
    mvprintw(Height+1,2,"Hi %s",Username);
    mvprintw(YB,XB," ");
    char chara;
    mvprintw(Y,X,"§");        //CHARACTER!!
	wrefresh(win);
}

void TitleAnimation(){
	attron(COLOR_PAIR(1));
	FOR(Rep,0,Rep<120){
		clear();
	FOR(i,0,i<25){
		FOR(j,0,j<100){
			if(MAP1[i][j])mvprintw(i+4,j+Rep,"#");
		}
	}
	Sleep(30);
	refresh();
	}
	attroff(COLOR_PAIR(1));
}
void Functions(){
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLUE);
	system("color 0B");
	CreateUser();
	initscr();
	Label:
	TitleAnimation();
	mvprintw(12,45,"PRESS ANY BUTTON TO START");
	getch();
	clear();
	LoadingMenu();
	if(Selection==1)while(!Verify)Login();
	if(Selection==2)while(!Verify)CreateAccount();
		
		Item();
		
	Start:
		clear();
		
		Menu();
		if(Logout){
			clear();
			goto Label;
		}
		Setup();
    	clear();
    	
	while(!Game){
		
		Draw();
		Console();
		if(Cheat)DevMenu();
		Algorithm();
		
	}	
			refresh();
		if(Quit) goto Start;
		clear();
		endwin();
}

main(){
	Back:
	Functions();
	return EXIT_SUCCESS;
//	endwin();
}


	
