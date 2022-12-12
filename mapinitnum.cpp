#include<bits/stdc++.h>
using namespace std;
int main(){
    int dump;
    vector<vector<int>>map(25,vector<int>(100,0));
    int cnt=1;
    int x, y;
    vector<int>p;
    while(cin>>dump){
       p.push_back(dump);
    }

   for(int i=0;i<p.size();i++){
      if(i%2==1){
          map[p[i-1]][p[i]]=1;
      }
   }
  
  for(int i=0;i<25;i++){
      for(int j=0;j<100;j++){
          cout<<map[i][j]<<',';
      }
      cout<<endl;
  }
    
}
