//ѧϰrabin karp
#include"iostream"
#include"string"
#include"cmath"
using namespace std;
int get_index(string &source,string &target);
int main()
{   
    string source,target;
    cin>>source>>target;
    cout<<get_index(source,target) ;
    return 0;
}
int get_index(string &source,string &target)
{
    int sval=0,tval=0,mod=1000000;
    int m=source.size();
    int n=target.size();
    int i,h=1;
    for(i=0;i<n;i++)
        h=(h*31)%mod;
    for(i=0;i<n;i++)
    {   
        tval=(tval*31+target[i])%mod;
        sval=(sval*31+source[i])%mod;
    }
    for(i=0;i<=m-n;i++)
    {
        if(tval==sval){
            if(source.substr(i,m)==target)
                return i;
        }
        sval=((sval-source[i]*h)*31+source[i+m])%mod;
        if(sval<0)
            sval+=mod;
    }
    return -1;
}