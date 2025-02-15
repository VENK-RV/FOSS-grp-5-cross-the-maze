#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#define MIN(x,y) (x)<(y)?(x):(y)
using namespace std;

const int N=110;
char m[N][N];
bool mz[N][N];
int dir[4][2] = {{0,-1},{-1,0},{0,1},{1,0}};
char dirn[4] = {'W','N','E','S'};
bool flag[N][N][4];
char step[20010];
int stepnum;

int fun(int sx,int sy,int ex,int ey,int head)
{
	//printf("sx %d sy %d step %d\n",sx,sy,step);
	if(sx==ex && sy==ey) return 0;
	if(mz[sx][sy] == 0) return -1;
	
	head = (head+3)%4;
	
	for(int i=0; i<4; i++)
	{		
		int headx = sx+dir[head][0];
		int heady = sy+dir[head][1];
		int left = (head+3)%4;
		int leftx = sx+dir[left][0];
		int lefty = sy+dir[left][1];
	
		if(flag[sx][sy][head]) continue;
		if(i>0 && mz[leftx][lefty]) break;
		
		step[stepnum++] = dirn[head];
		flag[sx][sy][head] = 1;
			
		int tmp = fun(headx,heady,ex,ey,head);
		if(tmp >= 0) return tmp + 1;
		
		step[--stepnum] = 0;
		
		head = (head+1)%4;
	}
	
	return -1;
}

int main()
{
	freopen("D-large-practice.in","r",stdin);
	freopen("D-large-practice.out","w",stdout);
	
	int t;
	scanf("%d",&t);
	for(int cnt=1;cnt<=t;cnt++)
	{
		int n;
		scanf("%d",&n);
		
		memset(m,0,sizeof(m));
		memset(mz,0,sizeof(mz));
		memset(flag,0,sizeof(flag));
		
		for(int i=0; i<n; i++)
			scanf("%s",m[i]);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(m[i][j] == '.')
					mz[i+1][j+1] = 1;
			
		int sx,sy,ex,ey;
		scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
		
		memset(step,0,sizeof(step));
		stepnum = 0;
		
		int head;
		
		if(sx==1 && sy==1) head = 3;
		else if(sx==1 && sy>1) head = 0;
		else if(sx>1 && sy==1) head = 2;
		else head = 1;
		
		int ans = fun(sx,sy,ex,ey,head);
		
		printf("Case #%d: ",cnt);
		if(ans < 0) printf("Edison ran out of energy.\n"); 
		else if(ans == 0) printf("0\n");
		else printf("%d\n%s\n",ans,step);
	} 
}