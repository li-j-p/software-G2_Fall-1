
#include<stdio.h>
using namespace std;
#define MAXN 1000005
int n,m,cnt,q[MAXN],degree[MAXN];
int ans;
struct node
{
	int id;
	node *next;
	node(){next=NULL;}
	node(int x,node *n) :id(x),next(n){}
};
struct city
{
	node *nc;
	int dp;
	city(){nc=NULL;dp=1;}
}a[MAXN];
void tuopu()
{
	for(int i=1;i<=n;i++)
		if(!degree[i])q[++cnt]=i;
	for(int i=1;q[i];i++)
	{
		int res=q[i];
		for(node *tmp=a[res].nc;tmp!=NULL;tmp=tmp->next)
		{
			if(a[res].dp+1>a[tmp->id].dp)a[tmp->id].dp=a[res].dp+1;
			if(a[tmp->id].dp>ans)ans=a[tmp->id].dp;
			degree[tmp->id]--;
			if(!degree[tmp->id])q[++cnt]=tmp->id;
		}
	}
}
int  main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		degree[y]++;
	    a[x].nc=new node(y,a[x].nc);
	}
	tuopu();
	printf("%d",ans);
	return 0;
}