#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
class DogOwner; 
class CDog
{
private:
    char dog_name[32];    //��������
    char dog_breed[32];   //����Ʒ��
    DogOwner * ptr_owner;  //ָ�����˵�ָ��
public:
    CDog(const char* _name, const char* _breed, DogOwner * pm);
    void print_info(bool if_print_owner = false);
    void change_info(char* _name, char* _breed);
    
    
    void set_ptr_owner(DogOwner* pm){ptr_owner = pm;};
    DogOwner* get_ptr_owner(){return ptr_owner;};
    
    bool reassign_owner(DogOwner* pm); //������ѡ�����ˣ�
};

class DogOwner
{
private:
    char owner_name[32];
    CDog * dogs[10];
    int dogNum ;
public:
    DogOwner(const char * );
    void rename(char*);
    bool adopt_a_dog(CDog*);  //������ǰ���˺�һֻ���й��Ĺ�ϵ
    bool transfer_a_dog(CDog*, DogOwner* ); //ʵ�ֹ���ϵ���ƽ�
    bool remove_a_dog(CDog*);  //�����ǰ������һֻ���й��Ĺ�ϵ
    int get_dognum(){return dogNum;};
	CDog * get_dog(int index){return dogs[index];};
    void print_info();
    void view_dogs();
};
DogOwner::DogOwner(const char* str)
{
    strcpy(owner_name, str);
  
    memset(dogs, 0, sizeof(dogs));
    dogNum = 0;
}
CDog::CDog(const char* _name, const char* _breed = "Unknown", DogOwner* pm = NULL)
{
    strcpy(dog_name, _name);
    strcpy(dog_breed, _breed);
    ptr_owner = NULL;
    if (pm != NULL) {
        bool if_adoption_success = pm->adopt_a_dog(this);
        if (if_adoption_success) {
            print_info(true); //���������Ϣ������true��ʾͬʱ���������Ϣ
            cout<<endl;
            cout<<"Dog initial owner set successfully! \n";
            ptr_owner = pm;
        }
        else {
            cout<<"Dog initial owner set failed! Owner set to [no one].\n";
        }
    }
}
bool DogOwner::adopt_a_dog(CDog* pd)
{
    //����������ֻ��Ӧ����û�����˵�
    if (pd->get_ptr_owner() != NULL) {
        cout<<"Dog '";
        pd->print_info();
        cout<<"' already belongs to ";
        pd->get_ptr_owner()->print_info();
        cout<<".\n";
        return false;
    }
    //�Ѿ����˳�����10ֻ������������
    if (dogNum >= 10) {
        cout<<"The owner '"<<owner_name<<"' already has 10 dogs!\n";
        return false;
    }
    else {
        dogs[dogNum++] = pd;      //���˴�������ֻ��
        pd->set_ptr_owner(this);  //����������
        return true;
    }
}
bool DogOwner::transfer_a_dog(CDog* pd, DogOwner* pm)
{
    if (pm == NULL)  //���Ŀ������Ϊ�գ���ʾ�������ͷ�
    {
        remove_a_dog(pd); //����������˺͹�֮��Ĺ�ϵ

        cout<<"Dog has been removed from owner: "<<owner_name<<'\n';
        cout<<"Dog has no owner now! \n";
        return true;
    }
    if (pm == this) {  //����ת��ͬһ���˵����
        cout<<"Can not transfer the dog to its original owner. \n";
        return false;
    }
    if (pm->dogNum == 10) { //Ŀ�������Ѿ���10ֻ������ת��ʧ��
        cout<<"Destined owner already has 10 dogs! \n";
        return false;
    }
    else {
        remove_a_dog(pd);     //�Ƚ�������˺͹�֮��Ĺ�ϵ
        pm->adopt_a_dog(pd);  //pd����������״̬�������˿���������ֻ��
       
        return true;
    }
}
bool DogOwner::remove_a_dog(CDog* pd) 
{
    for (int i = 0; i < dogNum; i++) {
        if(dogs[i] == pd) { 
            // �����˵�dogs�������ҵ���������
            // �ȴ����˶˽����ϵ
            int j = i; 
            while(j < dogNum - 1 ) {
                dogs[j] = dogs[j+1];
                j++;
            } 
            dogNum--;
            // �ٴӹ��˽����ϵ
            pd->set_ptr_owner(NULL);
            return true;
        }
    }
    return false;
}
void DogOwner::view_dogs()
{
   
    cout<<owner_name<<" has ";
    if(dogNum > 1) cout<<dogNum<<" dogs: \n";
    else if (dogNum == 1) cout<<dogNum<<" dog: \n";
    else cout<<"no dog.\n";

    for (int i = 0; i < dogNum; i++) {
        cout<<"  "<<i+1<<") ";
        dogs[i]->print_info();
        cout<<endl;
    }
}
void DogOwner::print_info()
{
    cout<<owner_name;
}
void CDog::print_info(bool if_print_owner)
{
    printf("%s [%s]",dog_name, dog_breed); // ����������ֺ�Ʒ��
    if (if_print_owner) {
        cout<<", which belongs to ";
        // �������ʱ���ж�ptr_owner�Ƿ�Ϊ��;
        if (ptr_owner != NULL) ptr_owner->print_info();
        else cout<<"[no one]";
        cout<<".";
    }
}
void DogOwner::rename(char* _name)
{
    if (_name) strcpy(owner_name, _name);
}
void CDog::change_info(char* _name, char* _breed)
{
    if (_name) strcpy(dog_name, _name);
    if (_breed) strcpy(dog_breed, _breed);
}
bool CDog::reassign_owner(DogOwner* pm)
{
    if (pm == ptr_owner) { //����ת��ͬһ���˵����
        cout<<"Cannot reassign the dog to the same owner.\n";
        return false;
    }
    if (pm == NULL) // ����ת������NULL�����ڹ���������
    { 
        //���ptr_ownerΪ�գ�ptr_owner->remove_a_dog()�����
        if (ptr_owner) { //��������������ˣ��ǵô����˶��Ƴ�
            ptr_owner->remove_a_dog(this); //���˫���ϵ
        }
        ptr_owner = pm; 
        return true;
    }
    else //ת����һ������
    {
        bool flag;
        if (ptr_owner)     //ԭ�����ˣ����á�ת�á�����
            flag = ptr_owner->transfer_a_dog(this, pm);
        else               //ԭ��û�����ˣ����Բ��á�����������
            flag = pm->adopt_a_dog(this);
        return flag;
    }
}

