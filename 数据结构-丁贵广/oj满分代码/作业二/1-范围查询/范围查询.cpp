#include<stdio.h>
#include<stdlib.h>
int bin(int *a, int e, int lo, int hi);
void m_qsort(int *s,int l,int r);
int main()
{
	int N;
	int M;
	scanf("%d",&N);
	scanf("%d",&M);
	int *s;
	s = (int*)malloc(sizeof(int)*N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&s[i]);
	}
	m_qsort(s,0,N-1);
	for(int i=0;i<M;i++)
	{
		int l,r,res;
		scanf("%d%d",&l,&r);
		int ll = bin(s,l,0,N);
		int rr = bin(s,r,0,N);
		if(ll>=0)
		{
		   if(l == s[ll])res = rr - ll +1;
		   else res = rr - ll;
		}
		if(ll == -1)
			res = rr+1;
		printf("%d\n",res);
	}
	return 0;
}

int bin(int *a, int e, int lo, int hi)
{
    int mid;
    while(lo<hi)
    {
        mid = lo + ((hi - lo)>>1);
        (e<a[mid])?hi=mid:lo = mid+1;
    }
    return --lo;//返回不大于e的最大序号，注意如果小于a[0]，返回的最大序号为-1
}

void m_qsort(int *s,int l,int r)
{
	if(l>=r)return ;
	int b = l;
	int c = r;
   int a = s[l];
   while(r>l)
   {
      while(s[r]>=a && r>l)r--;
	  s[l] = s[r];
	  while(s[l]<a && r>l)l++;
	  s[r] = s[l];
   }
   s[l] = a;
   m_qsort(s,b,l-1);
   m_qsort(s,l+1,c);
}