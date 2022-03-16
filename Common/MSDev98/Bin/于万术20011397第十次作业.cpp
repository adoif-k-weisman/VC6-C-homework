/*功能包括：1.某主人认养一只狗

          2.某主人把自己养的狗转让给别的主人

          3.能正确显示某主人养了哪些狗，以及某狗的主人是谁
*/
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
void help_menu();
void view_all_ower_with_dog( );
void view_all_dogs();
void add_a_dog();
void add_ower();
void adoption__dog();
void edit_dog();
void edit_master();
void transfer_a_dog();
void remove_dog();
void exit();//退出程序;
void search_dog_ower();//搜索狗的主人;
void show_ower_dog();//显示主人领养了那些狗;
class CMaster;
class CDog
{
    private:
    CMaster *p_Master;
    string D_name;
    string D_breed;
    public:
    CDog(string name,string breed="unknown",CMaster *p=NULL);
    void set_info(string name,string breed);
    void print_info(bool if_print_ower=false);//默认不打印主人情况;
    bool change_master(CMaster *master);
    void set_ower(CMaster *pm){p_Master=pm; };
    string get_own_name(){return D_name;};
    CMaster *get_ower(){return p_Master;};
};
class CMaster{
    private:
    int dognums;
    CDog *dogs[10];
    string ower_name;
    public:
    CMaster(string str);
    bool remove_dog(CDog *dog);//弃养一只狗;
    bool adopt_dog(CDog *dog);//领养一只狗;
    void correct_dog_info(CDog *dog);//更改这只狗的身份信息;
    bool tansfer_to_dog(CDog *dog,CMaster *pm);//把一只狗移交给另一个主人;成功返回true,否则返回false；
    void set_name(string name_){ower_name=name_;};
    void view_dogs();//浏览所有的狗;
    string get_ower_name(){return ower_name;};//为了方便从CDog类中输出主人的名字;
    int get_dogNum(){return dognums;};
    CDog* get_dog(int index){return dogs[index];};//为了方便从主人类中对每只狗进行操作;
};
CDog::CDog(string name,string breed,CMaster *pm)
{
    this->D_name=name;
    this->D_breed=breed;
    this->p_Master=NULL;
    if(pm!=NULL)
    {
        bool IsAdopt=pm->adopt_dog(this);
        if(IsAdopt)
        {
            print_info(true);
            cout<<"dog: "<<D_name<<" 被成功领养"<<endl;
        }
        else 
        {
            cout<<"初始化领养失败"<<endl;
        }
    }
    else
    {
        cout<<"dog:"<<D_name<<"未被初始化领养"<<endl;
    }
}
void CDog::set_info(string name,string breed)
{
    D_name=name;
    D_breed=breed;
}
bool CDog::change_master(CMaster *master)
{
    if(master==p_Master){
        cout<<"不能改变主人关系给同一个人!"<<endl;
    }
    if(master==NULL)//转让的主人是null，相当于弃养;
    {
        if(p_Master){
            p_Master->remove_dog(this);//解除关系;
        }
        p_Master=NULL;
        return true;
    }
    else{
        bool flag;
        if(p_Master){
          flag=p_Master->tansfer_to_dog(this,master);
        }
        else{//原来没有主人;
            flag=master->adopt_dog(this);
        }
        return flag;
    }
}
void CDog::print_info(bool if_print_ower)
{
    cout<<"这只狗的名字是:"<<D_name<<endl;
    cout<<"品种是:"<<D_breed<<endl;
    if(if_print_ower){
    if(p_Master!=NULL){
        cout<<"这只狗的主人是"<<p_Master->get_ower_name()<<endl;
    }
    else{
        cout<<"这只狗尚未被领养!"<<endl;
    }
    }
}
CMaster::CMaster(string str)
{
    ower_name=str;
    dognums=0;
    memset(dogs,0,sizeof(dogs));
}
bool CMaster::adopt_dog(CDog *dog)
{
    if(dog->get_ower()!=NULL)
    {
        cout<<"Dog："<<endl;
        dog->print_info(true);
        cout<<"这条狗已经属于 "<<dog->get_ower()->ower_name<<endl;
        cout<<"它不能被领养!!!"<<endl;
        return false;
    }
    else if(dognums>10)
    {
        cout<<"主人: "<<ower_name<<"已经有十只狗了，不能在领养新的狗了!"<<endl;
        return false;
    }
    else
    {
        dogs[dognums++]=dog;
        dog->set_ower(this);
        return true;
    }
}
bool CMaster::tansfer_to_dog(CDog *dog,CMaster *pm)
{
    if(pm==NULL)
    {
        this->remove_dog(dog);
        cout<<"狗已经从原来的主人"<<ower_name<<"移除了."<<endl;
        cout<<"狗现在没有主人!"<<endl;
        return true;
    }
    else if(pm==this)
    {
        cout<<"不能转让给他原来的主人"<<endl;
        return false;
    }
    else if(pm->dognums==10)
    {
        cout<<"目标主人已经有十只狗了."<<endl;
        cout<<"不能再接受新的狗!"<<endl;
        return false;
    }
    else 
    {
        remove_dog(dog);
        pm->adopt_dog(dog);
        cout<<dog->get_own_name()<<" 已经被移交从 "<<this->get_ower_name()<<" 到 "<<pm->get_ower_name()<<endl;
        return true;
    }
}
bool CMaster::remove_dog(CDog *dog)
{
    for(int i=0;i<dognums;i++)
    {
        if(dogs[i]==dog)//比较地址;
        {   
            int j=i;
            for(;j<dognums-1;j++){
                dogs[j]=dogs[j+1];
            }
            dog->set_ower(NULL);
            dognums--;
            return true;
        }
    }
    return false;
}
void CMaster::view_dogs()
{
    cout<<ower_name;
    if(dognums==1)   cout<<"有一条狗."<<endl;
    else if(dognums>1) cout<<"有"<<dognums<<"条狗."<<endl;
    else cout<<"没有狗."<<endl;
    for(int i=0;i<dognums;i++)
    {
        cout<<" 第"<<i+1<<"只狗 :"<<endl;
        dogs[i]->print_info(false);
    }
}
//该程序不仅要功能完善，还要考虑交互式设计;
//以此假定运行程序的人是管理员;
int t=1;
vector<CDog*>all_dogs;
vector<CMaster*>all_owers;
void help_menu()
{
    cout<<"-----------------------------------------\n";
    cout<<" 1. 浏览所有的主人和他们的狗\n";
    cout<<" 2. 浏览所有的狗 \n";
    cout<<" 3. 添加一只狗\n";
    cout<<" 4. 添加一个主人\n";
    cout<<" 5. 移交一只狗. \n";
    cout<<" 6. 领养一只狗. \n";
    cout<<" 7. 编辑一只狗. \n";
    cout<<" 8. 编辑主人信息. \n";
    cout<<" 9. 删除一只狗. \n";
	cout<<" 10.查找狗的主人\n";
    cout<<" 11.显示主人领养的狗\n";
    cout<<" 0. 帮助菜单. \n";
    cout<<"-1. 退出程序. \n";
    cout<<"-----------------------------------------\n";
}
void view_all_ower_with_dog( bool show_dogs=true)
{   
    int O_len=all_owers.size();
    if(all_owers.size()==0)
    {
        cout<<"没有主人存在!请先去添加主人再来重试!"<<endl;
        return;
    }
    cout<<" 所有主人的数量: "<<all_owers.size()<<endl;
    for(int i=0;i<O_len;i++)
    {   
        cout<<"第"<<i+1<<"位主人: "<<endl;
        if(show_dogs){
        all_owers[i]->view_dogs();
        cout<<endl;
        }
        else{
            cout<<all_owers[i]->get_ower_name()<<endl;
            cout<<endl;
        }
    }
}
void view_all_dogs()
{   
    int D_len=all_dogs.size();
    if(all_dogs.size()==0){
        cout<<"没有狗存在!请先去添加狗!"<<endl;
        return;
    }
    cout<<"所有狗的数量: "<<all_dogs.size()<<endl;
    for(int i=0;i<D_len;i++)
    {
        cout<<"第"<<i+1<<"只狗:"<<endl;
        all_dogs[i]->print_info(true);
        cout<<endl;
    }
}
void add_a_dog()
{
    cout<<"你正准备添加一只新的狗!"<<endl;
    string name_,breed_;
    cout<<"请输入这只狗的姓名:";
    cin>>name_;
    cout<<"请输入这只狗的品种:";
    cin>>breed_;
    cin.get();
    CDog *tmp_dog=new CDog(name_,breed_);
    all_dogs.push_back(tmp_dog);
    cout<<"---------添加新的狗之后---------"<<endl;
    view_all_dogs();   
}
void add_ower()
{
    cout<<"你正准备添加一个新的主人."<<endl;
    string m_name;
    cout<<"请输入这个主人的姓名:";
    cin>>m_name;
	cin.get();
    CMaster *tmp_ower=new CMaster(m_name);
    all_owers.push_back(tmp_ower);
    cout<<"---------添加了新的主人后---------:"<<endl;
    view_all_ower_with_dog(false);
}
void adoption__dog()
{	
	char input[32];
    int O_len=all_owers.size();
    if(O_len==0){
        cout<<"没有主人存在！请先去添加主人后才能领养狗."<<endl;
        return;
    }
    cout<<"谁愿意收养狗?"<<endl;
    view_all_ower_with_dog(false);
    cout<<"请输入要收养狗的主人的序号(或者输入0返回主菜单)"<<endl;
    int num_M=-1;
    while(num_M<0||num_M>O_len){
		cin.getline(input, 30,'\n');//防误触;
        num_M = atoi(input);
        if(num_M==0){
            cout<<"返回主菜单"<<endl;
            return ;
        }
        if(num_M<0||num_M>O_len){
            cout<<"你输入了错误的主人序号！！！"<<endl;
            cout<<"请重新输入正确的主人序号:"<<endl;
        }
    }
    int Is_register=-1,A_dog=-1;//A_dog是要收养的狗的序号;
    int Is_exit;
	cout<<"已选择到要收养狗的主人."<<endl;
    char input2[32];
    while(Is_register!=2&&Is_register!=1){
	cout<<"请确认要收养的狗是否登记在册？(输入1是记录在册,输入2是未记录在册,输入其它返回主菜单)"<<endl;
	cout<<"请输入:";
	cin.getline(input2, 30,'\n');//防误触;
    Is_register = atoi(input2);
    if(Is_register==1)//在小区已经记录的狗列表里收养狗;
    {
		int dog_num=0;//dog_num记录登记在册的没有主人的狗数量;
        cout<<"目前小区登记在册的没有主人的狗:"<<endl;
        for(int j=0;j<all_dogs.size();j++)
        {
            if(all_dogs[j]->get_ower()==NULL){
                cout<<"第"<<j+1<<"只狗:"<<endl;
                all_dogs[j]->print_info();
                dog_num++;
            }
        }
        if(dog_num==0) {
            cout<<"现在记录在册的狗中没有可以被收养的狗,请先去添加狗!"<<endl;
            cout<<"即将返回主菜单."<<endl;
            return;
        }
        cout<<"请选择"<<all_owers[num_M-1]->get_ower_name()<<"要收养的狗."<<endl;
        cout<<"输入这只狗的序号(或者输入0返回主菜单):"<<endl;
        while(A_dog<0||A_dog>all_dogs.size()){
		cin.getline(input, 30,'\n');//防误触;
        A_dog = atoi(input);
            if(A_dog==0){
                cout<<"返回主菜单"<<endl;
                return;
            }
            if(A_dog<0||A_dog>all_dogs.size()){//一定要这个if语句在前,不然执行后面的if语句可能会出现数组越界.
                cout<<"输入的狗序号有误,请重新输入:"<<endl;
				A_dog=-1;
				continue;
            }
			if(all_dogs[A_dog-1]->get_ower()!=NULL)
			{	cout<<"这只狗已有主人,不能被收养"<<endl;
				A_dog=-1;
			}
        }
        bool Is_Adopt=all_owers[num_M-1]->adopt_dog(all_dogs[A_dog-1]);
        if(Is_Adopt){
            all_dogs[A_dog-1]->print_info();
            cout<<"它已经被"<<all_owers[num_M-1]->get_ower_name()<<"收养成功!"<<endl;
        }
        else{
            cout<<"非常遗憾,收养失败."<<endl;
        }
        all_owers[num_M-1]->view_dogs();
		A_dog=-1;//千辛万苦,注意循环条件;
		cout<<"是否还要继续收养狗(输入1确认,输入0或其它退回主菜单)"<<endl;
		cin.getline(input,30);
		Is_exit=atoi(input);
		if(Is_exit!=1)	return;
		else if(Is_exit==1)  {
			Is_register=-1;
			continue;
		}
    }
    else if(Is_register==2)
    {
        cout<<"请先添加这只狗的信息:"<<endl;
        cout<<"你正准备添加一只新的狗!"<<endl;
        string name_,breed_;
        cout<<"请输入这只狗的名字:";
        cin>>name_;
        cout<<"请输入这只狗的品种:";
        cin>>breed_;
		cin.get();
        CDog *tmp_dog=new CDog(name_,breed_);
        all_dogs.push_back(tmp_dog);  
        bool Is_Adopt=all_owers[num_M-1]->adopt_dog(tmp_dog);
        if(Is_Adopt){
            tmp_dog->print_info();
            cout<<"它已经被"<<all_owers[num_M-1]->get_ower_name()<<"收养成功!"<<endl;
        }
        else{
            cout<<"非常遗憾,收养失败."<<endl;
        }
        all_owers[num_M-1]->view_dogs();
		cout<<"是否还要继续收养狗(输入1确认,输入0或其它退回主菜单)"<<endl;
		cin.getline(input,30);
		Is_exit=atoi(input);
		if(Is_exit!=1)	return;
		else if(Is_exit==1) {
			Is_register=-1;
			continue;
		}
    }
    else{
        cout<<"输入有误,即将返回主菜单."<<endl;
		return ;
    }
    }
}
void edit_dog()
{   char input[32];
	int D_len=all_dogs.size();
    int num=-1;
    string dog_name,dog_breed;
    if(D_len==0)  {
        cout<<"没有狗存在,返回主菜单."<<endl;
        return ;
    }
    view_all_dogs();
    cout<<" 请输入你想要改变信息的狗的序号(或者输入0,返回主菜单):";
    while(num<0||num>D_len){
		cin.getline(input, 30,'\n');//防误触;
        num = atoi(input);
        if(num==0) 
        {
            cout<<"返回主菜单"<<endl;
            return;
        }
        if(num<0||num>D_len)
        {
        cout<<"你输入了错误的狗序号，不存在这个序号的狗;"<<endl;
        cout<<"请重新输入:"<<endl;
        }    
    }
    cout<<"已选择到要改变信息的狗。"<<endl;
    cout<<"这只狗原来的信息是:"<<endl;
    all_dogs[num-1]->print_info(false);//减1是因为数组下标从0开始;
    cout<<"请输入要改变的狗的新名字:";
    cin>>dog_name;
    cout<<"请输入要改变的狗的新品种:";
    cin>>dog_breed;
	cin.get();
    all_dogs[num-1]->set_info(dog_name,dog_breed);
    cout<<"改变信息后的狗:"<<endl;
    all_dogs[num-1]->print_info(false);
}
void edit_master()
{   
	char input[32];
	int O_len=all_owers.size();
    int num=-1;
    string ower_name;
    if(O_len==0){
        cout<<"没有主人存在!返回主菜单."<<endl;
        return;
    }
	view_all_ower_with_dog(false);
    cout<<"请输入你想要改变信息的主人的序号(或者输入0,返回主菜单):";
    while(num<0||num>O_len){
		cin.getline(input, 30,'\n');//防误触;
        num = atoi(input);
        if(num==0) 
        {
            cout<<"返回主菜单"<<endl;
            return;
        }
        if(num<0||num>O_len)
        {
        cout<<"你输入了错误的人序号，不存在这个序号的主人;"<<endl;
        cout<<"请重新输入:"<<endl;
        }
    }
    cout<<"已选择到要改变个人信息的主人"<<endl;
    cout<<"主人原来的信息:";
    cout<<"原来的名字是: "<<all_owers[num-1]->get_ower_name()<<endl;
    cout<<"请输入主人的新名字:";
    cin>>ower_name;
	cin.get();
    all_owers[num-1]->set_name(ower_name);
    cout<<"改变信息后的主人:"<<endl;
    cout<<"主人的名字是: "<<all_owers[num-1]->get_ower_name()<<endl;
}

