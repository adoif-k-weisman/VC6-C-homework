#include"iostream"
#include"cstring"
#include"stdio.h"
using namespace std;
class String{
    private:
    char *ptr;
    public:
    String(){ptr=new char[1]; ptr[0]='\0';};
    String(const char * s);//���캯�������ַ���s��ʼ��

	String(const String& s);//�������캯��

	void concat(const String  &s);//���ַ���s���ӵ���ǰ�ַ�����

	String substring(int begin, int len);//���ص�ǰ�ַ����д��±�begin��ʼ������Ϊlen�����ַ���	

	String& operator=(const String &s);//��ֵ�����	

	int length()const; //�����ַ������� 

	void print()const; //����ַ���

	~String();//��������

};
String::String(const char *s)
{   
    if(s==NULL)
    {   ptr=new char[1];
        ptr[0]='\0';
        return; 
    }
    else{
    ptr=new char[strlen(s)+1];
    memset(ptr,0,strlen(s)+1);
    if(ptr==NULL) return ;
    strcpy(ptr,s);
    }
}
String::String(const String& s)
{   
    if(s.ptr){
    ptr=new char[strlen(s.ptr)+1];
    strcpy(ptr,s.ptr);
    }
    else 
        ptr=NULL;
}
String String::substring(int begin,int len)
{
    char *str=new char[len+1];
    int j=0;
    for(int i=begin;i<begin+len;i++)
    {
        str[j]=ptr[i];
        j++;
    }
	str[j]='\0';
    return str;
}
void String::concat(const String& s)
{
    char *temp=new char[strlen(ptr)+1];
    int len,j=0;
    len=strlen(ptr)+strlen(s.ptr);
    strcpy(temp,ptr);
    if(ptr)
    {
        delete []ptr;
        ptr=NULL;
    }
    ptr=new char[strlen(temp)+strlen(s.ptr)+1];
    strcpy(ptr,temp);
    for(int i=strlen(ptr);i<len;i++)
    {
        ptr[i]=s.ptr[j];
        j++;
    }
	ptr[len]='\0';
    delete []temp;
}

String& String::operator=(const String &s)
{
    if(ptr==s.ptr)
        return *this;
    if(ptr)//ptr��Ϊ��;
    {    delete []ptr;
         //   ptr=NULL;
    };
    if(s.ptr)
    {
        ptr=new char[strlen(s.ptr)+1];
        strcpy(ptr,s.ptr);
    }
    else
        ptr=NULL;
    return *this;
}
int String::length()const
{
    int i=1;
    while(ptr[i]!='\0'){
        i++;
    }
    return i;
}
void String::print()const
{   
        cout<<ptr<<endl;
}
String::~String()
{
    if(ptr)
        delete []ptr; 
    ptr=NULL;
}
int main()
{

	String s1("hello");

	String s2(s1);

	String s3;

	s1.print();

	s2.print();

	s3.print();

	s1 = "good morning ";

	s2 = "beijing";

	(s3=s2)=s1;

	cout << s1.length() << endl;

	cout << s2.length() << endl;

	cout << s3.length() << endl;

	s1.print();

	s2.print();

	s3.print();

	s1.concat(s2);//good morning beijing

	s1.print();// good morning beijing

	s2.print();//beijing

	String s4;

	s4 = s2.substring(2,3);

	s4.print();//iji

	s4 = s2.substring(2,15);

	s4.print();//ijing
    return 0;
}