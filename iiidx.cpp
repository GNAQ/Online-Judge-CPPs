#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

int n,seq[500010]; double k;
vector<int> edge[500010];
int tsiz[500010];


template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'0') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	edge[fx].push_back(tx);
}

namespace SGT
{
	#define LCH (inx<<1)
	#define RCH (inx<<1|1)
	
	struct Seg_Tree
	{
		int l,r,mid,val,tag;
	}tree[400010];
	
	void Pushdown(int inx)
	{
		
	}
	
	void BuildTree(int inx,int lxx,int rxx)
	{
		tree[inx].l=lxx; tree[inx].r=rxx;
		tree[inx].mid=(lxx+rxx)>>1;
		if (lxx==rxx) 
		{
			return;
		}
		BuildTree(LCH,lxx,tree[inx].mid);
		BuildTree(RCH,tree[inx].mid+1,rxx);
		
	}
	
	void Upd()
	{
		
	}
	
	#undef LCH
	#undef RCH
};

void DFS(int now)
{
	tsiz[now]=1;
	for (int v=0;v<edge[now].size();v++)
	{
		DFS(edge[now][v]);
		tsiz[now]+=tsiz[edge[now][v]];
	}
}
void BuildTree()
{
	for (int i=1;i<=n;i++)
		Is((int)floor(i/k),i);
	DFS(0);
}



int main()
{
	readx(n); scanf("%lf",&k); 
	for (int i=1;i<=n;i++) readx(seq[i]);
	BuildTree();
	for (int i=1;i<=n;i++) 
	{
		
	}
	
	
	
	
	
}