void transfer_a_dog()
{   
	char input[32];
	int O_len=all_owers.size();
    if(O_len==0){
        cout<<"没有主人存在!返回主菜单."<<endl;
        return;
    }
    cout<<"选择一个主人进行操作(或者输入0,返回主菜单):"<<endl;
    view_all_ower_with_dog(false);
    int num=-1;
    while(num<0||num>O_len){
		cin.getline(input, 30,'\n');//防误触;
        num = atoi(input);
        if(num==0) 
        {
            cout<<"返回主菜单"<<endl;
            return;
        }
		if(num<0||num>O_len)
        {
        cout<<"你输入了错误的主人序号,不存在这个序号的主人;"<<endl;
        cout<<"请重新输入:"<<endl;
		continue;
        }
        if(all_owers[num-1]->get_dogNum()==0){
            cout<<"该主人没有狗，请重新选择主人:"<<endl;
            num=-1;
        }
    }
    all_owers[num-1]->view_dogs();
    cout<<"你想要选择哪只狗进行移交?"<<endl;
    cout<<"请输入该狗的序号(或者输入0返回主菜单)"<<endl;
    int j=-1;
    while(j<0||j>all_owers[num-1]->get_dogNum()){
		cin.getline(input, 30,'\n');//防误触;
        j = atoi(input);
        if(j==0){ 
            cout<<"返回主菜单"<<endl;
            return;
        }
        if(j<0||j>all_owers[num-1]->get_dogNum()){
        cout<<"错误输入!!!"<<endl;
        cout<<"请重新输入:"<<endl;
        }
    }
    cout<<"你想要将这只狗移交给谁?"<<endl;
    cout<<"---"<<j<<".  ";
    all_owers[num-1]->get_dog(j-1)->print_info();
    int k=-1;
    CMaster *tmpM;
    cout<<"请输入这只狗想要移交的主人序号(或者输入0返回主菜单)："<<endl;
    while(k<0||k>O_len||num==k){
		cin.getline(input, 30,'\n');//防误触;
        k = atoi(input);
        if(k==0){
            cout<<"返回主菜单"<<endl;
            return;
        }    
        if(k==num){
            cout<<"出错！不能将狗移交给同一个主人"<<endl;
            cout<<"请重新输入要移交给的主人的序号:"<<endl;
            continue;
        }
        if(k<0||k>O_len){
            cout<<"错误输入！"<<endl;
            cout<<"请重新输入:";
            continue;
        }
        if(all_owers[k-1]->get_dogNum()==10){
            cout<<"该主人已经有十只狗，不能再继续收养新的狗了"<<endl;
            continue;
        }
        tmpM=all_owers[k-1];
    }
    bool flag=all_owers[num-1]->tansfer_to_dog(all_owers[num-1]->get_dog(j-1),tmpM);
    if(flag&&tmpM!=NULL){
        cout<<"这只狗已经移交给"<<tmpM->get_ower_name()<<endl;
        cout<<endl;
        cout<<"现在,";
        tmpM->view_dogs();
    }
    else if(!flag){
        cout<<"移交这只狗失败!"<<endl;
    }
}

