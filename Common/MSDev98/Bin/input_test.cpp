/*
    char input[32];
    int i = -1;
    while(i < 0 || i > upper_limit)
    {
        cin.getline(input,30); //��ȡ��������
        i = atoi(input);       //���ַ����õ���������
        if (i == 0) { cout<<"Exit! \n"; return; }
        if (i < 0 || i > upper_limit) cout<<"Illegal input! Try again: ";
    }
*/
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	char input[32];
	int num;
	cin.getline(input,30);
	num=atoi(input);
	cout<<num<<endl;
	return 0;
}
