#include"iostream"
#include"string"
using namespace std;
class employee{
private:

    string name;

    int id;

public:
    employee(string s1="\0",int ID=0);
    void set(string s1,int ID);   //�������ݳ�Ա

    double earnings(){return 0;}

    void print();//�����Ա��������id

};
employee::employee(string s1,int ID)
{
    name=s1;
    ID=id;
}
void employee::set(string s1,int ID)
{   
    name.assign(s1);
    id=ID;
}
void employee::print()
{
    cout<<"����Ա������:"<<name<<endl;
    cout<<"����Ա��ID��"<<id<<endl;
}
//��commissionEmployee��ָ��������"���۶�*��ɱ���"�Ĺ�Ա
class commissionEmployee:public employee{
private:
        double grossSales;//���۶�

        double commissionRate; //��ɱ���
public:

        commissionEmployee(double gS=0,double cR=0);

        void set(string s1,int ID,double gS,double cR);   //�������ݳ�Ա

        double earnings();//����������

        void print();//�����Ա������,id��������
};
commissionEmployee::commissionEmployee(double gS,double cR)
{   

    grossSales=gS;
    commissionRate=cR;
}
void commissionEmployee::set(string s1,int ID ,double gS,double cR)
{   
    employee::set(s1,ID);
    grossSales=gS;
    commissionRate=cR;
}
void commissionEmployee::print()
{
    employee::print();
}
double commissionEmployee::earnings()
{
    double Commission=grossSales*commissionRate;
    return Commission; 
}
//��basePlusCommissionEmployee��ָ��������"��������+���۶�*��ɱ���"�Ĺ�Ա;
class basePlusCommissionEmployee:public commissionEmployee{

private:

        double baseSalary;  //��������

public:

        basePlusCommissionEmployee(double bS=0){    baseSalary=bS;};

        void set(string s1,int ID ,double gS,double cR,double bS);   //�������ݳ�Ա

        double earnings();//����������

        void print();//�����Ա������,id��������

};
void basePlusCommissionEmployee::set(string s1,int ID ,double gS,double cR,double bS)
{
    commissionEmployee::set(s1,ID,gS,cR);
    baseSalary=bS;
}
double basePlusCommissionEmployee::earnings()
{
    double commission=commissionEmployee::earnings();
    return commission+baseSalary;
}  
void basePlusCommissionEmployee::print()
{
    commissionEmployee::print();
    cout<<"����Ա����������:"<<earnings()<<endl;
}
int main()
{
    cout<<"��ע������΢����һ�㺺�֣�ʹ�øó����������ݸ����,˼·����ʦһ��"<<endl; 
    basePlusCommissionEmployee  ce;

	ce.set("wang", 123, 30000, 0.2, 500);

	ce.print();
    return 0;
}