void remove_dog()
{   
	char input[32];
	int D_len=all_dogs.size();
    int num=-1;
    if(D_len==0){
        cout<<"没有狗存在!返回主菜单."<<endl;
        return;
    }
    view_all_dogs();
    cout<<" 请输入你想要删除的狗的序号(或者输入0,返回主菜单):";
    while(num<0||num>D_len){

		cin.getline(input, 30,'\n');//防误触;
        num = atoi(input);

        if(num==0) 
        {
            cout<<"返回主菜单"<<endl;
            return;
        }
        if(num<0||num>D_len)
        {
        cout<<"你输入了错误的狗序号，不存在这个序号的狗;"<<endl;
        cout<<"请重新输入:"<<endl;
        }
    }
	CDog *pdog=all_dogs[num-1];
	bool flag;
    if(pdog->get_ower()!=NULL)
		 flag=pdog->get_ower()->remove_dog(pdog);
	if(flag==false)
	{	cout<<"删除失败";
		return ;
	}
	
    pdog->print_info();
    cout<<" 已经被删除了!"<<endl;
    all_dogs.erase(all_dogs.begin()+num-1);//释放内存空间;
    cout<<"删除后现在有的全部狗:"<<endl;
    view_all_dogs();
}

void show_ower_dog()
{   
    if(all_owers.size()==0)
    {
        cout<<"没有主人存在!返回主菜单."<<endl;
        return;
    }
    string M_name;
    cout<<"请输入想要查找的主人的名字:"<<endl;
    cin>>M_name;
    cin.get();
    int i;
    for(i=0;i<all_owers.size();i++)
    {
        if(M_name==all_owers[i]->get_ower_name())
        {   all_owers[i]->view_dogs();
			return;
		}
    }
    cout<<"对不起，查不到该主人领养狗的情况!"<<endl;
    cout<<"请确认该主人是否登记在册,稍后再试."<<endl;
}

