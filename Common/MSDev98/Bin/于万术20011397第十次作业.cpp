/*���ܰ�����1.ĳ��������һֻ��

          2.ĳ���˰��Լ����Ĺ�ת�ø��������

          3.����ȷ��ʾĳ����������Щ�����Լ�ĳ����������˭
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
void exit();//�˳�����;
void search_dog_ower();//������������;
void show_ower_dog();//��ʾ������������Щ��;
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
    cout<<"Ʒ����:"<<D_breed<<endl;
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
        cout<<"����: "<<ower_name<<"�Ѿ���ʮֻ���ˣ������������µĹ���!"<<endl;
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
vector<CMaster*>all_owers;
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
    cout<<" 9. ɾ��һֻ��. \n";
	cout<<" 10.���ҹ�������\n";
    cout<<" 11.��ʾ���������Ĺ�\n";
    cout<<" 0. �����˵�. \n";
    cout<<"-1. �˳�����. \n";
    cout<<"-----------------------------------------\n";
}
void view_all_ower_with_dog( bool show_dogs=true)
{   
    int O_len=all_owers.size();
    if(all_owers.size()==0)
    {
        cout<<"û�����˴���!����ȥ���������������!"<<endl;
        return;
    }
    cout<<" �������˵�����: "<<all_owers.size()<<endl;
    for(int i=0;i<O_len;i++)
    {   
        cout<<"��"<<i+1<<"λ����: "<<endl;
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
    cin.get();
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
	cin.get();
    CMaster *tmp_ower=new CMaster(m_name);
    all_owers.push_back(tmp_ower);
    cout<<"---------������µ����˺�---------:"<<endl;
    view_all_ower_with_dog(false);
}
void adoption__dog()
{	
	char input[32];
    int O_len=all_owers.size();
    if(O_len==0){
        cout<<"û�����˴��ڣ�����ȥ������˺����������."<<endl;
        return;
    }
    cout<<"˭Ը��������?"<<endl;
    view_all_ower_with_dog(false);
    cout<<"������Ҫ�����������˵����(��������0�������˵�)"<<endl;
    int num_M=-1;
    while(num_M<0||num_M>O_len){
		cin.getline(input, 30,'\n');//����;
        num_M = atoi(input);
        if(num_M==0){
            cout<<"�������˵�"<<endl;
            return ;
        }
        if(num_M<0||num_M>O_len){
            cout<<"�������˴����������ţ�����"<<endl;
            cout<<"������������ȷ���������:"<<endl;
        }
    }
    int Is_register=-1,A_dog=-1;//A_dog��Ҫ�����Ĺ������;
    int Is_exit;
	cout<<"��ѡ��Ҫ������������."<<endl;
    char input2[32];
    while(Is_register!=2&&Is_register!=1){
	cout<<"��ȷ��Ҫ�����Ĺ��Ƿ�Ǽ��ڲ᣿(����1�Ǽ�¼�ڲ�,����2��δ��¼�ڲ�,���������������˵�)"<<endl;
	cout<<"������:";
	cin.getline(input2, 30,'\n');//����;
    Is_register = atoi(input2);
    if(Is_register==1)//��С���Ѿ���¼�Ĺ��б���������;
    {
		int dog_num=0;//dog_num��¼�Ǽ��ڲ��û�����˵Ĺ�����;
        cout<<"ĿǰС���Ǽ��ڲ��û�����˵Ĺ�:"<<endl;
        for(int j=0;j<all_dogs.size();j++)
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
        cout<<"��ѡ��"<<all_owers[num_M-1]->get_ower_name()<<"Ҫ�����Ĺ�."<<endl;
        cout<<"������ֻ�������(��������0�������˵�):"<<endl;
        while(A_dog<0||A_dog>all_dogs.size()){
		cin.getline(input, 30,'\n');//����;
        A_dog = atoi(input);
            if(A_dog==0){
                cout<<"�������˵�"<<endl;
                return;
            }
            if(A_dog<0||A_dog>all_dogs.size()){//һ��Ҫ���if�����ǰ,��Ȼִ�к����if�����ܻ��������Խ��.
                cout<<"����Ĺ��������,����������:"<<endl;
				A_dog=-1;
				continue;
            }
			if(all_dogs[A_dog-1]->get_ower()!=NULL)
			{	cout<<"��ֻ����������,���ܱ�����"<<endl;
				A_dog=-1;
			}
        }
        bool Is_Adopt=all_owers[num_M-1]->adopt_dog(all_dogs[A_dog-1]);
        if(Is_Adopt){
            all_dogs[A_dog-1]->print_info();
            cout<<"���Ѿ���"<<all_owers[num_M-1]->get_ower_name()<<"�����ɹ�!"<<endl;
        }
        else{
            cout<<"�ǳ��ź�,����ʧ��."<<endl;
        }
        all_owers[num_M-1]->view_dogs();
		A_dog=-1;//ǧ�����,ע��ѭ������;
		cout<<"�Ƿ�Ҫ����������(����1ȷ��,����0�������˻����˵�)"<<endl;
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
        cout<<"���������ֻ������Ϣ:"<<endl;
        cout<<"����׼�����һֻ�µĹ�!"<<endl;
        string name_,breed_;
        cout<<"��������ֻ��������:";
        cin>>name_;
        cout<<"��������ֻ����Ʒ��:";
        cin>>breed_;
		cin.get();
        CDog *tmp_dog=new CDog(name_,breed_);
        all_dogs.push_back(tmp_dog);  
        bool Is_Adopt=all_owers[num_M-1]->adopt_dog(tmp_dog);
        if(Is_Adopt){
            tmp_dog->print_info();
            cout<<"���Ѿ���"<<all_owers[num_M-1]->get_ower_name()<<"�����ɹ�!"<<endl;
        }
        else{
            cout<<"�ǳ��ź�,����ʧ��."<<endl;
        }
        all_owers[num_M-1]->view_dogs();
		cout<<"�Ƿ�Ҫ����������(����1ȷ��,����0�������˻����˵�)"<<endl;
		cin.getline(input,30);
		Is_exit=atoi(input);
		if(Is_exit!=1)	return;
		else if(Is_exit==1) {
			Is_register=-1;
			continue;
		}
    }
    else{
        cout<<"��������,�����������˵�."<<endl;
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
        cout<<"û�й�����,�������˵�."<<endl;
        return ;
    }
    view_all_dogs();
    cout<<" ����������Ҫ�ı���Ϣ�Ĺ������(��������0,�������˵�):";
    while(num<0||num>D_len){
		cin.getline(input, 30,'\n');//����;
        num = atoi(input);
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
	cin.get();
    all_dogs[num-1]->set_info(dog_name,dog_breed);
    cout<<"�ı���Ϣ��Ĺ�:"<<endl;
    all_dogs[num-1]->print_info(false);
}
void edit_master()
{   
	char input[32];
	int O_len=all_owers.size();
    int num=-1;
    string ower_name;
    if(O_len==0){
        cout<<"û�����˴���!�������˵�."<<endl;
        return;
    }
	view_all_ower_with_dog(false);
    cout<<"����������Ҫ�ı���Ϣ�����˵����(��������0,�������˵�):";
    while(num<0||num>O_len){
		cin.getline(input, 30,'\n');//����;
        num = atoi(input);
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
    cout<<"ԭ����������: "<<all_owers[num-1]->get_ower_name()<<endl;
    cout<<"���������˵�������:";
    cin>>ower_name;
	cin.get();
    all_owers[num-1]->set_name(ower_name);
    cout<<"�ı���Ϣ�������:"<<endl;
    cout<<"���˵�������: "<<all_owers[num-1]->get_ower_name()<<endl;
}

void transfer_a_dog()
{   
	char input[32];
	int O_len=all_owers.size();
    if(O_len==0){
        cout<<"û�����˴���!�������˵�."<<endl;
        return;
    }
    cout<<"ѡ��һ�����˽��в���(��������0,�������˵�):"<<endl;
    view_all_ower_with_dog(false);
    int num=-1;
    while(num<0||num>O_len){
		cin.getline(input, 30,'\n');//����;
        num = atoi(input);
        if(num==0) 
        {
            cout<<"�������˵�"<<endl;
            return;
        }
		if(num<0||num>O_len)
        {
        cout<<"�������˴�����������,�����������ŵ�����;"<<endl;
        cout<<"����������:"<<endl;
		continue;
        }
        if(all_owers[num-1]->get_dogNum()==0){
            cout<<"������û�й���������ѡ������:"<<endl;
            num=-1;
        }
    }
    all_owers[num-1]->view_dogs();
    cout<<"����Ҫѡ����ֻ�������ƽ�?"<<endl;
    cout<<"������ù������(��������0�������˵�)"<<endl;
    int j=-1;
    while(j<0||j>all_owers[num-1]->get_dogNum()){
		cin.getline(input, 30,'\n');//����;
        j = atoi(input);
        if(j==0){ 
            cout<<"�������˵�"<<endl;
            return;
        }
        if(j<0||j>all_owers[num-1]->get_dogNum()){
        cout<<"��������!!!"<<endl;
        cout<<"����������:"<<endl;
        }
    }
    cout<<"����Ҫ����ֻ���ƽ���˭?"<<endl;
    cout<<"---"<<j<<".  ";
    all_owers[num-1]->get_dog(j-1)->print_info();
    int k=-1;
    CMaster *tmpM;
    cout<<"��������ֻ����Ҫ�ƽ����������(��������0�������˵�)��"<<endl;
    while(k<0||k>O_len||num==k){
		cin.getline(input, 30,'\n');//����;
        k = atoi(input);
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
        if(all_owers[k-1]->get_dogNum()==10){
            cout<<"�������Ѿ���ʮֻ���������ټ��������µĹ���"<<endl;
            continue;
        }
        tmpM=all_owers[k-1];
    }
    bool flag=all_owers[num-1]->tansfer_to_dog(all_owers[num-1]->get_dog(j-1),tmpM);
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
{   
	char input[32];
	int D_len=all_dogs.size();
    int num=-1;
    if(D_len==0){
        cout<<"û�й�����!�������˵�."<<endl;
        return;
    }
    view_all_dogs();
    cout<<" ����������Ҫɾ���Ĺ������(��������0,�������˵�):";
    while(num<0||num>D_len){

		cin.getline(input, 30,'\n');//����;
        num = atoi(input);

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
	CDog *pdog=all_dogs[num-1];
	bool flag;
    if(pdog->get_ower()!=NULL)
		 flag=pdog->get_ower()->remove_dog(pdog);
	if(flag==false)
	{	cout<<"ɾ��ʧ��";
		return ;
	}
	
    pdog->print_info();
    cout<<" �Ѿ���ɾ����!"<<endl;
    all_dogs.erase(all_dogs.begin()+num-1);//�ͷ��ڴ�ռ�;
    cout<<"ɾ���������е�ȫ����:"<<endl;
    view_all_dogs();
}

void show_ower_dog()
{   
    if(all_owers.size()==0)
    {
        cout<<"û�����˴���!�������˵�."<<endl;
        return;
    }
    string M_name;
    cout<<"��������Ҫ���ҵ����˵�����:"<<endl;
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
    cout<<"�Բ��𣬲鲻�������������������!"<<endl;
    cout<<"��ȷ�ϸ������Ƿ�Ǽ��ڲ�,�Ժ�����."<<endl;
}

void search_dog_ower()
{   if(all_dogs.size()==0)
    {
        cout<<"û�й�����!�������˵�."<<endl;
        return;
    }
    string dog_name;
    cout<<"������Ҫ���ҵĹ�������:"<<endl;
    cin>>dog_name;
    cin.get();
    int i;
    for(i=0;i<all_dogs.size();i++)
    {
        if(dog_name==all_dogs[i]->get_own_name())
        {   cout<<"��ѯ������ֻ���������Ϣ:"<<endl;
			all_dogs[i]->print_info(true);
			//cout<<"��ֻ����������:"<<all_dogs[i]->get_ower()->get_ower_name()<<endl;
            return;
        }
    }
    cout<<"�Բ��𣬲鲻����ֻ��������."<<endl;
    cout<<"��ȷ����ֻ���Ƿ��¼�ڲ�,�Ժ�����"<<endl;
}
void exit()
{
    int flag=0;
    cout<<"��ȷ���Ƿ���Ҫ�˳��ó���(��1ȷ�ϣ���0ȡ��):";
    cin>>flag;
	cin.get();
    if(flag==0)
    {
        cout<<"�˳�ȡ��"<<endl;
    }
    else{
        t=0;
        cout<<"�ɹ��˳�����лʹ��"<<endl;
    }
}
//��ע:������ʹ�õ�cin.getline()��cin.get()������Ϊ��ֹ��������;
//�������������,һ�������û�ر�˵��,���ݳ����Ƿ������˵�;
//����vector��������size()����ʱ����ͬ���������ܶ��䷵��ֵsize_type���ͽ��бȽ�ʱ�в�ͬҪ��(��ÿ�ֱ��������Ż�,��Ȼ�Ⲣ��Ӱ���������),����:vscode,������Ĭ��vc6++;
int main()
{   
	char input[32];
    int choice;
	help_menu();
    while(t){
        cout<<"����������Ҫѡ��Ĺ������(����:��0�ǰ����˵�):";
		cin.getline(input, 30,'\n');//����;
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

//���Թ���,���ڲ������ʵ��;
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
    //��������
    owner1.adopt_dog(&dog1);
    owner1.adopt_dog(&dog3);
    owner1.adopt_dog(&dog2);
    
     owner1.view_dogs(); owner2.view_dogs(); owner3.view_dogs();
    //ת��Ȯֻ����
    owner1.tansfer_to_dog(&dog2,&owner2);
    //չʾ��λ���˵�Ȯֻӵ�����
    owner1.view_dogs(); owner2.view_dogs(); owner3.view_dogs();
    
    return 0;
}
*/
//��Ĺ���û������;