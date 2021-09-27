#include<stdio.h>

char ch[10002];

int main()
{
	int N;
	scanf("%d",&N);
	scanf("%s",ch);

	int sz = 0;
	for(int i=0;i<N;i++)
	{
		if(ch[i] == 'A' || ch[i] == 'C')
		{
			sz++;
		}
		if(ch[i] == 'B')
		{
			if(sz<=0)
			{
				puts("False");
				return 0;
			}
			else sz--;
		}
	}

	sz= 0;
	for(int i=N-1;i>=0;i--)
	{
		if(ch[i] == 'B' || ch[i] == 'C')
		{
			sz++;
		}
		if(ch[i] == 'A')
		{
			if(sz<=0)
			{
				puts("False");
				return 0;
			}
			else sz--;
		}
	}
	puts("True");
	return 0;
}