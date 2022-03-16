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
void exit();
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
    void print_info(bool if_print_ower=false);//Ĭ�ϲ���ӡ�������;
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
    bool remove_dog(CDog *dog);//����һֻ��;
    bool adopt_dog(CDog *dog);//����һֻ��;
    void correct_dog_info(CDog *dog);//������ֻ���������Ϣ;
    bool tansfer_to_dog(CDog *dog,CMaster *pm);//��һֻ���ƽ�����һ������;�ɹ�����true,���򷵻�false��
    void set_name(string name_){ower_name=name_;};
    void view_dogs();//������еĹ�;
    string get_ower_name(){return ower_name;};//Ϊ�˷����CDog����������˵�����;
    int get_dogNum(){return dognums;};
    CDog* get_dog(int index){return dogs[index];};//Ϊ�˷�����������ж�ÿֻ�����в���;
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
            cout<<"dog: "<<D_name<<" ���ɹ�����"<<endl;
        }
        else 
        {
            cout<<"��ʼ������ʧ��"<<endl;
        }
    }
    else
    {
        cout<<"dog:"<<D_name<<"δ����ʼ������"<<endl;
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
        cout<<"���ܸı����˹�ϵ��ͬһ����!"<<endl;
    }
    if(master==NULL)//ת�õ�������null���൱������;
    {
        if(p_Master){
            p_Master->remove_dog(this);//�����ϵ;
        }
        p_Master=NULL;
        return true;
    }
    else{
        bool flag;
        if(p_Master){
          flag=p_Master->tansfer_to_dog(this,master);
        }
        else{//ԭ��û������;
            flag=master->adopt_dog(this);
        }
        return flag;
    }
}
void CDog::print_info(bool if_print_ower)
{
    cout<<"��ֻ����������:"<<D_name<<endl;
    cout<<"������:"<<D_breed<<endl;
    if(if_print_ower){
    if(p_Master!=NULL){
        cout<<"��ֻ����������"<<p_Master->get_ower_name()<<endl;
    }
    else{
        cout<<"��ֻ����δ������!"<<endl;
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
        cout<<"Dog��"<<endl;
        dog->print_info(true);
        cout<<"�������Ѿ����� "<<dog->get_ower()->ower_name<<endl;
        cout<<"�����ܱ�����!!!"<<endl;
        return false;
    }
    else if(dognums>10)
    {
        cout<<"����: "<<ower_name<<"�Ѿ���ʮ�����ˣ������������µĹ���!"<<endl;
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
        cout<<"���Ѿ���ԭ��������"<<ower_name<<"�Ƴ���."<<endl;
        cout<<"������û������!"<<endl;
        return true;
    }
    else if(pm==this)
    {
        cout<<"����ת�ø���ԭ��������"<<endl;
        return false;
    }
    else if(pm->dognums==10)
    {
        cout<<"Ŀ�������Ѿ���ʮֻ����."<<endl;
        cout<<"�����ٽ����µĹ�!"<<endl;
        return false;
    }
    else 
    {
        remove_dog(dog);
        pm->adopt_dog(dog);
        cout<<dog->get_own_name()<<" �Ѿ����ƽ��� "<<this->get_ower_name()<<" �� "<<pm->get_ower_name()<<endl;
        return true;
    }
}
bool CMaster::remove_dog(CDog *dog)
{
    for(int i=0;i<dognums;i++)
    {
        if(dogs[i]==dog)//�Ƚϵ�ַ;
        {   
            int j=i;
            for(;j<dognums-1;j++){
                dogs[j]=dogs[j+1];
            }
            dog->set_ower(NULL);
            dognums--;
            return true;
        }
        return false;
    }
    return false;
}
void CMaster::view_dogs()
{
    cout<<ower_name;
    if(dognums==1)   cout<<"��һ����."<<endl;
    else if(dognums>1) cout<<"��"<<dognums<<"����."<<endl;
    else cout<<"û�й�."<<endl;

    for(int i=0;i<dognums;i++)
    {
        cout<<" ��"<<i+1<<"ֻ�� :"<<endl;
        dogs[i]->print_info(false);
    }
}
//�ó��򲻽�Ҫ�������ƣ���Ҫ���ǽ���ʽ���;
//�Դ˼ٶ����г�������ǹ���Ա;
int t=1;
vector<CDog*>all_dogs;
vector<CMaster*>all_masters;
void help_menu()
{
    cout<<"-----------------------------------------\n";
    cout<<" 1. ������е����˺����ǵĹ�\n";
    cout<<" 2. ������еĹ� \n";
    cout<<" 3. ���һֻ��\n";
    cout<<" 4. ���һ������\n";
    cout<<" 5. �ƽ�һֻ��. \n";
    cout<<" 6. ����һֻ��. \n";
    cout<<" 7. �༭һֻ��. \n";
    cout<<" 8. �༭������Ϣ. \n";
    cout<<" 9. ����һֻ��. \n";
    cout<<" 0. �����˵�. \n";
    cout<<"-1. �˳�����. \n";
    cout<<"-----------------------------------------\n";
}
void view_all_master_with_dog( bool show_dogs=true)
{   
    int O_len=all_masters.size();
    if(all_masters.size()==0)
    {
        cout<<"û�����˴���!����ȥ���������������!"<<endl;
        return;
    }
    cout<<" �������˵�����: "<<all_masters.size()<<endl;
    for(int i=0;i<O_len;i++)
    {   
        cout<<"��"<<i+1<<": "<<endl;
        if(show_dogs){
        all_masters[i]->view_dogs();
        cout<<endl;
        }
        else{
            cout<<all_masters[i]->get_ower_name()<<endl;
            cout<<endl;
        }
    }
}
void view_all_dogs()
{   
    int D_len=all_dogs.size();
    if(all_dogs.size()==0){
        cout<<"û�й�����!����ȥ��ӹ�!"<<endl;
        return;
    }
    cout<<"���й�������: "<<all_dogs.size()<<endl;
    for(int i=0;i<D_len;i++)
    {
        cout<<"��"<<i+1<<"ֻ��:"<<endl;
        all_dogs[i]->print_info(true);
        cout<<endl;
    }
}
void add_a_dog()
{
    cout<<"����׼�����һֻ�µĹ�!"<<endl;
    string name_,breed_;
    cout<<"��������ֻ��������:";
    cin>>name_;
    cout<<"��������ֻ����Ʒ��:";
    cin>>breed_;
    
    CDog *tmp_dog=new CDog(name_,breed_);
    all_dogs.push_back(tmp_dog);
    cout<<"---------����µĹ�֮��---------"<<endl;
    view_all_dogs();   
}
void add_ower()
{
    cout<<"����׼�����һ���µ�����."<<endl;
    string m_name;
    cout<<"������������˵�����:";
    cin>>m_name;
    CMaster *tmp_ower=new CMaster(m_name);
    all_masters.push_back(tmp_ower);
    cout<<"---------������µ����˺�---------:"<<endl;
    view_all_master_with_dog(false);
}
void adoption__dog()
{
    int O_len=all_masters.size();
    int D_len=all_dogs.size();
    if(O_len==0){
        cout<<"û�����˴��ڣ�����ȥ������˺����������."<<endl;
        return;
    }
    cout<<"˭Ը��������?"<<endl;
    view_all_master_with_dog(false);
    cout<<"������Ҫ�����������˵����(��������0�������˵�)"<<endl;
    int num_M=-1;
	char input[32];
    while(num_M<0||num_M>O_len){
        cin.getline(input,30);
		num_M=atoi(input);
        if(num_M==0){
            cout<<"�������˵�"<<endl;
            return ;
        }
        if(num_M<0||num_M>O_len){
            cout<<"�������˴����������ţ�����"<<endl;
            cout<<"������������ȷ���������:"<<endl;
        }
    }
    int Is_register=-1,dog_num=0,A_dog=-1;//dog_num��¼�Ǽ��ڲ��û�����˵Ĺ�����;A_dog��Ҫ�����Ĺ������;
    int Is_exit;
	cout<<"��ѡ��Ҫ������������."<<endl;
    
    while(Is_register!=0||Is_register!=1){
	cout<<"��ȷ��Ҫ�����Ĺ��Ƿ�Ǽ��ڲ᣿(����1�Ǽ�¼�ڲ�,����0��δ��¼�ڲ�)"<<endl;
	cout<<"������:";
    cin>>Is_register;
    if(Is_register==1)//��С���Ѿ���¼�Ĺ��б���������;
    {
        cout<<"ĿǰС���Ǽ��ڲ��û�����˵Ĺ�:"<<endl;
        for(int j=0;j<D_len;j++)
        {
            if(all_dogs[j]->get_ower()==NULL){
                cout<<"��"<<j+1<<"ֻ��:"<<endl;
                all_dogs[j]->print_info();
                dog_num++;
            }
        }
        if(dog_num==0) {
            cout<<"���ڼ�¼�ڲ�Ĺ���û�п��Ա������Ĺ�,����ȥ��ӹ�!"<<endl;
            cout<<"�����������˵�."<<endl;
            return;
        }
        cout<<"��ѡ��"<<all_masters[num_M-1]->get_ower_name()<<"Ҫ�����Ĺ�."<<endl;
        cout<<"������ֻ�������(��������0�������˵�):"<<endl;
        while(A_dog<0||A_dog>D_len){
            cin>>A_dog;
            if(A_dog==0){
                cout<<"�������˵�"<<endl;
                return;
            }
            if(A_dog<0||A_dog>D_len){
                cout<<"����Ĺ��������,����������:"<<endl;
            }
        }
        bool Is_Adopt=all_masters[num_M-1]->adopt_dog(all_dogs[A_dog-1]);
        if(Is_Adopt){
            all_dogs[A_dog-1]->print_info();
            cout<<"���Ѿ���"<<all_masters[num_M-1]->get_ower_name()<<"�����ɹ�!"<<endl;
        }
        else{
            cout<<"�ǳ��ź�,����ʧ��."<<endl;
        }
        all_masters[num_M-1]->view_dogs();
		cout<<"�Ƿ�Ҫ����������(����1ȷ��,����0�˻����˵�)"<<endl;
		cin>>Is_exit;
		if(Is_exit==0)	return;
		else  continue;
    }
    else if(Is_register==0)
    {
        cout<<"���������ֻ������Ϣ:"<<endl;
        cout<<"����׼�����һֻ�µĹ�!"<<endl;
        string name_,breed_;
        cout<<"��������ֻ��������:";
        cin>>name_;
        cout<<"��������ֻ����Ʒ��:";
        cin>>breed_;
        CDog *tmp_dog=new CDog(name_,breed_);
        all_dogs.push_back(tmp_dog);
    
        bool Is_Adopt=all_masters[num_M-1]->adopt_dog(tmp_dog);
        if(Is_Adopt){
            tmp_dog->print_info();
            cout<<"���Ѿ���"<<all_masters[num_M-1]->get_ower_name()<<"�����ɹ�!"<<endl;
        }
        else{
            cout<<"�ǳ��ź�,����ʧ��."<<endl;
        }
        all_masters[num_M-1]->view_dogs();
		cout<<"�Ƿ�Ҫ����������(����1ȷ��,����0�˻����˵�)"<<endl;
		cin>>Is_exit;
		if(Is_exit==0)	return;
		else  continue;
    }
    else{
        cout<<"��������,��������."<<endl;
    }
    }
}
void edit_dog()
{   int D_len=all_dogs.size();
    int num=-1;
    string dog_name,dog_breed;
    if(D_len==0)  {
        cout<<"û�й�����,�������˵�."<<endl;
        return ;
    }
    view_all_dogs();
    cout<<" ����������Ҫ�ı���Ϣ�Ĺ������(��������0,�������˵�):";
    while(num<0||num>D_len){
        cin>>num;
        if(num==0) 
        {
            cout<<"�������˵�"<<endl;
            return;
        }
        if(num<0||num>D_len)
        {
        cout<<"�������˴���Ĺ���ţ������������ŵĹ�;"<<endl;
        cout<<"����������:"<<endl;
        }
       
    }
    cout<<"��ѡ��Ҫ�ı���Ϣ�Ĺ���"<<endl;
    cout<<"��ֻ��ԭ������Ϣ��:"<<endl;
    all_dogs[num-1]->print_info(false);//��1����Ϊ�����±��0��ʼ;
    cout<<"������Ҫ�ı�Ĺ���������:";
    cin>>dog_name;
    cout<<"������Ҫ�ı�Ĺ�����Ʒ��:";
    cin>>dog_breed;
    all_dogs[num-1]->set_info(dog_name,dog_breed);
    cout<<"�ı���Ϣ��Ĺ�:"<<endl;
    all_dogs[num-1]->print_info(false);
}
void edit_master()
{   int O_len=all_masters.size();
    int num=-1;
    string ower_name;
    if(O_len==0){
        cout<<"û�����˴���!�������˵�."<<endl;
        return;
    }
	view_all_master_with_dog(false);
    cout<<"����������Ҫ�ı���Ϣ�����˵����(��������0,�������˵�):";
    while(num<0||num>O_len){
        cin>>num;
        if(num==0) 
        {
            cout<<"�������˵�"<<endl;
            return;
        }
        if(num<0||num>O_len)
        {
        cout<<"�������˴��������ţ������������ŵ�����;"<<endl;
        cout<<"����������:"<<endl;
        }
    }
    cout<<"��ѡ��Ҫ�ı������Ϣ������"<<endl;
    cout<<"����ԭ������Ϣ:";
    cout<<"ԭ����������: "<<all_masters[num-1]->get_ower_name()<<endl;
    cout<<"���������˵�������:";
    cin>>ower_name;
    all_masters[num-1]->set_name(ower_name);
    cout<<"�ı���Ϣ�������:"<<endl;
    cout<<"���˵�������: "<<all_masters[num-1]->get_ower_name()<<endl;
}

void transfer_a_dog()
{   int O_len=all_masters.size();
    if(O_len==0){
        cout<<"û�����˴���!�������˵�."<<endl;
        return;
    }
    cout<<"ѡ��һ�����˽��в���(��������0,�������˵�):"<<endl;
    view_all_master_with_dog(false);
    int num=-1;
    while(num<0||num>O_len){
        cin>>num;
        if(num==0) 
        {
            cout<<"�������˵�"<<endl;
            return;
        }
        if(all_masters[num-1]->get_dogNum()==0){
            cout<<"������û�й���������ѡ������"<<endl;
            num=-1;
            continue;
        }
        if(num<0||num>O_len)
        {
        cout<<"�������˴���������,�����������ŵ�����;"<<endl;
        cout<<"����������:"<<endl;
        }
    }
    all_masters[num-1]->view_dogs();
    cout<<"����Ҫѡ����ֻ�������ƽ�?"<<endl;
    cout<<"������ù������(��������0�������˵�)"<<endl;
    int j=-1;
    while(j<0||j>all_masters[num-1]->get_dogNum()){
        cin>>j;
        if(j==0){ 
            cout<<"�������˵�"<<endl;
            return;
        }
        if(j<0||j>all_masters[num-1]->get_dogNum()){
        cout<<"��������!!!"<<endl;
        cout<<"����������:"<<endl;
        }
    }
    cout<<"����Ҫ����ֻ���ƽ���˭?"<<endl;
    cout<<"---"<<j<<".  ";
    all_masters[num-1]->get_dog(j-1)->print_info();
    int k=-1;
    CMaster *tmpM;
    cout<<"��������ֻ����Ҫ�ƽ����������(��������0�������˵�)��"<<endl;
    while(k<0||k>O_len||num==k){
        cin>>k;
        if(k==0){
            cout<<"�������˵�"<<endl;
            return;
        }    
        if(k==num){
            cout<<"�������ܽ����ƽ���ͬһ������"<<endl;
            cout<<"����������Ҫ�ƽ��������˵����:"<<endl;
            continue;
        }
        if(k<0||k>O_len){
            cout<<"�������룡"<<endl;
            cout<<"����������:";
            continue;
        }
        if(all_masters[k-1]->get_dogNum()==10){
            cout<<"�������Ѿ���ʮֻ���������ټ��������µĹ���"<<endl;
            continue;
        }
        tmpM=all_masters[k-1];
    }
    bool flag=all_masters[num-1]->tansfer_to_dog(all_masters[num-1]->get_dog(j-1),tmpM);
    if(flag&&tmpM!=NULL){
        cout<<"��ֻ���Ѿ��ƽ���"<<tmpM->get_ower_name()<<endl;
        cout<<endl;
        cout<<"����,";
        tmpM->view_dogs();
    }
    else if(!flag){
        cout<<"�ƽ���ֻ��ʧ��!"<<endl;
    }
}

void remove_dog()
{   int D_len=all_dogs.size();
    int num=-1;
    if(D_len==0){
        cout<<"û�й�����!�������˵�."<<endl;
        return;
    }
    view_all_dogs();
    cout<<" ����������Ҫɾ���Ĺ������(��������0,�������˵�):";
    while(num<0||num>D_len){
        cin>>num;
        if(num==0) 
        {
            cout<<"�������˵�"<<endl;
            return;
        }
        if(num<0||num>D_len)
        {
        cout<<"�������˴���Ĺ���ţ������������ŵĹ�;"<<endl;
        cout<<"����������:"<<endl;
        }
    }
    if(all_dogs[num-1]->get_ower()!=NULL)
        all_dogs[num-1]->get_ower()->remove_dog(all_dogs[num-1]);
    all_dogs[num-1]->print_info();
    cout<<" �Ѿ���ɾ����!"<<endl;
    all_dogs.erase(all_dogs.begin()+num-1);//�ͷ��ڴ�ռ�;
    cout<<"ɾ���������е�ȫ����:"<<endl;
    view_all_dogs();
}

void exit()
{
    int flag=0;
    cout<<"��ȷ���Ƿ���Ҫ�˳��ó���(��1ȷ�ϣ���0ȡ��):";
    cin>>flag;
    if(flag==0)
    {
        cout<<"�˳�ȡ��"<<endl;
    }
    else{
        t=0;
        cout<<"�ɹ��˳�����лʹ��"<<endl;
    }
}

int main()
{   

    int choice;
    while(t){
        help_menu();
        cout<<"����������Ҫѡ��Ĺ������:";
        cin>>choice;
        switch (choice)
        {
        case 1:view_all_master_with_dog(true);
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
        case 0:help_menu();
            break;
        case -1:
            exit();    
        default:
            break;
        }
    }
	int i;
    for( i=0;i<all_dogs.size();i++)
        delete all_dogs[i];
    for( i=0;i<all_masters.size();i++)
        delete all_masters[i];
    return 0;
}