vector<CDog*>all_dogs;
vector<DogOwner*>all_owners;
void view_all_owners(bool show_dogs = false)
{
    if (all_owners.size() == 0) {
        cout<<"# No owner exists. Go and add one. \n";
        return;
    }
    cout<<"# Total owners: "<<all_owners.size()<<endl;
    for (int i = 0; i < all_owners.size(); i++) {
        cout<<i+1<<". ";
        if (show_dogs) all_owners[i]->view_dogs();
        else {
            all_owners[i]->print_info();
            cout<<endl;
        } 
    }
}
void view_all_dogs()
{
    if(all_dogs.size() == 0) {
        cout<<"# No dog exists. Go and add one.\n";
        return;
    }
    cout<<"# Total dogs: "<<all_dogs.size()<<endl;
    for (int i = 0; i < all_dogs.size(); i++) {
        cout<<i+1<<". ";
        all_dogs[i]->print_info(1);
        cout<<endl;
    }
}
void add_a_dog()
{   
    int Is_continue=1;
    while(Is_continue){
    cout<<"# You're going to add a new dog: \n";
    char name[32];
    char breed[32];
    cout<<"* Dog name: ";
    cin.getline(name,30);
    cout<<"* Dog breed: ";
    cin.getline(breed,30);
    if(breed[0] == '\0' || breed[0] == ' ') strcpy(breed, "Unknown");
    CDog* tpd = new CDog(name,breed,NULL);
    all_dogs.push_back(tpd);
    cout<<"Whether to continue to add the dog?"<<endl;
    cout<<"input 1 to continue,or 0 to exit!"<<endl;
    cin>>Is_continue;
    cin.get();
    if(Is_continue==1)
        continue;
    else{
        cout<<"back to the main menu!"<<endl;
        Is_continue=-1;
        break;
    }
    }
    cout<<"After adding  new dog"<<endl;
    view_all_dogs();
}
void add_a_owner()
{   
    int Is_continue=1;
    while(Is_continue){
    cout<<"# You're going to add a new owner: \n";
    char name[32];
    cout<<"* Owner name: ";
    cin.getline(name,30);
    if(name[0] == '\0' || name[0] == ' ') strcpy(name, "_No_Name_");
    DogOwner* tpm = new DogOwner(name);
    all_owners.push_back(tpm);
    cout<<"Whether to continue to add the owner?"<<endl;
    cout<<"input 1 to continue,or 0 to exit!"<<endl;
    cin>>Is_continue;
    cin.get();
    if(Is_continue==1)
        continue;
    else{
        cout<<"back to the main menu!"<<endl;
        Is_continue=-1;
        break;
    }
    }
    cout<<"After adding  new owner:"<<endl;
    view_all_owners(false);
}
void edit_dog()
{
    //1.չʾ���й�
    if (all_dogs.size() == 0) {cout<<"# No dogs exists. Backed to the main menu. \n"; return;}
    view_all_dogs();
    //2. ��ȡ�û�����
    cout<<"# Choose a dog to edit, type 0 to exit: ";
    int i = -1;
    char input[32];
    while (i < 0 || i > all_dogs.size())
    {
        cin.getline(input, 30);
        i = atoi(input);
        if (i == 0) { cout<<"Backed to the main menu. \n"; return;}
        if (i < 0 || i > all_dogs.size()) {
            cout<<"Illegal input! Try Again! \n";
        }
    }
    //3. ��ȡ�µ���Ϣ�����ڸ���
    char name[32]={0}, *_name;
    char breed[32]={0}, *_breed;
    cout<<"# Updating the information: \n";
    cout<<"* Dog's new name: ";
    cin.getline(name,30);
    cout<<"* Dog's new breed: ";
    cin.getline(breed,30);
    _name = name;
    _breed = breed;
    if(name[0] == '\0' || name[0] == ' ')  _name = NULL;
    if(breed[0] == '\0' || breed[0] == ' ') _breed = NULL;
    all_dogs[i-1]->change_info(_name,_breed);
    //4. չʾ����Ϣ
    cout<<"# Current: ";
    all_dogs[i-1]->print_info();
    cout<<endl;
}
void edit_owner()
{
    //1. չʾ������������
    if (all_owners.size() == 0) {cout<<"# No owners exists. Backed to the main menu. \n"; return;}
    view_all_owners();
    //2. ��ȡ�û�����
    cout<<"# Choose an owner to edit, type 0 to exit: \n";
    int i = -1;
    char input[32];
    while (i < 0 || i > all_owners.size())
    {
        cin.getline(input, 30);
        i = atoi(input);
        if (i == 0) { cout<<"Backed to the main menu. \n"; return;}
        if (i < 0 || i > all_dogs.size()) {
            cout<<"Illegal input! Try Again! \n";
        }
    }
    //3. ��ȡ�µ���Ϣ���ڸ���
    char name[32]={0}, *_name;
    cout<<"# Updating the information: \n";
    cout<<"* Owner's new name: ";
    cin.getline(name,30);
    _name = name;
    if(name[0] == '\0' || name[0] == ' ')  _name = NULL;
    all_owners[i-1]->rename(_name);
    //4. ���º����ʾ
    cout<<"# Current: ";
    all_owners[i-1]->print_info();
    cout<<endl;
}
void dog_removal()
{
    //1. չʾ���й�
    if (all_dogs.size() == 0) {cout<<"No dogs exists. Backed to the main menu. \n"; return;}
    view_all_dogs();
    //2. ����û���ѡ��
    cout<<"* Choose a dog to remove, type 0 to exit: ";
    int i = -1;
    char input[32];
    while (i < 0 || i > all_dogs.size())
    {
        cin.getline(input, 30);
        i = atoi(input);
        if (i == 0) { cout<<"Backed to the main menu. \n"; return;}
        if (i < 0 || i > all_dogs.size()) {
            cout<<"Illegal input! Try Again! \n";
        }
    }
    //3. ɾ�����Ĳ���
    CDog* pdog = all_dogs[i-1];
    //����������ˣ�˫�������Ĺ�ϵ
    if (pdog->get_ptr_owner() != NULL) 
        pdog->get_ptr_owner()->remove_a_dog(pdog);
    //���û�����ˣ���û�й�ϵ���Խ��
    cout<<"# ";
    pdog->print_info();
    cout<<" has been removed. \n";
    delete pdog; //�ǵ��ͷſռ�
    all_dogs.erase(all_dogs.begin()+(i-1)); 
    //4. չʾ���ڵ����й�
    view_all_dogs();
}
void dog_adoption()
{
    if (all_owners.size() == 0) {cout<<"No owner available. Go and add one.\n"; return;}
    cout<<"# Who'd like to adopt a dog? (Type 0 to exit)\n";
    view_all_owners();
    char input[32];
    int i = -1,j;
    while(i < 0 || i > all_owners.size())
    {
        cin.getline(input,30);
        i = atoi(input);
        if(i == 0) { cout<<"Exit! \n"; return; }
        if (i < 0 || i > all_owners.size()) cout<<"Illegal input! Try again: ";
    }
    cout<<"Dogs available: \n";
    int k = 0;
    for ( j = 0; j < all_dogs.size(); j++) {
        if (all_dogs[j]->get_ptr_owner() != NULL) continue;
        cout<<j+1<<". ";
        all_dogs[j]->print_info(1);
        cout<<endl;
        k++;
    }
    if(k == 0) {cout<<"No dog available. Go and add one.\n"; return;}
    cout<<"Which dog would ";
    all_owners[i-1]->print_info();
    cout<<" like to adopt? ";
    cout<<"(Type 0 to exit)\n";
     j = -1;
    while(j < 0 || j > all_dogs.size())
    {
        cin.getline(input,30);
        j = atoi(input);
        if(j == 0) { cout<<"Exit! \n"; return; }
        if (all_dogs[j-1]->get_ptr_owner() != NULL || j < 0 || j > all_dogs.size()) {
            cout<<"Illegal input! Try again. \n";
            j = -1;
        }
    }
    bool flag = all_owners[i-1]->adopt_a_dog(all_dogs[j-1]);
    if(flag) cout<<"Adoption successfully!\n";
    else cout<<"Adoption failed.\n";
    all_owners[i-1]->view_dogs();
}
void dog_transfer()
{
    char input[32];
    cout<<"Would you like to operate on a certain owner or a certain dog?\n";
    cout<<"- 1. An owner;\n";
    cout<<"- 2. A dog; \n";
    cin.getline(input,30);
    if (input[0] == '1')
    {
        if(all_owners.size() == 0) {cout<<"No owners exists. Backed to the main menu. \n"; return;}
        cout<<"Choose an owner to operate on: ";
        cout<<"(Type 0 to exit)\n";
        view_all_owners(false);
        
        int i = -1;
        while(i < 0 || i > all_owners.size())
        {
            cin.getline(input,30);
            i = atoi(input);
            if(i == 0) { cout<<"Exit! \n"; return; }
            if (all_owners[i-1]->get_dognum() == 0) {cout<<"This owner has no dogs. Try another. \n"; i = -1; continue;}
            if (i < 0 || i > all_owners.size()) cout<<"Illegal input! Try again. \n";
        }
        all_owners[i-1]->view_dogs();
        
        cout<<"Which dog would you like to transfer? ";
        cout<<"(Type 0 to exit)\n";
        int j = -1;
        while(j < 0 || j > all_owners[i-1]->get_dognum())
        {
            cin.getline(input,30);
            j = atoi(input);
            if (j == 0) { cout<<"Exit! \n"; return; }
            if (j < 0 || j > all_owners[i-1]->get_dognum()) cout<<"Illegal input! Try again. \n";
        }
        cout<<"To whom are you going to transfer the dog? \n";
        cout<<" - "<<j<<". ";
        all_owners[i-1]->get_dog(j-1)->print_info();
        cout<<"(Type 'N' for [no owner]; Type -1 to exit) \n";
        int k = -1;
        DogOwner* tpm = NULL;
        while(k < 0 || k > all_owners.size()||i-1 == k-1)
        {
            cin.getline(input,30);
            k = atoi(input);
            if (input[0]=='N') {tpm = NULL; break;}
            if (k == 0) { cout<<"Exit! \n"; return; }
            if (i-1 == k-1) {
                cout<<"You can not transfer a dog to its current owner.\n";
                cout<<"Try again!\n";
                continue; 
            }
            if (k < 0 || k > all_owners.size()) {cout<<"Illegal input! Try again: "; continue;}
            tpm = all_owners[k-1];
        }
        bool flag = all_owners[i-1]->transfer_a_dog(all_owners[i-1]->get_dog(j-1), tpm);
        if(flag && tpm != NULL) {
            cout<<"Dog transferred to ";
            tpm->print_info();
            cout<<endl;
            cout<<"Now ";
            tpm->view_dogs();
        }
        else if (!flag){
            cout<<"Transfer failed!\n";
        }
        return;
    }
    else if(input[0] == '2')
    {
        if(all_dogs.size() == 0) {cout<<"No dogs exists. Backed to the main menu. \n"; return;}
        view_all_dogs();
        cout<<"Which dog would you like to transfer? (Type 0 to exit)\n";
        int i = -1;
        while(i < 0 || i > all_dogs.size())
        {
            cin.getline(input,30);
            i = atoi(input);
            if (i == 0) { cout<<"Exit! \n"; return; }
            if (i < 0 || i > all_dogs.size()) cout<<"Illegal input! Try again: ";
        }
        if (all_owners.size() == 0) {cout<<"No owners exists. Backed to the main menu. \n"; return;}
        view_all_owners(false);
        cout<<"Which owner would you like to transfer to? \n";
        cout<<"(Type 'N' for [no owner]; Type -1 to exit) \n";
        int j = -2;
        DogOwner* tpm = NULL;
        while(j < -1 || j > all_owners.size() || all_owners[j-1] == all_dogs[i-1]->get_ptr_owner())
        {
            cin.getline(input,30);
            j = atoi(input);
            if (input[0] == 'N') {
                tpm = NULL;
                break;
            }
            if (j == -1) { cout<<"Exit! \n"; return; }
            if (all_owners[j-1] == all_dogs[i-1]->get_ptr_owner()) 
            {
                cout<<"Can not transfer the dog to its original owner. Try again!\n";
                continue;
            }
            if (j < -1 || j > all_owners.size()) cout<<"Illegal input! Try again!\n";
            else {tpm = all_owners[j-1]; break;}
        }
        if (tpm == NULL) { //transfer to no owner / set the dog free
            cout<<"You're going to set ";
            all_dogs[i-1]->print_info();
            cout<<" FREE. \n";
            cout<<"Previous owner: ";
            if (all_dogs[i-1]->get_ptr_owner()) all_dogs[i-1]->get_ptr_owner()->print_info();
            else cout<<"[no owner]";
            cout<<endl;
            if (all_dogs[i-1]->get_ptr_owner()) {
                all_dogs[i-1]->get_ptr_owner()->transfer_a_dog(all_dogs[i-1],tpm);

            }
           
            return;
        }
        else { //transfer to an owner
            cout<<"The dog is goint to be transferred from ";
            if (all_dogs[i-1]->get_ptr_owner()) all_dogs[i-1]->get_ptr_owner()->print_info();
            else cout<<"[no owner]";
            cout<<" to ";
            tpm->print_info();
            cout<<"! \n";
            bool flag = false;
            if (all_dogs[i-1]->get_ptr_owner()) //if the dog has an owner before
            {
                flag = all_dogs[i-1]->get_ptr_owner()->transfer_a_dog(all_dogs[i-1],tpm);
            }
            else {
                flag = tpm->adopt_a_dog(all_dogs[i-1]);
            }
            if (flag) cout<<"Transferred successfully!\n";
            else cout<<"Transfer failed!\n";
            return;
        }
    }
    else {
        cout<<"Illegal input! Try again!\n";
		cout<<"back to the menu!"<<endl;
        return ;
    }
}
void help_prompt()
{
    cout<<"-----------------------------------------\n";
    cout<<" 1. View all dog owners with their dogs; \n";
    cout<<" 2. View all dogs; \n";
    cout<<" 3. Add a dog; \n";
    cout<<" 4. Add a owner;\n";
    cout<<" 5. Transfer a dog; \n";
    cout<<" 6. Adopt a dog; \n";
    cout<<" 7. Edit a dog; \n";
    cout<<" 8. Edit an owner; \n";
    cout<<" 9. Remove a dog; \n";
    cout<<" 0. Help. \n";
    cout<<"-1. Exit. \n";
    cout<<"-----------------------------------------\n";
}
int main()
{
    int choice = 0;
    char input[32];
    while (choice != -1)
    {
        switch (choice)
        {
            case 1: view_all_owners(true); break;
            case 2: view_all_dogs(); break;
            case 3: add_a_dog(); break;
            case 4: add_a_owner(); break;
            case 5: dog_transfer(); break;
            case 6: dog_adoption(); break;
            case 7: edit_dog(); break;
            case 8: edit_owner(); break;
            case 9: dog_removal(); break; 
            case -1: break;
            case 0: default: help_prompt(); break;
        }
        cin.getline(input, 32);
        choice = atoi(input);
    }
	int i;
    for ( i = 0; i < all_dogs.size(); i++){
        delete all_dogs[i];
    }
    for ( i = 0; i < all_owners.size(); i++){
        delete all_owners[i];
    }
    return 0;
}
