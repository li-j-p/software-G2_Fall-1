#include<stdio.h>
#include<stdlib.h>


int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	bool *flag = (bool*)malloc(sizeof(bool)*(n+2));
	int *c = (int*)malloc(sizeof(int)*(n+2));
	int *a=(int*)malloc(sizeof(int)*m);
	int *b=(int*)malloc(sizeof(int)*m);
	for(int i=0;i<n+1;i++)flag[i] = 0;
	for(int i=0;i<m;i++)scanf("%d%d",&a[i],&b[i]);
	int *queue=(int*)malloc(sizeof(int)*(n+2));
	int size = 0;
	c[a[0]]=0;
	flag[a[0]]=1;
	queue[size++]=a[0];
	int cur = 0;
	while(size<n)
	{
		if(cur>=size)
		{
			for(int i=1;i<n+1;i++)
			{
				if(flag[i]==0)
				{
					flag[i]=1;queue[size++]=i;c[i]=0;break;
				}
			}
		}
		for(int i=0;i<m;i++)
		{
			if(a[i]==queue[cur]&&flag[b[i]]==0){c[b[i]]=(c[a[i]]+1)%2;flag[b[i]]=1;queue[size++]=b[i];}
			if(a[i]==queue[cur]&&flag[b[i]]==1)if(c[a[i]]==c[b[i]]){printf("-1");return 0;}
			if(b[i]==queue[cur]&&flag[a[i]]==0){c[a[i]]=(c[b[i]]+1)%2;flag[a[i]]=1;queue[size++]=a[i];}
			if(b[i]==queue[cur]&&flag[a[i]]==1)if(c[a[i]]==c[b[i]]){printf("-1");return 0;}
		}
		cur++;
	}
	printf("1");
	return 0;
}