void search_dog_ower()
{   if(all_dogs.size()==0)
    {
        cout<<"没有狗存在!返回主菜单."<<endl;
        return;
    }
    string dog_name;
    cout<<"请输入要查找的狗的名字:"<<endl;
    cin>>dog_name;
    cin.get();
    int i;
    for(i=0;i<all_dogs.size();i++)
    {
        if(dog_name==all_dogs[i]->get_own_name())
        {   cout<<"查询到的这只狗的相关信息:"<<endl;
			all_dogs[i]->print_info(true);
			//cout<<"这只狗的主人是:"<<all_dogs[i]->get_ower()->get_ower_name()<<endl;
            return;
        }
    }
    cout<<"对不起，查不到这只狗的主人."<<endl;
    cout<<"请确认这只狗是否记录在册,稍后再试"<<endl;
}
void exit()
{
    int flag=0;
    cout<<"请确认是否想要退出该程序(按1确认，按0取消):";
    cin>>flag;
	cin.get();
    if(flag==0)
    {
        cout<<"退出取消"<<endl;
    }
    else{
        t=0;
        cout<<"成功退出，感谢使用"<<endl;
    }
}
//备注:程序中使用的cin.getline()和cin.get()函数皆为防止误触所设置;
//如果误触其它按键,一般情况下没特别说明,根据程序是返回主菜单;
//在用vector容器调用size()函数时，不同编译器可能对其返回值size_type类型进行比较时有不同要求(看每种编译器的优化,当然这并不影响程序运行),例如:vscode,本程序默认vc6++;
int main()
{   
	char input[32];
    int choice;
	help_menu();
    while(t){
        cout<<"请输入你想要选择的功能序号(提醒:按0是帮助菜单):";
		cin.getline(input, 30,'\n');//防误触;
        choice = atoi(input);
        switch (choice)
        {
        case 1:view_all_ower_with_dog(true);
            break;
        case 2:view_all_dogs();
            break;
        case 3:add_a_dog();
            break;
        case 4:add_ower();
            break;
        case 5:transfer_a_dog();
            break;
        case 6:adoption__dog();
            break;
        case 7:edit_dog();
            break;
        case 8:edit_master();
            break;
        case 9:remove_dog();
            break;
		case 10:search_dog_ower();
            break;
        case 11:show_ower_dog();
            break;
        case 0:help_menu();
            break;
        case -1:
            exit();
			break;
        default:help_menu();
            break;
        }
    }
	int i;
    for( i=0;i<all_dogs.size();i++)
        delete all_dogs[i];
    for( i=0;i<all_owers.size();i++)
        delete all_owers[i];
    return 0;
}

//测试功能,用于测试类的实现;
/*
int main()
{
    CMaster owner1("Leon"), owner2("Mike"), owner3("Chan");
    CDog dog1("Koko","Pomeranian",NULL);
    CDog dog2("Jack","Retriever");
    CDog dog3("Henry","Huskey",&owner3);

    dog1.print_info(true); cout<<endl;
    dog2.print_info(true); cout<<endl;
    dog3.print_info(true); cout<<endl;

       owner1.view_dogs(); owner2.view_dogs(); owner3.view_dogs();
    //领养测试
    owner1.adopt_dog(&dog1);
    owner1.adopt_dog(&dog3);
    owner1.adopt_dog(&dog2);
    
     owner1.view_dogs(); owner2.view_dogs(); owner3.view_dogs();
    //转移犬只测试
    owner1.tansfer_to_dog(&dog2,&owner2);
    //展示三位主人的犬只拥有情况
    owner1.view_dogs(); owner2.view_dogs(); owner3.view_dogs();
    
    return 0;
}
*/
//类的功能没有问题;