#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
//p数组记录time次请求完成时，刚进行位置变换的员工的位置。 
//f[time][a][b]表示第time次指令完成时，三个员工分别位于p[time]、a、b时的花费。 
int f[2][210][210],p[1010],c[210][210];
int n,m;
int main()
{
	// m个位置，n个请求 
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			cin>>c[i][j];
	for(int i=1;i<=n;i++) cin>>p[i];
	// 选取一个初始状态，也可以选p[0]=1,f[0][2][3]=0、p[0]=2,f[0][1][3]=0; 
	p[0]=3;
	memset(f,0x3f,sizeof(f));
	f[0][1][2]=0;
	for(int i=1;i<=n;i++)
		for(int x=1;x<=m;x++)
			for(int y=1;y<=m;y++)
				if(f[(i-1)&1][x][y]!=0x3f3f3f3f)
				{
					int z=p[i-1]; //z（p[i-1]）为上次移动的员工的位置 
					if(y!=p[i]&&z!=p[i])  //如果可以移动x (y和z都不在本次要被服务的位置) 
						f[i&1][y][z]=min(f[i&1][y][z],f[(i-1)&1][x][y]+c[x][p[i]]);
					if(x!=p[i]&&z!=p[i]) f[i&1][x][z]=min(f[i&1][x][z],f[(i-1)&1][x][y]+c[y][p[i]]);
					if(x!=p[i]&&y!=p[i]) f[i&1][x][y]=min(f[i&1][x][y],f[(i-1)&1][x][y]+c[z][p[i]]);
					f[(i-1)&1][x][y]=0x3f3f3f3f;
				}
	int ans=1<<30;
	for(int x=1;x<=m;x++)
		for(int y=1;y<=m;y++)
			ans=min(ans,f[n&1][x][y]);
	cout<<ans<<endl;
}