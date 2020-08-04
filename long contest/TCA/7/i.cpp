#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
int fx[] = {+1,-1,+1,-1};
int fy[] = {+1,-1,-1,+1};

bool check(int x,int y,vector<vector<char>> A){
    if(x>=5 || x<0)return false;
    if(y>=9 || y<0)return false;
    if(A[x][y] == '.' || A[x][y] == 'x')return false;
    return true;
}

lli win1 = 0;
lli win2 = 0;
void play(vector<vector<char>> A,int turn){
    cout<<"Turno"<<turn<<endl;
    for(int i =0;i<5;i++)
        for(int j = 0;j<9;j++)
            cout<<A[i][j]<<" \n"[j == 8];
    bool last = true;
    for(int i = 0;i<5;i++){
        for(int j = 0;j<9;j++){
            if(check(i,j,A)){   
                for(int z = 0;z<4;z++){
                    int nx = i,ny = j; 
                    vector<vector<char>> aux = A;
                    for(int k = 0;k<5;k++){
                        nx+=fx[z];
                        ny+=fy[z];
                        if(check(nx,ny,aux)){
                            cout<<nx<<" "<<ny<<endl;
                            last = false;
                            aux[nx][ny] = '.';
                            play(aux,turn^1);
                        }
                        else break;
                    }
                }
            }
        }
    }
    if(last && turn)win1++;
    else win2++;
}

int main(){
    int n;
    vector<vector<char>> grid(5,vector<char>(9,'x'));

    for(int i = 0;i<3;i++)
        cin>>grid[0][2+(i*2)];
    for(int i = 0;i<4;i++)
        cin>>grid[1][1+(i*2)];
    for(int i = 0;i<5;i++)
        cin>>grid[2][(i*2)];
    for(int i = 0;i<4;i++)
        cin>>grid[3][1+(i*2)];
    for(int i = 0;i<3;i++)
        cin>>grid[4][2+(i*2)];

    for(int i =0;i<5;i++)
        for(int j = 0;j<9;j++)
            cout<<grid[i][j]<<" \n"[j == 8];
    cout<<endl;
    play(grid,0);
    cout<<win1<<" "<<win2<<endl;
    
    return 0;
}

//   . . .
//  . . . .
// . O O O O
//  O O O O
//   O O O