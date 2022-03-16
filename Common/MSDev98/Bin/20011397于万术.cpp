#include<iostream>
#include<cstring>
using namespace std;
/*
1.为可变长数组类(CArray)添加如下两个成员函数,判断两个CArray类的对象是否相等。只有当两



个数组的长度相等，并且对应的每个数组元素都相等时，两个CArray类的对象才相等。

 bool operator ==(const CArray &);//相等返回true

 bool operator !=(const CArray &);//不相等返回true

2.重载流插入运算符<<，可以直接输出CArray类的对象。(输出每个数组元素)

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
	bool operator ==(const CArray &p);//相等返回true
	bool operator !=(const CArray &p);//不相等返回true
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
bool CArray::operator ==(const CArray &p)//相等返回true
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
bool CArray::operator !=(const CArray &p)//不相等返回true
{	
/*	if(this->length()!=p.length())
		 return true;
	 for(int i=0;i<this->length();i++)
	 {
		 if(this->ptr[i]!=p.ptr[i])
			 return true;
	 }
	 return false;*/

	 //简便写法;
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
	//测试重载是否成功;
	if(a2==a3)
		cout<<"a2=a3"<<endl;
	if(a2!=a3)
		cout<<"a2!=a3"<<endl;
	cout<<a;
	return 0;
}

