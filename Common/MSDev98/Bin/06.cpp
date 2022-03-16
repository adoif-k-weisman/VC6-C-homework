#include<iostream>
#include<cmath>
using namespace std;
//调用的函数还是主要放在类里面;
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
polynomial::polynomial(polynomial &p)//复制构造函数;
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
void polynomial::display()//会自动对输出的多项式按指数高低排序;
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
//系数可以有小数，指数统一整数;
void polynomial::assign_coef()
{   double coefs;
    int expo;//储存指数;
    cout<<"输入指数(0~29):";
    cin>>expo;
    cout<<"输入系数:";
    cin>>coefs;
    coef[expo]=coefs;
}
//具有自动合并多项式的功能;
void polynomial::add_to_ceof()
{
    double coefs;
    int expo;
    cout<<"请输入指数(0~29):";
    cin>>expo;
    cout<<"请输入系数:";
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
    polynomial temp(*this);//定义临时变量以破坏数据;
    for(int i=1;i<=29;i++)
    {   temp.coef[i-1]=temp.coef[i]*i;
    }
    cout<<"求导后的表达式:";
    temp.display();
    cout<<endl;
}
double polynomial::count_value()
{   double value=0,x;
    cout<<"请输入变量x的值:";
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
            {   cout<<"多项式指数过大，请尝试用指数更小的多项式";
                return ;
            }
            a.add_to_ceof(coef[i]*b.coef[j],i+j);
        }
    }
    a.display();
    cout<<endl;
}
//全局变量，用它来操作指向的多项式;
polynomial *ptr=NULL;
int t=1;
void choose_coef(polynomial p[]);
void menu();
void quit();
int main()
{   
    char c;//功能选项;
    double tem;
    polynomial p[3];
    ptr=p;//默认指向a多项式;
    polynomial temp;//避免改变多项式a的数据;
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
            cout<<"多项式";
            ptr->display();
            cout<<"的值是:"<<tem;
            break;
        case '+':
            p[0].display();
            cout<<"+";
            p[1].display();
            cout<<"的结果是:"; 
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
            cout<<" ) "<<"的结果是:"; 
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
            cout<<" ) "<<"的结果是:"; 
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
    cout<<"s - 设置当前多项式(选择要设置的多项式）"<<endl;
    cout<<"l - 调用assign_coef函数"<<endl;
    cout<<"t - 调用add_to_coef函数"<<endl;
    cout<<"c - 调用clear函数"<<endl;
    cout<<"v - 显示当前多项式"<<endl;
    cout<<"a - 显示所有多项式"<<endl;
    cout<<"d - 对当前多项式求导并显示"<<endl;
    cout<<"e - 计算当前多项式的值"<<endl;
    cout<<"+ - 显示A+B的和"<<endl;
    cout<<"- - 显示A-B的差"<<endl;
    cout<<"* - 显示A*B的积"<<endl;
    cout<<"q - quit"<<endl;
    cout<<"------------------------------------------"<<endl;
}
void quit()
{   
    t=0;
    cout<<"你已成功退出！";
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