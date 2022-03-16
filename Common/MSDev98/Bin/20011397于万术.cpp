#include<iostream>
#include<cstring>
using namespace std;
/*
1.Ϊ�ɱ䳤������(CArray)�������������Ա����,�ж�����CArray��Ķ����Ƿ���ȡ�ֻ�е���



������ĳ�����ȣ����Ҷ�Ӧ��ÿ������Ԫ�ض����ʱ������CArray��Ķ������ȡ�

 bool operator ==(const CArray &);//��ȷ���true

 bool operator !=(const CArray &);//����ȷ���true

2.���������������<<������ֱ�����CArray��Ķ���(���ÿ������Ԫ��)

*/

class CArray
{
private:
	int size;
	int* ptr;
public:
	CArray(int s=0);
	CArray(CArray &a);
	~CArray();
	void push_back(int v);
	CArray & operator = (const CArray &a);
	int length() const {return size;}
	int& operator[](int i)
	{	return ptr[i];	}
	bool operator ==(const CArray &p);//��ȷ���true
	bool operator !=(const CArray &p);//����ȷ���true
	friend ostream& operator << (ostream & os, CArray &a)  
    {
        for (int i = 0; i < a.length(); i++) 
            os << a[i] << " ";
        os << endl;
        return os;
    }
};

CArray::CArray(int s):size(s)
{
	if(s==0)
		ptr=NULL;
	else
		ptr=new int[s];
}
CArray::CArray(CArray& a)
{
	if(!a.ptr){
		ptr=NULL;
		size=0;
		return;
	}
	ptr=new int[a.size];
	memcpy(ptr,a.ptr,sizeof(int)*a.size);
	size=a.size;
}
CArray::~CArray()
{
	if(ptr) delete []ptr;
}
CArray & CArray::operator = (const CArray & a)
{
	if(ptr==a.ptr)
		return *this;
	if(a.ptr==NULL){
		if(ptr)
			delete []ptr;
		ptr=NULL;
		size=0;
		return *this;
	}
	if(size<a.size){
		if(ptr)
			delete []ptr;
		ptr=new int[a.size];
	}
	memcpy(ptr,a.ptr,sizeof(int)*a.size);
	size=a.size;
	return *this;
}

void CArray::push_back(int v)
{
	if(ptr){
		int *tmptr=new int [size+1];
		memcpy(tmptr,ptr,sizeof(int)*size);
		delete []ptr;
		ptr=tmptr;
	}
	else
		ptr=new int[1];
	ptr[size++]=v;
}
/*
CArray:: ostream& operator << (ostream & os,const CArray &a) const
{
	for(int i=0;i<a.length();i++)
		os<<a[i]<<" ";
	return os;
}
*/
bool CArray::operator ==(const CArray &p)//��ȷ���true
 {
	 if(this->length()!=p.length())
		 return false;
	 for(int i=0;i<this->length();i++)
	 {
		 if(this->ptr[i]!=p.ptr[i])
			 return false;
	 }
	 return true;
 }
bool CArray::operator !=(const CArray &p)//����ȷ���true
{	
/*	if(this->length()!=p.length())
		 return true;
	 for(int i=0;i<this->length();i++)
	 {
		 if(this->ptr[i]!=p.ptr[i])
			 return true;
	 }
	 return false;*/

	 //���д��;
	 return !(*this==p);
}
int main()
{	
	int i;
	CArray a;
	for( i=0;i<5;++i)
		a.push_back(i);
	CArray a2,a3;
	a2=a;
	for( i=0;i<a.length();++i)
		cout<<a2[i]<<" ";
	a2=a3;
	for( i=0;i<a2.length();++i)
		cout<<a2[i]<<" ";
	cout<<endl;
	a[3]=100;
	CArray a4(a);
	for( i=0;i<a4.length();++i)
		cout<<a4[i]<<" ";
	cout<<endl;
	//���������Ƿ�ɹ�;
	if(a2==a3)
		cout<<"a2=a3"<<endl;
	if(a2!=a3)
		cout<<"a2!=a3"<<endl;
	cout<<a;
	return 0;
}

