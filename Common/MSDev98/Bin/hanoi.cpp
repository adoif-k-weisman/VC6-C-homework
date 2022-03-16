#include<iostream>
using namespace std;
//问题：
//有N件物品，告诉你这N件物品的重量以及价值，将这些物品划分为n组，每组中的物品互相冲突，
//最多选一件，求解将哪些物品装入背包可使这些物品的体积综合不超过背包的容量，且价值总和最大。
#define max(a,b) a>b ? a : b
const int N = 105;

int v[N][N],w[N][N],s[N];
int dp[N];
int n, m;

int main()
{
	cin >> n >> m;
	int i,j,k;
	for ( i = 1; i <= n; i++) {
		cin >> s[i];//第i组的物品数量
		for ( j = 0; j < s[i]; j++)
			cin >> v[i][j] >> w[i][j];//第i组物品第j件的体积和价值
	}

	for( i =1;i<=n;i++)//第i组
		for ( j = m; j >= 0; j--) {
			for ( k = 0; k < s[i]; k++) {
				if(j>=v[i][k])
				dp[j] = max(dp[j], dp[j - v[i][k]] + w[i][k]);
			}
		}
	cout <<"answer:"<< dp[m]<<endl;
	return 0;
}

//分组的背包问题将彼此互斥的若干物品称为一个组，这建立了一个很好的模型。
//不少背包问题的变形都可以转化为分组的背包问题由分组的背包问题进一步可定义“泛化物品”的概念，
//十分有利于解题。
