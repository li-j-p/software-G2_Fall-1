#include<stdio.h>
#include<stdlib.h>
struct list{
	int ID;
	list* next;
	list* front;
};
int n,m;
list* insert(list*now,int ID)
{

	list* cur = (list*)malloc(sizeof(list));
	cur->ID = ID;
	cur->next = now->next;
	now->next->front = cur;
	now->next = cur;
	cur->front = now;
	return cur;
}
int main()
{
	scanf("%d%d",&n,&m);
	if(n==0)return 0;
	list* now = (list*)malloc(sizeof(list));
	int id;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&id);
		if(i==0)
		{			
			now->ID = id;
			now->next = now->front = now;
		}
		else
		{
			for(int j=0;j<m-1;j++)
			{
				now = now->next;
			}
			now = insert(now,id);	
		}
	}
	for(int i=0;i<n;i++)
	{
		printf("%d ",now->ID);
		now = now->front;
	}
	return  0;
}