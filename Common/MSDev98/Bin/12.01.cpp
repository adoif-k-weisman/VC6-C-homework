#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

//struct ChessMove;

class game
{
protected:
    int move_numbers;//�غ�,��move_number,��Ҫ�����private,������;
    bool is_game_over;
public:
    enum Who {NEUTRAL, PLAYER1, PLAYER2, COMPUTER};
    enum GAME_MODE {DEFAULT, PVP, PVC};
    
    Who firstmover, next_mover;//����,����Ϸ����;
    GAME_MODE gamemode;//ö�ٳ���,ʵ��ģʽѡ��;

    game();
    int is_legal(int a,int b );

    virtual ~game();
    virtual Who play() = 0;
};
game::game()//��ʼ��
{
    move_numbers = 0;
    is_game_over = false;
}
game::~game()//��������,ûʲô�����,������Ϸ��ֱ�����¿�ʼ,�����ǻغ���;
{
}
int game::is_legal(int a,int b )//�ж�����Ϸ���;
{
    //a,b---�ֱ�����������Ŀ�ʼ�ͽ���;
    //�û�������1,Ҫ����;
    int choice = 0;
    char input[32];
    while (choice < a || choice > b)
    {
        cin.getline(input,30);
        choice = atoi(input);
        if (choice < a || choice > b) cout<<"�������! ��������!"<<endl;
    }
    return choice;
}

struct C4_Move//��¼�ƶ�����һ��,��������most_recent_column;
{
    int col;
};

class Connect4 : public game
{
private:
    int rowNum;//�� = 6;
    int colNum;//�� = 7;

    int data[6][7];
    //int **data;
    int many_used[7];
    //int *many_used;
    //C4_Move history_moves[6*7];
    C4_Move* history_moves;//���ڴ洢ÿ�ζ����н��еĲ���;

    void player_move();
    bool c_find_1_to_win(int check);
    //bool find_2_win(int check);
    bool find_2_win(int check);
    void computer_move();
    bool make_move(C4_Move&);

