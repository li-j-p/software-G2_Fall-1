#include<stdio.h>
#include<stdlib.h>

long long int answer = 0;

struct Point
{
	int x;
	int y;
};

Point *sorted;
Point * point;

void merge(int s,int m,int e)
{
	int i=s;
	int j=m;
	int k=0;	
	while(i<m&&j<e)
	{
		if(point[i].x<point[j].x)
			sorted[k++] = point[i++];
		else
			sorted[k++] = point[j++];
	}
	while(i<m)sorted[k++] = point[i++];
	while(j<e)sorted[k++] = point[j++];
	for(int v=0;v<e-s;v++)
	{
		point[s+v] = sorted[v];
	}
}

void mergesort(int s,int e)
{
  if(e-s>1)
  {
	  int m = (e+s)/2;
	  mergesort(s,m);
	  mergesort(m,e);
	  merge(s,m,e);
  }
}

void merge1(int s,int m,int e)
{
	int i=s;
	int j=m;
	int k=0;
	int h=s;
	while(i<m&&j<e)
	{
		if(point[i].y<=point[j].y)
		{
			sorted[k++] = point[i++];
			answer += e-j;
		}
		else
			sorted[k++] = point[j++];
	}
	while(i<m)sorted[k++] = point[i++];
	while(j<e)sorted[k++] = point[j++];
	for(int v=0;v<e-s;v++)
	{
		point[s+v] = sorted[v];
	}
}

void mergesort1(int s,int e)
{
  if(e-s>1)
  {
	  int m = (e+s)/2;
	  mergesort1(s,m);
	  mergesort1(m,e);
	  merge1(s,m,e);
  }
}

int main()
{
	int n;
	scanf("%d",&n);
	point = (Point*)malloc(sizeof(Point)*n);
	sorted = (Point*)malloc(sizeof(Point)*n);
	for(int i=0 ; i<n; i++)
	{
		scanf("%d%d",&point[i].x,&point[i].y);
	}
	mergesort(0,n);
	mergesort1(0,n);

	printf("%ld",answer);
	return 0;
}
