#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#include<ctime>
#include<cstring>
using namespace std;

struct mergedball{
	int c,x;
};

const int inf=1000;
int totball;
mergedball ball[100];
int F[100][100][7][7][3];
int ans=0;

int extraneed1(int x){
	if(x==1) return 2;
	return 1;
}

int extraneed2(int x){
	if(x==2) return 1;
	return 0;
}

int dp(int l,int r,int c1,int c2,int k){
//	if(c1>c2) swap(c1,c2);
	int nc=ball[l].c,nx=ball[l].x,ans=inf;
	
	if(l==r) return extraneed1(nx);
	if(l>r)
		if(c1==0&&c2==0) return 0;
		else return inf;
	if(F[l][r][c1][c2][k]) return F[l][r][c1][c2][k];
	
	
	if(k==0){
		//直接消除
		if((nc!=c1&&nc!=c2&&c1!=c2)||(c1==0&&c2==0)) ans=min(ans,dp(l+1,r,0,0,0)+extraneed1(nx));
		else ans=min(ans,dp(l+1,r,min(nc,c1),max(nc,c2),0)+extraneed1(nx));
	}
	for(int p=l+1;p<=r;++p){
		if(ball[p].c==nc){
			if(!(k==2&&ball[p].x!=1)){
				//将这两段组合并消去
				if((nc!=c1&&nc!=c2&&c1!=c2)||(c1==0&&c2==0)||(c1==c2&&p==r)) ans=min(ans,dp(l+1,p-1,nc,nc,0)+dp(p+1,r,0,0,0)+extraneed2(nx+ball[p].x+k));
				else ans=min(ans,dp(l+1,p-1,nc,nc,0)+extraneed2(nx+ball[p].x+k)+dp(p+1,r,min(nc,c1),max(nc,c2),0));
			}
			if((k==0&&ball[p].x==1)||(k==1&&nx==1&&ball[p].x==1)){
				//留着不消，但合并
				ans=min(ans,dp(l+1,p-1,nc,nc,0)+dp(p,r,c1,c2,min(nx+k,2)));
			}
		}
	}
	return F[l][r][c1][c2][k]=ans;
}

int main(){ 
	freopen("in1.txt","r",stdin);
	scanf("%d",&totball);
	for(int i=1;i<=totball;++i) scanf("%d%d",&ball[i].c,&ball[i].x);
	
	freopen("dp.txt","w",stdout);
	ans=dp(1,totball,0,0,0);
	printf("%d\n",ans);
	fclose(stdout);
}
