
/*问题:有一个邮递员要送东西，邮局在节点 1。他总共要送 n-1 样东西，其目的地分别是节点 2 到节点 n。由于这个城市的交通比较繁忙，
因此所有的道路都是单行的，共有 mm 条道路。这个邮递员每次只能带一样东西，并且运送每件物品过后必须返回邮局。
求送完这 n-1n?1 样东西并且最终回到邮局最少需要的时间。
*/
//分析：
//很明显这道题是单源最短路问题，但是这道题要求往返最短路径，且每次只能携带一个信件，所以需要跑正反两遍最短路
//因为是有向图，所以要想反过来跑还需反向建边，反向图中源到顶点的最短路径即原图中顶点到源的最短路径
#include<iostream>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;
typedef pair<int, int> PII;//这个应该放在using namespace std;后面
const int M =200010,N = 1003;
int e[M],nxt[M],head[M],weight[M],dp[N];
int idx;
int e2[M],nxt2[M],head2[M],weight2[M],dp2[N];
int idx2;
bool book1[M],book2[M];
int n,m;
void add1(int x,int y,int val)
{
    e[idx]=y;
    nxt[idx] = head[x];
    weight[idx] = val;
    head[x] = idx++;
}
void add2(int x,int y,int val)
{
    e2[idx2]=y;
    nxt2[idx2] = head2[x];
    weight2[idx2] = val;
    head2[x] = idx2++;
}
void dijkstra1() {
	memset(dp, 0x3f, sizeof dp);
	dp[1] = 0;
	
	priority_queue<PII, vector<PII>, greater<PII> > q;//使用堆优化
	q.push({ 0,1 });

	while (q.size()) {
		auto t = q.top();//每次直接弹出的就是不在集合S中的最短节点;
		
		q.pop();
		int now = t.second, distance = t.first;

		if (book1[now])continue;
		book1[now] = true;

		for (int i = head[now]; i != -1; i = nxt[i]) {//更新不在集合S中的点的距离
			int j = e[i];
			if (dp[j] > distance + weight[i]) {
				dp[j] = distance + weight[i];//d[j]  --- 第一个节点到第j个节点的最短距离;
				q.push({ dp[j],j });
			}
		}
	}

}
void dijkstra2() {
	memset(dp2, 0x3f, sizeof dp2);
	dp2[1] = 0;
	
	priority_queue<PII, vector<PII>, greater<PII>> q;//使用堆优化
	q.push({ 0,1 });

	while (q.size()) {
		auto t = q.top();//每次直接弹出的就是不在集合S中的最短节点;
		
		q.pop();
		int now = t.second, distance = t.first;

		if (book2[now])continue;
		book2[now] = true;

		for (int i = head2[now]; i != -1; i = nxt2[i]) {//更新不在集合S中的点的距离
			int j = e2[i];
			if (dp2[j] > distance + weight2[i]) {
				dp2[j] = distance + weight2[i];//d[j]  --- 第一个节点到第j个节点的最短距离;
				q.push({ dp2[j],j });
			}
		}
	}

}
int main()
{
    memset(head,0xff,sizeof head);
    memset(head2,0xff,sizeof head2);
    cin>> n >> m;
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        add1(x,y,z);
        add2(y,x,z);
    }
    int ans{};
    dijkstra1();
    dijkstra2();
    for(int i=1;i<=n;i++)
        ans += dp[i]+dp2[i];
    cout<<ans;
    return 0;
}