#include<iostream>
#include<string>
using namespace std;
const int N = 100100;
int nxt[N];
int main()
{   
    string s1;
    cin>>s1;

    //��ʼ��next[]����
    //s1 = ' '+s1;
	int i,j;
    for( i=1,j=0;i<s1.size();i++){
        while(j && s1[i]!=s1[j]) j = nxt[j-1];
        if(s1[i] == s1[j]) j++;
        nxt[i] = j;
    }
    //nxt[] ��ȷ
    for( i =0;i<s1.size();i++)
        cout<<nxt[i];
    for( i=1;i<=s1.size();i++){
        if( i%(i-nxt[i])==0 && nxt[i]!=0 )//nxt[i]����Ϊ0
        {   cout<<"sb"<<endl; 
            cout<<i<<i/(i-nxt[i])<<endl;
                cout<<i<<endl;
        }
    }
    return 0;
}