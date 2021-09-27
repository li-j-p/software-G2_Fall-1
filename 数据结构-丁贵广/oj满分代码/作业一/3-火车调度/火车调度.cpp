#include<stdio.h>
#include<stdlib.h>

int n,m;
int size = 0;
int *stack ;
int *b ;
int *answer ;
int k=0;
int t=1;
void pop()
{
	size--;
	answer[k++] = 0;
}

void push(int i)
{
	stack[size] = i;
	size++;
	answer[k++] = 1;
}

int top()
{
	if(size>0)
		return stack[size-1];
}

bool full()
{
	if(size == m)return true;
	return false;
}

bool empty()
{
	if(size == 0)return true;
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	stack = (int*)malloc(sizeof(int)*m);
	b= (int*)malloc(sizeof(int)*n);
	answer = (int*)malloc(sizeof(int)*n*2);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&b[i]);
	}
	for(int i=0;i<n;i++)
	{
		while(empty() || (size>0 && b[i]!=top()))
		{
			if(t>n || full())
			{
				puts("No");
				return 0;
			}
			push(t++);
		}
		pop();	
	}
	for(int i=0;i<2*n;i++)
	{
		if(answer[i]==0)puts("pop");
		if(answer[i]==1)puts("push");
	}
	return 0;
}