    void display_status();
    void display_info();
    void restart();
    Who win_check(Who last_mover);

public:
    virtual Who play();
    Connect4();
    virtual ~Connect4();
};
Connect4::Connect4() {//��ʼ��;
    memset(data, 0, sizeof(data));
	rowNum = 6;
	colNum = 7;
    memset(many_used, 0, sizeof(many_used));
    firstmover = NEUTRAL;
    gamemode = DEFAULT;
    history_moves = NULL;
}
Connect4::~Connect4()
{
}
void Connect4::restart()
{
	int i;
    for ( i = 0; i< rowNum; i++)
    {
        for (int j = 0;j<colNum; j++)
        {
            data[i][j] = 0;
        }
    }
    for ( i = 0; i<6*7; i++)
    {
        history_moves[i].col = 0;
    }
    for ( i = 0; i<colNum; i++)
    {
        many_used[i] = 0;
    }
}
game::Who Connect4::play()
{
    cout<<"��ӭ������������Ϸ!"<<endl;
    cout<<"ѡ����Ϸģʽ: \n- 1. PvC(�˻���ս) \n- 2. PvP(���˶Կ�). "<<endl;
    int choice = is_legal(1,2);
    if (choice == 1) {
        gamemode = PVC;
        cout<<"��Ϸ ģʽ: Player v.s. Computer"<<endl;
        cout<<"˭������? \n- 1. Player \n- 2. Computer"<<endl;
        choice = is_legal(1,2);
        if (choice == 1) {
            firstmover = PLAYER1;
        }
        else firstmover = COMPUTER;
    }
    else {
        gamemode = PVP;
        cout<<"��Ϸ ģʽ: Player v.s. Player"<<endl;
        cout<<"˭������? \n- 1. Player1 \n- 2. Player2"<<endl;
        choice = is_legal(1,2);
        if(choice == 1){
            firstmover = PLAYER1;
        }
        else firstmover = PLAYER2;
    }

    history_moves = new C4_Move [rowNum * colNum];//��¼ÿһ�ε��ƶ�;

    restart();
    //��Ϸ��ʼ;
    next_mover = firstmover;
    Who winner;
    cout<<"��Ϸ��ʼ!"<<endl;
    while(!is_game_over)
    {
        move_numbers++;
        display_info();
        Who last_mover = next_mover;
        if (next_mover == PLAYER1)
        {
            if (gamemode == PVC) {
                cout<<"Player's turn: "; 
                player_move();
                next_mover = COMPUTER;
            }
            else if (gamemode == PVP) {
                cout<<"Player 1's turn: ";
                player_move();
                next_mover = PLAYER2;
            }
        }
        else if (next_mover == PLAYER2)
        {
            cout<<"Player 2's turn: ";
            player_move();
            next_mover = PLAYER1;
        }
        else if (next_mover == COMPUTER)
        {
            cout<<"Computer's turn: ";
            computer_move();
            next_mover = PLAYER1;
        }
        //ÿ��һ����,��Ҫִ��һ��win_check(),�ж�winner
        winner = win_check(last_mover);

        //���Ƕ�����ж�;
        if (move_numbers == rowNum * colNum) is_game_over = true;
    }
    display_info();

    delete[] history_moves;

    return winner;
}
void Connect4::display_status() //��ӡ����
{
    cout<<endl;

    int SPACE_NUM = 10;
    int current_row = 1;
	int k,j,i,m;
    //@,1 for firstmover
    for ( i = rowNum - 1; i >= 0; i--)//һ��һ�е����,���ϵ���;
    {
        for ( k = 0; k < SPACE_NUM; k++) cout<<' ';//���������ʽ;
        for ( j = 0; j < colNum; j++) {
            if (data[i][j] == 1) cout << '@' << ' ';
            else if (data[i][j] == 2) cout << '$' << ' ';
            else cout << '.' << ' ';
        }
        if(current_row == 1) {
            cout<<"   @: ";
            if (gamemode == PVP)
            {
                if (firstmover == PLAYER1) cout<<"Player 1";
                else if (firstmover == PLAYER2) cout<<"Player 2";
            }
            else if (gamemode == PVC)
            {
                if (firstmover == PLAYER1) cout<<"Player";
                else if (firstmover == COMPUTER) cout<<"Computer";
            }
        }
        if(current_row == 2){
            cout<<"   $: ";
            if (gamemode == PVP)
            {
                if (firstmover == PLAYER1) cout<<"Player 2";
                else if (firstmover == PLAYER2) cout<<"Player 1";
            }
            else if (gamemode == PVC)
            {
                if (firstmover == PLAYER1) cout<<"Computer";
                else if (firstmover == COMPUTER) cout<<"Player";
            }
        }
        current_row++;
        cout<<endl;
    }
    for ( k = 0; k < SPACE_NUM; k++) cout<<' ';
    for ( m = 0; m < colNum - 1; m++) cout<<"--";
    cout<<'-';
    cout<<endl;
    for ( k = 0; k < SPACE_NUM; k++) cout<<' ';
    if (colNum < 10) {
        for ( m = 0; m < colNum; m++) cout<<m+1<<' ';
    }
    cout<<endl;
}
void Connect4::display_info()
{
    display_status();
    cout<<"Round(�غ�): "<< move_numbers<<endl;
    cout<<"����: ";
    //��Ϊ������,�±��0��ʼ,���������Ĭ�ϴ�1��ʼ;
    //������Ҫ+1;
    for (int i = 0; i < move_numbers - 1; i++) cout<<history_moves[i].col + 1<<' ';
    cout<<endl;
}
bool Connect4::make_move(C4_Move& tmove)//�޸�����
{
    if (many_used[tmove.col] >= rowNum) return false;
    else {
        if (next_mover == firstmover) data[many_used[tmove.col]++][tmove.col] = 1;

        else data[many_used[tmove.col]++][tmove.col] = 2;

        history_moves[move_numbers-1] = tmove;

        return true;
    }
}
void Connect4::player_move()//�������;
{
    int choice = is_legal(1,colNum);
    C4_Move usr_move = {choice-1};
    bool flag = make_move(usr_move);
    while(!flag)//��һ�����벻�ɹ�ִ�и�ѭ��;
    {
        cout<<"�����ƶ�! ���³���! ";
        choice = is_legal(1,colNum) -1;
        usr_move.col = choice;//�±��0��ʼ,��Ȼ�û������1��ʼ;
        flag = make_move(usr_move);
    }
}
bool Connect4::c_find_1_to_win(int check)
{
    C4_Move cmove;
    int i,j;
    for( i = 0; i < rowNum - 3; i++)
    {
        for( j = 0; j < colNum - 3; j++)
        {
            //˭����,˭����@
            if (data[i][j] == check && data[i+1][j+1] == check && data[i+2][j+2] == check && data[i+3][j+3] == 0 && data[i+2][j+3] != 0) 
            {                      //       *
                cmove.col = j + 3; //     @ &
                make_move(cmove);  //   @ & &
                return true;       // @ & & &
            }
            if (data[i][j] == check && data[i+1][j+1] == check && data[i+2][j+2] == 0 && data[i+3][j+3] == check && data[i+1][j+2] != 0) 
            {                      //       @
                cmove.col = j + 2; //     * &
                make_move(cmove);  //   @ & &
                return true;       // @ & & &
            }
            if (data[i][j] == check && data[i+1][j+1] == 0 && data[i+2][j+2] == check && data[i+3][j+3] == check && data[i][j+1] != 0) 
            {                      //       @
                cmove.col = j + 1; //     @ &
                make_move(cmove);  //   * & &
                return true;       // @ & & &
            }
            if (data[i][j] == 0  && data[i+1][j+1] == check && data[i+2][j+2] == check && data[i+3][j+3] == check && (i==0 ||( i>=1 && data[i-1][j] != 0))) 
            {                      //       @
                cmove.col = j + 3; //     @ &
                make_move(cmove);  //   @ & &
                return true;       // *  & & &
            }
            if (data[i+3][j] == 0 && data[i+2][j+1] == check && data[i+1][j+2] == check && data[i][j+3] == check && data[i+2][j] != 0) 
            {                      // *
                cmove.col = j;     // & @
                make_move(cmove);  // & & @ 
                return true;       // & & & @
            }
            if (data[i+3][j] == check && data[i+2][j+1] == 0 && data[i+1][j+2] == check && data[i][j+3] == check && data[i+1][j+1] != 0) 
            {                      // @
                cmove.col = j+1;   // & *
                make_move(cmove);  // & & @ 
                return true;       // & & & @
            }
            if (data[i+3][j] == check && data[i+2][j+1] == check && data[i+1][j+2] == 0 && data[i][j+3] == check && data[i][j+2] != 0) 
            {                      // @
                cmove.col = j+2;   // & @
                make_move(cmove);  // & & * 
                return true;       // & & & @
            }
            if (data[i+3][j] == check && data[i+2][j+1] == check && data[i+1][j+2] == check && data[i][j+3] == 0 && (i==0 || (i>=1 && data[i-1][j+3] != 0))) 
            {                      // @
                cmove.col = j;     // & @
                make_move(cmove);  // & & @ 
                return true;       // & & & *
            }
        }
    }
    for ( i = 0; i< rowNum ;i++) {
        for ( j =0; j < colNum -3;j++) {
            if(data[i][j] == 0 && data[i][j+1] == check && data[i] [j+2] == check && data[i][j+3] == check && (i == 0 || (i>0 && data[i-1][j] != 0))) {
                // * @ @ @
                cmove.col = j;
                make_move(cmove);
                return true;
            }
            if(data[i][j] == check && data[i][j+1] == 0 && data[i][j+2] == check && data[i][j+3] == check && (i == 0 || (i>0 && data[i-1][j+1] != 0))) {
                // @ * @ @
                cmove.col = j+1;
                make_move(cmove);
                return true;
            }
            if(data[i][j] == check && data[i][j+1] == check && data[i][j+2] == 0 && data[i][j+3] == check && (i == 0 || (i>0 && data[i-1][j+2] != 0))) {
                // @ @ * @
                cmove.col = j+2;
                make_move(cmove);
                return true;
            }
            if(data[i][j] == check && data[i][j+1] == check && data[i] [j+2] == check && data[i][j+3] == 0 && (i == 0 || (i>0 && data[i-1][j+3] != 0))) {
                // @ @ @ *
                cmove.col = j+3;
                make_move(cmove);
                return true;
            }
        }
    }
    for ( i = 0; i < rowNum - 3; i++)
    {
        for ( j = 0 ; j < colNum ; j++)
        {
            if (data[i][j]==check && data[i+1][j]==check  && data[i+2][j] == check && data[i+3][j] == 0){
                cmove.col = j;
                make_move(cmove);
                return true;
            }
        }
    }
    return false;
}
//==============================================================
bool Connect4::find_2_win(int check)
{
    C4_Move cmove;
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < colNum; j++)
        {
            if (data[i][j]==check)
            {
                int ti = i, tj = j;

                int cnt = 0;

				//check diagnally 1
				//y=x �������;

                while (ti >= 0 && tj >= 0 && data[ti][tj] == check) {ti--;tj--;cnt++;}
                int bl_i = ti, bl_j = tj; 
                ti = i+1; tj = j+1;
				//����
                while (ti < rowNum && tj < colNum && data[ti][tj] == check) {ti++; tj++; cnt++; }
                int tr_i = ti, tr_j = tj;
                //����
                if (cnt == 2)
                {	
					//���½�
                    if(bl_i-1 >= 0 && bl_j-1 >= 0//������,ûԽ�� 
						&& data[bl_i][bl_j] == 0
						&& tr_i <rowNum && tr_j < colNum 
						&&data[tr_i][tr_j] == 0//y=x���Ҷ��п�
						&&data[bl_i-1][bl_j-1] == 0//��������ж�����
						&& data[bl_i-1][bl_j] != 0//�������� 
					)// 
					{
                     cmove.col = bl_j;
                     make_move(cmove);
                     return true;
                    }
					//���Ͻ�
                    if(tr_i+1 < rowNum && tr_j+1 < colNum 
						&& data[tr_i][tr_j] == 0
						&& bl_i >= 0 && bl_j >=0
						&& data[bl_i][bl_j] == 0
						&& data[tr_i+1][tr_j+1] == 0 //�����ұ��ж�����
						&& data[tr_i-1][tr_j] != 0 ) {cmove.col = tr_j; make_move(cmove); return true;}
                }
                //check diagnally 2
				//y = -x ������
                cnt = 0;
                ti = i; tj = j;
                while(data[ti][tj] == check && ti >= 0 && tj < colNum) {ti--;tj++;cnt++;}
                int br_i = ti, br_j = tj; 
				//����
                ti = i+1; tj = j-1;
                while(data[ti][tj] == check && ti < rowNum && tj >= 0 ) {ti++; tj--; cnt++; }
                int tl_i = ti, tl_j = tj;
				//����
                if (cnt == 2) {
                    if (br_i-1 >= 0 && br_j+1 < colNum 
						&& data[br_i][br_j] == 0
						&& data[tl_i][tl_j] == 0
						&& tl_i < rowNum && tl_j >= 0
						&& data[br_i-1][br_j+1] == 0//�����ж�����
						&& data[br_i-1][br_j] != 0 ) 
                    {
                        cmove.col = br_j; make_move(cmove);
                        return true;
                    }
                    if (tl_i+1 < rowNum && tl_j-1 >= 0
						&& data[tl_i][tl_j] == 0
						&& br_i >= 0 && br_j < rowNum
						&& data[br_i][br_j] == 0
						&& data[tl_i+1][tl_j-1] == 0//�����ж�����
						&& data[tl_i-1][tl_j] != 0 ) 
                    {cmove.col = tl_j; make_move(cmove); return  true;}
                }
                //check horizontally
				//ˮƽ����;
                cnt = 0;
                tj = j;
				//�ӵ�ǰ�㵽��
                while(data[i][tj] == check && tj < colNum){tj++; cnt++; }
                int ttj = tj;
                tj = j-1;
				//�ӵ�ǰ�㵽��
                while(data[i][tj] == check && tj >= 0) {tj--; cnt++;}
				//û����,ttj �� tj ���Ǳ�ʾ����Ϊ�յĵ�һ��
				//tj---����ߵ�����
				//ttj --- ���ұߵ�����
                if(cnt == 2)
                {
                    if(ttj + 1 < colNum && data[i][ttj] == 0 &&
					(i == 0 ||( i >= 1 && data[i-1][ttj] != 0) )
					&& tj>=0
					&&data[i][tj] ==0
					&& data[i][ttj+1] == 0//�ұ��ж�����
					) 
					{
					cmove.col = ttj;
					make_move(cmove); 
					return true;
					}
                    if(tj - 1 >= 0 && data[i][tj] == 0 
						&& (i == 0 || (i >= 1 && data[i-1][ttj] != 0))
						&& ttj < colNum
						&&data[i][ttj] == 0 //����ж�����
						&& data[i][tj-1] == 0) 
					{ 
						cmove.col = tj;
						make_move(cmove);
						return true;
					}
                }
                //check vertically
                //���·���
				cnt = 0;
                ti = i; tj= j;
                while(ti >= 0 && data[ti][j]==check) {ti--; cnt++;}//���±���;
                ti = i+1;
                while(ti < rowNum && data[ti][j] == check) {ti++; cnt++;}
                //��������ϲ���Ҫ����2����������һ������,��Ϊע���ᱻ��,�������ȼ�Ӧ�ÿ���һ�������ֻ�����Ķ��ֵ���;
				if(cnt == 2)
				{
					cmove.col = j;//j --- ��
					make_move(cmove);
					return true;
				}
			
			//ʵ�鲿��;
            }
        }
    }
	return false;
}
//========================================

