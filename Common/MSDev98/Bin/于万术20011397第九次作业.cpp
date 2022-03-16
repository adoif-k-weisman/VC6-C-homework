#include"iostream"
#include"string"
using namespace std;
class employee{
private:

    string name;

    int id;

public:
    employee(string s1="\0",int ID=0);
    void set(string s1,int ID);   //设置数据成员

    double earnings(){return 0;}

    void print();//输出雇员的姓名和id

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
    cout<<"销售员的名字:"<<name<<endl;
    cout<<"销售员的ID："<<id<<endl;
}
//类commissionEmployee是指总收入是"销售额*提成比例"的雇员
class commissionEmployee:public employee{
private:
        double grossSales;//销售额

        double commissionRate; //提成比例
public:

        commissionEmployee(double gS=0,double cR=0);

        void set(string s1,int ID,double gS,double cR);   //设置数据成员

        double earnings();//返回总收入

        void print();//输出雇员的姓名,id和总收入
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
//类basePlusCommissionEmployee是指总收入是"基本工资+销售额*提成比例"的雇员;
class basePlusCommissionEmployee:public commissionEmployee{

private:

        double baseSalary;  //基本工资

public:

        basePlusCommissionEmployee(double bS=0){    baseSalary=bS;};

        void set(string s1,int ID ,double gS,double cR,double bS);   //设置数据成员

        double earnings();//返回总收入

        void print();//输出雇员的姓名,id和总收入

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
    cout<<"销售员的总收入是:"<<earnings()<<endl;
}
int main()
{
    cout<<"备注：我稍微加了一点汉字，使得该程序的输出内容更清楚,思路与老师一样"<<endl; 
    basePlusCommissionEmployee  ce;

	ce.set("wang", 123, 30000, 0.2, 500);

	ce.print();
    return 0;
}