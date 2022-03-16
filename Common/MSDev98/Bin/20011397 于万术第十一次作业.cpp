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
    virtual void print();//�������;
    Person(int age_=18,char sex_='M',string s1="joan ",string ID_="5201314");
    virtual ~Person(){cout<<"�����������������������"<<endl;};
};
void Person::print()
{
    cout<<"����:"<<name<<endl;
    cout<<"ְ�����:"<<ID<<endl;
    cout<<"�Ա�:"<<sex<<endl;
    cout<<"����:"<<age<<endl;
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
    void set_info(int age_,char sex_,string s1,string ID_);//����
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
    cout<<"нˮ:"<<getPay()<<endl;
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
    cout<<"нˮ:"<<getPay()<<endl;
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
    cout<<"нˮ:"<<getPay()<<endl;
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
    double commissionRate;//Ĭ��5%�����;
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
void CommWorker::set_commissionRate(double rate)//����������ɱ���;
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
	cout<<"m----����,w---Ů��"<<endl;
    master.print();
    Ikaros.print();
    luoluoluo.print();
    shiina.print();

    cout<<"���¾�Ϊ�Զ�̬��ʵ��,������ָ��"<<endl;
    Person *hero;
    hero=&Ikaros;
    hero->print();
    cout<<hero->getPay()<<endl;
    hero=&luoluoluo;
    cout<<hero->getPay()<<endl;
    hero->print();
    return 0;
}