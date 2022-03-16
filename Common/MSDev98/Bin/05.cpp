
#include<iostream>
#include<cmath>
using namespace std;
class Point
{
private:
    double x,y;
public:
    Point():x(1.0),y(1.0){cout<<"Point Default constructor called"<<endl;};
    Point(double x_,double y_);
    Point(const Point& p);
    double getX();
    double getY();
    void dispaly();
    ~Point();
};
Point::Point(double x_,double y_):x(x_),y(y_){
    cout<<"Point constructor called"<<endl;
};
double Point::getX()
{
    return x;
}
double Point::getY()
{
    return y;
}
Point::Point(const Point& p)
{
    x=p.y;
    y=p.x;
    cout<<"Point copy constructor called"<<endl;
}
void Point::dispaly()
{
    cout<<"Point 的x,y坐标分别是"<<x<<","<<y<<endl;
}
Point::~Point()
{
    cout<<"Point desconstructor called"<<endl;
}
class Line
{
    private:
    Point p1,p2;
    int color;
    static int num;
    public:
    Line();
    Line(int color_,double x1,double y1,double x2,double y2);
    Line(const Line& p);
    double getLength();
    void print();
    ~Line();
};
int Line::num=0;
Line::Line()
{
    color=0;
  //  p1.Point();
   // p2.Point();
    num++;
    cout<<"Line default constructor called"<<endl;
}
Line::Line(int color_,double x1,double y1,double x2,double y2):p1(x1,y1),p2(x2,y2)
{
    color=color_;
    num++;
    cout<<"Line constructor called"<<endl;
}
Line::Line(const Line& p)
{
    color=p.color;
    p1=p.p1;
    p2=p.p2;
    num++;
}
double Line::getLength()
{
  //  double length=0;
    return sqrt(pow(p1.getY()-p2.getY(),2)+pow(p1.getX()-p2.getX(),2));
}
void Line::print()
{
    cout<<"线段的起点，终点的坐标分别是:"<<"("<<p1.getX()<<","<<p1.getY()<<")";
    cout<<",("<<p2.getX()<<","<<p2.getY()<<")"<<endl;
    cout<<"线段的颜色是"<<color<<endl;
    cout<<"线段的长度是"<<getLength()<<endl;
    cout<<"总的线段的个数:"<<num<<endl;
}
Line::~Line()
{
    num--;
    cout<<"Line desconsructor called"<<endl;
}
int main()
{
    Point p1,p2(2.3,4.1);
    p1.dispaly();
    p2.dispaly();

    Line l1,l2(1,2.0,4.0,6.0,8.0),l3(l2);
    l1.print();
    l2.print();
    l3.print();
    return 0;
}

