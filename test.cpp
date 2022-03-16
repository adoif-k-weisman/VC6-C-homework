/* C++程序的基本结构 */
#include <iostream.h>
void main()
{
	double r, area;				// 声明变量
	cout<<"输入圆的半径：";		// 显示提示信息
	cin>>r;				// 从键盘上输入变量r的值
	area = 3.14159 * r * r;			// 计算面积
	cout<<"圆的面积为："<<area<<"\n"; 	// 输出面积
}
