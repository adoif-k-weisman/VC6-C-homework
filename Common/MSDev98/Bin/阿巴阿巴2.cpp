
/*����:��һ���ʵ�ԱҪ�Ͷ������ʾ��ڽڵ� 1�����ܹ�Ҫ�� n-1 ����������Ŀ�ĵطֱ��ǽڵ� 2 ���ڵ� n������������еĽ�ͨ�ȽϷ�æ��
������еĵ�·���ǵ��еģ����� mm ����·������ʵ�Աÿ��ֻ�ܴ�һ����������������ÿ����Ʒ������뷵���ʾ֡�
�������� n-1n?1 �������������ջص��ʾ�������Ҫ��ʱ�䡣
*/
//������
//������������ǵ�Դ���·���⣬���������Ҫ���������·������ÿ��ֻ��Я��һ���ż���������Ҫ�������������·
//��Ϊ������ͼ������Ҫ�뷴�����ܻ��跴�򽨱ߣ�����ͼ��Դ����������·����ԭͼ�ж��㵽Դ�����·��
#include<iostream>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;
typedef pair<int, int> PII;//���Ӧ�÷���using namespace std;����
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
	
	priority_queue<PII, vector<PII>, greater<PII> > q;//ʹ�ö��Ż�
	q.push({ 0,1 });

	while (q.size()) {
		auto t = q.top();//ÿ��ֱ�ӵ����ľ��ǲ��ڼ���S�е���̽ڵ�;
		
		q.pop();
		int now = t.second, distance = t.first;

		if (book1[now])continue;
		book1[now] = true;

		for (int i = head[now]; i != -1; i = nxt[i]) {//���²��ڼ���S�еĵ�ľ���
			int j = e[i];
			if (dp[j] > distance + weight[i]) {
				dp[j] = distance + weight[i];//d[j]  --- ��һ���ڵ㵽��j���ڵ����̾���;
				q.push({ dp[j],j });
			}
		}
	}

}
void dijkstra2() {
	memset(dp2, 0x3f, sizeof dp2);
	dp2[1] = 0;
	
	priority_queue<PII, vector<PII>, greater<PII>> q;//ʹ�ö��Ż�
	q.push({ 0,1 });

	while (q.size()) {
		auto t = q.top();//ÿ��ֱ�ӵ����ľ��ǲ��ڼ���S�е���̽ڵ�;
		
		q.pop();
		int now = t.second, distance = t.first;

		if (book2[now])continue;
		book2[now] = true;

		for (int i = head2[now]; i != -1; i = nxt2[i]) {//���²��ڼ���S�еĵ�ľ���
			int j = e2[i];
			if (dp2[j] > distance + weight2[i]) {
				dp2[j] = distance + weight2[i];//d[j]  --- ��һ���ڵ㵽��j���ڵ����̾���;
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