void Connect4::computer_move()
{
    C4_Move cmove;

    int check, oppo_check;
    if (firstmover == COMPUTER) {check = 1; oppo_check = 2;}
    else {check = 2; oppo_check = 1; }
    //��δ�������������:
    //����ҵ��ҵ�������һ�����Ӯ�ĵط�,��ֱ����������;
    //����ҵ�������һ�����Ӯ�ĵط�,��ֱ�Ӷ�������;
    //finding 1-to-win place 
    if(c_find_1_to_win(check)) {cout<<history_moves[move_numbers-1].col<<endl; return;}
    //if opponent's 1-to-win
    //�ҵ����ֵ�ֻ��һ��Ϳ���Ӯ�ĵط��ط�
    if(c_find_1_to_win(oppo_check)) {cout<<history_moves[move_numbers-1].col<<endl; return;}
    
    //���Դ������������:δ���,�������������պ�һ��;
    //�����뷨�Ǳ����µ�ÿ�е����,ѡ�����ż���;
    //����������õķ���;��д����������ĺ���˼��;
    if(find_2_win(check)) {cout<<history_moves[move_numbers-1].col+1<<endl; return;}

    if(find_2_win(oppo_check)) {cout<<history_moves[move_numbers-1].col+1<<endl; return;}
//��һ�����ִ���������õ��Դ����ҿ�ʼ��,����;
    for (int i = 0; i< colNum ;i++)
    {
        if(many_used[i] > 0 && many_used[i]<rowNum//�����������; 
        && data[many_used[i]][i] == check //�������������������Լ���ͬ��; һ��������
         || many_used[i] == 0  
         ){
            cmove.col = i;
            make_move(cmove);
            cout<<cmove.col+1<<endl;
            return;
        }
    }
    //�����ֱ������;
    int choice = rand() % colNum;
    cmove.col = choice;
    bool flag = make_move(cmove);
    while(!flag)
    {
        //cout<<"Illegal move! Try again. ";
        choice = rand() % colNum;
        cmove.col = choice;
        flag = make_move(cmove);
    }
    cout<<cmove.col+1<<endl;

    return;
}
game::Who Connect4::win_check(Who last_mover)
{
    //����last_mover����ȷ����һ����������Ƿ��Ӯ���ⳡ��Ϸ

    int last_move_col = history_moves[move_numbers-1].col;
    //�൱��most_recent_cloumn,����ϴ����������
    
    int last_move_row = many_used[last_move_col] - 1;
    //��many_used[most_recent_column]�����������;
    
    int check = data[last_move_row][last_move_col];
    //���������λ��;
    
    int t, cnt = 0;
    //check horizontally,ˮƽ���;
    t = last_move_col;
    cnt = 0;
    //��check ȥ������human,����computer,��ʡ����;
    while (t >= 0 && data[last_move_row][t] == check) {cnt++; t--; }
    //���ӵ�ǰλ�õ������
    t = last_move_col + 1;
    while (t < colNum && data[last_move_row][t] == check) {cnt++; t++; }
    //���ӵ�ǰλ�õ������
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    //�ж�

    //check vertically ,��ֱ���
    t = last_move_row;
    cnt = 0;
    while (t >= 0 && data[t][last_move_col] == check) {cnt++; t--; }
    t = last_move_row + 1;
    while (t < rowNum && data[t][last_move_col] == check) {cnt++; t++; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    
    //check diagnolly 1
    //�����µ�����,y=x����б��;
    int ti = last_move_row;
    int tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj >=0 && data[ti][tj] == check) {cnt++; ti--; tj--;}
    ti = last_move_row + 1;
    tj = last_move_col + 1;
    while (ti < rowNum && tj < colNum && data[ti][tj] == check) {cnt++; ti++; tj++; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}

    //check diagnolly 2
    //�����ϵ�����,�� y=-x ����б��
    ti = last_move_row;
    tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj < colNum && data[ti][tj] == check) { cnt++; ti--; tj++;}
    ti = last_move_row + 1;
    tj = last_move_col - 1;
    while (ti < rowNum && tj >= 0 && data[ti][tj] == check) { cnt++; ti++; tj--; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    return NEUTRAL;
}
int main()
{
    srand((unsigned int)(time(NULL)));
    Connect4 instance;
    game::Who winner = instance.play();
    //���ʤ���Ľ��;
    if (instance.gamemode == game::PVC)
    {
        if (winner == game::PLAYER1) cout<<"Player wins!"<<endl;
        else if (winner == game::COMPUTER) cout<<"Computer wins!"<<endl;
        else if (winner == game::NEUTRAL) cout<<"Draw!"<<endl;
    }
    else if (instance.gamemode == game::PVP){
        if (winner == game::PLAYER1) cout<<"Player 1 wins!"<<endl;
        else if (winner == game::PLAYER2) cout<<"Player 2 wins!"<<endl;
        else if (winner == game::NEUTRAL) cout<<"Draw!"<<endl;
    }
    return 0;
}
 