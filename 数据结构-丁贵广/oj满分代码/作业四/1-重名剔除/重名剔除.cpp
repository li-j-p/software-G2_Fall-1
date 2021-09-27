#include <cstring>
#include <iostream>
using namespace std;
const int MAXSIZE = 6e5 + 5;
char str[50];

typedef struct node
{
    char val[50];
    int cnt;
    node()
    {
        cnt = 0;
    }
    node *next;
} * Node;
Node nodeList[MAXSIZE];

int main()
{
    int moddle = 6e5 - 10, p = 13331, n, length;
    long long int hight = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        hight = 0;
        scanf("%s", str);
        length = strlen(str);
        for (int j = 0; j < length; j++)
        {
            hight = (hight * p % moddle + (str[j] - 'a' + 1)) % moddle;
        }
        node *current = nodeList[hight];
        int flag = 0;
        if (nodeList[hight] == NULL)
            nodeList[hight] = new node;

        while (NULL != current)
        {
            if (strcmp(current->val, str) == 0)
            {
                current->cnt++;
                if (current->cnt == 2)
                {
                    printf("%s\n", str);
                }
                flag = 1;
                break;
            }
            current = current->next;
        }
        if (!flag)
        {
            node *temp = new node;
            strcpy(temp->val, str);
            temp->next = nodeList[hight]->next;
            temp->cnt = 1;
            nodeList[hight]->next = temp;
        }
    }
    return 0;
}