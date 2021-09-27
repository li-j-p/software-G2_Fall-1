#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;
int f[10];
int dists[40320 + 5];
struct Node1
{
    int data, dataList[10];
    int Couter();
    void Exchange(int &, int &);
    void Fun1();
    void Fun2();
    void Fun3();
} queue[41000];

int Node1::Couter()
{
    data = 0;
    for (int i = 1, x; i <= 8; i++)
    {
        x = 0;
        for (int j = i + 1; j <= 8; j++)
        {
            if (dataList[j] < dataList[i])
            {
                x++;
            }
        }
        data += x * f[9 - i];
    }
    return data;
}

void bfs()
{
    Node1 current;
    for (int i = 1; i <= 8; i++)
    {
        current.dataList[i] = i;
    }
    int head = 0, tail = 0;
    dists[current.Couter()] = 1;
    queue[tail++] = current;
    Node1 temp;
    while (head != tail)
    {
        current = queue[head++];
        head %= 40900;
        temp = current;
        temp.Fun1();
        if (!dists[temp.Couter()])
        {
            queue[tail++] = temp;
            tail %= 40900;

            dists[temp.Couter()] = dists[current.data] + 1;
        }

        temp = current;
        temp.Fun2();
        if (!dists[temp.Couter()])
        {
            queue[tail++] = temp;
            tail %= 40900;

            dists[temp.Couter()] = dists[current.data] + 1;
        }

        temp = current;
        temp.Fun3();
        if (!dists[temp.Couter()])
        {
            queue[tail++] = temp;
            tail %= 40900;
            dists[temp.Couter()] = dists[current.data] + 1;
        }
    }
}

void init()
{
    f[1] = 0;
    f[2] = 1;
    for (int i = 3; i <= 8; i++)
    {
        f[i] = f[i - 1] * (i - 1);
    }
}

int main()
{
    init();
    bfs();
    int n;
    cin >> n;
    Node1 x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= 8; j++)
            cin >> x.dataList[j];
        cout << dists[x.Couter()] - 1 << endl;
    }
    return 0;
}

void Node1::Exchange(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
void Node1::Fun1()
{
    for (int i = 1; i <= 4; i++)
        Exchange(dataList[i], dataList[9 - i]);
}
void Node1::Fun2()
{
    dataList[0] = dataList[1];
    for (int i = 1; i <= 3; i++)
    {
        dataList[i] = dataList[i + 1];
    }
    dataList[4] = dataList[0];
    dataList[9] = dataList[8];
    for (int i = 8; i >= 6; i--)
    {
        dataList[i] = dataList[i - 1];
    }
    dataList[5] = dataList[9];
}
void Node1::Fun3()
{
    dataList[0] = dataList[2];
    dataList[2] = dataList[3];
    dataList[3] = dataList[6];
    dataList[6] = dataList[7];
    dataList[7] = dataList[0];
}