#include<stdio.h>
#include<stdlib.h>

    int *r,*l;
	int *pre;
	int *last;
	int *lastid;
void build(int root,int p1,int p2,int l1, int l2);
void print(int root);
int main()
{
	int n;
	scanf("%d",&n);
	l = (int*)malloc(sizeof(int)*(n+1));
	r = (int*)malloc(sizeof(int)*(n+1));
	pre = (int*)malloc(sizeof(int)*n);
	last= (int*)malloc(sizeof(int)*n);
	lastid = (int*)malloc(sizeof(int)*(n+1));
	for(int i=0;i<n;i++)scanf("%d",&pre[i]);
	for(int i=0;i<n;i++)scanf("%d",&last[i]);
	for(int i=0;i<n;i++){lastid[last[i]]=i;l[i+1]=r[i+1]=0;}
	build(pre[0],0,n-1,0,n-1);
	print(pre[0]);
	return 0;
}

void print(int root)
{
	if(root)
	{
		print(l[root]);
		printf("%d ",root);
		print(r[root]);
	}
}

void build(int root,int p1,int p2,int l1,int l2)
{
	if(p1==p2)return ;
	l[root] = pre [p1+1];r[root] = last[l2-1];
	build(l[root],p1+1,lastid[l[root]]-l1+p1+1,l1,lastid[l[root]]);
	build(r[root],lastid[l[root]]+p1+2-l1,p2,lastid[l[root]]+1,l2-1);
}

