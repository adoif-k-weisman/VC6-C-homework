#include<iostream>
#include<cmath>
using namespace std;
//���õĺ���������Ҫ����������;
class polynomial
{
    private:
        double coef[30];
    public:
        polynomial();
        void display();
        void add_to_ceof();
        void add_to_ceof(double coefs,int expo);
        void clear();
        void assign_coef();
        void derivation();
        double count_value();
        void add(const polynomial &b);
        void subtract(const polynomial &b);
        void multiply(const polynomial &b);
        polynomial(polynomial &p);
        void set_copy(const polynomial &p);
};
polynomial::polynomial()
{
    clear();
}
polynomial::polynomial(polynomial &p)//���ƹ��캯��;
{
    for(int i=0;i<30;i++)
    {
        coef[i]=p.coef[i];
    }
}
void polynomial::set_copy(const polynomial &p)
{
    for(int i=0;i<30;i++)
    {
        coef[i]=p.coef[i];
    }
}
void polynomial::display()//���Զ�������Ķ���ʽ��ָ���ߵ�����;
{   
    bool flag=false;
    for(int i=29;i>=0;--i)
    {
        if(coef[i]==0) continue;
        if(flag) cout<<" + ";
            flag=true;
        if(i>1)
        {
            cout<<coef[i]<<"x^"<<i;
        } 
        if(i==1&&coef[i]!=0) 
            cout<<coef[i]<<"x";
        if(i==0&&coef[i]!=0)
            cout<<coef[i];
    }
    //cout<<endl;
}
void polynomial::clear()
{
    for(int i=0;i<30;i++)
        coef[i]=0;
}
//ϵ��������С����ָ��ͳһ����;
void polynomial::assign_coef()
{   double coefs;
    int expo;//����ָ��;
    cout<<"����ָ��(0~29):";
    cin>>expo;
    cout<<"����ϵ��:";
    cin>>coefs;
    coef[expo]=coefs;
}
//�����Զ��ϲ�����ʽ�Ĺ���;
void polynomial::add_to_ceof()
{
    double coefs;
    int expo;
    cout<<"������ָ��(0~29):";
    cin>>expo;
    cout<<"������ϵ��:";
    cin>>coefs;
    coef[expo]+=coefs;
}
void polynomial::add_to_ceof(double coefs,int expo)
{   
    if(expo<0)
    {
        cout << "# The exponent needs to be a natural number!\n";
        cout << "# Failed to add polynomial";
        return ;
    }
    if(expo>29)
    {
        cout << "# The exponent is too big!\n";
        cout << "# Failed to add term: '";
        return;
    }
    coef[expo]+=coefs;
}
void polynomial::derivation()
{
    polynomial temp(*this);//������ʱ�������ƻ�����;
    for(int i=1;i<=29;i++)
    {   temp.coef[i-1]=temp.coef[i]*i;
    }
    cout<<"�󵼺�ı��ʽ:";
    temp.display();
    cout<<endl;
}
double polynomial::count_value()
{   double value=0,x;
    cout<<"���������x��ֵ:";
    cin>>x;
    for(int i=0;i<30;i++)
    {
        value+=coef[i]*pow(x,i);
    }
    return value;
}
void polynomial::add(const polynomial &b)
{
    for(int i=0;i<30;i++)
    {
        coef[i]+=b.coef[i];
    }
}
void polynomial::subtract(const polynomial &b)
{
    for(int i=0;i<30;i++)
    {
        coef[i]-=b.coef[i];
    }
}
void polynomial::multiply(const polynomial &b)
{
    polynomial a;
    for(int i=0;i<30;i++)
    {   if(coef[i]==0) continue;
        for(int j=0;j<30;j++)
        {   
            if(b.coef[j]==0) continue;
            if(i+j>29) 
            {   cout<<"����ʽָ�������볢����ָ����С�Ķ���ʽ";
                return ;
            }
            a.add_to_ceof(coef[i]*b.coef[j],i+j);
        }
    }
    a.display();
    cout<<endl;
}
//ȫ�ֱ���������������ָ��Ķ���ʽ;
polynomial *ptr=NULL;
int t=1;
void choose_coef(polynomial p[]);
void menu();
void quit();
int main()
{   
    char c;//����ѡ��;
    double tem;
    polynomial p[3];
    ptr=p;//Ĭ��ָ��a����ʽ;
    polynomial temp;//����ı����ʽa������;
    while(t)
    {
        menu();
        cin>>c;
        switch (c)
        {
        case 's': 
            choose_coef(p);
            break;
        case 'l': 
            ptr->assign_coef();
            ptr->display();
            cout<<endl;
            break;
        case 't': 
            ptr->add_to_ceof();
            ptr->display();
            cout<<endl;
            break;
        case 'c':
            ptr->clear();
            break;
        case 'v': 
            ptr->display();
            cout<<endl;
            break;
        case 'a': 
            p[0].display();
            cout<<endl;
            p[1].display();
            cout<<endl;
            p[2].display();
            cout<<endl;
            break;
        case 'd': 
            ptr->display();
            ptr->derivation();
            break;
        case 'e': 
            tem=ptr->count_value();
            cout<<"����ʽ";
            ptr->display();
            cout<<"��ֵ��:"<<tem;
            break;
        case '+':
            p[0].display();
            cout<<"+";
            p[1].display();
            cout<<"�Ľ����:"; 
            temp.set_copy(p[0]);
            temp.add(p[1]);
            temp.display();
            cout<<endl;
            break;
        case '-': 
            cout<<" ( ";
             p[0].display();
            cout<<" ) "<<"-"<<" ( ";
            p[1].display();
            cout<<" ) "<<"�Ľ����:"; 
            temp.set_copy(p[0]);
            temp.subtract(p[1]);
            temp.display();
            cout<<endl;
            break;
        case '*': 
            cout<<" ( ";
            p[0].display();
            cout<<" ) "<<" * "<<" ( ";
            p[1].display();
            cout<<" ) "<<"�Ľ����:"; 
            temp.set_copy(p[0]);
            temp.multiply(p[1]);
            break;
        case 'q': 
            quit();
            break;
        default:
            break;
        }
    }
    return 0;
}
void menu()
{
    cout<<"---------------The Commands---------------"<<endl;
    cout<<"s - ���õ�ǰ����ʽ(ѡ��Ҫ���õĶ���ʽ��"<<endl;
    cout<<"l - ����assign_coef����"<<endl;
    cout<<"t - ����add_to_coef����"<<endl;
    cout<<"c - ����clear����"<<endl;
    cout<<"v - ��ʾ��ǰ����ʽ"<<endl;
    cout<<"a - ��ʾ���ж���ʽ"<<endl;
    cout<<"d - �Ե�ǰ����ʽ�󵼲���ʾ"<<endl;
    cout<<"e - ���㵱ǰ����ʽ��ֵ"<<endl;
    cout<<"+ - ��ʾA+B�ĺ�"<<endl;
    cout<<"- - ��ʾA-B�Ĳ�"<<endl;
    cout<<"* - ��ʾA*B�Ļ�"<<endl;
    cout<<"q - quit"<<endl;
    cout<<"------------------------------------------"<<endl;
}
void quit()
{   
    t=0;
    cout<<"���ѳɹ��˳���";
}

void choose_coef(polynomial p[])
{   
    char s;
    cout<<"Enter the polynomial you want to work on(a,b,c):";
    cin>>s;
    switch (s)
    {
    case 'a': 
        ptr=&p[0];
        break;
    case 'b': 
        ptr=&p[1];
        break;
    case 'c': 
        ptr=&p[2];
        break;
    default:
        break;
    }
}