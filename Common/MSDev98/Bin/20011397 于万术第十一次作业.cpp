#include<iostream>
#include<string>
using namespace std;
class Person{
    private:
    int age;
    char sex;
    string name;
    string ID;
    public:
    virtual double getPay()=0;
    virtual void print();//做个标记;
    Person(int age_=18,char sex_='M',string s1="joan ",string ID_="5201314");
    virtual ~Person(){cout<<"抽象类的析构函数被调用了"<<endl;};
};
void Person::print()
{
    cout<<"姓名:"<<name<<endl;
    cout<<"职工编号:"<<ID<<endl;
    cout<<"性别:"<<sex<<endl;
    cout<<"年龄:"<<age<<endl;
}
Person::Person(int age_,char sex_,string s1,string ID_)
{
    age=age_;
    sex=sex_;
    name=s1;
    ID=ID_;
}
class Boss:public Person
{
    private:
    double year_salary;
    public:
    virtual double getPay();
    virtual void print();
    Boss(int age_,char sex_,string s1,string ID_,double salary);
    void change_salary(double new_s);
    void set_info(int age_,char sex_,string s1,string ID_);//待定
    ~Boss(){}; 
};
void Boss::change_salary(double new_s)
{
    year_salary=new_s;
}
Boss::Boss(int age_,char sex_,string s1,string ID_,double salary):Person(age_,sex_,s1,ID_)
{
	year_salary=salary;
}
double Boss::getPay()
{
    return year_salary;
}
void Boss::print()
{
    cout<<"Boss:"<<endl;
    Person::print();
    cout<<"薪水:"<<getPay()<<endl;
}
void Boss::set_info(int age_,char sex_,string s1,string ID_)
{

}
class Employee:public Person{
private:
    double Base_salary;
    double bonus;
    double month_salary;
public:
    Employee(int age_,char sex_,string s1,string ID_,double Base,double bonus_);
    virtual double getPay();
    void print();
    ~Employee(){};
};
Employee::Employee(int age_,char sex_,string s1,string ID_,double Base,double bonus_):Person(age_,sex_,s1,ID_)
{
    Base_salary=Base;
    bonus=bonus_;
}
double Employee::getPay()
{
    month_salary=Base_salary+bonus;
    return month_salary;
}
void Employee::print()
{
    cout<<"Employee:"<<endl;
    Person::print();
    cout<<"薪水:"<<getPay()<<endl;
}
class HourlyWorker :public Person
{
    private:
    double work_hour;
    double hour_salary;
    double hour_price;
    public:
    virtual double getPay();
    HourlyWorker(int age_,char sex_,string s1,string ID_,double hour_price,double work_hour);
    virtual void print();
    ~HourlyWorker(){};
};
double HourlyWorker::getPay()
{
    hour_salary=hour_price*work_hour;
    return hour_salary;
}
void HourlyWorker::print()
{   
    cout<<"HourlyWorker:"<<endl;
    Person::print();
    cout<<"薪水:"<<getPay()<<endl;
}
HourlyWorker::HourlyWorker(int age_,char sex_,string s1,string ID_,double hour_price,double work_hour):Person(age_,sex_,s1,ID_)
{
    this->work_hour=work_hour;
    this->hour_price=hour_price;
    
}
class  CommWorker:public Person
{
    private:
    double month_salary;
    double Base_salary;
    double commissionRate;//默认5%的提成;
    double profit;
    public:
    CommWorker(int age_,char sex_,string s1,string ID_,double Base,double profit_,double rate);
    virtual double getPay();
    void set_commissionRate(double rate);
    void print();
    ~CommWorker(){};
};
CommWorker::CommWorker(int age_,char sex_,string s1,string ID_,double Base,double profit_,double rate):Person( age_, sex_, s1, ID_)
{ 
    Base_salary=Base;
    profit=profit_;
	this->commissionRate=rate;
}
double CommWorker::getPay()
{
    month_salary=Base_salary+profit*commissionRate;
    return month_salary;
}
void CommWorker::set_commissionRate(double rate)//重新设置提成比例;
{
    commissionRate=rate;
}
void CommWorker::print()
{
    cout<<"CommWorker:"<<endl;
    Person::print();
    cout<<"salary:"<<getPay()<<endl;
}
int main()
{   
    Boss master(19,'m',"adoif","123456",150000);
    Employee Ikaros(18,'w',"ikaros","520360",10000,520);
    HourlyWorker luoluoluo(19,'m',"giegie","5211314",200,30);
    CommWorker shiina(17,'w',"Mashiro","1314520",9999,10000,0.05);
	cout<<"m----男性,w---女性"<<endl;
    master.print();
    Ikaros.print();
    luoluoluo.print();
    shiina.print();

    cout<<"以下均为对多态的实验,抽象类指针"<<endl;
    Person *hero;
    hero=&Ikaros;
    hero->print();
    cout<<hero->getPay()<<endl;
    hero=&luoluoluo;
    cout<<hero->getPay()<<endl;
    hero->print();
    return 0;
}