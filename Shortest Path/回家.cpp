/*
*问题描述：现在是晚餐时间,而母牛们在外面分散的牧场中。你的工作是指出哪只母牛会最先到达谷仓(在给出的测试数据中,总会有且只有一只最快的母牛)。 
*在挤奶的时候(晚餐前),每只母牛都在她自己的牧场上,一些牧场上可能没有母牛。 每个牧场由一条条道路和一个或多个牧场连接(可能包括自己)。 
*有时，两个牧场(可能是字母相同的)之间会有超过一条道路相连。 至少有一个牧场和谷仓之间有道路连接。 
*因此,所有的母牛最后都能到达谷仓,并且母牛总是走最短的路径。 当然,母牛能向着任意一方向前进,并且她们以相同的速度前进。 
*牧场被标记为'a'..'z'和'A'..'Y',在用大写字母表示的牧场中有一只母牛,小写字母中则没有。 谷仓的标记是'Z',注意没有母牛在谷仓中。
*输入说明：第 1 行: 整数 P(1<= P<=10000),表示连接牧场(谷仓)的道路的数目。
*第 2 ..P+1行:  用空格分开的两个字母和一个整数:被道路连接牧场的标记和道路的长度(1<=长度<=1000)。
*输出：单独的一行包含二个项目:最先到达谷仓的母牛所在的牧场的标记,和这只母牛走过的路径的长度。
*/



#include <iostream>
using namespace std;
const int INF = 99999999;
int graph[52][52];
int N;

int getCode(char c)
{
	if (c >= 'a' && c <= 'z')
		return c - 'a';
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 26;
	return -1;
}

void input()
{
	for (int i = 0; i < 52; i++)
	{
		for (int j = 0; j < 52; j++)
		{		
			if (i == j)
				graph[i][j] = 0;
			else
				graph[i][j] = INF;
		}		
	}
	
	/*对输入编码：
	*a b c d ..  A B C D .. Z
	*0 1 2 3 ..  26 27 28 .. 51
	*/

	cin >> N;
	char m, n;
	int v, s, t;
	for (int i = 0; i < N; i++)
	{
		cin >> m >> n >> v;
		s = getCode(m);
		t = getCode(n);
		if (v < graph[s][t])				//输入有重边的情况，选择最短的那条边
		{
			graph[s][t] = v;
			graph[t][s] = v;
		}
	}
}

void flyod()
{
	int i, j, k;
	for (k = 0; k < 52; k++)
	{
		for (i = 0; i < 52; i++)
		{
			for (j = 0; j < 52; j++)
			{
				if (graph[i][k] < INF && graph[k][j] < INF && graph[i][j] > graph[i][k] + graph[k][j])
					graph[i][j] = graph[i][k] + graph[k][j];
			}
		}
	}
}

void output()
{
	char c;
	int min = INF;
	for (int i = 26; i < 51; i++)
	{
		if (graph[i][51] < min)
		{
			min = graph[i][51];
			c = i - 26 + 'A';
		}
	}
	cout << c << " " << min;
}

int main()
{
	input();
	flyod();
	output();
	return 0;
}
