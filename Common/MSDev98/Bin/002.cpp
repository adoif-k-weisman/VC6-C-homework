//最长公共子序列的长度;
#include"iostream"
#include"vector"
using namespace std;
int main()
{
    string s1,s2;
    cin>>s1；cin>>s2;
    int len1=s1.length();
    int len2=s2.length();
    vector<vector<int > >a(len1);
    for(int i=1;i<len1+1;i++)
    {
        for(int j=1;j<len2+1;j++)
        {
            if(s1[i]==s2[j])
                a[i][j]=a[i-1][j-1]+1;
            else if(a[i][j-1]>a[i-1][j-1])
                a[i][j]=a[i][j-1];
            else
                a[i][i]=a[i-1][j];
        }
    }
    cout<<"the max len is "<<a[len1][len2]<<endl;
    return 0;
}